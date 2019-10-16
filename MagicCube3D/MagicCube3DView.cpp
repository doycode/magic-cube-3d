
// MagicCube3DView.cpp : CMagicCube3DView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MagicCube3D.h"
#endif

#include "MagicCube3DDoc.h"
#include "MagicCube3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMagicCube3DView

IMPLEMENT_DYNCREATE(CMagicCube3DView, CView)

	BEGIN_MESSAGE_MAP(CMagicCube3DView, CView)
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMagicCube3DView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()

		ON_WM_CLOSE()
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_WM_TIMER()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_COMMAND(ID_FILE_NEW, &CMagicCube3DView::OnGameNew)
		ON_COMMAND(ID_RUN_SHUFFLE, &CMagicCube3DView::OnShuffle)
		ON_COMMAND(ID_RUN_RESTORE, &CMagicCube3DView::OnRestoreMagicCube)
		ON_WM_KEYDOWN()
		ON_WM_CHAR()
		ON_COMMAND(ID_FILE_SAVE32774, &CMagicCube3DView::OnSave)
		ON_COMMAND(ID_FILE_OPEN32775, &CMagicCube3DView::OnOpen)
		ON_COMMAND(ID_SECOND_SHUFFLE, &CMagicCube3DView::OnSecondShuffle)
		ON_COMMAND(ID_SECOND_RESTORE, &CMagicCube3DView::OnSecondRestore)
		ON_COMMAND(ID_SECOND_INIT, &CMagicCube3DView::OnSecondInit)
		ON_COMMAND(ID_RUN_INIT, &CMagicCube3DView::OnRunInit)
	END_MESSAGE_MAP()

	// CMagicCube3DView 构造/析构

	CMagicCube3DView::CMagicCube3DView(): shuffledNum(0), figurePtr(0), secondOrThird(0), st(0)
	{
		// TODO: 在此处添加构造代码
		srand(unsigned(time(NULL)));
	}

	CMagicCube3DView::~CMagicCube3DView()
	{
	}

	BOOL CMagicCube3DView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CView::PreCreateWindow(cs);
	}

	// CMagicCube3DView 绘制

	void CMagicCube3DView::OnDraw(CDC* /*pDC*/)
	{
		CMagicCube3DDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 在此处为本机数据添加绘制代码
	}


	// CMagicCube3DView 打印

#if(1)
	void CMagicCube3DView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CMagicCube3DView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CMagicCube3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CMagicCube3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}
#endif

	void CMagicCube3DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void CMagicCube3DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}

	// CMagicCube3DView 诊断

#ifdef _DEBUG
	void CMagicCube3DView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CMagicCube3DView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CMagicCube3DDoc* CMagicCube3DView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMagicCube3DDoc)));
		return (CMagicCube3DDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CMagicCube3DView 消息处理程序
	void CMagicCube3DView::OnClose()
	{
		CView::OnClose();
	}

	void CMagicCube3DView::OnInitialUpdate()
	{
		CView::OnInitialUpdate();

		((CMagicCube3DApp*)AfxGetApp())->openGL.Init();
		((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.initialize();

		((CMagicCube3DApp*)AfxGetApp())->openGL.secondOrderCube.initialize();
	}

	int CMagicCube3DView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;

		((CMagicCube3DApp*)AfxGetApp())->openGL.SetupPixelFormat(::GetDC(m_hWnd));

		return 0;
	}

	void CMagicCube3DView::OnSize(UINT nType, int cx, int cy)
	{
		CView::OnSize(nType, cx, cy);

		int height = cy;
		int width = cx;
		if (height == 0)
		{
			height = 1;
		}
		((CMagicCube3DApp*)AfxGetApp())->openGL.Reshape(width, height);
	}

	void CMagicCube3DView::OnTimer(UINT_PTR nIDEvent)
	{
		//because the nondeterministic feature of timer event,I rotate 
		//color table first ,then let update cube rotate from negative 
		//position to current position
		const static char asp[18] = {'F', 'B', 'L', 'R', 'U', 'D',
			'f', 'b', 'l', 'r', 'u', 'd', 'x', 'y', 'z', 'E', 'M', 'S'
		};
		const static char asp2[9] = {'F', 'B', 'L', 'R', 'U', 'D', 'x', 'y', 'z'};
		if (timerRotate == nIDEvent)
		{//rotate
			if (rotateInfo.angle < 0)
			{
				rotateInfo.angle += rotateStep;
				((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.setRotateInfo(rotateInfo);
			}
			else
			{
				rotateInfo.angle = 0;
				((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.setRotateInfo(rotateInfo);
				KillTimer(timerRotate);
			}
		}
		else if(timerRotate2 == nIDEvent)
		{
			if (rotateInfo.angle < 0)
			{
				rotateInfo.angle += rotateStep;
				((CMagicCube3DApp*)AfxGetApp())->openGL.secondOrderCube.setRotateInfo(rotateInfo);
			}
			else
			{
				rotateInfo.angle = 0;
				((CMagicCube3DApp*)AfxGetApp())->openGL.secondOrderCube.setRotateInfo(rotateInfo);
				KillTimer(timerRotate2);
			}
		}
		else if (timerShuffle == nIDEvent)
		{//打乱
			if (shuffledNum < totleShuffleNum)
			{
				shuffledNum++;
				rotateInfo.type = asp[rand() % 18];
				if(rand() % 2)
				{
					rotateInfo.reversed = true;
				}
				else
				{
					rotateInfo.reversed = false;
				}
				//rotate color table
				Executor(nIDEvent);
			}
			else
			{
				KillTimer(timerShuffle);
				shuffledNum = 0;
			}
		}
		else if (timerShuffle2 == nIDEvent)
		{//打乱
			if (shuffledNum < totleShuffleNum)
			{
				shuffledNum++;
				rotateInfo.type = asp2[rand() % 9];
		
				if(rand() % 2)
				{
					rotateInfo.reversed = true;
				}
				else
				{
					rotateInfo.reversed = false;
				}
				//rotate color table
				Executor(nIDEvent);
			}
			else
			{
				KillTimer(timerShuffle2);
				shuffledNum = 0;
			}
		}
		else if (timerRestore == nIDEvent)
		{//复原
			if (restoredPos < restoreString.GetLength())
			{			
				Restore_UpdateRotateInfo();
				Executor(nIDEvent);
			}
			else
			{
				KillTimer(timerRestore);
			}
		}
		else if (timerRestore2 == nIDEvent)
		{//复原
			if (restoredPos < restoreString.GetLength())
			{			
				Restore_UpdateRotateInfo();
				Executor(nIDEvent);
			}
			else
			{
				KillTimer(timerRestore2);
			}
		}

		CView::OnTimer(nIDEvent);
	}

	void CMagicCube3DView::OnLButtonDown(UINT nFlags, CPoint point)
	{

		CView::OnLButtonDown(nFlags, point);
	}

	void CMagicCube3DView::OnLButtonUp(UINT nFlags, CPoint point)
	{

		CView::OnLButtonUp(nFlags, point);
	}

	void CMagicCube3DView::OnMouseMove(UINT nFlags, CPoint point)
	{

		CView::OnMouseMove(nFlags, point);
	}

	void CMagicCube3DView::OnGameNew()
	{
		KillTimer(timerRestore);
		KillTimer(timerRotate);
		KillTimer(timerShuffle);

		KillTimer(timerRestore2);
		KillTimer(timerRotate2);
		KillTimer(timerShuffle2);

		((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.initialize();	
		((CMagicCube3DApp*)AfxGetApp())->openGL.secondOrderCube.initialize();
	}

	void CMagicCube3DView::OnShuffle()
	{	
		magicCube.initialize();

		shuffledNum = 0;

		st = 3;
		secondOrThird = 0;

		SetTimer(timerShuffle, rotateInterval, NULL);//NULL表示使用OnTimer函数
	}

	//resemble Executor,except it turns command string into RotateInfo
	//restoredPos and rotateInfo will be modified and restoreString is used.
	void CMagicCube3DView::Restore_UpdateRotateInfo()
	{
		bool goon = true;
		while(goon && restoredPos < restoreString.GetLength())
		{
			switch(restoreString[restoredPos])
			{						
			case '2'://continue previous rotate state
				goon = false;
				break;

			case '#':
				do
				{
					restoredPos++;
				}
				while (restoreString[restoredPos] != '#' && restoredPos < restoreString.GetLength());
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
			case 'u':
			case 'r':
			case 'f':
			case 'd':
			case 'l':
			case 'b':
			case 'E':
			case 'M':
			case 'S':
				rotateInfo.reversed = false;
				rotateInfo.type = restoreString[restoredPos];
				if ('\'' == restoreString[restoredPos + 1])
				{
					rotateInfo.reversed = 1;
					restoredPos++;
				}
				goon = false;
				break;

			default:
				break;	
			}
			restoredPos++;
		}
		if (goon)
		{
			rotateInfo.type = '\0';
		}
	}

	void CMagicCube3DView::Executor(UINT_PTR nIDEvent)
	{

		rotateInfo.angle = -90;

		if(timerShuffle == nIDEvent || timerRestore == nIDEvent)
		{
			((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.setRotateInfo(rotateInfo);
			((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.rotateColor();

			SetTimer(timerRotate, rotateStepInterval, NULL);
		}
		else if(timerShuffle2 == nIDEvent || timerRestore2 == nIDEvent)
		{
			((CMagicCube3DApp*)AfxGetApp())->openGL.secondOrderCube.setRotateInfo(rotateInfo);
			((CMagicCube3DApp*)AfxGetApp())->openGL.secondOrderCube.rotateColor();

			SetTimer(timerRotate2, rotateStepInterval, NULL);
		}

	}

	void CMagicCube3DView::OnRestoreMagicCube()
	{
		st = 3;
		secondOrThird = 0;

		//restoreString.Empty();
		
		restoreString = ((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.restore();
		restoredPos = 0;
		//rotate
		SetTimer(timerRestore, rotateInterval, NULL);
	}

	//for test
	void CMagicCube3DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{

		CView::OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CMagicCube3DView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		//rotateInfo.type=nChar;
		//Executor();
		CView::OnChar(nChar, nRepCnt, nFlags);
	}

	void CMagicCube3DView::OnSave()
	{
		
	}

	void CMagicCube3DView::OnOpen()
	{	
		
	}


	void CMagicCube3DView::OnSecondShuffle()
	{
		// TODO: 在此添加命令处理程序代码
		secondOrderCube.initialize();

		shuffledNum = 0;

		st = 2;
		secondOrThird = 0;

		SetTimer(timerShuffle2, rotateInterval, NULL);//NULL表示使用OnTimer函数
	}


	void CMagicCube3DView::OnSecondRestore()
	{
		// TODO: 在此添加命令处理程序代码
		st = 2;
		secondOrThird = 0;

		//restoreString.Empty();

		restoreString = ((CMagicCube3DApp*)AfxGetApp())->openGL.secondOrderCube.restore();
		restoredPos = 0;
		//rotate
		SetTimer(timerRestore2, rotateInterval, NULL);
	}


	void CMagicCube3DView::OnSecondInit()
	{
		// TODO: 在此添加命令处理程序代码
		secondOrThird = 2;//有必要吗
		st = 0;

		shuffledNum = 0;

		//secondOrderCube.initialize();
	}


	void CMagicCube3DView::OnRunInit()
	{
		// TODO: 在此添加命令处理程序代码
		secondOrThird = 3;
		st = 0;

		shuffledNum = 0;

		//magicCube.initialize();

	}
