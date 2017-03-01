#pragma once

#include"stdafx.h"

#include"BoardClass.h"

#include<utility>
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class OseloSystem
{
public:
	using Flip = vector<CellCoord>;

public:
//Check

	//座標[x,y]が盤面の中ならtrue
	static bool CheckInside(const BoardClass &board, const CellCoord &coord);

	//一直線上に裏返せるものがったらtrue
	//かつ裏返せる座標[x,y]をflip_pieceに格納
	static bool CheckLine(const BoardClass &board, const CellCoord &coord, const CellCoord &dcoord, const int &color, Flip *flip_piece);

	//隣接するセル方向に裏返せるものがあったらtrue
	//かつ裏返せる座標[x,y]をflip_pieceに格納
	static bool CheckSide(const BoardClass &board, const CellCoord &coord, const int &color, Flip *flip_piece);

	//座標[x,y]に石が配置されていなければtrue
	static bool CheckNone(const BoardClass &board, const CellCoord &coord);

	//座標[x,y]に石が配置されていない、かつ座標[x,y]の隣接方向に裏返せるものがあればtrue
	static bool CheckPut(const BoardClass &board, const CellCoord &coord, const int &color, Flip *flip_piece);

	//盤面に石を配置できる座標があればtrue
	static bool CheckPutable(const BoardClass &board, const int &color);

	//石を配置できる場所がない、もしくは配置された石の総数が盤面のサイズと等しければtrue
	static bool CheckFinish(const BoardClass &board);

//Put,Init

	//盤面の中央に石を配置
	static std::pair<PutState,PutState> Init(BoardClass *board);

	static PutState Put(BoardClass *board, const CellCoord &coord, const int &color);
	
//Disp

	//盤面の描画
	static void DrawBoard(const BoardClass &board);

	//石の数を表示
	static void DispCells(const int &black_count, const int &white_count);

	//石を配置できない場合に呼び出す
	static void Pass(const int &color);

//ETC

	//turn_colorの反転
	static void ChangeTurn(int *turn_color);

//Get

	static BoardClass GetEstimate(const BoardClass &board, const CellCoord &coord, const int &color);
	
	static vector<CellCoord> GetPutable(const BoardClass& board, const int &color);

	static int GetWin(const BoardClass &board);

//Undo,Redo

	static PutState Undo(BoardClass *board);

	static bool Redo(BoardClass *board);
};