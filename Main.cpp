// DXOselo.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "DXOselo.h"

#include"OseloObject.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	using namespace std;

	DxClass obj("オセロです＾ｐ＾");

	unique_ptr<ObjectIF> cells(new OseloObject(8));
	Input input;

	cells->Init();

	while (obj.MainLoop())
	{
		obj.UpDate(cells,&input);
		obj.Draw(cells);
	}
	WaitKey();
}
