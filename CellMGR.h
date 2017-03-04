#pragma once

#include"../Console/COselo/OseloClass.h"
#include<DxFunc.h>

using namespace std;

class CellMGR:public ObjectIF
{
private:
	vector<vector<BaseImage>> cells;
	int handle[BoardClass::Cell_NUM];
	ImagRate rate;

	OseloClass oselo;

public:
	CellMGR(const BoardSize &board_size)
		:oselo(board_size)
	{
		this->handle[BoardClass::Cell_BLACK] = LoadGraph("Image/black.png");
		this->handle[BoardClass::Cell_WHITE] = LoadGraph("Image/white.png");

		TCoordinate<int> coord;
		int dum;
		GetScreenState(&coord.x, &coord.y, &dum);

		ImagSize size;

		GetGraphSizeF(this->handle[BoardClass::Cell_BLACK], &size.x, &size.y);

		this->rate=TCoordinate<double>(1.)*coord/board_size/size;
	}

	void Init()
	{
		auto board_size=oselo.GetBoard().GetBoardSize();
		this->cells = vector<vector<BaseImage>>(board_size.y, vector<BaseImage>(board_size.x));

		auto init=this->oselo.Init();

		vector<PutState> inits({ init.first,init.second });

		for (auto &j : inits)
		{
			for (auto &i : j.flip)
			{
				this->PutPieceAt(i, j.color);
			}
		}
	}

	void Put(const CellCoord &coord)
	{
		oselo.Put(coord);
		this->PutPieceAt(coord, oselo.GetCurrent());
	}

	void PutPieceAt(const CellCoord &coord, const int &color)
	{
		auto &cell = this->cells[coord.y][coord.x];
		auto imag_coord = this->CellToImag(coord);
		cell.Init(imag_coord, this->handle[color],this->rate);
	}

	ImagCoord CellToImag(const CellCoord &coord)
	{
		ImagSize ret;
		GetGraphSizeF(this->handle[BoardClass::Cell_BLACK], &ret.x, &ret.y);
		
		return ret * coord*this->rate;
	}

	void Draw()const
	{
		auto func1 = [](const BaseImage &imag)
		{
			imag.Draw();
		};
		
		auto func2 = [&func1](const vector<BaseImage> &images)
		{
			for_each(begin(images), end(images), func1);
		};

		for_each(begin(this->cells), end(this->cells), func2);
	}

	void UpDate(const Input &input) {}
};