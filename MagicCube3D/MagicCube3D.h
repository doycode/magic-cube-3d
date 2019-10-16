
// MagicCube3D.h : MagicCube3D 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#include "OpenGL.h"

// CMagicCube3DApp:
// 有关此类的实现，请参阅 MagicCube3D.cpp
//

class CMagicCube3DApp : public CWinAppEx
{
public:
	CMagicCube3DApp();

	COpenGL openGL;

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnIdle(LONG lCount);
};

extern CMagicCube3DApp theApp;
