#pragma once

#include"stdafx.h"

#include"RateClass.h"
#include"CellClass.h"

#include<Coordinate.h>
#include<vector>
#include<memory>

#include<OseloClass.h>

typedef TCoordinate<int> CellNum;

class CellMGR:public RateClass
{
private:
	std::vector<std::vector<std::unique_ptr<CellClass>>> cells;
	std::unique_ptr<CellClass> fake;
	int handle[BoardClass::Cell_NUM];
	int init_turn;

	CellNum cell_num;
	OseloClass oselo_obj;

public:
	CellMGR(const CellNum &cell_num, const int &current_turn);

	~CellMGR();

	void Init();

	void Draw();

	void PutPiecesAt(const PutState &state);

	void PutPieceAt(const CellCoord &coord, const int &color);

	void PutFake(const CellCoord &coord);

	int PutReal(const CellCoord &coord);

	void UpDate();

	OseloClass GetOselo()const
	{
		return this->oselo_obj;
	}
};