#pragma once

#include"BaseAgent.h"
#include<OseloSystem.h>
#include<algorithm>
#include<Randomer.h>
class RandomAgent:public BaseAgent,public Randomer
{
public:
	RandomAgent(const shared_ptr<PieceMGR> &pieces)
		:BaseAgent(pieces)
	{}

	void Put(const Input &input)
	{
		auto board = this->pieces->GetBoard();
		auto color = this->pieces->GetCurrent();
		auto putable = OseloSystem::GetPutable(board, color);

		shuffle(begin(putable), end(putable), this->mt);
		auto coord = putable.front();

		this->pieces->Put(coord);
	}
};