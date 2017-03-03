#pragma once

#include"../Console/COselo/OseloClass.h"
#include"CellClass.h"

using namespace std;

class CellMGR
{
private:
	vector<vector<BaseImage>> cells;
	int handle[BoardClass::Cell_NUM];

	OseloClass oselo;

public:
	CellMGR(const BoardSize &board_size)
		:oselo(board_size)
	{
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
				this->PutPieceAt(i, init.first.color);
			}
		}
	}

	void PutPieceAt(const CellCoord &coord, const int &color)
	{
		oselo.Put(coord);

		auto imag_coord = this->CellToImag(coord);
		this->cells[coord.y][coord.x].Init(imag_coord, this->handle[color]);
	}

	ImagCoord CellToImag(const CellCoord &coord)
	{
		return (CellCoord)100 * coord;
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
};