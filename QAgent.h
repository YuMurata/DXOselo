#pragma once

#include"BaseAgent.h"
#include<Hash.h>
#include"../../MachineLearning/ReinforcementLearning/QLearning/QLearning/QLClass.h"
#include<StringPlus.h>
#include<sstream>

class QAgent :public BaseAgent
{
private:
	QLClass<BoardClass, CellCoord> ql_obj;

public:
	QAgent(const shared_ptr<PieceMGR> &pieces,const int &color)
		:BaseAgent(pieces,color) ,ql_obj(0.4,0.7,0.)
	{
		using S = BoardClass;
		using A = CellCoord;
		using QL = QLClass<S, A>;
		using SA = QL::SA;
		using Q = QL::Q;
		using SAQ = QL::SAQ;

		using QTable = QL::QTable;

		using R = QL::FuncR;
		using T = QL::FuncT;
		using As = QL::FuncAs;
		using Load = QL::FuncLoad;
		using Write = QL::FuncWrite;


		auto func_r = [&](const S &s)
		{
			int ampl = 1;
			int reward = s.GetCellNum(this->my_color);

			return reward*ampl;
		};

		T func_t = [&](const S &s, const A &a)
		{
			auto ret = OseloSystem::GetEstimate(s, a, this->my_color);
			return ret;
		};

		As func_as = [&](const S &s)
		{
			auto ret = OseloSystem::GetPutable(s, this->my_color);
			return ret;
		};

		Load func_load = [&](const vector<vector<wstring>> &data_list)
		{
			vector<SAQ> ret(size(data_list));
			auto board_size = this->pieces->GetBoard().GetBoardSize();
			vector<int> gyh(1, 3);
			auto s_size = board_size.x*board_size.y;
			auto a_size = 2;

			auto func = [&board_size, a_size](const vector<wstring> &input)
			{
				SAQ ret;
				auto &s = ret.first.first;
				auto &a = ret.first.second;
				auto &q = ret.second;

				auto itr = begin(input);

				vector<vector<int>> board(board_size.y);

				auto ret_board = [](const vector<wstring> &str)
				{
					vector<int> ret(size(str));
					auto func=[](const wstring &str) 
					{
						size_t temp = 0;
						return stoi(str,&temp);
					};
					transform(begin(str), end(str), begin(ret),func);
					return ret;
				};

				for (int y = 0; y < board_size.y; ++y)
				{
					auto last = itr + board_size.x;
					board[y] = ret_board(vector<wstring>(itr, last));

					itr = last;
				}

				s = board;
				size_t temp1=0, temp2=0;

				auto x = stoi(*itr, &temp1);
				auto y = stoi(*(itr + 1), &temp2);

				a = CellCoord(x,y);

				itr += a_size;
				size_t temp3 = 0;
				q = stod(*itr,&temp3);

				return ret;
			};

			transform(begin(data_list), end(data_list), begin(ret), func);

			return ret;
		};

		Write func_write = [](const QTable &q_table, vector<vector<wstring>> *ret)
		{
			string s;
			string a;
			string q;

			ret->resize(size(q_table));

			auto func = [](const pair<SA, double> &saq)
			{
				wstringstream is;
				is << saq.first.first << saq.first.second << saq.second;

				auto input = is.str();
				vector<wstring> ret = SplitW(input);

				return ret;
			};

			transform(begin(q_table), end(q_table), begin(*ret), func);

			//return ret;
		};

		this->ql_obj.SetFunc(func_r, func_t, func_as, func_load, func_write);
	}

	void Put(const Input &input)
	{
		auto board = this->pieces->GetBoard();
		auto coord=this->ql_obj.Learn(board);

		this->pieces->Put(coord);
	}

	void Load(const int &color)
	{
		wstring file_name;
		if (color == BoardClass::Cell_BLACK)
		{
			file_name = L"black.ql";
		}
		else
		{
			file_name = L"white.ql";
		}
		this->ql_obj.LoadFile(file_name);
	}

	void Write(const int &color)
	{
		wstring file_name;
		if (color == BoardClass::Cell_BLACK)
		{
			file_name = L"black.ql";
		}
		else
		{
			file_name = L"white.ql";
		}
		this->ql_obj.WriteFile(file_name);
	}
};