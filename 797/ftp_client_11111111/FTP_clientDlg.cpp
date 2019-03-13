// FTP_clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include <fstream>
#include "FTP_client.h"
#include "FTP_clientDlg.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	 GetDlgItem(IDC_QUIT)->EnableWindow(false);
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTP_clientDlg dialog

CFTP_clientDlg::CFTP_clientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFTP_clientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFTP_clientDlg)
	host = "127.0.0.3";
	password = "123";
	username ="xh2019";
	port = 21;
	
	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFTP_clientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFTP_clientDlg)
	DDX_Control(pDX, IDC_LISTFILE, listfile);
	DDX_Control(pDX, IDC_LISTINFO, listinfo);
	DDX_Text(pDX, IDC_HOST, host);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDX_Text(pDX, IDC_USERNAME, username);
	DDX_Text(pDX, IDC_PORT, port);
	DDX_Text(pDX, IDC_DIRNAME, create_dir);
	DDX_Control(pDX, IDC_PROGRESS, progress); //�ؼ���ֵ
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFTP_clientDlg, CDialog)
	//{{AFX_MSG_MAP(CFTP_clientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_LBN_DBLCLK(IDC_LISTFILE, OnDblclkListfile)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_STOREFILE, OnStorefile)
	ON_BN_CLICKED(IDC_LOADFILE, OnLoadfile)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_BN_CLICKED(IDC_BUTTON1, OnDeleteFile)
	ON_BN_CLICKED(IDC_BUTTON2, OnDeleteDir)
	ON_BN_CLICKED(IDC_BUTTON4, OnCreateDir)
	ON_BN_CLICKED(IDC_BUTTON7, OnReturntoFatherDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTP_clientDlg message handlers

BOOL CFTP_clientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
        
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);
	// Set small icon
	
	// TODO: Add extra initialization here
	     progress.SetRange(0,100);
         progress.SetStep(1);
         progress.SetPos(0);
     
	/*/SetDlgItemText(IDC_PORT,NULL);
	SetDlgItemText(IDC_HOST,NULL);
	SetDlgItemText(IDC_PASSWORD,NULL);
	SetDlgItemText(IDC_USERNAME,NULL);/*/
    GetDlgItem(IDC_QUIT)->EnableWindow(false);
	GetDlgItem(IDC_DELEDIR)->EnableWindow(false);
	GetDlgItem(IDC_DELEFILE)->EnableWindow(false);
	GetDlgItem(IDC_CREATEDIR)->EnableWindow(false);
	GetDlgItem(IDC_UPDATE)->EnableWindow(false);
	GetDlgItem(IDC_STOREFILE)->EnableWindow(false);
	GetDlgItem(IDC_LOADFILE)->EnableWindow(false);
	GetDlgItem(IDC_RETURN)->EnableWindow(false);//�ؼ���ʼ��
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFTP_clientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFTP_clientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFTP_clientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFTP_clientDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here

  if( !sock_client.Create() )	//socket����	
	{
		AfxMessageBox("socket����ʧ��");
		return;
	}

	UpdateData(true);//�ؼ���ֵ����


	if( !sock_client.Connect(host,port))//socket����
	{
		AfxMessageBox("socket���ӷ�����ʧ��");
		return;
	}	
	MySockRecv();
    CString	sendmsg;	//���з������ĵ���
    sendmsg="USER ";
	sendmsg+=username;
	sendmsg+="\r\n";	
	MySockSend(sendmsg);
	MySockRecv();
    sendmsg="PASS ";
	sendmsg+=password;
	sendmsg+="\r\n";	
	MySockSend(sendmsg);
	MySockRecv();
     
	temp_buf.TrimLeft();  //�ó����������ص�����
	temp_buf.TrimRight();
	int pos=temp_buf.Find(" ");
	CString recv_num=temp_buf.Left(pos);
	int num=_ttoi(recv_num);
	if(num==230)
	{                                         //�û�����󣬽�����ذ�ť������
	GetDlgItem(IDC_USERNAME)->EnableWindow(false);
	GetDlgItem(IDC_PASSWORD)->EnableWindow(false);
    GetDlgItem(IDC_HOST)->EnableWindow(false);
	GetDlgItem(IDC_PORT)->EnableWindow(false);
	GetDlgItem(IDC_CONNECT)->EnableWindow(false);
	GetDlgItem(IDC_QUIT)->EnableWindow(true);
	GetDlgItem(IDC_QUIT)->EnableWindow(true);
	GetDlgItem(IDC_DELEDIR)->EnableWindow(true);
	GetDlgItem(IDC_DELEFILE)->EnableWindow(true);
	GetDlgItem(IDC_CREATEDIR)->EnableWindow(true);
	GetDlgItem(IDC_UPDATE)->EnableWindow(true);
	GetDlgItem(IDC_STOREFILE)->EnableWindow(true);
	GetDlgItem(IDC_LOADFILE)->EnableWindow(true);
	GetDlgItem(IDC_RETURN)->EnableWindow(true);
	}
else{
    GetDlgItem(IDC_USERNAME)->EnableWindow(true);
	GetDlgItem(IDC_PASSWORD)->EnableWindow(true);
    GetDlgItem(IDC_HOST)->EnableWindow(false);
	GetDlgItem(IDC_PORT)->EnableWindow(false);
	GetDlgItem(IDC_CONNECT)->EnableWindow(true);

	AfxMessageBox("�û����������������������");

	 
}
}
void CFTP_clientDlg::Parse_list()  //�Է��������͵ĵ�ǰĿ¼���б���н���
{


    char  filelist[1024] = "";
	
	if( sock_temp.Receive(filelist,1024)==-1)
	{
		AfxMessageBox("���ݽ���ʧ��");
		return;
	}
	CString parse_list = filelist;
	
	int  len = parse_list.GetLength();

if(len!=0)
{
              listfile.ResetContent();//��Listbox�������
              	CString str=filelist;
	             int i;
	             int a=0;
	            char file_list[32]="";
          while(a<len)
		  {
	       int index_end=str.Find("\r\n",a);
	             CString	temp_str=str.Left(index_end);
	              int k=0;
	 
	            for(i = index_end-1;str.GetAt(i)!= ' ';i--);//��ǰ������Ϊ�յ�Ԫ��
				{
	               	for(i = i+1;i<index_end;i++)
					{
		                	file_list[k++] = str.GetAt(i);//�õ�STring��Ԫ��
					}

	                       listfile.AddString(file_list);
		                      memset(file_list,0,32);
		                       a=index_end+2; //����a��ֵ������һ�еı���
				}
		  }
}

         else
		 {
	           listfile.ResetContent();
	            CString word="�ļ���Ϊ��";
	            listfile.AddString(word);
		 }
}
  
BOOL CFTP_clientDlg::Pasv_mode()//����ģʽ
{

	if( !sock_temp.Create() )
	{
		AfxMessageBox("sock_temp����ʧ��");
		return false;
	}

	 CString send_msg;	
     send_msg = "PASV\r\n";
	MySockSend(send_msg);
     char buf_recv[64] = "";
	if( SOCKET_ERROR==sock_client.Receive(buf_recv,64))
	{
		AfxMessageBox("�����ѶϿ������������ӷ�����");
		sock_temp.Close();
		GetDlgItem(IDC_CONNECT)->EnableWindow(true);//��ť������
		GetDlgItem(IDC_QUIT)->EnableWindow(false);
	    GetDlgItem(IDC_DELEDIR)->EnableWindow(false);
	   GetDlgItem(IDC_DELEFILE)->EnableWindow(false);
	   GetDlgItem(IDC_CREATEDIR)->EnableWindow(false);
	   GetDlgItem(IDC_UPDATE)->EnableWindow(false);
	   GetDlgItem(IDC_STOREFILE)->EnableWindow(false);
	   GetDlgItem(IDC_LOADFILE)->EnableWindow(false);
	   GetDlgItem(IDC_RETURN)->EnableWindow(false);
	   return false;
	}
		
		
	CString show_msg = "��Ӧ��";
	show_msg=show_msg+buf_recv;
	listinfo.AddString(show_msg);
 
	
	CString str=buf_recv;
	 int index_1,index_2,index_3=0;
  	int i,k=0;
	int new_port;
	index_1=str.ReverseFind(',');//�������
	index_2=str.ReverseFind(')');//�������
if(index_2!=-1)
{	
	  for(i=0;i<=3;i++)
	{
		index_3=str.Find(',',index_3+1);//��������
	}

	char str_1[10]="";

     for(i=index_3+1;i<index_1;i++)
	 {
	    	str_1[k++]=str.GetAt(i);
	 }
		k=0;
	    int num1=atoi(str_1);
		memset(str_1,0,10);
		for(i=index_1+1;i<index_2;i++)
		{
		   str_1[k++]=str.GetAt(i);
		 }
		int num2=atoi(str_1);
         new_port=256*num1+num2;//�����µĶ˿ں�
		port_int1=new_port;
	    memset(str_1,0,10);
}

else
{
       	new_port=port_int1+2;
      	port_int1=new_port;
}

if( !sock_temp.Connect(host,new_port))	//�����¶˿ڵ�����
	{
     	AfxMessageBox("������");
		sock_temp.Close();
		return false;
	}
	return true;
}

void CFTP_clientDlg::MySockRecv()//���ܷ��������������ݲ�����ʾ����
{
	char buf_recv[1024] = "";
	if(sock_client.Receive(buf_recv,1024)==-1)
	{
		AfxMessageBox("���ݽ���ʧ��");
		return;
	}
     CString showmsg = "��Ӧ��";
	showmsg+= buf_recv;
      temp_buf=buf_recv;
	listinfo.AddString(showmsg);	
}

void CFTP_clientDlg::MySockSend(CString send_msg)//���������������������ʾ
{
	if( SOCKET_ERROR == sock_client.Send( send_msg,send_msg.GetLength() ) )
	{
		AfxMessageBox("���ݷ���ʧ��");
		return;
	}
    CString show_msg = "���";
	show_msg += send_msg;
	listinfo.AddString(show_msg);
}

void CFTP_clientDlg::OnDblclkListfile() //˫������������ļ�
{
	// TODO: Add your control notification handler code here

	if( !Pasv_mode() )
		return;
    int index = listfile.GetCurSel();
	CString filename = "";
	listfile.GetText(index,filename);//�õ����������ļ���
	CString sendmsg = "CWD ";
	 sendmsg+= filename;
	sendmsg+= "\r\n";
	MySockSend(sendmsg);
	MySockRecv();
   sendmsg = "LIST ";
   sendmsg+= "\r\n";
	MySockSend(sendmsg);
	MySockRecv();
	Parse_list();
	sock_temp.Close();
}


void CFTP_clientDlg::fileStore(CString filename)//�����ļ�������
{

	
	CFileDialog save_dlg(false,NULL,filename);
    if( save_dlg.DoModal() == IDOK)
	{
	   CString full_name = save_dlg.GetPathName();
	   
	      std::ofstream out;  //�����ļ���
		  out.open(full_name,std::ios::binary);
		  char write_buf[128]="";
		  int write_size;
		  int  out_size=0;
		  int total=file_size;
		  float down_progress;
		  int down_rate;

         while(total>0)
		 {       
			 out.clear();
             memset(write_buf,0,128);
             sock_temp.Receive(write_buf,128);
			 write_size=total<128?total:128;
			 out.write(write_buf,write_size);//д���ļ�
			 out_size+=write_size;
			 total-=write_size;
			down_progress=float(out_size/file_size);
			 down_rate=int(100*down_progress);
               progress.SetPos(down_rate);//����������ʾ

		 }
		 out.flush();
		 out.close();
		 sock_temp.Close();
		 	AfxMessageBox("���������");
		 progress.SetPos(0);//��������Ϊ0

	}
	
	else 
	{

         	AfxMessageBox("������ȡ��");
	}
}	 
			  
void CFTP_clientDlg::OnUpdate()//��ʾ�������ļ�Ŀ¼
{
	// TODO: Add your control notification handler code here


	if( !Pasv_mode() )
		return;
	CString send_msg = "LIST\r\n";
	MySockSend(send_msg);
	MySockRecv();
 	Parse_list();
    sock_temp.Close();
}

void CFTP_clientDlg::OnStorefile() //�ϴ��ļ�
{
	// TODO: Add your control notification handler code here

	CFileDialog open_dlg(true);//�򿪱����ļ�

	CString full_name;	
	CString file_name;
	

	if(open_dlg.DoModal() == IDOK)
	{	
			full_name = open_dlg.GetPathName();
	        file_name= open_dlg.GetFileName();
	if( !Pasv_mode() )
			return;
        CString sendmsg;

		sendmsg = "MODE ";
		sendmsg+= "S\r\n";
		MySockSend(sendmsg);
		MySockRecv();       //������ģʽ����
	
        sendmsg = "STOR ";
		sendmsg+=file_name;
		sendmsg+="\r\n";
		MySockSend(sendmsg);
		MySockRecv();
 
		std::ifstream in;//�����ļ���
	 	 char read_buf[512]="";
		 in.open(full_name,std::ios::binary);
		 in.seekg(0, std::ios::end);
	     int pos=in.tellg();//�õ���ǰ�ļ���ָ��λ��
	      int length=pos;
		 int read_size=0;
		 int progress1=0;
		 float rate_progress;
		 int   show_progress;
		 while(pos>0)
		 {
			     in.clear();
			     memset(read_buf,0,512);
			     in.seekg(read_size,std::ios::beg);
		         in.read(read_buf,512);
				 int send_size=pos<512?pos:512;
				 read_size=read_size+send_size;
                 sock_temp.Send(read_buf,send_size);//socket����
				 pos=pos-send_size;
				 progress1+=send_size;
                 rate_progress=float(progress1/length);
				 show_progress=int(100*rate_progress);
				 progress.SetPos(show_progress);//��������ʾ
		}
		   
		    in.close();
		    sock_temp.Close();
		 	AfxMessageBox("�ϴ����");
	        progress.SetPos(0);
	}
else 
{   
		AfxMessageBox("�����Ѿ�ȡ��");
}
}
		 
				  
void CFTP_clientDlg::OnCancel() //�رտͻ���
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CFTP_clientDlg::OnLoadfile() //�����ļ�����
{
	// TODO: Add your control notification handler code here

	if( !Pasv_mode() )
		return;
	int index = listfile.GetCurSel();
	CString filename = "";
	listfile.GetText(index,filename);
	CString sendmsg;
   sendmsg = "TYPE ";
    sendmsg += "I\r\n";
	MySockSend(sendmsg);
	MySockRecv();

     sendmsg = "MODE ";
		sendmsg+= "S\r\n";
		MySockSend(sendmsg);
		MySockRecv();
	
	sendmsg = "SIZE ";
	sendmsg += filename;
	sendmsg += "\r\n";
	MySockSend(sendmsg);
	MySockRecv();  //�����ļ���С
	
	 temp_buf.TrimLeft();
	 temp_buf.TrimRight();
	 int pos=temp_buf.Find(" ");
	 CString buf_size=temp_buf.Right(pos);
    file_size=_ttoi(buf_size);  //STring ת��Ϊint

	sendmsg = "RETR ";
	sendmsg+= filename;
	sendmsg+= "\r\n";
	MySockSend(sendmsg);
	MySockRecv();
   fileStore(filename);

}
void CFTP_clientDlg::OnQuit() //�ر�����
{
	// TODO: Add your control notification handler code here

	CString send_msg = "QUIT\r\n";
	MySockSend(send_msg);
	MySockRecv();
    sock_client.Close();
	GetDlgItem(IDC_CONNECT)->EnableWindow(true);
	GetDlgItem(IDC_DELEDIR)->EnableWindow(false);
	GetDlgItem(IDC_DELEFILE)->EnableWindow(false);
	GetDlgItem(IDC_CREATEDIR)->EnableWindow(false);
	GetDlgItem(IDC_UPDATE)->EnableWindow(false);
	GetDlgItem(IDC_STOREFILE)->EnableWindow(false);
	GetDlgItem(IDC_LOADFILE)->EnableWindow(false);
	GetDlgItem(IDC_RETURN)->EnableWindow(false);
     GetDlgItem(IDC_QUIT)->EnableWindow(false);//��ť������
}
void CFTP_clientDlg::OnDeleteFile() //ɾ���ļ�
{
	// TODO: Add your control notification handler code here
	if( !Pasv_mode() )
		return;
	int index =listfile.GetCurSel();
	CString filename = "";
	listfile.GetText(index,filename);
	CString sendmsg;
     sendmsg = "DELE ";
	sendmsg += filename;
	sendmsg += "\r\n";
	MySockSend(sendmsg);
	MySockRecv();
	temp_buf.TrimLeft();
	temp_buf.TrimRight();
	int pos=temp_buf.Find(" ");
	CString recv_num=temp_buf.Left(pos);
	int num=_ttoi(recv_num);//�õ�����������Ӧ��
	if(num==250)  //�����Ӧ��Ϊ550 ��ɾ���Ŀ���Ϊ�ļ���
	{
		AfxMessageBox("ɾ���ɹ�");
	}
	 sendmsg="LIST ";
    sendmsg+="\r\n";
	MySockSend(sendmsg);
	MySockRecv();
	Parse_list();
}
void CFTP_clientDlg::OnDeleteDir() //ɾ��Ŀ¼
{
	// TODO: Add your control notification handler code here
	if( !Pasv_mode() )
		    return;
	int index = listfile.GetCurSel();
	CString filename = "";
	listfile.GetText(index,filename);//�õ��ļ�Ŀ¼��
	CString sendmsg;
	 sendmsg = "RMD ";
	sendmsg += filename;
	sendmsg += "\r\n";
	MySockSend(sendmsg);
	MySockRecv();
	temp_buf.TrimLeft();
	temp_buf.TrimRight();
	int pos=temp_buf.Find(" ");
	CString recv_num=temp_buf.Left(pos);
	int num=_ttoi(recv_num);
	sendmsg="LIST ";
     sendmsg+="\r\n";
	MySockSend(sendmsg);
	MySockRecv();
	Parse_list();
	if(num==250)//��֧��ɾ����Ϊ�յ��ļ���
	{
		AfxMessageBox("ɾ���ɹ�");
}

}

void CFTP_clientDlg::OnCreateDir() //�����ļ���
{
	// TODO: Add your control notification handler code here
    if( !Pasv_mode() )
		    return;
	CString sendmsg = "MKD ";
	UpdateData(true);
    sendmsg+=create_dir;
	sendmsg+="\r\n";
    MySockSend(sendmsg);
	MySockRecv();
	temp_buf.TrimLeft();
	temp_buf.TrimRight();
	int pos=temp_buf.Find(" ");
	CString recv_num=temp_buf.Left(pos);
	int num=_ttoi(recv_num);//�õ���������Ӧ��
	if(num==257)
	{
		AfxMessageBox("�����ɹ�");
	}

	sendmsg="LIST ";
    sendmsg+="\r\n";
	MySockSend(sendmsg);
	MySockRecv();
	Parse_list();


	sock_temp.Close();
}

void CFTP_clientDlg::OnReturntoFatherDir() //�����ϼ�Ŀ¼
{
	// TODO: Add your control notification handler code here
	if( !Pasv_mode() )
		    return;
	CString sendmsg;
	sendmsg="CWD ";
    sendmsg+="..";
    sendmsg += "\r\n";
	MySockSend(sendmsg);
	MySockRecv();
    sendmsg="LIST ";
    sendmsg+="\r\n";
	MySockSend(sendmsg);
	MySockRecv();
	Parse_list();
}


