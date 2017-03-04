#pragma once

#include<OseloClass.h>
#include<OseloSystem.h>
#include<DxFunc.h>

using namespace std;

class PieceMGR:public ImageMGR
{
private:
	vector<vector<BaseImage>> cells;
	int handle[BoardClass::Cell_NUM];
	ImagRate rate;
	BoardSize board_size;
	BaseImage fake;
	OseloClass oselo;

public:
	PieceMGR(const BoardSize &board_size)
		:oselo(board_size),board_size(board_size)
	{
		this->handle[BoardClass::Cell_BLACK] = LoadGraph("Image/black_a.png");
		this->handle[BoardClass::Cell_WHITE] = LoadGraph("Image/white_a.png");

		TCoordinate<int> coord;
		int dum;
		GetScreenState(&coord.x, &coord.y, &dum);

		ImagSize size;

		GetGraphSizeF(this->handle[BoardClass::Cell_BLACK], &size.x, &size.y);

		this->rate=TCoordinate<double>(1.)*coord/board_size/size;
	}

	void Init()
	{
		this->images = vector<BaseImage>(this->board_size.x*this->board_size.y);
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
		auto state=this->oselo.Put(coord);
		
		if (state.IsPut())
		{
			this->PutPiecesAt(state);
			this->oselo.ChangeTurn();
			if (!this->oselo.CheckPutable())
			{
				this->oselo.ChangeTurn();
			}
		}
	}

	int GetWin()const
	{
		return this->oselo.GetWin();
}

	void TempPut(const CellCoord &coord)
	{
		auto board = this->oselo.GetBoard();
		auto color = this->oselo.GetCurrent();
		OseloSystem::Flip dum;

		if (OseloSystem::CheckPut(board, coord, color, &dum))
		{
			auto imag_coord = this->CellToImag(coord);
			this->fake.Init(imag_coord, this->handle[color], this->rate);
		}
		else
		{
			this->fake.Init(coord, -1, this->rate);
		}

	}

	void PutPiecesAt(const PutState &state)
	{
		auto color = state.color;
		this->PutPieceAt(state.put, color);

		for (auto &i : state.flip)
		{
			this->PutPieceAt(i, color);
		}
	}

	void PutPieceAt(const CellCoord &coord, const int &color)
	{
		auto index = coord.y*this->board_size.x + coord.x;
		auto &cell = this->images[index];
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
		this->ImageMGR::Draw();
		this->fake.Draw();
	}

	bool CheckFinish()const
	{
		return this->oselo.CheckFinish();
	}

	ImagSize GetSize()const
	{
		auto handle = this->handle[BoardClass::Cell_BLACK];
		ImagSize size;
		GetGraphSizeF(handle, &size.x, &size.y);

		return size*this->rate;
	}

	int GetCurrent()const
	{
		return this->oselo.GetCurrent();
	}

	BoardClass GetBoard()const
	{
		return this->oselo.GetBoard();
	}
};