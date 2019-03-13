// FTP_clientDlg.h : header file
//

#if !defined(AFX_FTP_CLIENTDLG_H__FABA9B10_B549_46B5_82FF_A08A709B355A__INCLUDED_)
#define AFX_FTP_CLIENTDLG_H__FABA9B10_B549_46B5_82FF_A08A709B355A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFTP_clientDlg dialog

class CFTP_clientDlg : public CDialog
{
// Construction
public:
	BOOL connect_push;
	
	
	int file_size;
	CString temp_buf;
	int port_int1;
	CFTP_clientDlg(CWnd* pParent = NULL);	

	void MySockRecv();					
	void MySockSend(CString send_msg);	

	
	BOOL Pasv_mode();					
	void Parse_list();					
	void fileStore(CString filename);	

// Dialog Data
	//{{AFX_DATA(CFTP_clientDlg)
	enum { IDD = IDD_FTP_CLIENT_DIALOG };
	CListBox	listfile;
	CListBox	listinfo;
	CString	      host;
	CString	       password;
	CString	        username;
	int		        port;
    CString            create_dir;
	CProgressCtrl   progress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTP_clientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON			m_hIcon;
	CSocket			sock_client;
	CSocket			sock_temp;

	// Generated message map functions
	//{{AFX_MSG(CFTP_clientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnDblclkListfile();
	afx_msg void OnUpdate();
	afx_msg void OnStorefile();
	virtual void OnCancel();
	afx_msg void OnLoadfile();
	afx_msg void OnQuit();
	afx_msg void OnDeleteFile();
	afx_msg void OnDeleteDir();
	afx_msg void OnCreateDir();
	afx_msg void OnReturntoFatherDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTP_CLIENTDLG_H__FABA9B10_B549_46B5_82FF_A08A709B355A__INCLUDED_)
