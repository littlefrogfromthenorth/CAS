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

// CntrItem.cpp : CguiCntrItem ���ʵ��
//

#include "stdafx.h"
#include "gui.h"

#include "guiDoc.h"
#include "guiView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CguiCntrItem ��ʵ��

IMPLEMENT_SERIAL(CguiCntrItem, COleClientItem, 0)

CguiCntrItem::CguiCntrItem(CguiDoc* pContainer)
	: COleClientItem(pContainer)
{
	// TODO: �ڴ����һ���Թ������
}

CguiCntrItem::~CguiCntrItem()
{
	// TODO: �ڴ˴�����������
}

void CguiCntrItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	COleClientItem::OnChange(nCode, dwParam);

	// �ڱ༭ĳ��ʱ(�͵ر༭����ȫ�򿪽��б༭)��
	//  �����������״̬�ĸ���
	//  �������ݵĿ������״̬�ĸ��ķ��� OnChange ֪ͨ��

	// TODO: ͨ������ UpdateAllViews ʹ������Ч
	//  (�����ʺ�����Ӧ�ó������ʾ)

	GetDocument()->UpdateAllViews(NULL);
		// ����ֻ����������ͼ/����ʾ
}

BOOL CguiCntrItem::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);

	// �͵ؼ����ڼ䣬���������� CguiCntrItem::OnChangeItemPosition
	//  �Ը��ľ͵ش��ڵ�λ�á�
	//  ��ͨ�������ڷ�����
	//  �ĵ��е����ݸ��Ķ����·�Χ�ı����
	//  �͵ص�����С������ġ�
	//
	// �˴���Ĭ�����õ��û��࣬�û��ཫ����
	//  COleClientItem::SetItemRects �Խ�����
	//  �ƶ����µ�λ�á�

	if (!COleClientItem::OnChangeItemPosition(rectPos))
		return FALSE;

	// TODO: ���¸���ľ���/��Χ���ܴ��ڵ��κλ���

	return TRUE;
}

BOOL CguiCntrItem::OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow)
{
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, pFrameWnd);

	if (pMainFrame != NULL)
	{
		ASSERT_VALID(pMainFrame);
		return pMainFrame->OnShowPanes(bShow);
	}

	return FALSE;
}

void CguiCntrItem::OnGetItemPosition(CRect& rPosition)
{
	ASSERT_VALID(this);

	// �͵ؼ����ڼ䣬������ CguiCntrItem::OnGetItemPosition
	//  �Ծ��������λ�á�ͨ����
	//  �þ��λᷴӳ�뼤��������ͼ 
	//  �����ĵ�ǰλ�á����� 
	//  CguiCntrItem::GetActiveView �ɵõ���ͼ��

	// TODO: ���� rPosition �е���ȷ����(�����ر�ʾ)

	CSize size;
	rPosition.SetRectEmpty();
	if (GetExtent(&size, m_nDrawAspect))
	{
		CguiView* pView = GetActiveView();
		ASSERT_VALID(pView);
		if (!pView)
			return;
		CDC *pDC = pView->GetDC();
		ASSERT(pDC);
		if (!pDC)
			return;
		pDC->HIMETRICtoLP(&size);
		rPosition.SetRect(10, 10, size.cx + 10, size.cy + 10);
	}
	else
		rPosition.SetRect(10, 10, 210, 210);
}

void CguiCntrItem::OnActivate()
{
    // ÿ�����ֻ����һ���͵ؼ�����
    CguiView* pView = GetActiveView();
    ASSERT_VALID(pView);
	if (!pView)
		return;
    COleClientItem* pItem = GetDocument()->GetInPlaceActiveItem(pView);
    if (pItem != NULL && pItem != this)
        pItem->Close();
    
    COleClientItem::OnActivate();
}

void CguiCntrItem::OnDeactivateUI(BOOL bUndoable)
{
	COleClientItem::OnDeactivateUI(bUndoable);

    DWORD dwMisc = 0;
    m_lpObject->GetMiscStatus(GetDrawAspect(), &dwMisc);
    if (dwMisc & OLEMISC_INSIDEOUT)
        DoVerb(OLEIVERB_HIDE, NULL);
}

void CguiCntrItem::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	// ���ȵ��û����Զ�ȡ COleClientItem ���ݡ�
	// ��Ϊ���������ô� CguiCntrItem::GetDocument ���ص� m_pDocument ָ�룬
	//  ��������ȵ���
	//  ���� Serialize��
	COleClientItem::Serialize(ar);

	// ���ڴ洢/�����ض��� CguiCntrItem ������
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

BOOL CguiCntrItem::CanActivate()
{
	// �������������ھ͵ر༭ģʽʱ���͵ر༭��Ч�Ҳ���֧�֡�
	//  ��ˣ�����������½��þ͵�
	//  ���
	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;
	ASSERT_KINDOF(COleServerDoc, pDoc);
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COleServerDoc)))
	{
		return FALSE;
	}
	if (pDoc->IsInPlaceActive())
		return FALSE;

	// ��������Ĭ����Ϊ
	return COleClientItem::CanActivate();
}


// CguiCntrItem ���

#ifdef _DEBUG
void CguiCntrItem::AssertValid() const
{
	COleClientItem::AssertValid();
}

void CguiCntrItem::Dump(CDumpContext& dc) const
{
	COleClientItem::Dump(dc);
}
#endif

