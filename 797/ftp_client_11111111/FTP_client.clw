; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFTP_clientDlg
LastTemplate=CProgressCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FTP_client.h"

ClassCount=5
Class1=CFTP_clientApp
Class2=CFTP_clientDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMySocket
Class5=progress_bar
Resource3=IDD_FTP_CLIENT_DIALOG

[CLS:CFTP_clientApp]
Type=0
HeaderFile=FTP_client.h
ImplementationFile=FTP_client.cpp
Filter=N

[CLS:CFTP_clientDlg]
Type=0
HeaderFile=FTP_clientDlg.h
ImplementationFile=FTP_clientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_DIRNAME

[CLS:CAboutDlg]
Type=0
HeaderFile=FTP_clientDlg.h
ImplementationFile=FTP_clientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FTP_CLIENT_DIALOG]
Type=1
Class=CFTP_clientDlg
ControlCount=25
Control1=IDCANCEL,button,1342242816
Control2=IDC_CONNECT,button,1342242816
Control3=IDC_LISTINFO,listbox,1353777409
Control4=IDC_LISTFILE,listbox,1352728833
Control5=IDC_UPDATE,button,1342242816
Control6=IDC_STOREFILE,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_HOST,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_USERNAME,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_PASSWORD,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_PORT,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_LOADFILE,button,1342242816
Control18=IDC_QUIT,button,1342242816
Control19=IDC_DELEFILE,button,1342242816
Control20=IDC_DELEDIR,button,1342242816
Control21=IDC_PROGRESS,msctls_progress32,1350565888
Control22=IDC_STATIC,static,1342308352
Control23=IDC_CREATEDIR,button,1342242816
Control24=IDC_DIRNAME,edit,1350631552
Control25=IDC_RETURN,button,1342242816

[CLS:CMySocket]
Type=0
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=CMySocket
VirtualFilter=q

[CLS:progress_bar]
Type=0
HeaderFile=progress_bar.h
ImplementationFile=progress_bar.cpp
BaseClass=CProgressCtrl
Filter=W

