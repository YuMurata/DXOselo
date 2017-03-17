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
		this->agents[this->user_color].reset(new UserAgent(this->pieces, this->user_color));
		this->agents[this->q_color].reset(new QAgent(this->pieces, this->q_color));

			auto q_agent = dynamic_cast<QAgent*>(this->agents[this->q_color].get());
			if (q_agent != nullptr)
			{
				q_agent->Load(this->q_color);
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
			auto q_agent = dynamic_cast<QAgent*>(this->agents[this->q_color].get());
			if (q_agent != nullptr)
			{
				q_agent->Write(this->q_color);
			}
		}
	}

};