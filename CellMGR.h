#pragma once

#include<DxFunc.h>

using namespace std;

class CellMGR:public ImageMGR
{
private:
	vector<vector<BaseImage>> cells;
	int handle;
	BoardSize board_size;
	ImagRate rate;

public:
	CellMGR(const BoardSize &board_size)
		:board_size(board_size)
	{
		this->handle = LoadGraph("Image/cell.bmp");

		TCoordinate<int> coord;
		int dum;
		GetScreenState(&coord.x, &coord.y, &dum);

		ImagSize size;

		GetGraphSizeF(this->handle, &size.x, &size.y);

		this->rate = TCoordinate<double>(1.)*coord / board_size / size;
	}

	void Init()
	{
		this->images = vector<BaseImage>(this->board_size.x*this->board_size.y);

		CellCoord coord;
		for (coord.y = 0; coord.y < board_size.y; ++coord.y)
		{
			for (coord.x = 0; coord.x < board_size.x; ++coord.x)
			{
				this->PutPieceAt(coord);
			}
		}
	}

	void PutPieceAt(const CellCoord &coord)
	{
		auto &cell = this->images[coord.y*board_size.x+coord.x];
		auto imag_coord = this->CellToImag(coord);
		cell.Init(imag_coord, this->handle, this->rate);
	}

	ImagCoord CellToImag(const CellCoord &coord)
	{
		ImagSize ret;
		GetGraphSizeF(this->handle, &ret.x, &ret.y);

		return ret * coord*this->rate;
	}

	ImagSize GetSize()
	{
		return this->images.front().GetAppSize();
	}

	void UpDate(const Input &input) {}
};