// DXOselo.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "DXOselo.h"

#include"CellMGR.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	using namespace std;

	DxClass obj;

	unique_ptr<ObjectIF> cells(new CellMGR(8));

	cells->Init();

	while (obj.MainLoop())
	{
		obj.Draw(cells);
	}
	WaitKey();
}
