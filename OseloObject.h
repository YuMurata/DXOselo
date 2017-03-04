#pragma once
#include<DxFunc.h>
#include"PieceMGR.h"
#include"CellMGR.h"
#include"UserAgent.h"
#include"RandomAgent.h"
#include"QAgent.h"

class OseloObject:public ObjectIF
{
private:
	CellMGR cells;
	shared_ptr<PieceMGR> pieces;
	ImagRate rate;
	unique_ptr<BaseAgent> agents[BoardClass::Cell_NUM];

public:
	OseloObject(const BoardSize &board_size)
		:cells(board_size),pieces(new PieceMGR(board_size))
	{
		auto black = BoardClass::Cell_BLACK;
		auto white = BoardClass::Cell_WHITE;

		this->agents[black].reset(new UserAgent(this->pieces,black));
		this->agents[white].reset(new QAgent(this->pieces,white));
	}
	
	~OseloObject() {}

	void Put(const int &color) {}

	virtual void Init()
	{
		this->cells.Init();
		this->pieces->Init();
		
		auto q_agent = dynamic_cast<QAgent*>(this->agents[BoardClass::Cell_WHITE].get());
		if (q_agent != nullptr)
		{
			q_agent->Load();
		}
	}

	virtual void Draw()const
	{
		this->cells.Draw();
		this->pieces->Draw();
	}

	virtual void UpDate(const Input &input)
	{
		auto color = this->pieces->GetCurrent();
		this->agents[color]->Put(input);

		if (this->pieces->CheckFinish())
		{
			this->pieces->Init();
			auto q_agent = dynamic_cast<QAgent*>(this->agents[BoardClass::Cell_WHITE].get());
			if (q_agent != nullptr)
			{
				q_agent->Write();
			}
		}
	}

	CellCoord MouseToCell(MouseCoord x) { return 0; }
};