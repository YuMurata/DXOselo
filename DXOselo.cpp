// DXOselo.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "DXOselo.h"
#include<DxFunc.h>

#include"CellMGR.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	DxClass obj;

	CellMGR cells(8);

	cells.Init();
	cells.Draw();

	WaitKey();
}
