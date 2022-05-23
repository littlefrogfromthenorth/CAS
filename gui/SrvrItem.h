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

// SrvrItem.h : CguiSrvrItem ��Ľӿ�
//

#pragma once

class CguiSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CguiSrvrItem)

// ���캯��
public:
	CguiSrvrItem(CguiDoc* pContainerDoc);

// ����
	CguiDoc* GetDocument() const
		{ return reinterpret_cast<CguiDoc*>(COleServerItem::GetDocument()); }

// ��д
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

// ʵ��
public:
	~CguiSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // Ϊ�ĵ� I/O ��д
};

