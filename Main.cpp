// DXOselo.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "DXOselo.h"

#include<DxFunc.h>
#include"MenuObject.h"
#include"OseloObject.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	using namespace std;

	DxClass obj("オセロです＾ｐ＾");

	SceneMGR scene;

	scene.builder.Register<MenuObject>("MENU");
	scene.builder.Register<OseloObject>("GAME");

	unique_ptr<ObjectIF> cells(new OseloObject(8));
	unique_ptr<ObjectIF> menu(new MenuObject);
	Input input;

	//cells->Init();
	scene.Init("MENU");
	while (obj.MainLoop())
	{
		//obj.UpDate(menu,&input);
		//obj.Draw(menu);

		obj.UpDate(&scene, &input);
		obj.Draw(scene);
	}
	WaitKey();
}
