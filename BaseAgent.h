#pragma once

#include"PieceMGR.h"

using namespace std;

class BaseAgent
{
protected:
	shared_ptr<PieceMGR> pieces;
	int my_color;
public:
	BaseAgent(const shared_ptr<PieceMGR> &pieces,const int &color)
		:pieces(pieces),my_color(color)
	{}

	virtual void Put(const Input &input) = 0;
};