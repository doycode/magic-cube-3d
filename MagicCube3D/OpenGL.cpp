#include "StdAfx.h"
#include "OpenGL.h"

#include "SecondOrderCube.h"

//#include "MagicCube3DView.h"

COpenGL :: COpenGL(void): eyePos(4, 4.5, 5)
//COpenGL :: COpenGL(void): eyePos(0, 5, 6)
{

}

COpenGL :: ~COpenGL(void)
{
	wglMakeCurrent(hDC, NULL);
	wglDeleteContext(hRC);
}

void COpenGL :: Init(void)
{
	glClearColor(0, 0, 0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

bool COpenGL::SetupPixelFormat(HDC hDC0)
{
	int nPixelFormat;					  
	hDC=hDC0;
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    
		1,                                
		PFD_DRAW_TO_WINDOW |              
		PFD_SUPPORT_OPENGL |              
		PFD_DOUBLEBUFFER,                 
		PFD_TYPE_RGBA,                    
		24,                               
		0, 0, 0, 0, 0, 0,                 
		0,                                
		0,                                
		0,                                
		0, 0, 0, 0,                       
		32,                               
		0,                                
		0,                                
		PFD_MAIN_PLANE,                   
		0,                                
		0, 0, 0                           
	}; 
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{ MessageBox(NULL,"can not find proper mode","Error",MB_OK|MB_ICONEXCLAMATION);
	return FALSE;
	}
	SetPixelFormat(hDC,nPixelFormat,&pfd);
	hRC = wglCreateContext(hDC);          
	wglMakeCurrent(hDC, hRC);             
	return TRUE;
}

void COpenGL::Reshape(int width,int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,(GLfloat)width/(GLfloat)height,0.1,3000.0);
	glMatrixMode(GL_MODELVIEW);
}

void COpenGL::Render()
{	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	

	glLoadIdentity();
	gluLookAt(eyePos.x, eyePos.y, eyePos.z,//相机在世界坐标的位置，可以理解为脑袋的位置
		0, 0, 0,//相机镜头对准的物体在世界坐标的位置，可以理解为物体的位置
		0, 1, 0);//相机向上的方向在世界坐标中的方向，可以理解为头顶朝向的方向(因为你可以歪着头看同一个物体)
		
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CMagicCube3DView* g_pViw = (CMagicCube3DView*)pFrame->GetActiveView();

	if(0 == g_pViw->secondOrThird && 0 == g_pViw->st)
	{
		magicCube.display();
	}

	else if(3 == g_pViw->secondOrThird)//三阶初始化
	{
		magicCube.initialize();
		magicCube.display();
	}

	else if(2 == g_pViw->secondOrThird)//二阶初始化
	{
		secondOrderCube.initialize();
		secondOrderCube.display();
	}

	else if(3 == g_pViw->st)
	{
		magicCube.display();
	}

	else if(2 == g_pViw->st)
	{
		secondOrderCube.display();
	}

	glFlush();
	SwapBuffers(hDC);
}