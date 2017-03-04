#pragma once
#include<DxFunc.h>
#include"PieceMGR.h"
#include"CellMGR.h"
#include"UserAgent.h"

class OseloObject:public ObjectIF
{
private:
	CellMGR cells;
	shared_ptr<PieceMGR> pieces;
	ImagRate rate;
	unique_ptr<UserAgent> agents[BoardClass::Cell_NUM];

public:
	OseloObject(const BoardSize &board_size)
		:cells(board_size),pieces(new PieceMGR(board_size))
	{
		agents[BoardClass::Cell_BLACK].reset(new UserAgent(this->pieces));
		agents[BoardClass::Cell_WHITE].reset(new UserAgent(this->pieces));
	}
	
	~OseloObject() {}

	void Put(const int &color) {}

	virtual void Init()
	{
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
		}
	}

	CellCoord MouseToCell(MouseCoord x) { return 0; }
};