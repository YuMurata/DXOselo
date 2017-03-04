#pragma once
#include"PieceMGR.h"
#include"BaseAgent.h"

using namespace std;

class UserAgent:public BaseAgent
{
private:
	CellCoord MouseToCell(const MouseCoord &coord)
	{
		auto size = this->pieces->GetSize();
		return (CellCoord)coord / size;
	}

public:
	UserAgent(const shared_ptr<PieceMGR> &pieces)
		:BaseAgent(pieces)
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