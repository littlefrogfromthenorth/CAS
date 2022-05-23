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

// guiView.h : CguiView ��Ľӿ�
//

#pragma once

class CguiCntrItem;

class CguiView : public CView
{
protected: // �������л�����
	CguiView();
	DECLARE_DYNCREATE(CguiView)

// ����
public:
	CguiDoc* GetDocument() const;
	// m_pSelection ����ѡ���ݱ����ڵ�ǰ�� CguiCntrItem �С�
	// �������Ӧ�ó������ֳ�Ա����������
	//  ��ʾĳ��ѡ�������ڲ����� CguiCntrItem �Ķ�����
	//  ѡ����һ�����������ṩ����ѡ��
	//  ���Ƶ�Ŀ��ֻ�ǰ���������

	// TODO: ���ʺ�Ӧ�ó����ѡ������滻��ѡ�����
	CguiCntrItem* m_pSelection;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// ����֧��

// ʵ��
public:
	virtual ~CguiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnFilePrint();
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // guiView.cpp �еĵ��԰汾
inline CguiDoc* CguiView::GetDocument() const
   { return reinterpret_cast<CguiDoc*>(m_pDocument); }
#endif

