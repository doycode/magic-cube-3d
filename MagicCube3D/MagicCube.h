#ifndef __MAGICCUBE_H__
#define __MAGICCUBE_H__

#include "StdAfx.h"
#include "utilities.h"

class CMagicCube
{
public:
	CMagicCube(void);
	~CMagicCube(void);

	void setRotateInfo(RotateInfo& info)
	{
		rotateInfo = info;	
	}

	void display(void);
	void initialize(void);
	void rotateColor(void);
	CString restore(void);

private:
	RotateInfo rotateInfo;
};

#endif