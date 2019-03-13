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
	DDX_Control(pDX, IDC_PROGRESS, progress); //控件传值
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
	GetDlgItem(IDC_RETURN)->EnableWindow(false);//控件初始化
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

  if( !sock_client.Create() )	//socket创建	
	{
		AfxMessageBox("socket创建失败");
		return;
	}

	UpdateData(true);//控件传值更新


	if( !sock_client.Connect(host,port))//socket连接
	{
		AfxMessageBox("socket连接服务器失败");
		return;
	}	
	MySockRecv();
    CString	sendmsg;	//进行服务器的登入
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
     
	temp_buf.TrimLeft();  //得出服务器返回的数字
	temp_buf.TrimRight();
	int pos=temp_buf.Find(" ");
	CString recv_num=temp_buf.Left(pos);
	int num=_ttoi(recv_num);
	if(num==230)
	{                                         //用户登入后，进行相关按钮的设置
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

	AfxMessageBox("用户名或密码错误，请重新输入");

	 
}
}
void CFTP_clientDlg::Parse_list()  //对服务器发送的当前目录的列表进行解析
{


    char  filelist[1024] = "";
	
	if( sock_temp.Receive(filelist,1024)==-1)
	{
		AfxMessageBox("数据接收失败");
		return;
	}
	CString parse_list = filelist;
	
	int  len = parse_list.GetLength();

if(len!=0)
{
              listfile.ResetContent();//对Listbox进行清空
              	CString str=filelist;
	             int i;
	             int a=0;
	            char file_list[32]="";
          while(a<len)
		  {
	       int index_end=str.Find("\r\n",a);
	             CString	temp_str=str.Left(index_end);
	              int k=0;
	 
	            for(i = index_end-1;str.GetAt(i)!= ' ';i--);//向前遍历不为空的元素
				{
	               	for(i = i+1;i<index_end;i++)
					{
		                	file_list[k++] = str.GetAt(i);//得到STring内元素
					}

	                       listfile.AddString(file_list);
		                      memset(file_list,0,32);
		                       a=index_end+2; //更新a的值进行下一行的遍历
				}
		  }
}

         else
		 {
	           listfile.ResetContent();
	            CString word="文件夹为空";
	            listfile.AddString(word);
		 }
}
  
BOOL CFTP_clientDlg::Pasv_mode()//被动模式
{

	if( !sock_temp.Create() )
	{
		AfxMessageBox("sock_temp创建失败");
		return false;
	}

	 CString send_msg;	
     send_msg = "PASV\r\n";
	MySockSend(send_msg);
     char buf_recv[64] = "";
	if( SOCKET_ERROR==sock_client.Receive(buf_recv,64))
	{
		AfxMessageBox("连接已断开，请重新连接服务器");
		sock_temp.Close();
		GetDlgItem(IDC_CONNECT)->EnableWindow(true);//按钮的设置
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
		
		
	CString show_msg = "响应：";
	show_msg=show_msg+buf_recv;
	listinfo.AddString(show_msg);
 
	
	CString str=buf_recv;
	 int index_1,index_2,index_3=0;
  	int i,k=0;
	int new_port;
	index_1=str.ReverseFind(',');//反向查找
	index_2=str.ReverseFind(')');//反向查找
if(index_2!=-1)
{	
	  for(i=0;i<=3;i++)
	{
		index_3=str.Find(',',index_3+1);//查找三次
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
         new_port=256*num1+num2;//计算新的端口号
		port_int1=new_port;
	    memset(str_1,0,10);
}

else
{
       	new_port=port_int1+2;
      	port_int1=new_port;
}

if( !sock_temp.Connect(host,new_port))	//进行新端口的连接
	{
     	AfxMessageBox("请重试");
		sock_temp.Close();
		return false;
	}
	return true;
}

void CFTP_clientDlg::MySockRecv()//接受服务器发来的数据并且显示出来
{
	char buf_recv[1024] = "";
	if(sock_client.Receive(buf_recv,1024)==-1)
	{
		AfxMessageBox("数据接收失败");
		return;
	}
     CString showmsg = "响应：";
	showmsg+= buf_recv;
      temp_buf=buf_recv;
	listinfo.AddString(showmsg);	
}

void CFTP_clientDlg::MySockSend(CString send_msg)//发送命令给服务器及其显示
{
	if( SOCKET_ERROR == sock_client.Send( send_msg,send_msg.GetLength() ) )
	{
		AfxMessageBox("数据发送失败");
		return;
	}
    CString show_msg = "命令：";
	show_msg += send_msg;
	listinfo.AddString(show_msg);
}

void CFTP_clientDlg::OnDblclkListfile() //双击进入服务器文件
{
	// TODO: Add your control notification handler code here

	if( !Pasv_mode() )
		return;
    int index = listfile.GetCurSel();
	CString filename = "";
	listfile.GetText(index,filename);//得到鼠标所点击文件名
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


void CFTP_clientDlg::fileStore(CString filename)//进行文件的下载
{

	
	CFileDialog save_dlg(false,NULL,filename);
    if( save_dlg.DoModal() == IDOK)
	{
	   CString full_name = save_dlg.GetPathName();
	   
	      std::ofstream out;  //创建文件流
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
			 out.write(write_buf,write_size);//写入文件
			 out_size+=write_size;
			 total-=write_size;
			down_progress=float(out_size/file_size);
			 down_rate=int(100*down_progress);
               progress.SetPos(down_rate);//进度条的显示

		 }
		 out.flush();
		 out.close();
		 sock_temp.Close();
		 	AfxMessageBox("下载已完成");
		 progress.SetPos(0);//进度条变为0

	}
	
	else 
	{

         	AfxMessageBox("操作已取消");
	}
}	 
			  
void CFTP_clientDlg::OnUpdate()//显示服务器文件目录
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

void CFTP_clientDlg::OnStorefile() //上传文件
{
	// TODO: Add your control notification handler code here

	CFileDialog open_dlg(true);//打开本地文件

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
		MySockRecv();       //设置流模式传输
	
        sendmsg = "STOR ";
		sendmsg+=file_name;
		sendmsg+="\r\n";
		MySockSend(sendmsg);
		MySockRecv();
 
		std::ifstream in;//创建文件流
	 	 char read_buf[512]="";
		 in.open(full_name,std::ios::binary);
		 in.seekg(0, std::ios::end);
	     int pos=in.tellg();//得到当前文件的指针位置
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
                 sock_temp.Send(read_buf,send_size);//socket发送
				 pos=pos-send_size;
				 progress1+=send_size;
                 rate_progress=float(progress1/length);
				 show_progress=int(100*rate_progress);
				 progress.SetPos(show_progress);//进度条显示
		}
		   
		    in.close();
		    sock_temp.Close();
		 	AfxMessageBox("上传完毕");
	        progress.SetPos(0);
	}
else 
{   
		AfxMessageBox("操作已经取消");
}
}
		 
				  
void CFTP_clientDlg::OnCancel() //关闭客户端
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CFTP_clientDlg::OnLoadfile() //进行文件下载
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
	MySockRecv();  //返回文件大小
	
	 temp_buf.TrimLeft();
	 temp_buf.TrimRight();
	 int pos=temp_buf.Find(" ");
	 CString buf_size=temp_buf.Right(pos);
    file_size=_ttoi(buf_size);  //STring 转换为int

	sendmsg = "RETR ";
	sendmsg+= filename;
	sendmsg+= "\r\n";
	MySockSend(sendmsg);
	MySockRecv();
   fileStore(filename);

}
void CFTP_clientDlg::OnQuit() //关闭连接
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
     GetDlgItem(IDC_QUIT)->EnableWindow(false);//按钮的设置
}
void CFTP_clientDlg::OnDeleteFile() //删除文件
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
	int num=_ttoi(recv_num);//得到服务器的响应码
	if(num==250)  //如果响应码为550 即删除的可能为文件夹
	{
		AfxMessageBox("删除成功");
	}
	 sendmsg="LIST ";
    sendmsg+="\r\n";
	MySockSend(sendmsg);
	MySockRecv();
	Parse_list();
}
void CFTP_clientDlg::OnDeleteDir() //删除目录
{
	// TODO: Add your control notification handler code here
	if( !Pasv_mode() )
		    return;
	int index = listfile.GetCurSel();
	CString filename = "";
	listfile.GetText(index,filename);//得到文件目录名
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
	if(num==250)//不支持删除不为空的文件夹
	{
		AfxMessageBox("删除成功");
}

}

void CFTP_clientDlg::OnCreateDir() //创建文件夹
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
	int num=_ttoi(recv_num);//得到服务器响应码
	if(num==257)
	{
		AfxMessageBox("创建成功");
	}

	sendmsg="LIST ";
    sendmsg+="\r\n";
	MySockSend(sendmsg);
	MySockRecv();
	Parse_list();


	sock_temp.Close();
}

void CFTP_clientDlg::OnReturntoFatherDir() //返回上级目录
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


