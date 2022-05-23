// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// IpFrame.cpp : CInPlaceFrame ���ʵ��
//

#include "stdafx.h"
#include "gui.h"

#include "IpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInPlaceFrame

IMPLEMENT_DYNCREATE(CInPlaceFrame, COleIPFrameWndEx)

BEGIN_MESSAGE_MAP(CInPlaceFrame, COleIPFrameWndEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CInPlaceFrame ����/����

CInPlaceFrame::CInPlaceFrame()
{
}

CInPlaceFrame::~CInPlaceFrame()
{
}

int CInPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleIPFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CResizeBar ʵ�־͵ص�����С��
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // δ�ܴ���
	}

	// Ĭ������£����ע��һ�����ܴ���
	//  �޹صķ���Ŀ�ꡣ�⽫��ֹ
	//  �ϷŶ��󡰴����֧���Ϸŵ������С�
	m_dropTarget.Register(this);

	return 0;
}

// ��ܽ����� OnCreateControlBars �Ա���
//  ����Ӧ�ó���Ĵ����ϴ����ؼ�����pWndFrame �������Ķ�����ܴ��ڣ�
//  ����ʼ�ղ�Ϊ NULL��pWndDoc ���ĵ�����ܴ��ڣ�
//  ������������ SDI Ӧ�ó���ʱΪ NULL��
//  ������Ӧ�ó�����Խ� MFC �ؼ������������������е��κ�һ���ϡ�
BOOL CInPlaceFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// ���ʹ�� pWndDoc���򽫴��Ƴ�
	UNREFERENCED_PARAMETER(pWndDoc);

	// ���ô˴��ڵ������ߣ��Ա㽫��Ϣ���͵���ȷ��Ӧ�ó���
	m_wndToolBar.SetOwner(this);

	// �ڿͻ��˵Ŀ�ܴ����ϴ���������
	if (!m_wndToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_CASTYPE_SRVR_IP))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->DockControlBar(&m_wndToolBar);

	return TRUE;
}

BOOL CInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ

	return COleIPFrameWndEx::PreCreateWindow(cs);
}


// CInPlaceFrame ���

#ifdef _DEBUG
void CInPlaceFrame::AssertValid() const
{
	COleIPFrameWndEx::AssertValid();
}

void CInPlaceFrame::Dump(CDumpContext& dc) const
{
	COleIPFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CInPlaceFrame ����

