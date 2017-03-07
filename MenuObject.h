#pragma once

#include<DxFunc.h>
#include<Coordinate.h>
#include"AgentInfo.h"

class MenuObject :public ObjectIF,public SceneChanger,public AgentInfo
{
public:

	MenuObject() {}

	~MenuObject() {}

	void Init()override
	{
	}

	void Draw()const override
	{
		using ScreenSize = TCoordinate<int>;
		ScreenSize screen_size;

		GetScreenState(&screen_size.x, &screen_size.y, int());
		
		auto mid = screen_size / (ScreenSize)2;
		
		auto black = GetColor(0, 0, 0);
		auto white = GetColor(255, 255, 255);

		DrawBox(0, 0, mid.x, screen_size.y, black, TRUE);
		DrawBox(mid.x,0,screen_size.x,screen_size.y, white, TRUE);

		auto quart = mid / (ScreenSize)2;
		DrawString(quart.x, mid.y, "çï", white);
		DrawString(3*quart.x, mid.y, "îí", black);
	}

	void UpDate(const Input &input)override;

};
