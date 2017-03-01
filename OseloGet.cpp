#include"stdafx.h"

#include"OseloClass.h"
#include"OseloSystem.h"

int OseloClass::GetCurrent()const
{
	return this->current_turn;
}

BoardClass OseloClass::GetBoard()const
{
	return this->board;
}

int OseloClass::GetWin()const
{
	return OseloSystem::GetWin(this->board);
}

BoardClass OseloSystem::GetEstimate(const BoardClass &board, const CellCoord &coord, const int &color)
{
	auto ret = board;
	Put(&ret, coord, color);

	return board;
}

vector<CellCoord> OseloSystem::GetPutable(const BoardClass& board, const int &color)
{
	Flip dummy;
	vector<CellCoord> ret;

	auto board_size = board.GetBoardSize();

	ret.reserve(board_size.x*board_size.y);

	CellCoord coord;
	for (coord.y = 0; coord.y < board_size.y; ++coord.y)
	{
		for (coord.x = 0; coord.x < board_size.x; ++coord.x)
		{
			if (CheckPut(board, coord, color, &dummy))
			{
				ret.push_back(coord);
			}
		}
	}

	return ret;
}

int OseloSystem::GetWin(const BoardClass &board)
{
	return board.GetOften();
}