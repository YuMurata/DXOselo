#include"stdafx.h"

#include"OseloObject.h"
#include"UserAgent.h"
#include"RandomAgent.h"

typedef TCoordinate<int> ScreenSize;

using namespace std;

CellCoord OseloObject::Mouse2Cell(const MouseCoord &coord)
{
	auto cell = (coord - this->rate*this->board_offset) / (this->board_cell_size*(Rate)this->rate);

	return cell;
}


OseloObject::OseloObject(const CellNum &cell_num, const int &current_turn)
	:cells(new CellMGR(cell_num, current_turn))
{
	unique_ptr<UserAgent> black(new UserAgent(this->cells));
	unique_ptr<RandomAgent> white(new RandomAgent(this->cells));

	this->agents.resize(BoardClass::Cell_NUM);

	this->agents[BoardClass::Cell_BLACK] = move(black);
	this->agents[BoardClass::Cell_WHITE] = move(white);
}

OseloObject::~OseloObject() {}

	void OseloObject::Put(const int &color)
	{
		this->cells->PutPieceAt(ObjCoord(0, 0), color);
	}

	void OseloObject::Init()
	{
		const string pass = "figure\\";
		ObjCoord coord(0, 0);

		this->board.Init(coord, pass + "board.png");

		ScreenSize ss;
		int dummy;

		GetScreenState(&ss.x, &ss.y, &dummy);

		SetRate(((Rate)ss / (Rate)this->board.GetGraphSize()));

		this->board.SetRate(this->rate);
		this->cells->SetRate(this->rate);

		for (auto &i : this->agents)
		{
			i->SetRate(this->rate);
		}

		this->cells->Init();
	}

	void OseloObject::Draw()
	{
		this->board.Draw();
		this->cells->Draw();
	}

	void OseloObject::UpDate(const Input &input)
	{
		auto color = this->cells->GetOselo().GetCurrent();
		if (this->agents[color]->Put(input) != BoardClass::Cell_Empty)
		{
			this->cells->Init();
		}
	}