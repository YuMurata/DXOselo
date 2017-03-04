#pragma once
#include<DxFunc.h>
#include"PieceMGR.h"
#include"CellMGR.h"

class OseloObject:public ObjectIF
{
private:
	CellMGR cells;
	PieceMGR pieces;
	ImagRate rate;

public:
	OseloObject(const BoardSize &board_size)
		:cells(board_size),pieces(board_size)
	{
	}
	
	~OseloObject() {}

	void Put(const int &color) {}

	virtual void Init()
	{
		this->cells.Init();
		this->pieces.Init();
	}

	virtual void Draw()const
	{
		this->cells.Draw();
		this->pieces.Draw();
	}

	virtual void UpDate(const Input &input) 
	{
		auto mouse_coord = input.GetMouseCoord();
		auto cell_coord = this->MouseToCell(mouse_coord);
		this->pieces.TempPut(cell_coord);
		
		if (input.GetMouseInPut(MOUSE_INPUT_LEFT))
		{
			this->pieces.Put(cell_coord);
		}
	}

	CellCoord MouseToCell(const MouseCoord &coord)
	{
		auto size = this->cells.GetSize();
		return (CellCoord)coord / size;
	}
};