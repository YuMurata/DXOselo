#include"stdafx.h"

#include"CellMGR.h"
#include"../../Console/Oselo/OseloSystem.h"

void CellMGR::PutPiecesAt(const PutState &state)
{
	auto color = state.color;
	this->PutPieceAt(state.put, color);
	for (auto &i : state.flip)
	{
		this->PutPieceAt(i, color);
	}
}

void CellMGR::PutPieceAt(const CellCoord &coord, const int &color)
{
	auto &cell = this->cells[coord.y][coord.x];
	cell->Init(coord, this->handle[color], this->rate);
}

void CellMGR::PutFake(const CellCoord &coord)
{
	auto color = this->oselo_obj.GetCurrent();
	auto cell_handle = -1;
	OseloSystem::Flip dummy;

	if (OseloSystem::CheckInside(oselo_obj.GetBoard(),coord) && OseloSystem::CheckPut(this->oselo_obj.GetBoard(),coord, color, &dummy))
	{
		cell_handle = this->handle[color];
	}

	this->fake->Init(coord, cell_handle, this->rate);
}

int CellMGR::PutReal(const CellCoord &coord)
{
	auto color = this->oselo_obj.GetCurrent();
	auto put_state = this->oselo_obj.Put(coord);

	if (put_state.IsPut())
	{
		this->PutPiecesAt(put_state);

		this->oselo_obj.ChangeTurn();
		if (!this->oselo_obj.CheckPutable())
		{
			this->oselo_obj.ChangeTurn();
		}

		if (this->oselo_obj.CheckFinish())
		{
			return this->oselo_obj.GetWin();
		}
	}

	return BoardClass::Cell_Empty;
}
