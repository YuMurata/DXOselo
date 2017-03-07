#pragma once
#include<DxFunc.h>
#include"PieceMGR.h"
#include"CellMGR.h"
#include"UserAgent.h"
#include"RandomAgent.h"
#include"QAgent.h"
#include"AgentInfo.h"

class OseloObject:public ObjectIF,public SceneChanger,public AgentInfo
{
private:
	CellMGR cells;
	shared_ptr<PieceMGR> pieces;
	ImagRate rate;
	unique_ptr<BaseAgent> agents[BoardClass::Cell_NUM];

public:
	OseloObject(const BoardSize &board_size=8)
		:cells(board_size),pieces(new PieceMGR(board_size))
	{
		
	}
	
	~OseloObject() {}

	void Put(const int &color) {}

	virtual void Init()
	{
		auto black = BoardClass::Cell_BLACK;
		auto white = BoardClass::Cell_WHITE;

		if (this->user_color == BoardClass::Cell_BLACK)
		{
			this->agents[black].reset(new UserAgent(this->pieces, black));
			this->agents[white].reset(new QAgent(this->pieces, white));
		}
		else
		{
			this->agents[black].reset(new QAgent(this->pieces, black));
			this->agents[white].reset(new UserAgent(this->pieces, white));
		}

		auto q_agent = dynamic_cast<QAgent*>(this->agents[BoardClass::Cell_WHITE].get());
		if (q_agent != nullptr)
		{
			q_agent->Load();
		}

		this->cells.Init();
		this->pieces->Init();
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

};