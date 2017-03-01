#pragma once

#include<memory>
#include"CellMGR.h"
#include<DxFunc.h>
#include"BoardInfo.h"
#include"BaseAgent.h"

using namespace std;

class UserAgent:public BoardInfo,public BaseAgent
{
private:
	CellCoord Mouse2Cell(const MouseCoord &coord)
	{
		auto cell = (coord - this->rate*this->board_offset) / (this->board_cell_size*(Rate)this->rate);
		return cell;
	}

public:
	UserAgent(const shared_ptr<CellMGR> &cells)
		:BaseAgent(cells){}

	int Put(const Input &input)
	{
		auto coord = Mouse2Cell(input.GetMouseCoord());
		int win = BoardClass::Cell_Empty;
		if (input.GetMouseInPut(MOUSE_INPUT_LEFT))
		{
			 win = this->cells->PutReal(coord);
		}
		else
		{
			this->cells->PutFake(coord);
		}
		this->cells->UpDate();

		return win;
	}
};