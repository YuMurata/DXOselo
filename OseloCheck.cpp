#include"stdafx.h"

#include"OseloClass.h"
#include"OseloSystem.h"

//盤面に石を配置できる座標があればtrue
bool OseloClass::CheckPutable()const
{
	return OseloSystem::CheckPutable(this->board, this->current_turn);
}

//石を配置できる場所がない、もしくは配置された石の総数が盤面のサイズと等しければtrue
bool OseloClass::CheckFinish()const
{
	return OseloSystem::CheckFinish(this->board);
}

//座標[x,y]が盤面の中ならtrue
bool OseloSystem::CheckInside(const BoardClass &board, const CellCoord &coord)
{
	bool flag = (CellCoord)0 <= coord&&coord < board.GetBoardSize();

	return flag;
}

//一直線上に裏返せるものがったらtrue
//かつ裏返せる座標[x,y]をflip_pieceに格納
bool OseloSystem::CheckLine(const BoardClass &board, const CellCoord &coord, const CellCoord &dcoord, const int &color, Flip *flip_piece)
{
	const int enemy_color = (color + 1) % 2;

	auto sum_coord = coord + dcoord;

	if (!CheckInside(board, sum_coord))
	{
		return false;
	}

	if (board.GetCellState(sum_coord) == color)
	{
		flip_piece->push_back(coord);
		return true;
	}
	else if (board.GetCellState(sum_coord) == enemy_color)
	{
		bool line_flag = CheckLine(board, sum_coord, dcoord, color, flip_piece);
		if (line_flag)
		{
			flip_piece->push_back(coord);
		}
		return line_flag;
	}
	else
	{
		return false;
	}
}

//隣接するセル方向に裏返せるものがあったらtrue
//かつ裏返せる座標[x,y]をflip_pieceに格納
bool OseloSystem::CheckSide(const BoardClass &board, const CellCoord &coord, const int &color, Flip *flip_piece)
{
	const int UP = -1;
	const int DOWN = 1;
	const int LEFT = -1;
	const int RIGHT = 1;

	const int enemy_color = (color + 1) % 2;
	bool putable_flag = false;

	for (int dy = UP; dy <= DOWN; ++dy)
	{
		if (!CheckInside(board, CellCoord(coord.x, coord.y + dy)))
		{
			continue;
		}

		for (int dx = LEFT; dx <= RIGHT; ++dx)
		{
			auto dcoord = CellCoord(dx, dy);
			auto sum_coord = coord + dcoord;
			if (!CheckInside(board, sum_coord))
			{
				continue;
			}

			if (board.GetCellState(sum_coord) == enemy_color)
			{
				if (CheckLine(board, sum_coord, dcoord, color, flip_piece))
				{
					putable_flag = true;
				}
			}
		}
	}
	return putable_flag;
}

//座標[x,y]に石が配置されていなければtrue
bool OseloSystem::CheckNone(const BoardClass &board, const CellCoord &coord)
{
	return board.GetCellState(coord) == BoardClass::Cell_Empty;
}

//座標[x,y]に石が配置されていない、かつ座標[x,y]の隣接方向に裏返せるものがあればtrue
bool OseloSystem::CheckPut(const BoardClass &board, const CellCoord &coord, const int &color, Flip *flip_piece)
{
	return CheckInside(board, coord) && CheckNone(board, coord) && CheckSide(board, coord, color, flip_piece);
}

//盤面に石を配置できる座標があればtrue
bool OseloSystem::CheckPutable(const BoardClass &board, const int &color)
{
	return !GetPutable(board, color).empty();
}

//石を配置できる場所がない、もしくは配置された石の総数が盤面のサイズと等しければtrue
bool OseloSystem::CheckFinish(const BoardClass &board)
{
	bool putable_flag = false;

	for (int i = BoardClass::Cell_BLACK; i <= BoardClass::Cell_WHITE; ++i)
	{
		if (CheckPutable(board, i))
		{
			putable_flag = true;
		}
	}

	return !putable_flag;
}