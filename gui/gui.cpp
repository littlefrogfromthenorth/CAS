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

// gui.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "gui.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "IpFrame.h"
#include "guiDoc.h"
#include "guiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CguiApp

BEGIN_MESSAGE_MAP(CguiApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CguiApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CguiApp ����

CguiApp::CguiApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("gui.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CguiApp ����

CguiApp theApp;
// ���ɵĴ˱�ʶ����ͳ���϶�������Ӧ�ó�����Ψһ��
// �������Ըѡ��һ���ض��ı�ʶ��������Ը�����

// {6E6E121C-3534-4428-B710-280EEC3DD13D}
static const CLSID clsid =
{ 0x6E6E121C, 0x3534, 0x4428, { 0xB7, 0x10, 0x28, 0xE, 0xEC, 0x3D, 0xD1, 0x3D } };


// CguiApp ��ʼ��

BOOL CguiApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(5);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_CASTYPE,
		RUNTIME_CLASS(CguiDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CguiView));
	if (!pDocTemplate)
		return FALSE;
	pDocTemplate->SetContainerInfo(IDR_CASTYPE_CNTR_IP);
	pDocTemplate->SetServerInfo(
		IDR_CASTYPE_SRVR_EMB, IDR_CASTYPE_SRVR_IP,
		RUNTIME_CLASS(CInPlaceFrame));
	AddDocTemplate(pDocTemplate);
	// �� COleTemplateServer ���ӵ��ĵ�ģ��
	// COleTemplateServer ͨ��ʹ��
	// �ĵ�ģ����ָ������Ϣ��Ϊ���� OLE ����
	// �������ĵ�
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);
	// �����е� OLE ����������ע��Ϊ�������С��⽫����
	//  OLE ���Դ�����Ӧ�ó����д�������
	COleTemplateServer::RegisterAll();
		// ע��: MDI Ӧ�ó���ע�����еķ��������󣬶�����
		// �������ϵ� /Embedding �� /Automation

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
	// ������/��
	m_pMainWnd->DragAcceptFiles();

	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Ӧ�ó������� /Embedding �� /Automation ���������ġ�
	//ʹӦ�ó�����Ϊ�Զ������������С�
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// ����ʾ������
		return TRUE;
	}
	// ʹ�� /Unregserver �� /Unregister ��������Ӧ�ó���ע��
	// ���Ϳ⡣����ע�������� ProcessShellCommand() �з�����
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		UnregisterShellFileTypes();
		m_server.UpdateRegistry(OAT_INPLACE_SERVER, NULL, NULL, FALSE);
	}
	// Ӧ�ó������Զ�����ʽ������������(�� /Register
	// �� /Regserver)�����ġ�����ע�����������Ϳ⡣
	else
	{
		m_server.UpdateRegistry(OAT_INPLACE_SERVER);
	}

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CguiApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CguiApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CguiApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CguiApp �Զ������/���淽��

void CguiApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CguiApp::LoadCustomState()
{
}

void CguiApp::SaveCustomState()
{
}

// CguiApp ��Ϣ�������



