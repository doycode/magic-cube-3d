#include "StdAfx.h"//必须
#include "SecondOrderCube.h"
//#include "MagicCube.h"

const GLubyte colorTable2[7][3] = {
	{0, 0, 255},//blue
	{0, 255, 0},//green
	{255, 0, 0},//red
	{255, 111, 0},//orange
	{255, 255, 255},//white
	{255, 255, 0},//yellow
	{0, 0, 0}//black
};

Color aspectColors2[6][4];

Color aspectColor_org2[6][4] = {
	{ RED, RED, RED, RED },//front
	{ ORANGE, ORANGE, ORANGE, ORANGE },//back
	{ YELLOW, YELLOW, YELLOW, YELLOW },//left
	{ WHITE, WHITE, WHITE, WHITE},//right
	{ GREEN, GREEN, GREEN, GREEN },//up
	{ BLUE, BLUE, BLUE, BLUE }//down
};

const int aspectDotIndex2[6][9] = {
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },//front
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8 },//back
	{ 0, 3, 6, 9, 12, 15, 18, 21, 24 },//left
	{ 2, 5, 8, 11, 14, 17, 20, 23, 26 },//right
	{ 6, 7, 8, 15, 16, 17, 24, 25, 26 },//up
	{ 0, 1, 2, 9, 10, 11, 18, 19, 20 }//down
};

const GLfloat points2[27][3] = {
	{-1.5, -1.5, -1.5}, {0, -1.5, -1.5}, {1.5, -1.5, -1.5},//P0--P2
	{-1.5, 0, -1.5}, {0, 0, -1.5}, {1.5, 0, -1.5},//P3--P5
	{-1.5, 1.5, -1.5}, {0, 1.5, -1.5}, {1.5, 1.5, -1.5},//P6--P8
	{-1.5, -1.5, 0}, {0, -1.5, 0}, {1.5, -1.5, 0},//P9--P11
	{-1.5, 0, 0}, {}, {1.5, 0, 0},//P12--P14
	{-1.5, 1.5, 0}, {0, 1.5, 0}, {1.5, 1.5, 0},//P15--P17
	{-1.5, -1.5, 1.5}, {0, -1.5, 1.5}, {1.5, -1.5, 1.5},//P18--P20
	{-1.5, 0, 1.5}, {0, 0, 1.5}, {1.5, 0, 1.5},//P21--P23
	{-1.5, 1.5, 1.5}, {0, 1.5,  1.5}, {1.5, 1.5, 1.5},//P24--P26
};

inline void vertexs2(int* index)
{
	glVertex3fv(points2[index[0]]);//Specifies a vertex.
	glVertex3fv(points2[index[1]]);
	glVertex3fv(points2[index[2]]);
	glVertex3fv(points2[index[3]]);
}

inline void drawAspect2(Aspect asp, int index)
{
	int colorIndex = (index / 3) * 2 + index % 3;

	glColor3ubv(colorTable2[aspectColors2[asp][colorIndex]]);//Sets the current color from an already existing array of color values.

	int indexArray[4] = {aspectDotIndex2[asp][index], aspectDotIndex2[asp][index + 3],
		aspectDotIndex2[asp][index + 4], aspectDotIndex2[asp][index + 1]};

	glBegin(GL_QUADS);
	vertexs2(indexArray);
	glEnd();

	glColor3ubv(colorTable2[BLACK]);
	glLineWidth(11.f);
	glBegin(GL_LINE_LOOP);
	vertexs2(indexArray);
	glEnd();
}

inline void drawFullAspect2(Aspect asp)
{
	for(int line = 0; line < 2; line++)
	{
		for(int i = 0; i < 2; i++)//2 aspects of every line
		{
			int ind = line * 3 + i;
			drawAspect2(asp, ind);
		}
	}
}

void drawXRight2(void)
{
	drawFullAspect2(RIGHT);//right part

	for(int i = 0; i < 2; i++)
	{
		drawAspect2(UP, 1 + 3 * i);//up part
		drawAspect2(DOWN, 1 + 3 * i);
		drawAspect2(FRONT, 1 + 3 * i);
		drawAspect2(BACK, 1 + 3 * i);
	}

	glColor3ubv(colorTable2[BLACK]);//shield part

	//right
	int indexArray[4] = {1, 7, 25, 19};

	glBegin(GL_QUADS);

	vertexs2(indexArray);

	glEnd();
}

void drawXLeft2(void)
{
	drawFullAspect2(LEFT);

	for (int i = 0; i < 2; i++)
	{

		drawAspect2(UP, 3 * i);
		drawAspect2(DOWN, 3 * i);
		drawAspect2(FRONT, 3 * i);
		drawAspect2(BACK, 3 * i);
	}

	glColor3ubv(colorTable2[BLACK]);

	//left
	int indexArray[4] = {1, 7, 25, 19};

	glBegin(GL_QUADS);	

	vertexs2(indexArray);

	glEnd();
}

void drawYDown2(void)
{
	drawFullAspect2(DOWN);

	for (int i = 0; i < 2; i++)
	{
		drawAspect2(LEFT, 3 * i);
		drawAspect2(RIGHT, 3 * i);
		drawAspect2(FRONT, i);
		drawAspect2(BACK, i);
	}

	glColor3ubv(colorTable2[BLACK]);

	//down
	int indexArray[4] = {3, 5, 23, 21};

	glBegin(GL_QUADS);

	vertexs2(indexArray);

	glEnd();
}

void drawYUp2(void)
{
	drawFullAspect2(UP);

	for (int i = 0; i < 2; i++)
	{
		drawAspect2(LEFT, 1 + 3 * i);
		drawAspect2(RIGHT, 1 + 3 * i);
		drawAspect2(FRONT, 3 + i);
		drawAspect2(BACK, 3 + i);
	}

	glColor3ubv(colorTable2[BLACK]);

	//up
	int indexArray[4] = {3, 5, 23, 21};

	glBegin(GL_QUADS);

	vertexs2(indexArray);

	glEnd();
}

void drawZFront2()
{
	drawFullAspect2(FRONT);

	for (int i = 3; i < 5; i++)
	{		
		drawAspect2(LEFT, i);
		drawAspect2(RIGHT, i);
		drawAspect2(UP, i);
		drawAspect2(DOWN, i);
	}

	glColor3ubv(colorTable2[BLACK]);

	//front
	int indexArray[4] = {9, 11, 17, 15};

	glBegin(GL_QUADS);

	vertexs2(indexArray);

	glEnd();
}

void drawZBack2()
{
	drawFullAspect2(BACK);	

	for (int i = 0; i < 2; i++)
	{
		drawAspect2(LEFT, i);
		drawAspect2(RIGHT, i);
		drawAspect2(UP, i);
		drawAspect2(DOWN, i);
	}

	glColor3ubv(colorTable2[BLACK]);

	//back
	int indexArray[4] = {9, 11, 17, 15};

	glBegin(GL_QUADS);

	vertexs2(indexArray);

	glEnd();
}

void rotateFullAspectClockwise2(Aspect asp)
{
	if(UP == asp || DOWN == asp)
	{
		Color t = aspectColors2[asp][0];
		aspectColors2[asp][0] = aspectColors2[asp][2];
		aspectColors2[asp][2] = aspectColors2[asp][3];
		aspectColors2[asp][3] = aspectColors2[asp][1];
		aspectColors2[asp][1] = t;
	}
	else
	{
		Color t = aspectColors2[asp][0];
		aspectColors2[asp][0] = aspectColors2[asp][1];
		aspectColors2[asp][1] = aspectColors2[asp][3];
		aspectColors2[asp][3] = aspectColors2[asp][2];
		aspectColors2[asp][2] = t;
	}
}

void rotateFullAspectAnticlockwise2(Aspect asp)
{
	if(UP == asp || DOWN == asp)
	{
		Color t = aspectColors2[asp][0];
		aspectColors2[asp][0] = aspectColors2[asp][1];
		aspectColors2[asp][1] = aspectColors2[asp][3];
		aspectColors2[asp][3] = aspectColors2[asp][2];
		aspectColors2[asp][2] = t;
	}
	else
	{
		Color t = aspectColors2[asp][0];
		aspectColors2[asp][0] = aspectColors2[asp][2];
		aspectColors2[asp][2] = aspectColors2[asp][3];
		aspectColors2[asp][3] = aspectColors2[asp][1];
		aspectColors2[asp][1] = t;
	}
}

void rotateXLeftClockwise2()//L顺
{
	rotateFullAspectClockwise2(LEFT);

	for (int i = 0; i < 3; i += 2)
	{
		Color t = aspectColors2[FRONT][i];
		aspectColors2[FRONT][i] = aspectColors2[DOWN][i];
		aspectColors2[DOWN][i] = aspectColors2[BACK][2 - i];
		aspectColors2[BACK][2 - i] = aspectColors2[UP][2 - i];
		aspectColors2[UP][2 - i] = t;
	}
}

void rotateXLeftAnticlockwise2()//L逆
{
	rotateFullAspectAnticlockwise2(LEFT);

	for (int i = 0; i < 3; i += 2)
	{
		Color t = aspectColors2[FRONT][i];
		aspectColors2[FRONT][i] = aspectColors2[UP][2 - i];
		aspectColors2[UP][2 - i] = aspectColors2[BACK][2 - i];
		aspectColors2[BACK][2 - i] = aspectColors2[DOWN][i];
		aspectColors2[DOWN][i] = t;
	}
}

void rotateXRightClockwise2()//R顺
{
	rotateFullAspectClockwise2(RIGHT);

	for (int i = 0; i < 3; i += 2)
	{
		Color t = aspectColors2[FRONT][i + 1];
		aspectColors2[FRONT][i + 1] = aspectColors2[DOWN][i + 1];
		aspectColors2[DOWN][i + 1] = aspectColors2[BACK][2 - i + 1];
		aspectColors2[BACK][2 - i + 1] = aspectColors2[UP][2 - i + 1];
		aspectColors2[UP][2 - i + 1] = t;
	}
}

void rotateXRightAnticlockwise2()//R逆
{
	rotateFullAspectAnticlockwise2(RIGHT);

	for (int i = 0; i < 3; i += 2)
	{
		Color t = aspectColors2[FRONT][i + 1];
		aspectColors2[FRONT][i + 1] = aspectColors2[UP][2 - i + 1];
		aspectColors2[UP][2 - i + 1] = aspectColors2[BACK][2 - i + 1];
		aspectColors2[BACK][2 - i + 1] = aspectColors2[DOWN][i + 1];
		aspectColors2[DOWN][i + 1] = t;
	}
}

void rotateYDownClockwise2()//D顺
{
	rotateFullAspectClockwise2(DOWN);

	for (int i = 0; i < 2; i++)
	{
		Color t = aspectColors2[FRONT][i];
		aspectColors2[FRONT][i] = aspectColors2[RIGHT][2 - 2 * i];
		aspectColors2[RIGHT][2 - 2 * i] = aspectColors2[BACK][1 - i];
		aspectColors2[BACK][1 - i] = aspectColors2[LEFT][2 * i];
		aspectColors2[LEFT][2 * i] = t;
	}
}

void rotateYDownAnticlockwise2()//D逆
{
	rotateFullAspectAnticlockwise2(DOWN);

	for (int i = 0; i < 2; i++)
	{
		Color t = aspectColors2[FRONT][i];
		aspectColors2[FRONT][i] = aspectColors2[LEFT][2 * i];
		aspectColors2[LEFT][2 * i] = aspectColors2[BACK][1 - i];
		aspectColors2[BACK][1 - i] = aspectColors2[RIGHT][2 - 2 * i];
		aspectColors2[RIGHT][2 - 2 * i] = t;
	}
}

void rotateYUpClockwise2()//U顺
{
	rotateFullAspectClockwise2(UP);

	for (int i = 0; i < 2; i++)
	{
		Color t = aspectColors2[FRONT][i + 2];
		aspectColors2[FRONT][i + 2] = aspectColors2[RIGHT][2 - 2 * i + 1];
		aspectColors2[RIGHT][2 - 2 * i + 1] = aspectColors2[BACK][1 - i + 2];
		aspectColors2[BACK][1 - i + 2] = aspectColors2[LEFT][2 * i + 1];
		aspectColors2[LEFT][2 * i + 1] = t;
	}
}

void rotateYUpAnticlockwise2()//U逆
{
	rotateFullAspectAnticlockwise2(UP);

	for (int i = 0; i < 2; i++)
	{
		Color t = aspectColors2[FRONT][i + 2];
		aspectColors2[FRONT][i + 2] = aspectColors2[LEFT][2 * i + 1];
		aspectColors2[LEFT][2 * i + 1] = aspectColors2[BACK][1 - i + 2];
		aspectColors2[BACK][1 - i + 2] = aspectColors2[RIGHT][2 - 2 * i + 1];
		aspectColors2[RIGHT][2 - 2 * i + 1] = t;
	}
}

void rotateZFrontClockwise2()//F顺
{
	rotateFullAspectClockwise2(FRONT);

	for(int i = 2; i < 4; i++)
	{
		Color t = aspectColors2[UP][i];
		aspectColors2[UP][i] = aspectColors2[LEFT][i];
		aspectColors2[LEFT][i] = aspectColors2[DOWN][5 - i];
		aspectColors2[DOWN][5 - i] = aspectColors2[RIGHT][5 - i];
		aspectColors2[RIGHT][5 - i] = t;
	}
}

void rotateZFrontAnticlockwise2()//F逆
{
	rotateFullAspectAnticlockwise2(FRONT);

	for(int i = 2; i < 4; i++)
	{
		Color t = aspectColors2[UP][i];
		aspectColors2[UP][i] = aspectColors2[RIGHT][5 - i];
		aspectColors2[RIGHT][5 - i] = aspectColors2[DOWN][5 - i];
		aspectColors2[DOWN][5 - i] = aspectColors2[LEFT][i];
		aspectColors2[LEFT][i] = t;
	}
}

void rotateZBackClockwise2()//B顺
{
	rotateFullAspectClockwise2(BACK);

	for(int i = 0; i < 2; i++)
	{
		Color t = aspectColors2[UP][i];
		aspectColors2[UP][i] = aspectColors2[LEFT][i];
		aspectColors2[LEFT][i] = aspectColors2[DOWN][1 - i];
		aspectColors2[DOWN][1 - i] = aspectColors2[RIGHT][1 - i];
		aspectColors2[RIGHT][1 - i] = t;
	}
}

void rotateZBackAnticlockwise2()//B逆
{
	rotateFullAspectAnticlockwise2(BACK);

	for(int i = 0; i < 2; i++)
	{
		Color t = aspectColors2[UP][i];
		aspectColors2[UP][i] = aspectColors2[RIGHT][1 - i];
		aspectColors2[RIGHT][1 - i] = aspectColors2[DOWN][1 - i];
		aspectColors2[DOWN][1 - i] = aspectColors2[LEFT][i];
		aspectColors2[LEFT][i] = t;
	}
}

typedef void (*PRotatecolorTable2)();
PRotatecolorTable2 pRotatecolorTable2[3][2][2] = {
	//x
	{{rotateXLeftClockwise2, rotateXLeftAnticlockwise2},
	{rotateXRightClockwise2, rotateXRightAnticlockwise2}},
	//y
	{{rotateYDownClockwise2, rotateYDownAnticlockwise2},
	{rotateYUpClockwise2, rotateYUpAnticlockwise2}},
	//z
	{{rotateZBackClockwise2, rotateZBackAnticlockwise2},
	{rotateZFrontClockwise2, rotateZFrontAnticlockwise2}},
};

PRotatecolorTable2 F__ = rotateZFrontClockwise2;
PRotatecolorTable2 Fr__ = rotateZFrontAnticlockwise2;

PRotatecolorTable2 B__ = rotateZBackAnticlockwise2;
PRotatecolorTable2 Br__ = rotateZBackClockwise2;

PRotatecolorTable2 R__ = rotateXRightClockwise2;
PRotatecolorTable2 Rr__ = rotateXRightAnticlockwise2;

PRotatecolorTable2 L__ = rotateXLeftAnticlockwise2;
PRotatecolorTable2 Lr__ = rotateXLeftClockwise2;

PRotatecolorTable2 U__ = rotateYUpClockwise2;
PRotatecolorTable2 Ur__ = rotateYUpAnticlockwise2;

PRotatecolorTable2 D__ = rotateYDownAnticlockwise2;
PRotatecolorTable2 Dr__ = rotateYDownClockwise2;

void F2__()
{
	F__();
	F__();
}

void B2__()
{
	B__();
	B__();
}

void R2__()
{
	R__();
	R__();
}

void L2__()
{
	L__();
	L__();
}

void U2__()
{
	U__();
	U__();
}

void D2__()
{
	D__();
	D__();
}

//rotate whole cube along x axis clockwisely
void x__()
{
	rotateXLeftClockwise2();
	rotateXRightClockwise2();
}

void xr__()
{
	rotateXLeftAnticlockwise2();
	rotateXRightAnticlockwise2();
}

void x2__()
{
	x__();
	x__();
}

//rotate whole cube along y axis clockwisely
void y__()
{
	rotateYDownClockwise2();
	rotateYUpClockwise2();
}

void yr__()
{
	rotateYDownAnticlockwise2();
	rotateYUpAnticlockwise2();
}

void y2__()
{
	y__();
	y__();
}

//rotate whole cube along z axis clockwisely
void z__()
{
	rotateZBackClockwise2();
	rotateZFrontClockwise2();
}

void zr__()
{
	rotateZBackAnticlockwise2();
	rotateZFrontAnticlockwise2();
}

void z2__()
{
	z__();
	z__();
}

//store operation string
static char cmdString[555];
static int cmdStrPtr = 0;

void _F__()
{
	F__();
	cmdString[cmdStrPtr++] = 'F';
}

void _Fr__()//F'表示逆时针旋转
{
	Fr__();
	cmdString[cmdStrPtr++] = 'F';
	cmdString[cmdStrPtr++] = '\'';
}

void _F2__()
{
	F__();
	F__();
	cmdString[cmdStrPtr++] = 'F';
	cmdString[cmdStrPtr++] = '2';
}

void _B__()
{
	B__();
	cmdString[cmdStrPtr++] = 'B';
}

void _Br__()
{
	Br__();
	cmdString[cmdStrPtr++] = 'B';
	cmdString[cmdStrPtr++] = '\'';
}

void _B2__()
{
	B__();
	B__();
	cmdString[cmdStrPtr++] = 'B';
	cmdString[cmdStrPtr++] = '2';
}

void _R__()
{
	R__();
	cmdString[cmdStrPtr++] = 'R';
}

void _Rr__()
{
	Rr__();
	cmdString[cmdStrPtr++] = 'R';
	cmdString[cmdStrPtr++] = '\'';
}

void _R2__()
{
	R__();
	R__();
	cmdString[cmdStrPtr++] = 'R';
	cmdString[cmdStrPtr++] = '2';
}

void _L__()
{
	L__();
	cmdString[cmdStrPtr++] = 'L';
}

void _Lr__()
{
	Lr__();
	cmdString[cmdStrPtr++] = 'L';
	cmdString[cmdStrPtr++] = '\'';
}

void _L2__()
{
	L__();
	L__();
	cmdString[cmdStrPtr++] = 'L';
	cmdString[cmdStrPtr++] = '2';
}

void _U__()
{
	U__();
	cmdString[cmdStrPtr++] = 'U';
}

void _Ur__()
{
	Ur__();
	cmdString[cmdStrPtr++] = 'U';
	cmdString[cmdStrPtr++] = '\'';
}

void _U2__()
{
	U__();
	U__();
	cmdString[cmdStrPtr++] = 'U';
	cmdString[cmdStrPtr++] = '2';
}

void _D__()
{
	D__();
	cmdString[cmdStrPtr++] = 'D';
}

void _Dr__()
{
	Dr__();
	cmdString[cmdStrPtr++] = 'D';
	cmdString[cmdStrPtr++] = '\'';
}

void _D2__()
{
	D__();
	D__();
	cmdString[cmdStrPtr++] = 'D';
	cmdString[cmdStrPtr++] = '2';
}

void _x__()
{
	x__();
	cmdString[cmdStrPtr++] = 'x';
}

void _xr__()
{
	xr__();
	cmdString[cmdStrPtr++] = 'x';
	cmdString[cmdStrPtr++] = '\'';
}

void _x2__()
{
	x__();
	x__();
	cmdString[cmdStrPtr++] = 'x';
	cmdString[cmdStrPtr++] = '2';
}

void _y__()
{
	y__();
	cmdString[cmdStrPtr++] = 'y';
}

void _yr__()
{
	yr__();
	cmdString[cmdStrPtr++] = 'y';
	cmdString[cmdStrPtr++] = '\'';
}

void _y2__()
{
	y__();
	y__();
	cmdString[cmdStrPtr++] = 'y';
	cmdString[cmdStrPtr++] = '2';
}

void _z__()
{
	z__();
	cmdString[cmdStrPtr++] = 'z';
}

void _zr__()
{
	zr__();
	cmdString[cmdStrPtr++] = 'z';
	cmdString[cmdStrPtr++] = '\'';
}

void _z2__()
{
	z__();
	z__();
	cmdString[cmdStrPtr++] = 'z';
	cmdString[cmdStrPtr++] = '2';
}

bool IsTopLayerComplete()
{
	//Color t = aspectColors2[UP][0];

	if (aspectColors2[FRONT][2] == aspectColors2[FRONT][3] && aspectColors2[BACK][2] == aspectColors2[BACK][3] && 
		aspectColors2[LEFT][1] == aspectColors2[LEFT][3] && aspectColors2[RIGHT][1] == aspectColors2[RIGHT][3])
	{
		/*for (int i = 1; i < 4; i++)//此for循环是否多此一举？应该是
		{
			if (aspectColors2[UP][i] != t)
			{
				return false;
			}
		}*/
		return true;
	}
	return false;
}

CString RestoreTopLayer()//排好顶层，排好后转过来
{
	memset(cmdString, 0, 555);
	cmdStrPtr = 0;

	while(!IsTopLayerComplete())
	{
		int a[6] = {2, 3, 5, 7, 11, 13};
		int num = a[aspectColors2[UP][1]] * a[aspectColors2[RIGHT][1]];
		if((a[aspectColors2[UP][0]] * a[aspectColors2[BACK][2]] * a[aspectColors2[LEFT][1]]) % num == 0)
		{
			_L2__(); _D__();
		}
		else if((a[aspectColors2[UP][2]] * a[aspectColors2[FRONT][2]] * a[aspectColors2[LEFT][3]]) % num == 0)
		{
			if(aspectColors2[UP][2] == aspectColors2[UP][1] && aspectColors2[FRONT][2] == aspectColors2[RIGHT][1])
			{
				_F__(); _Rr__(); _Dr__(); _R__(); _D__();
			}
			else
			{
				_F2__();
			}
		}
		else if((a[aspectColors2[UP][3]] * a[aspectColors2[FRONT][3]] * a[aspectColors2[RIGHT][3]]) % num == 0)
		{
			if(aspectColors2[UP][3] != aspectColors2[UP][1])
			{
				if(aspectColors2[RIGHT][3] == aspectColors2[UP][1] && aspectColors2[FRONT][3] == aspectColors2[RIGHT][1])
				{
					_Rr__(); _Dr__(); _R__(); _D__();
				}
				else
				{
					_F__();
				}
			}
		}
		else if((a[aspectColors2[DOWN][0]] * a[aspectColors2[BACK][0]] * a[aspectColors2[LEFT][0]]) % num == 0)
		{
			_D2__();
		}
		else if((a[aspectColors2[DOWN][1]] * a[aspectColors2[BACK][1]] * a[aspectColors2[RIGHT][0]]) % num == 0)
		{
			_Dr__();//顺时针
		}
		else if((a[aspectColors2[DOWN][2]] * a[aspectColors2[FRONT][0]] * a[aspectColors2[LEFT][2]]) % num == 0)
		{
			_D__();
		}

		//UP[1]对应颜色在右前下角的三种情况：正对、侧面、底面
		if(aspectColors2[FRONT][1] == aspectColors2[UP][1])//正对
		{
			_F__(); _D__(); _Fr__();
		}
		else if(aspectColors2[RIGHT][2] == aspectColors2[UP][1])//侧面
		{
			if(aspectColors2[DOWN][3] == aspectColors2[RIGHT][1])
			{
				_Fr__();
			}
			else
			{
				_Rr__(); _Dr__(); _R__();
			}
		}
		else if(aspectColors2[DOWN][3] == aspectColors2[UP][1])//底面
		{
			_Fr__(); _Rr__(); _Dr__(); _R__(); _D__();
			if(aspectColors2[UP][3] != aspectColors2[UP][1] || aspectColors2[RIGHT][3] != aspectColors2[RIGHT][1])
			{//这个条件是否多余？不多余！
				_Rr__(); _Dr__(); _R__();
			}
		}

		if(aspectColors2[UP][3] == aspectColors2[UP][1] && aspectColors2[RIGHT][3] == aspectColors2[RIGHT][1])
		{
			_yr__();
		}
	}
	return CString(cmdString);
}

bool IsSecondLayerTopSurfaceComplete()
{
	Color t = aspectColors2[UP][0];
	if (aspectColors2[FRONT][0] == aspectColors2[FRONT][1] && aspectColors2[BACK][0] == aspectColors2[BACK][1] && 
		aspectColors2[LEFT][0] == aspectColors2[LEFT][2] && aspectColors2[RIGHT][0] == aspectColors2[RIGHT][2])
	{
		for (int i = 1; i < 4; i++)
		{
			if (aspectColors2[UP][i] != t)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

CString RestoreSecondLayerTopSurface()
{
	//ASSERT(IsTopLayerComplete());

	memset(cmdString, 0, 555);
	cmdStrPtr = 0;

	_z2__();//把排好的顶层转到底层

	int cnt = 0;//假如此时排好的底面颜色是白色，那么cnt就是顶面黄色个数
	Color downColor = aspectColors2[DOWN][0];
	Color upGoalColor;

	if(downColor % 2)
	{
		upGoalColor = (Color)(downColor - 1);
	}
	else
	{
		upGoalColor = (Color)(downColor + 1);
	}

	while(!IsSecondLayerTopSurfaceComplete())
	{
		cnt = 0;
		for(int i = 0; i < 4; i++)
		{
			if(aspectColors2[UP][i] == upGoalColor)
			{
				cnt++;
			}
		}

		if(0 == cnt)//两次小鱼1？是固定的吗？
		{
			while(aspectColors2[LEFT][1] != upGoalColor)
			{
				_y__();
				//_U__();
			}

			_Rr__(); _Ur__(); _R__(); _Ur__(); _Rr__(); _U2__(); _R__();//小鱼1

			//会不会有UP面有一目标色且不在0处而目标色在FRONT的2或3处的情况？会！
			while(aspectColors2[UP][0] != upGoalColor)
			{
				_y__();
				//_U__();
			}
		}
		else if(1 == cnt)
		{
			while(aspectColors2[UP][0] != upGoalColor)
			{
				_y__();
				//_U__();
			}
		}
		else if(2 == cnt)//小鱼1 + 小鱼2 ？是固定的吗？
		{
			while(aspectColors2[BACK][2] != upGoalColor)
			{
				_y__();
				//_U__();
			}

			_Rr__(); _Ur__(); _R__(); _Ur__(); _Rr__(); _U2__(); _R__();//小鱼1

			while(aspectColors2[UP][0] != upGoalColor)
			{
				_y__();
				//_U__();
			}
		}

		if(aspectColors2[FRONT][2] == upGoalColor)
		{
			_Rr__(); _Ur__(); _R__(); _Ur__(); _Rr__(); _U2__(); _R__();//小鱼1
		}
		else if(aspectColors2[FRONT][3] == upGoalColor)
		{
			_F__(); _U__(); _Fr__(); _U__(); _F__(); _U2__(); _Fr__();//小鱼2
		}
	}
	return CString(cmdString);
}

CString RestoreSecondLayerSideSurface()
{
	//ASSERT(IsSecondLayerTopSurfaceComplete());

	memset(cmdString, 0, 555);
	cmdStrPtr = 0;

	bool flg;

	while(!IsTopLayerComplete())
	{
		flg = false;
		for(int i = 0; i < 4; i++)
		{
			if(aspectColors2[RIGHT][3] == aspectColors2[RIGHT][1])
			{
				flg = true;
				break;
			}
			_y__();
			//_U__();
		}
		
		_R2__(); _F2__(); _Rr__(); _Br__(); _R__(); _F2__(); _Rr__(); _B__(); _Rr__();
	}

	while(aspectColors2[FRONT][0] != aspectColors2[FRONT][2])
	{
		_U__();
	}

	return CString(cmdString);
}

void Executor2(const char* cmd)
{
	while(*cmd)
	{
		switch(*cmd)
		{
		case ' ':							
			break;

		case '#':				
			do
			{
				cmd++;
			}
			while(*cmd != '#' && *cmd);
			break;

		case 'F':
			if ('\'' == *(cmd + 1))
			{
				Fr__();	
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				F2__();
				cmd++;
			}
			else
			{
				F__();
			}
			break;

		case 'B':
			if ('\'' == *(cmd + 1))
			{
				Br__();
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				B2__();
				cmd++;
			}
			else
			{
				B__();
			}
			break;

		case 'L':
			if ('\'' == *(cmd + 1))
			{
				Lr__();
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				L2__();
				cmd++;
			}
			else
			{
				L__();
			}
			break;

		case 'R':
			if ('\'' == *(cmd + 1))
			{
				Rr__();
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				R2__();
				cmd++;
			}
			else
			{
				R__();
			}
			break;

		case 'U':
			if ('\'' == *(cmd + 1))
			{
				Ur__();
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				U2__();
				cmd++;
			}
			else
			{
				U__();
			}
			break;

		case 'D':
			if ('\'' == *(cmd + 1))
			{
				Dr__();
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				D2__();
				cmd++;
			}
			else
			{
				D__();
			}
			break;

		case 'x':
			if ('\'' == *(cmd + 1))
			{
				xr__();
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				x2__();
				cmd++;
			}
			else
			{
				x__();
			}
			break;

		case 'y':
			if ('\'' == *(cmd + 1))
			{
				yr__();
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				y2__();
				cmd++;
			}
			else
			{
				y__();
			}
			break;

		case 'z':
			if ('\'' == *(cmd + 1))
			{
				zr__();
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				z2__();
				cmd++;
			}
			else
			{
				z__();
			}
			break;

		default:
			break;
		}
		cmd++;
	}
}

CString UndoCmdString2(const char* cmd)
{
	CString undoCmd;
	while(*cmd)
	{
		switch(*cmd)
		{
		case ' ':
			break;

		case '#':				
			do
			{
				cmd++;
			}
			while(*cmd != '#' && *cmd);
			break;

		case 'F':
		case 'B':
		case 'L':
		case 'R':
		case 'U':
		case 'D':
		case 'x':
		case 'y':
		case 'z':
			undoCmd.Insert(0, *cmd);
			if ('\'' == *(cmd + 1))
			{
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				undoCmd.Insert(1, '2');
				cmd++;
			}
			else
			{
				undoCmd.Insert(1, '\'');
			}
			break;

		default:
			break;					
		}
		cmd++;
	}
	return undoCmd;
}

int CountSteps2(const char* cmd)
{
	//method:
	int steps = 0;
	while(*cmd)
	{
		switch(*cmd)
		{
		case ' ':
			break;

		case '#':				
			do
			{
				cmd++;
			}
			while(*cmd != '#' && *cmd);
			break;

		case 'F':
		case 'B':
		case 'L':
		case 'R':
		case 'U':
		case 'D':
			steps++;
			if ('\'' == *(cmd + 1))
			{
				cmd++;
			}
			else if ('2' == *(cmd + 1))
			{
				//steps++;
				cmd++;
			}
			break;

		default:
			break;					
		}
		cmd++;
	}
	return steps;
}

CString MethodFewerFormula2()
{
	CString cmd;
	cmd = "#Restore Top Layer:\r\n\t#";
	cmd += RestoreTopLayer();
	cmd += "#\r\nRestore Second Layer Top Surface:\r\n\t#";
	cmd += RestoreSecondLayerTopSurface();
	cmd += "#\r\nRestore Second Layer Side Surface:\r\n\t#";
	cmd += RestoreSecondLayerSideSurface();

	int len = CountSteps2(cmd.GetBuffer());
	CString str;
	str.Format("#\r\n\r\nStep Number:\r\n\t%d#", len);
	cmd += str;
	//the view is not updated,and we should undo all the operations 
	//during the steps above
	CString undo = UndoCmdString2(cmd.GetBuffer(cmd.GetLength()));
	Executor2(undo.GetBuffer(undo.GetLength()));

	return cmd;
}

CSecondOrderCube::CSecondOrderCube(void)
{
}

CSecondOrderCube::~CSecondOrderCube(void)
{
}

void CSecondOrderCube::initialize()
{
	memcpy(aspectColors2, aspectColor_org2, sizeof(aspectColor_org2));
	rotateInfo = RotateInfo();
}

void CSecondOrderCube::rotateColor(void)
{
	switch (rotateInfo.type)
	{
	case 'F':
		if (rotateInfo.reversed)
		{
			Fr__();
		}
		else 
		{
			F__();
		}
		break;

	case 'B':
		if (rotateInfo.reversed)
		{
			Br__();
		}
		else 
		{
			B__();
		}
		break;

	case 'L':
		if (rotateInfo.reversed)
		{
			Lr__();
		}
		else 
		{
			L__();
		}
		break;

	case 'R':
		if (rotateInfo.reversed)
		{
			Rr__();
		}
		else 
		{
			R__();
		}
		break;

	case 'U':
		if (rotateInfo.reversed)
		{
			Ur__();
		}
		else 
		{
			U__();
		}
		break;

	case 'D':
		if (rotateInfo.reversed)
		{
			Dr__();
		}
		else 
		{
			D__();
		}
		break;

	case 'x':
		if (rotateInfo.reversed)
		{
			xr__();
		}
		else 
		{
			x__();
		}
		break;

	case 'y':
		if (rotateInfo.reversed)
		{
			yr__();
		}
		else 
		{
			y__();
		}
		break;

	case 'z':
		if (rotateInfo.reversed)
		{
			zr__();
		}
		else 
		{
			z__();
		}
		break;

	default:
		break;
	}
}

void CSecondOrderCube::display()
{	
	static float rotateVect[3][2][3] = {
		{{1, 0, 0}, {-1, 0, 0}},//绕X轴旋转，正表示逆时针
		{{0, 1, 0}, {0, -1, 0}},//绕Y轴旋转
		{{0, 0, 1}, {0, 0, -1}}//绕Z轴旋转
	};
	Axis axis;
	int direct;
	switch (rotateInfo.type)
	{
	case 'F':
		axis = Z;
		if (rotateInfo.reversed)
		{
			direct = 0;
		}
		else 
		{
			direct = 1;
		}
		drawZBack2();
		glPushMatrix();
		glRotatef(rotateInfo.angle, rotateVect[axis][direct][0],
			rotateVect[axis][direct][1], rotateVect[axis][direct][2]);
		drawZFront2();
		glPopMatrix();
		break;

	case 'B':
		axis = Z;
		if (rotateInfo.reversed)
		{
			direct = 1;
		}
		else 
		{
			direct = 0;
		}					
		drawZFront2();
		glPushMatrix();
		glRotatef(rotateInfo.angle, rotateVect[axis][direct][0],
			rotateVect[axis][direct][1], rotateVect[axis][direct][2]);
		drawZBack2();
		glPopMatrix();
		break;

	case 'L':
		axis = X;
		if (rotateInfo.reversed)
		{
			direct = 1;
		}
		else 
		{
			direct = 0;
		}
		drawXRight2();
		glPushMatrix();
		glRotatef(rotateInfo.angle, rotateVect[axis][direct][0],
			rotateVect[axis][direct][1], rotateVect[axis][direct][2]);
		drawXLeft2();
		glPopMatrix();
		break;

	case 'R':
		axis = X;
		if (rotateInfo.reversed)
		{
			direct = 0;
		}
		else 
		{
			direct = 1;
		}
		drawXLeft2();
		glPushMatrix();
		glRotatef(rotateInfo.angle, rotateVect[axis][direct][0],
			rotateVect[axis][direct][1], rotateVect[axis][direct][2]);
		drawXRight2();
		glPopMatrix();
		break;

	case 'U':
		axis = Y;
		if (rotateInfo.reversed)
		{
			direct = 0;
		}
		else 
		{
			direct = 1;
		}
		drawYDown2();
		glPushMatrix();
		glRotatef(rotateInfo.angle, rotateVect[axis][direct][0],
			rotateVect[axis][direct][1], rotateVect[axis][direct][2]);
		drawYUp2();
		glPopMatrix();
		break;

	case 'D':
		axis = Y;
		if (rotateInfo.reversed)
		{
			direct = 1;
		}
		else 
		{
			direct = 0;
		}
		drawYUp2();
		glPushMatrix();
		glRotatef(rotateInfo.angle, rotateVect[axis][direct][0],
			rotateVect[axis][direct][1], rotateVect[axis][direct][2]);
		drawYDown2();
		glPopMatrix();
		break;

	case 'x':
		axis = X;
		if (rotateInfo.reversed)
		{
			direct = 0;
		}
		else 
		{
			direct = 1;
		}
		glPushMatrix();
		glRotatef(rotateInfo.angle, rotateVect[axis][direct][0],
			rotateVect[axis][direct][1], rotateVect[axis][direct][2]);
		drawXLeft2();
		drawXRight2();
		glPopMatrix();
		break;

	case 'y':
		axis = Y;
		if (rotateInfo.reversed)
		{
			direct = 0;
		}
		else 
		{
			direct = 1;
		}
		glPushMatrix();
		glRotatef(rotateInfo.angle, rotateVect[axis][direct][0],
			rotateVect[axis][direct][1], rotateVect[axis][direct][2]);
		drawYDown2();
		drawYUp2();
		glPopMatrix();
		break;

	case 'z':
		axis = Z;
		if (rotateInfo.reversed)
		{
			direct = 0;
		}
		else 
		{
			direct = 1;
		}
		glPushMatrix();
		glRotatef(rotateInfo.angle, rotateVect[axis][direct][0],
			rotateVect[axis][direct][1], rotateVect[axis][direct][2]);
		drawZBack2();
		drawZFront2();
		glPopMatrix();
		break;

	default:
		drawZFront2();
		drawZBack2();
		break;
	}
}

CString CSecondOrderCube::restore()
{
	return MethodFewerFormula2();
}