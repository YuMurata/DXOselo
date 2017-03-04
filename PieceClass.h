#pragma once

#include<DxFunc.h>

class CellClass :public BaseImage
{
public:
	CellClass(){}

	~CellClass() {}

	

	void Init(const CellCoord &coord, const int &handle)
	{
		this->coord = coord;
		this->handle = handle;
	}

	virtual void UpDate()
	{

	}
};