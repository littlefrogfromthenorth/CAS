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

// SrvrItem.cpp : CguiSrvrItem ���ʵ��
//

#include "stdafx.h"
#include "gui.h"

#include "guiDoc.h"
#include "SrvrItem.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CguiSrvrItem ʵ��

IMPLEMENT_DYNAMIC(CguiSrvrItem, COleServerItem)

CguiSrvrItem::CguiSrvrItem(CguiDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
	// TODO: �ڴ����һ���Թ������
	//  (�罫���Ӽ������ʽ��ӵ��������Դ��)
}

CguiSrvrItem::~CguiSrvrItem()
{
	// TODO: �ڴ˴�����������
}

void CguiSrvrItem::Serialize(CArchive& ar)
{
	// ���������Ƶ��������У����ܽ����� CguiSrvrItem::Serialize��
	//  �����
	//  ͨ�� OLE �ص� OnGetClipboardData ���Զ�ִ�С�
	//  ����Ƕ���Ĭ�����ֱ��ί�и��ĵ��� Serialize ������
	//  ���֧�����ӣ���ֻ�����л�
	//  �ĵ���һ���֡�

	if (!IsLinkedItem())
	{
		CguiDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc)
			pDoc->Serialize(ar);
	}
}

BOOL CguiSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// �����������Ƶ�Ӧ�ó���ֻ�Ի����������
	//  ������д������ϣ��֧���������棬��
	//  DVASPECT_THUMBNAIL (ͨ����д OnDrawEx)����Ӧ�޸�
	//  OnGetExtent �Ĵ�ʵ���Դ���
	//  �������档

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// ���� CguiSrvrItem::OnGetExtent �Ա��ȡ�������
	//  HIMETRIC ��Ԫ��ʾ�ķ�Χ���˴���Ĭ��ʵ��
	//  ֻ���ص�Ԫ��Ӳ�������֡�

	// TODO: �滻�������С

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC ��Ԫ

	return TRUE;
}

BOOL CguiSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	if (!pDC)
		return FALSE;

	// ���ʹ�� rSize���򽫴��Ƴ�
	UNREFERENCED_PARAMETER(rSize);

	// TODO: ����ӳ��ģʽ�ͷ�Χ
	//  (�˷�Χͨ����� OnGetExtent ���صĴ�С��ͬ)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// TODO: �ڴ˴���ӻ��ƴ��롣Ҳ������� HIMETRIC ��Χ��
	//  ���л��ƶ�����ͼԪ�ļ��豸������(pDC)�н��С�

	// TODO: ͬʱ����Ƕ��� CguiCntrItem ����

	// ���´��뽫������λ�û��Ƶ�һ���

	// TODO: ��������Ļ��ƴ���󣬽��Ƴ��˴���

	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;

	POSITION pos = pDoc->GetStartPosition();
	CguiCntrItem* pItem = DYNAMIC_DOWNCAST(CguiCntrItem, pDoc->GetNextClientItem(pos));
	if (pItem != NULL)
		pItem->Draw(pDC, CRect(10, 10, 1010, 1010));
	return TRUE;
}


// CguiSrvrItem ���

#ifdef _DEBUG
void CguiSrvrItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void CguiSrvrItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

