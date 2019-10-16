
#ifndef __SECONDORDERCUBE_H__
#define __SECONDORDERCUBE_H__

//#include "StdAfx.h"
#include "utilities.h"

class CSecondOrderCube
{
public:
	CSecondOrderCube(void);
	~CSecondOrderCube(void);

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