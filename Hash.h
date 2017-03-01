#pragma once

#include"stdafx.h"

#include<utility>
#include<numeric>
#include"BoardClass.h"



using SA = std::pair<BoardClass, CellCoord>;

template<>
struct std::hash<SA>
{	
	size_t operator()(const SA &sa) const
	{	
		auto board = sa.first.GetBoard();
		const auto &coord = sa.second;
			const int C = 997;

		auto func1 = [&C](const size_t &left, const int &right)
		{
			return left*C + right;
		};

		auto func2 = [&func1](const size_t &left, const std::vector<int> &right)
		{
			return accumulate(begin(right), end(right), left, func1);
		};

		auto ret=std::accumulate(begin(board), end(board), 0, func2);

		ret = ret*C + coord.x;
		ret = ret*C + coord.y;
		
		return ret;
	}
};