#pragma once
#include"PieceMGR.h"
using namespace std;

class UserAgent
{
private:
	CellCoord MouseToCell(const MouseCoord &coord)
	{
		auto size = this->pieces->GetSize();
		return (CellCoord)coord / size;
	}

	shared_ptr<PieceMGR> pieces;

public:
	UserAgent(const shared_ptr<PieceMGR> &pieces)
		:pieces(pieces)
	{}

	void Put(const Input &input)
	{
		auto coord = MouseToCell(input.GetMouseCoord());

		if (input.GetMouseInPut(MOUSE_INPUT_LEFT))
		{
			this->pieces->Put(coord);
		}
		else
		{
			this->pieces->TempPut(coord);
		}
	}
};