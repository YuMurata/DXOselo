#pragma once

#include"stdafx.h"

#include"RateClass.h"
#include"BoardInfo.h"
#include"Object.h"
#include"CellMGR.h"
#include"BaseAgent.h"

#include<DxFunc.h>
#include<Coordinate.h>
#include<OseloClass.h>
#include<vector>
#include<memory>

class OseloObject:public ObjectIF,RateClass,BoardInfo
{
private:
	Object board;
	std::shared_ptr<CellMGR> cells;
	std::vector<int> win;
	CellCoord Mouse2Cell(const MouseCoord &coord);
	std::vector<std::unique_ptr<BaseAgent>> agents;

public:
	OseloObject(const CellNum &cell_num, const int &current_turn);
	
	~OseloObject();

	void Put(const int &color);

	virtual void Init();

	virtual void Draw();

	virtual void UpDate(const Input &input);
};