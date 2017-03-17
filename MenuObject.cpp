#include"MenuObject.h"

int AgentInfo::user_color;
int AgentInfo::q_color;

void MenuObject::UpDate(const Input &input)
{
	auto coord = input.GetMouseCoord();

	if (input.GetMouseInPut(MOUSE_INPUT_LEFT))
	{
		using ScreenSize = TCoordinate<int>;
		ScreenSize screen_size;
		GetScreenState(&screen_size.x, &screen_size.y, int());
		ScreenSize beg = 0;
		auto mid = screen_size / ScreenSize(2, 1);

		if (beg <= coord&&coord <= mid)
		{
			this->user_color = BoardClass::Cell_BLACK;
			this->q_color = BoardClass::Cell_WHITE;
			this->scene_name = "GAME";
		}
		else if (ScreenSize(mid.x, 0) <= coord&&coord <= screen_size)
		{
			this->user_color = BoardClass::Cell_WHITE;
			this->q_color = BoardClass::Cell_BLACK;
			this->scene_name = "GAME";
		}
	}
}