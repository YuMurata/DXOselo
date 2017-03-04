#pragma once

#include"PieceMGR.h"

using namespace std;

class BaseAgent
{
protected:
	shared_ptr<PieceMGR> pieces;

public:
	BaseAgent(const shared_ptr<PieceMGR> &pieces)
		:pieces(pieces)
	{}

	virtual void Put(const Input &input) = 0;
};