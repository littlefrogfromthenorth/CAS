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

// guiDoc.cpp : CguiDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "gui.h"
#endif

#include "guiDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CguiDoc

IMPLEMENT_DYNCREATE(CguiDoc, COleServerDocEx)

BEGIN_MESSAGE_MAP(CguiDoc, COleServerDocEx)
	// ����Ĭ�ϵ� OLE ����ʵ��
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &COleServerDocEx::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, &COleServerDocEx::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, &COleServerDocEx::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, &COleServerDocEx::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &COleServerDocEx::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &COleServerDocEx::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &COleServerDocEx::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()


// CguiDoc ����/����

CguiDoc::CguiDoc()
{
	// ʹ�� OLE �����ļ�
	EnableCompoundFile();

	// TODO: �ڴ����һ���Թ������

}

CguiDoc::~CguiDoc()
{
}

BOOL CguiDoc::OnNewDocument()
{
	if (!COleServerDocEx::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}


// CguiDoc ������ʵ��

COleServerItem* CguiDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem �ɿ�ܵ����Ի�ȡ����ĵ������� COleServerItem��
	//  ֻ�ڱ�Ҫʱ�ŵ�������

	CguiSrvrItem* pItem = new CguiSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}




// CguiDoc ���л�

void CguiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}

	// ���û��� COleServerDocEx ������
	//  �����ĵ��� COleClientItem ��������л���
	COleServerDocEx::Serialize(ar);
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CguiDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CguiDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CguiDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CguiDoc ���

#ifdef _DEBUG
void CguiDoc::AssertValid() const
{
	COleServerDocEx::AssertValid();
}

void CguiDoc::Dump(CDumpContext& dc) const
{
	COleServerDocEx::Dump(dc);
}
#endif //_DEBUG


// CguiDoc ����
