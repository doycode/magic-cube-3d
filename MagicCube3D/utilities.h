#pragma once

//#ifndef __UTILITIES_H__
//#define __UTILETIES_H__

#include"stdafx.h"

//rotate direction
enum Axis{X, Y, Z};

//description of chunk position
enum ChunkIndex{NEGATIVE, MIDDLE, POSTIVE};
enum RotateDirection{CLOCKWISE, COUNTERCLOCKWISE, NOROTATE};

//description of the 6 aspects and the situation that no aspect
enum Aspect{FRONT, BACK, LEFT, RIGHT, UP, DOWN, NOASPECT};

//black, color of sheltered aspects which can be seen when rotation
enum Color{BLUE, GREEN, RED, ORANGE, WHITE, YELLOW, BLACK};

class GLPoint2f
{
public:
	float x, y;

	GLPoint2f(): x(0), y(0){}

	GLPoint2f(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

class GLPoint3f
{
public:
	float x, y, z;

	GLPoint3f(): x(0), y(0), z(0){}

	GLPoint3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

//selected situation
class TheSelected
{
public:
	GLPoint2f selectedPoint;
	Aspect aspect;
	int aspectIndex;

	TheSelected():aspectIndex(0), aspect(NOASPECT){}
};

//rotate infomation
class RotateInfo
{
public:	
	float angle;
	char type;
	bool reversed;//为真表示逆时针

	RotateInfo():type('F'),angle(0),reversed(false){}

	RotateInfo& operator = (RotateInfo& info)
	{
		angle = info.angle;
		type = info.type;
		reversed = info.reversed;
		return *this;
	}
};

class Facelet
{
public:
	Aspect asp;
	int index;
	Color color;

	Facelet(): asp(NOASPECT), index(-1), color(BLACK){}
};

class Edge
{
public:
	Facelet faceletMain;
	Facelet faceletSide;
};

//#endif