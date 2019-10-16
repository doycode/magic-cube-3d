
// MagicCube3DView.h : CMagicCube3DView 类的接口
//

#pragma once

#include "OpenGL.h"
//#include "utilities.h"

class CMagicCube3DView : public CView
{
protected: // 仅从序列化创建
	CMagicCube3DView();
	DECLARE_DYNCREATE(CMagicCube3DView)

// 特性
public:
	CMagicCube3DDoc* GetDocument() const;

	int shuffledNum;
	static const int timerRotate = 1;//rotate timer index
	static const int timerShuffle = 2;//shuffle timer index
	static const int totleShuffleNum = 30;//shuffle number
	static const int rotateStep = 5;
	static const int rotateStepInterval = 5;

	//time needed for a rotate 
	//that's 90/rotateStep*rotateStepInterval+surplus time
	static const int rotateInterval = 90 / rotateStep * rotateStepInterval + 333;

	static const int timerRestore = 3;//restore timer index
	int restoredPos;//use in timer during restoration
	CString restoreString;
	RotateInfo rotateInfo;

	int figurePtr;//pointer to figures

	static const int timerRotate2 = 4;//二阶
	static const int timerShuffle2 = 5;//二阶
	static const int timerRestore2 = 6;//二阶

	//static const int timerInitialSecond = 7;
	//static const int timerInitialThird = 8;

	int secondOrThird;//要初始化
	int st;

	CMagicCube magicCube;

	CSecondOrderCube secondOrderCube;

// 操作
public:
	void Restore_UpdateRotateInfo();
	//void Executor();
	void Executor(UINT_PTR nIDEvent);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMagicCube3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnGameNew();
	afx_msg void OnShuffle();
	afx_msg void OnRestoreMagicCube();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSave();
	afx_msg void OnOpen();
	afx_msg void OnSecondShuffle();
	afx_msg void OnSecondRestore();
	afx_msg void OnSecondInit();
	afx_msg void OnRunInit();
};

#ifndef _DEBUG  // MagicCube3DView.cpp 中的调试版本
inline CMagicCube3DDoc* CMagicCube3DView::GetDocument() const
   { return reinterpret_cast<CMagicCube3DDoc*>(m_pDocument); }
#endif

