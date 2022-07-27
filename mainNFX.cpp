// 注意: 本项目的所有源文件都必须是 UTF-8 编码

#include <iostream>
#include <typeinfo> 
#include <map>
#include <time.h>
#include <mirai.h>
#include "myheader.h"
#include <windows.h>
#include <Winsock2.h>
#include <wininet.h>
#include <winternl.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <codecvt>
#include <locale>
#pragma comment(lib, "Wininet.lib")

//#define _AFXDLL
//#include <SDKDDKVer.h>
//#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的
// 关闭 MFC 的一些常见且经常可放心忽略的隐藏警告消息
//#define _AFX_ALL_WARNINGS
//#include <afxwin.h>         // MFC 核心组件和标准组件
//#include <afxext.h>         // MFC 扩展
//#include <afxdisp.h>        // MFC 自动化类

using namespace std;
using namespace Cyan;
using std::locale;

ofstream syslog("X:\\WMProject1217\\WMBot\\Log\\log.wmlog", ios::app);
ofstream textout("X:\\WMProject1217\\WMBot\\Memory\\textout.wmst", ios::app);

typedef struct systask {
	bool init;
	double id;
	string name;
	string description;
	string shot[8];
};
typedef struct wmuser {
	string useruid;
	string firstname;
	string lastname;
	string permission;
	string coin;
	string exp;
	string language;
};
string service_LxBotAutoSign = "END";
systask tasklist[255];

string UnicodeToANSI(const std::wstring& wstr)
{
	std::string ret;
	std::mbstate_t state = {};
	const wchar_t* src = wstr.data();
	size_t len = std::wcsrtombs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) {
		std::unique_ptr< char[] > buff(new char[len + 1]);
		len = std::wcsrtombs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) {
			ret.assign(buff.get(), len);
		}
	}
	return ret;
}

wstring ANSIToUnicode(const std::string& str)
{
	std::wstring ret;
	std::mbstate_t state = {};
	const char* src = str.data();
	size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) {
		std::unique_ptr< wchar_t[] > buff(new wchar_t[len + 1]);
		len = std::mbsrtowcs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) {
			ret.assign(buff.get(), len);
		}
	}
	return ret;
}

string UnicodeToUTF8(const std::wstring& wstr)
{
	std::string ret;
	try {
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.to_bytes(wstr);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return ret;
}

wstring UTF8ToUnicode(const std::string& str)
{
	std::wstring ret;
	try {
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.from_bytes(str);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return ret;
}

string UTF8ToANSI(const std::string& str)
{
	return UnicodeToANSI(UTF8ToUnicode(str));
}

string ANSIToUTF8(const std::string& str)
{
	return UnicodeToUTF8(ANSIToUnicode(str));
}

string GetCmdInfo(const char* pszCmd)
{
	string returndd, retfdds;
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return FALSE;
	}
	char command[1024];    //长达1K的命令行，够用了吧  
	strcpy(command, "Cmd.exe /C ping ");
	strcat(command, pszCmd);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;            //把创建进程的标准错误输出重定向到管道输入  
	si.hStdOutput = hWrite;           //把创建进程的标准输出重定向到管道输入  
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//关键步骤，CreateProcess函数参数意义请查阅MSDN  
	if (!CreateProcess(NULL, command, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return "非预期错误:在创建进程时出错";
	}
	CloseHandle(hWrite);
	char buffer[4096] = { 0 };          //用4K的空间来存储输出的内容，只要不是显示文件内容，一般情况下是够用了。  
	DWORD bytesRead;
	int iff = 0;
	while (true)
	{
		if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)
			break;
		//buffer中就是执行的结果，可以保存到文本，也可以直接输出  
		returndd = buffer;   //这里是弹出对话框显示  
		if (iff == 0) {
			retfdds = buffer;
			retfdds = retfdds.substr(0,size(retfdds)-1);
		}
		iff = iff + 1;
	}
	CloseHandle(hRead);
	string ffsfdsfa;
	returndd = retfdds + returndd;
	ffsfdsfa = ANSIToUTF8(returndd);
	return ffsfdsfa;
}

string GetCmdInfoI(const char* pszCmd)
{
	string returndd, retfdds;
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return FALSE;
	}
	char command[1024];    //长达1K的命令行，够用了吧  
	strcpy(command, "Cmd.exe /C nslookup ");
	strcat(command, pszCmd);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;            //把创建进程的标准错误输出重定向到管道输入  
	si.hStdOutput = hWrite;           //把创建进程的标准输出重定向到管道输入  
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//关键步骤，CreateProcess函数参数意义请查阅MSDN  
	if (!CreateProcess(NULL, command, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return "非预期错误:在创建进程时出错";
	}
	CloseHandle(hWrite);
	char buffer[4096] = { 0 };          //用4K的空间来存储输出的内容，只要不是显示文件内容，一般情况下是够用了。  
	DWORD bytesRead;
	int iff = 0;
	while (true)
	{
		if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)
			break;
		//buffer中就是执行的结果，可以保存到文本，也可以直接输出  
		stringstream cct;
		cct << buffer;
		returndd = cct.str();   //这里是弹出对话框显示  
	}
	CloseHandle(hRead);
	string ffsfdsfa;
	returndd = retfdds + returndd;
	ffsfdsfa = ANSIToUTF8(returndd);
	return ffsfdsfa;
}

int systemlog(string strdata) {
	time_t timenow = time(0);
	string textrc;
	stringstream strStreamrc;
	tm* ltm = localtime(&timenow);
	strStreamrc << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " ";
	strStreamrc << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
	textrc = strStreamrc.str();
	cout << "[" << UTF8ToANSI(textrc) << "]" << UTF8ToANSI(strdata) << endl;
	syslog << "[" << textrc << "]" << strdata << endl;
	return 0;
}
/*
int getScreenCapture()
{
	//获取桌面窗口的CDC
	CDC* pdeskdc = CDC::FromHandle(GetDC(NULL));
	CRect re;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pdeskdc, 1024, 768);
	//创建一个兼容的内存画板
	CDC memorydc;
	memorydc.CreateCompatibleDC(pdeskdc);

	//选中画笔
	CBitmap* pold = memorydc.SelectObject(&bmp);

	//绘制图像
	memorydc.BitBlt(0, 0, re.Width(), re.Height(), pdeskdc, 0, 0, SRCCOPY);

	//获取鼠标位置，然后添加鼠标图像
	CPoint po;
	GetCursorPos(&po);
	HICON hinco = (HICON)GetCursor();
	memorydc.DrawIcon(po.x - 10, po.y - 10, hinco);
	//选中原来的画笔
	memorydc.SelectObject(pold);
	BITMAP bit;
	bmp.GetBitmap(&bit);
	//	DWORD size = bit.bmWidth * bit.bmHeight ;

		//定义 图像大小（单位：byte）
	DWORD size = bit.bmWidthBytes * bit.bmHeight;
	LPSTR lpdata = (LPSTR)GlobalAlloc(GPTR, size);

	//后面是创建一个bmp文件的必须文件头，想要了解可以参考msdn

	BITMAPINFOHEADER pbitinfo;
	pbitinfo.biBitCount = 24;
	pbitinfo.biClrImportant = 0;
	pbitinfo.biCompression = BI_RGB;
	pbitinfo.biHeight = bit.bmHeight;
	pbitinfo.biPlanes = 1;
	pbitinfo.biSize = sizeof(BITMAPINFOHEADER);
	pbitinfo.biSizeImage = size;
	pbitinfo.biWidth = bit.bmWidth;
	pbitinfo.biXPelsPerMeter = 0;
	pbitinfo.biYPelsPerMeter = 0;

	GetDIBits(pdeskdc->m_hDC, bmp, 0, pbitinfo.biHeight, lpdata,
		(BITMAPINFO*)&pbitinfo, DIB_RGB_COLORS);

	BITMAPFILEHEADER bfh;
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType = ((WORD)('M' << 8) | 'B');
	bfh.bfSize = 54 + size;
	bfh.bfOffBits = 54;

	//写入文件

	CFile file;
	if (file.Open("./Temp/Screen.bmp", CFile::modeCreate | CFile::modeWrite))
	{
		file.Write(&bfh, sizeof(BITMAPFILEHEADER));
		file.Write(&pbitinfo, sizeof(BITMAPINFOHEADER));
		file.Write(lpdata, size);
		file.Close();
	}
	GlobalFree(lpdata);
	return 0;
}*/

string readpermissiongroup(string groupgid) {
	char textretvaltmp[255] = { "" };
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\Group\\" << groupgid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	GetPrivateProfileString("WMBot", "Permission", "None", textretvaltmp, sizeof(textretvaltmp), textretvalret);
	return ANSIToUTF8(textretvaltmp);
}

int writepermissiongroup(string groupgid,string permission) {
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp,strtttttp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\Group\\" << groupgid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, textretvalret);
	const char* temppre;
	strtttttp << UTF8ToANSI(permission);
	textretvaldd = strtttttp.str();
	textretvalret = textretvaldd.c_str();
	temppre = textretvalret;
	WritePrivateProfileString("WMBot", "Permission", temppre, lpPath);
	return 0;
}

string readpermissionuser(string useruid) {
	char textretvaltmp[255] = { "" };
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();

	GetPrivateProfileString("WMBot", "Permission", "None", textretvaltmp, sizeof(textretvaltmp), textretvalret);
	strStreamtmp.clear();
	return ANSIToUTF8(textretvaltmp);
}

int writepermissionuser(string useruid, string permission) {
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp, strtttttp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, textretvalret);
	const char* temppre;
	strtttttp << UTF8ToANSI(permission);
	textretvaldd = strtttttp.str();
	textretvalret = textretvaldd.c_str();
	temppre = textretvalret;
	WritePrivateProfileString("WMBot", "Permission", temppre, lpPath);
	return 0;
}

string readcoinuser(string useruid) {
	char textretvaltmp[255] = { "" };
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	GetPrivateProfileString("WMBot", "coin", "-1", textretvaltmp, sizeof(textretvaltmp), textretvalret);
	return ANSIToUTF8(textretvaltmp);
}

int writecoinuser(string useruid, string coin) {
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp, strtttttp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, textretvalret);
	const char* temppre;
	strtttttp << UTF8ToANSI(coin);
	textretvaldd = strtttttp.str();
	textretvalret = textretvaldd.c_str();
	temppre = textretvalret;
	WritePrivateProfileString("WMBot", "coin", temppre, lpPath);
	return 0;
}

string readexpuser(string useruid) {
	char textretvaltmp[255] = { "" };
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	GetPrivateProfileString("WMBot", "exp", "-1", textretvaltmp, sizeof(textretvaltmp), textretvalret);
	return ANSIToUTF8(textretvaltmp);
}

int writeexpuser(string useruid, string exp) {
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp, strtttttp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, textretvalret);
	const char* temppre;
	strtttttp << UTF8ToANSI(exp);
	textretvaldd = strtttttp.str();
	textretvalret = textretvaldd.c_str();
	temppre = textretvalret;
	WritePrivateProfileString("WMBot", "exp", temppre, lpPath);
	return 0;
}

string readfirstnameuser(string useruid) {
	char textretvaltmp[255] = { "" };
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	GetPrivateProfileString("WMBot", "UserName", "", textretvaltmp, sizeof(textretvaltmp), textretvalret);
	return ANSIToUTF8(textretvaltmp);
}

int writefirstnameuser(string useruid, string firstname) {
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp, strtttttp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, textretvalret);
	const char* temppre;
	strtttttp << UTF8ToANSI(firstname);
	textretvaldd = strtttttp.str();
	textretvalret = textretvaldd.c_str();
	temppre = textretvalret;
	WritePrivateProfileString("WMBot", "UserName", temppre, lpPath);
	return 0;
}

string readlastnameuser(string useruid) {
	char textretvaltmp[255] = { "" };
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	GetPrivateProfileString("WMBot", "lastname", "", textretvaltmp, sizeof(textretvaltmp), textretvalret);
	return ANSIToUTF8(textretvaltmp);
}

int writelastnameuser(string useruid, string lastname) {
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp, strtttttp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, textretvalret);
	const char* temppre;
	strtttttp << UTF8ToANSI(lastname);
	textretvaldd = strtttttp.str();
	textretvalret = textretvaldd.c_str();
	temppre = textretvalret;
	WritePrivateProfileString("WMBot", "lastname", temppre, lpPath);
	return 0;
}

string readlanguageuser(string useruid) {
	char textretvaltmp[255] = { "" };
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	GetPrivateProfileString("WMBot", "Language", "zh-cn", textretvaltmp, sizeof(textretvaltmp), textretvalret);
	return ANSIToUTF8(textretvaltmp);
}

int writelanguageuser(string useruid, string language) {
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp, strtttttp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, textretvalret);
	const char* temppre;
	strtttttp << UTF8ToANSI(language);
	textretvaldd = strtttttp.str();
	textretvalret = textretvaldd.c_str();
	temppre = textretvalret;
	WritePrivateProfileString("WMBot", "Language", temppre, lpPath);
	return 0;
}

string randomgirl(string username) {
	std::string strTemp = "http://wemakeli.net.wm/api/randomgirl.php";
	char* pChar;
	int len = strTemp.length();
	pChar = new char[len + 1];
	strcpy(pChar, strTemp.c_str());
	int gold = 0;
	string sGold = "gold";
	string text;
	char* hostname = "wemakeli.net.wm";
	char* api = pChar;
	char* parameters = "test";
	WSADATA WsaData;
	WSAStartup(0x0101, &WsaData);
	//初始化socket
	struct hostent* host_addr = gethostbyname("wemakeli.net.wm");
	if (host_addr == NULL)
	{
		return "Unable to locate host";
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons((unsigned short)80);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		return "-100";
	}
	//建立连接
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sockaddr_in)) == -1)
	{
		return "connect failed";
	}
	//初始化发送信息
	char send_str[2048] = { 0 };
	//头信息
	strcat(send_str, "POST ");
	strcat(send_str, api);
	strcat(send_str, " HTTP/1.1\r\n");
	strcat(send_str, "Host: ");
	strcat(send_str, hostname);
	strcat(send_str, "\r\n");
	strcat(send_str, "Connection: keep-alive\r\n");
	char content_header[100];
	sprintf(content_header, "Content-Length: %d\r\n", strlen(parameters));
	strcat(send_str, content_header);
	strcat(send_str, "Cache-Control: max-age=0\r\n");
	strcat(send_str, "Origin: http://www.hao123.com\r\n");
	strcat(send_str, "User-Agent: Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/15.0.849.0 Safari/535.1\r\n");
	strcat(send_str, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(send_str, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n");
	strcat(send_str, "Referer: http://www.hao123.com/\r\n");
	strcat(send_str, "Accept-Encoding: gzip,deflate,sdch\r\n");
	strcat(send_str, "Accept-Language: zh-CN,zh;q=0.8\r\n");
	//内容信息
	strcat(send_str, "\r\n");
	strcat(send_str, parameters);
	if (send(sock, send_str, strlen(send_str), 0) == -1)
	{
		return "send failed";
	}
	//获取返回信息
	char recv_str[4096] = { 0 };
	if (recv(sock, recv_str, sizeof(recv_str), 0) == -1)
	{
		return "recv failed";
	}
	//char *temp = (char*)ptr;
	string sTemp = recv_str;
	string sOutTemp = "";
	string::size_type idx = sTemp.find(sGold);
	string::size_type xx = sTemp.find_last_of("OK");
	string::size_type yy = sTemp.find_first_of("OK");
	text = sTemp;
	cout << text;
	if (idx != string::npos) {
		sOutTemp = sTemp.substr(idx + 4, 4);
		text = sOutTemp;
	}
	WSACleanup();
	string s1f = text;
	int startf = s1f.find_first_of('>');
	int endf = s1f.find_last_of('<');
	string s2f = s1f.substr(startf + 1, endf - startf - 1);
	text = s2f;
	text.replace(text.find("#username#"), 10, username);
	return text;
}

string randomsplashes() {
	std::string strTemp = "http://wemakeli.net.wm/api/splashes.php";
	char* pChar;
	int len = strTemp.length();
	pChar = new char[len + 1];
	strcpy(pChar, strTemp.c_str());
	int gold = 0;
	string sGold = "gold";
	string text;
	char* hostname = "wemakeli.net.wm";
	char* api = pChar;
	char* parameters = "test";
	WSADATA WsaData;
	WSAStartup(0x0101, &WsaData);
	//初始化socket
	struct hostent* host_addr = gethostbyname("wemakeli.net.wm");
	if (host_addr == NULL)
	{
		return "Unable to locate host";
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons((unsigned short)80);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		return "-100";
	}
	//建立连接
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sockaddr_in)) == -1)
	{
		return "connect failed";
	}
	//初始化发送信息
	char send_str[2048] = { 0 };
	//头信息
	strcat(send_str, "POST ");
	strcat(send_str, api);
	strcat(send_str, " HTTP/1.1\r\n");
	strcat(send_str, "Host: ");
	strcat(send_str, hostname);
	strcat(send_str, "\r\n");
	strcat(send_str, "Connection: keep-alive\r\n");
	char content_header[100];
	sprintf(content_header, "Content-Length: %d\r\n", strlen(parameters));
	strcat(send_str, content_header);
	strcat(send_str, "Cache-Control: max-age=0\r\n");
	strcat(send_str, "Origin: http://www.hao123.com\r\n");
	strcat(send_str, "User-Agent: Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/15.0.849.0 Safari/535.1\r\n");
	strcat(send_str, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(send_str, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n");
	strcat(send_str, "Referer: http://www.hao123.com/\r\n");
	strcat(send_str, "Accept-Encoding: gzip,deflate,sdch\r\n");
	strcat(send_str, "Accept-Language: zh-CN,zh;q=0.8\r\n");
	//内容信息
	strcat(send_str, "\r\n");
	strcat(send_str, parameters);
	if (send(sock, send_str, strlen(send_str), 0) == -1)
	{
		return "send failed";
	}
	//获取返回信息
	char recv_str[4096] = { 0 };
	if (recv(sock, recv_str, sizeof(recv_str), 0) == -1)
	{
		return "recv failed";
	}
	//char *temp = (char*)ptr;
	string sTemp = recv_str;
	string sOutTemp = "";
	string::size_type idx = sTemp.find(sGold);
	string::size_type xx = sTemp.find_last_of("OK");
	string::size_type yy = sTemp.find_first_of("OK");
	text = sTemp;
	if (idx != string::npos) {
		sOutTemp = sTemp.substr(idx + 4, 4);
		text = sOutTemp;
	}
	WSACleanup();
	string s1f = text;
	int startf = s1f.find_first_of('>');
	int endf = s1f.find_last_of('<');
	string s2f = s1f.substr(startf + 1, endf - startf - 1);
	text = s2f;
	return text;
}

string randomtarot() {
	std::string strTemp = "http://wemakeli.net.wm/api/tarot.php";
	char* pChar;
	int len = strTemp.length();
	pChar = new char[len + 1];
	strcpy(pChar, strTemp.c_str());
	int gold = 0;
	string sGold = "gold";
	string text;
	char* hostname = "wemakeli.net.wm";
	char* api = pChar;
	char* parameters = "test";
	WSADATA WsaData;
	WSAStartup(0x0101, &WsaData);
	//初始化socket
	struct hostent* host_addr = gethostbyname("wemakeli.net.wm");
	if (host_addr == NULL)
	{
		return "Unable to locate host";
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons((unsigned short)80);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		return "-100";
	}
	//建立连接
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sockaddr_in)) == -1)
	{
		return "connect failed";
	}
	//初始化发送信息
	char send_str[2048] = { 0 };
	//头信息
	strcat(send_str, "POST ");
	strcat(send_str, api);
	strcat(send_str, " HTTP/1.1\r\n");
	strcat(send_str, "Host: ");
	strcat(send_str, hostname);
	strcat(send_str, "\r\n");
	strcat(send_str, "Connection: keep-alive\r\n");
	char content_header[100];
	sprintf(content_header, "Content-Length: %d\r\n", strlen(parameters));
	strcat(send_str, content_header);
	strcat(send_str, "Cache-Control: max-age=0\r\n");
	strcat(send_str, "Origin: http://www.hao123.com\r\n");
	strcat(send_str, "User-Agent: Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/15.0.849.0 Safari/535.1\r\n");
	strcat(send_str, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(send_str, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n");
	strcat(send_str, "Referer: http://www.hao123.com/\r\n");
	strcat(send_str, "Accept-Encoding: gzip,deflate,sdch\r\n");
	strcat(send_str, "Accept-Language: zh-CN,zh;q=0.8\r\n");
	//内容信息
	strcat(send_str, "\r\n");
	strcat(send_str, parameters);
	if (send(sock, send_str, strlen(send_str), 0) == -1)
	{
		return "send failed";
	}
	//获取返回信息
	char recv_str[4096] = { 0 };
	if (recv(sock, recv_str, sizeof(recv_str), 0) == -1)
	{
		return "recv failed";
	}
	//char *temp = (char*)ptr;
	string sTemp = recv_str;
	string sOutTemp = "";
	string::size_type idx = sTemp.find(sGold);
	string::size_type xx = sTemp.find_last_of("OK");
	string::size_type yy = sTemp.find_first_of("OK");
	text = sTemp;
	if (idx != string::npos) {
		sOutTemp = sTemp.substr(idx + 4, 4);
		text = sOutTemp;
	}
	WSACleanup();
	string s1f = text;
	int startf = s1f.find_first_of('>');
	int endf = s1f.find_last_of('<');
	string s2f = s1f.substr(startf + 1, endf - startf - 1);
	text = s2f;
	return text;
}
string wmscriptPHP(string coderet) {
	std::string strTemp = "http://wemakeli.net.wm/api/wmscript.php?code=" + coderet;
	char* pChar;
	int len = strTemp.length();
	pChar = new char[len + 1];
	strcpy(pChar, strTemp.c_str());
	int gold = 0;
	string sGold = "gold";
	string text;
	char* hostname = "wemakeli.net.wm";
	char* api = pChar;
	char* parameters = "test";
	WSADATA WsaData;
	WSAStartup(0x0101, &WsaData);
	//初始化socket
	struct hostent* host_addr = gethostbyname("wemakeli.net.wm");
	if (host_addr == NULL)
	{
		return "Unable to locate host";
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons((unsigned short)80);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		return "-100";
	}
	//建立连接
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sockaddr_in)) == -1)
	{
		return "connect failed";
	}
	//初始化发送信息
	char send_str[2048] = { 0 };
	//头信息
	strcat(send_str, "POST ");
	strcat(send_str, api);
	strcat(send_str, " HTTP/1.1\r\n");
	strcat(send_str, "Host: ");
	strcat(send_str, hostname);
	strcat(send_str, "\r\n");
	strcat(send_str, "Connection: keep-alive\r\n");
	char content_header[100];
	sprintf(content_header, "Content-Length: %d\r\n", strlen(parameters));
	strcat(send_str, content_header);
	strcat(send_str, "Cache-Control: max-age=0\r\n");
	strcat(send_str, "Origin: http://www.hao123.com\r\n");
	strcat(send_str, "User-Agent: Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/15.0.849.0 Safari/535.1\r\n");
	strcat(send_str, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(send_str, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n");
	strcat(send_str, "Referer: http://www.hao123.com/\r\n");
	strcat(send_str, "Accept-Encoding: gzip,deflate,sdch\r\n");
	strcat(send_str, "Accept-Language: zh-CN,zh;q=0.8\r\n");
	//内容信息
	strcat(send_str, "\r\n");
	strcat(send_str, parameters);
	if (send(sock, send_str, strlen(send_str), 0) == -1)
	{
		return "send failed";
	}
	//获取返回信息
	char recv_str[4096] = { 0 };
	if (recv(sock, recv_str, sizeof(recv_str), 0) == -1)
	{
		return "recv failed";
	}
	//char *temp = (char*)ptr;
	string sTemp = recv_str;
	string sOutTemp = "";
	string::size_type idx = sTemp.find(sGold);
	string::size_type xx = sTemp.find_last_of("OK");
	string::size_type yy = sTemp.find_first_of("OK");
	text = sTemp;
	if (idx != string::npos) {
		sOutTemp = sTemp.substr(idx + 4, 4);
		text = sOutTemp;
	}
	WSACleanup();
	string s1f = text;
	int startf = s1f.find_first_of('>');
	int endf = s1f.find_last_of('<');
	string s2f = s1f.substr(startf + 1, endf - startf - 1);
	text = s2f;
	return text;
}

string joingroupverify(string useruid, string groupgid) {
	char textretvaltmp[255] = { "" };
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\Group\\" << groupgid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	GetPrivateProfileString("WMBot", "joingroupverify", "-1", textretvaltmp, sizeof(textretvaltmp), textretvalret);
	if (ANSIToUTF8(textretvaltmp) == "-1") {
		return "-1";
	}
	const char* ctextretvalret;
	string ctextretvaldd;
	stringstream cstrStreamtmp, cstrtttttp,cnmbv;
	cstrStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	ctextretvaldd = cstrStreamtmp.str();
	ctextretvalret = ctextretvaldd.c_str();
	LPTSTR clpPath = new char[MAX_PATH];
	strcpy(clpPath, ctextretvalret);
	const char* ctemppre;
	cnmbv << rand();
	string cfff = cnmbv.str();
	cstrtttttp << UTF8ToANSI(cfff);
	ctextretvaldd = cstrtttttp.str();
	ctextretvalret = ctextretvaldd.c_str();
	ctemppre = ctextretvalret;
	string fffffc = "jgvcode_";
	stringstream wdnmdfffa;
	wdnmdfffa << fffffc << groupgid;
	string wdnmdcc;
	wdnmdcc = UTF8ToANSI(wdnmdfffa.str());
	const char* wdnmdret;
	wdnmdret = wdnmdcc.c_str();
	WritePrivateProfileString("WMBot", wdnmdret, ctemppre, clpPath);
	return cnmbv.str();
}

int joingroupverifycheck(string useruid, string groupgid,string coder) {
	char textretvaltmp[255] = { "" };
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\Group\\" << groupgid << ".ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	GetPrivateProfileString("WMBot", "joingroupverify", "-1", textretvaltmp, sizeof(textretvaltmp), textretvalret);
	if (ANSIToUTF8(textretvaltmp) == "-1") {
		return -1;
	}
	char ctextretvaltmp[255] = { "" };
	const char* ctextretvalret;
	string ctextretvaldd;
	stringstream cstrStreamtmp;
	cstrStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
	ctextretvaldd = cstrStreamtmp.str();
	ctextretvalret = ctextretvaldd.c_str();
	GetPrivateProfileString("WMBot", "joingroupverifycode", "-1", ctextretvaltmp, sizeof(ctextretvaltmp), ctextretvalret);
	if (ANSIToUTF8(ctextretvaltmp) == "-1") {
		return -1;
	}
	if (coder == ANSIToUTF8(ctextretvaltmp)) {
		const char* fctextretvalret;
		string fctextretvaldd;
		stringstream fcstrStreamtmp, fcstrtttttp, fcnmbv;
		fcstrStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\User\\" << useruid << ".ini";
		fctextretvaldd = fcstrStreamtmp.str();
		fctextretvalret = fctextretvaldd.c_str();
		LPTSTR fclpPath = new char[MAX_PATH];
		strcpy(fclpPath, fctextretvalret);
		const char* fctemppre;
		fcnmbv << -1;
		string fcfff = fcnmbv.str();
		fcstrtttttp << UTF8ToANSI(fcfff);
		fctextretvaldd = fcstrtttttp.str();
		fctextretvalret = fctextretvaldd.c_str();
		fctemppre = fctextretvalret;
		string fffffc = "jgvcode_";
		stringstream wdnmdfffa;
		wdnmdfffa << fffffc << groupgid;
		string wdnmdcc;
		wdnmdcc = UTF8ToANSI(wdnmdfffa.str());
		const char* wdnmdret;
		wdnmdret = wdnmdcc.c_str();
		WritePrivateProfileString("WMBot", wdnmdret, fctemppre, fclpPath);
		return 0;
	}
	return 1;
}

string wmbotmemory(string uidret,string plain) {
	std::string strTemp = "http://wemakeli.net.wm/api/wmbotmemory.php?useruid=" + uidret + "&plain=" + plain;
	char* pChar;
	int len = strTemp.length();
	pChar = new char[len + 1];
	strcpy(pChar, strTemp.c_str());
	int gold = 0;
	string sGold = "gold";
	string text;
	char* hostname = "wemakeli.net.wm";
	char* api = pChar;
	char* parameters = "test";
	WSADATA WsaData;
	WSAStartup(0x0101, &WsaData);
	//初始化socket
	struct hostent* host_addr = gethostbyname("wemakeli.net.wm");
	if (host_addr == NULL)
	{
		return "Unable to locate host";
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons((unsigned short)80);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		return "-100";
	}
	//建立连接
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sockaddr_in)) == -1)
	{
		return "connect failed";
	}
	//初始化发送信息
	char send_str[2048] = { 0 };
	//头信息
	strcat(send_str, "POST ");
	strcat(send_str, api);
	strcat(send_str, " HTTP/1.1\r\n");
	strcat(send_str, "Host: ");
	strcat(send_str, hostname);
	strcat(send_str, "\r\n");
	strcat(send_str, "Connection: keep-alive\r\n");
	char content_header[100];
	sprintf(content_header, "Content-Length: %d\r\n", strlen(parameters));
	strcat(send_str, content_header);
	strcat(send_str, "Cache-Control: max-age=0\r\n");
	strcat(send_str, "Origin: http://www.hao123.com\r\n");
	strcat(send_str, "User-Agent: Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/15.0.849.0 Safari/535.1\r\n");
	strcat(send_str, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(send_str, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n");
	strcat(send_str, "Referer: http://www.hao123.com/\r\n");
	strcat(send_str, "Accept-Encoding: gzip,deflate,sdch\r\n");
	strcat(send_str, "Accept-Language: zh-CN,zh;q=0.8\r\n");
	//内容信息
	strcat(send_str, "\r\n");
	strcat(send_str, parameters);
	if (send(sock, send_str, strlen(send_str), 0) == -1)
	{
		return "send failed";
	}
	//获取返回信息
	char recv_str[4096] = { 0 };
	if (recv(sock, recv_str, sizeof(recv_str), 0) == -1)
	{
		return "recv failed";
	}
	//char *temp = (char*)ptr;
	string sTemp = recv_str;
	string sOutTemp = "";
	string::size_type idx = sTemp.find(sGold);
	string::size_type xx = sTemp.find_last_of("OK");
	string::size_type yy = sTemp.find_first_of("OK");
	text = sTemp;
	if (idx != string::npos) {
		sOutTemp = sTemp.substr(idx + 4, 4);
		text = sOutTemp;
	}
	WSACleanup();
	string s1f = text;
	int startf = s1f.find_first_of('>');
	int endf = s1f.find_last_of('<');
	string s2f = s1f.substr(startf + 1, endf - startf - 1);
	text = s2f;
	return text;
}

string wmbotmcserverstatus(string serverip, string serverport) {
	std::string strTemp = "http://wemakeli.net.wm/api/wmbotmcserverstatus.php?ip=" + serverip + "&port=" + serverport;
	char* pChar;
	int len = strTemp.length();
	pChar = new char[len + 1];
	strcpy(pChar, strTemp.c_str());
	int gold = 0;
	string sGold = "gold";
	string text;
	char* hostname = "wemakeli.net.wm";
	char* api = pChar;
	char* parameters = "test";
	WSADATA WsaData;
	WSAStartup(0x0101, &WsaData);
	//初始化socket
	struct hostent* host_addr = gethostbyname("wemakeli.net.wm");
	if (host_addr == NULL)
	{
		return "Unable to locate host";
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons((unsigned short)80);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		return "-100";
	}
	//建立连接
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sockaddr_in)) == -1)
	{
		return "connect failed";
	}
	//初始化发送信息
	char send_str[2048] = { 0 };
	//头信息
	strcat(send_str, "POST ");
	strcat(send_str, api);
	strcat(send_str, " HTTP/1.1\r\n");
	strcat(send_str, "Host: ");
	strcat(send_str, hostname);
	strcat(send_str, "\r\n");
	strcat(send_str, "Connection: keep-alive\r\n");
	char content_header[100];
	sprintf(content_header, "Content-Length: %d\r\n", strlen(parameters));
	strcat(send_str, content_header);
	strcat(send_str, "Cache-Control: max-age=0\r\n");
	strcat(send_str, "Origin: http://www.hao123.com\r\n");
	strcat(send_str, "User-Agent: Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/15.0.849.0 Safari/535.1\r\n");
	strcat(send_str, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(send_str, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n");
	strcat(send_str, "Referer: http://www.hao123.com/\r\n");
	strcat(send_str, "Accept-Encoding: gzip,deflate,sdch\r\n");
	strcat(send_str, "Accept-Language: zh-CN,zh;q=0.8\r\n");
	//内容信息
	strcat(send_str, "\r\n");
	strcat(send_str, parameters);
	if (send(sock, send_str, strlen(send_str), 0) == -1)
	{
		return "send failed";
	}
	//获取返回信息
	char recv_str[4096] = { 0 };
	if (recv(sock, recv_str, sizeof(recv_str), 0) == -1)
	{
		return "recv failed";
	}
	//char *temp = (char*)ptr;
	string sTemp = recv_str;
	string sOutTemp = "";
	string::size_type idx = sTemp.find(sGold);
	string::size_type xx = sTemp.find_last_of("OK");
	string::size_type yy = sTemp.find_first_of("OK");
	text = sTemp;
	if (idx != string::npos) {
		sOutTemp = sTemp.substr(idx + 4, 4);
		text = sOutTemp;
	}
	WSACleanup();
	string s1f = text;
	int startf = s1f.find_first_of('>');
	int endf = s1f.find_last_of('<');
	string s2f = s1f.substr(startf + 1, endf - startf - 1);
	text = s2f;
	return text;
}

double groupsendnumber(double gid) {
	const char* textretvalret;
	string textretvaldd;
	stringstream strStreamtmp, strtttttp;
	strStreamtmp << "X:\\WMProject1217\\WMBot\\Library\\SendNumbers.ini";
	textretvaldd = strStreamtmp.str();
	textretvalret = textretvaldd.c_str();
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, textretvalret);
	const char* groupuid;
	stringstream groupp;
	string grouup;
	groupp << gid;
	grouup = groupp.str();
	groupuid = grouup.c_str();
	char textretvaltmpr[255] = { "" };
	const char* textretvalretr;
	GetPrivateProfileString("WMBot", groupuid, "0", textretvaltmpr, sizeof(textretvaltmpr), lpPath);
	stringstream cres, cren;
	cres << textretvaltmpr;
	double crmm;
	cres >> crmm;
	crmm = crmm + 1;
	cres.clear();
	cren << crmm;
	string crena;
	crena = cren.str();
	const char* crenb;
	crenb = crena.c_str();
	WritePrivateProfileString("WMBot", groupuid, crenb, lpPath);
	return crmm;
}

int main()
{
	setlocale(LC_CTYPE, "");
	tasklist[0].init = TRUE;
	tasklist[0].id = 0;
	tasklist[0].name = "app_system";
	tasklist[0].description = "WMBot 内置任务系统进程";
	tasklist[0].shot[0] = "int main();";
	clock_t timestart, timeend;
	clock_t appstart, append;
	appstart = clock();
	int guesscinit = 0;
	string guesscinitgroup = "";
	string guesscanswer = "";
	string guessccoverpath = "";
/*#if defined(WIN32) || defined(_WIN32)
    // 控制台显示乱码纠正
    system("chcp 65001"); //设置字符集 （使用SetConsoleCP(65001)设置无效，原因未知）
    CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = 16; // leave X as zero
    info.FontWeight = FW_NORMAL;
    wcscpy(info.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
#endif*/

	MiraiBot bot("127.0.0.1", 1145);
	while (true)
	{
		try
		{
			bot.Auth("114514", 114514_qq);
			break;
		}
		catch (const std::exception& ex)
		{
			cout << UTF8ToANSI(ex.what()) << endl;
		}
		MiraiBot::SleepSeconds(1);
	}
	cout << "Bot Working..." << endl;
 
 
	bot.On<GroupMessage>(
		[&](GroupMessage m)
		{
			try
			{
				int inttemp;
				stringstream strStreamtmp;
				wmuser usernow;
				string plain = m.MessageChain.GetPlainText();
				timestart = clock();
				strStreamtmp << m.Sender.Group.Name << "(" << m.Sender.Group.GID << ") " << m.Sender.MemberName << "(" << m.Sender.QQ.ToInt64() << ") : " << plain;

				inttemp = systemlog(strStreamtmp.str());
				strStreamtmp.clear();
				strStreamtmp.str("");
				stringstream ffffffffffuser, ffffffffffruser;
				ffffffffffuser << m.Sender.QQ.ToInt64();
				usernow.useruid = ffffffffffuser.str();
				usernow.permission = readpermissionuser(ffffffffffuser.str());
				usernow.coin = readcoinuser(ffffffffffuser.str());
				usernow.exp = readexpuser(ffffffffffuser.str());
				usernow.firstname = readfirstnameuser(ffffffffffuser.str());
				usernow.lastname = readlastnameuser(ffffffffffuser.str());
				usernow.language = readlanguageuser(ffffffffffuser.str());
				ffffffffffuser.clear();
				double tenm;
				tenm = groupsendnumber(m.Sender.Group.GID.ToInt64());
				string userfirstname;
				if (usernow.firstname != "") {
					userfirstname = usernow.firstname;
				}
				else {
					userfirstname = m.Sender.MemberName;
				}
				if (usernow.permission == "Banned") {
					return;
				}
				if (usernow.permission == "Locked") {
					return;
				}
				if (usernow.permission == "RootAdministrator")
				{
					if (plain == "/wm rootadmin getgrouplist")
					{
						auto groups = bot.GetGroupList();
						int i = 1;
						string text;
						text = "";
						for (const auto& g : groups)
						{
							stringstream strStream;
							strStream << "[" << i << "] " << g.GID << ", " << g.Name << ", " << GroupPermissionStr(g.Permission) << "\n";
							i = i + 1;
							text = text + strStream.str();
						}
						MessageChain msg = MessageChain().Plain(text);
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 43) == "/wm rootadmin config permission localgroup ") {
						string text;
						stringstream strStream,strrrc;
						string fitstr = plain;
						fitstr = fitstr.replace(0, 43, "");
						strStream << fitstr;
						text = strStream.str();
						strrrc << m.Sender.Group.GID.ToInt64();
						writepermissiongroup(strrrc.str(),text);
						MessageChain msg = MessageChain().Plain("Operation has been performed.");
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 27) == "/wm rootadmin image upload ") {
						string text;
						stringstream strStream;
						string fitstr = plain;
						fitstr = fitstr.replace(0, 27, "");
						strStream << fitstr;
						text = strStream.str();
						try {
							GroupImage gImg = bot.UploadGroupImage(text);
							m.QuoteReply(MessageChain().Image(gImg));
							return;
						}
						catch (const std::exception& ex)
						{
							stringstream strStream;
							strStream << "Fatal Error\nAt GroupImage gImg = bot.UploadGroupImage(text);\n" << ex.what();
							MessageChain msg = MessageChain().Plain(strStream.str());
							m.QuoteReply(msg);
							return;
						}
					}
					if (plain.substr(0, 27) == "/wm rootadmin voice upload ") {
						string text;
						stringstream strStream;
						string fitstr = plain;
						fitstr = fitstr.replace(0, 27, "");
						strStream << fitstr;
						text = strStream.str();
						try {
							MiraiVoice voice = bot.UploadGroupVoice(text);
							m.Reply(MessageChain().Voice(voice));
							return;
						}
						catch (const std::exception& ex)
						{
							stringstream strStream;
							strStream << "Fatal Error\nAt MiraiVoice voice = bot.UploadGroupVoice(text);\n" << ex.what();
							MessageChain msg = MessageChain().Plain(strStream.str());
							m.QuoteReply(msg);
							return;
						}
					}
					if (plain == "/wm rootadmin stat")
					{
						string text;
						stringstream strStream;
						append = clock();		//程序结束用时
						long double endtime = (append - appstart) / CLOCKS_PER_SEC;
						MEMORYSTATUS ms;
						::GlobalMemoryStatus(&ms);
						double totalspace = 0, freespace = 0;
						DWORD dwLen = GetLogicalDriveStrings(0, NULL);	//获取系统字符串长度.
						char* pszDriver = new char[dwLen];				//构建一个相应长度的数组.
						GetLogicalDriveStrings(dwLen, pszDriver);		//获取盘符字符串.
						vector<string> v;
						while (*pszDriver != '\0')
						{
							//strStream << pszDriver << " ---- " << endl;
							v.push_back(pszDriver);
							pszDriver += strlen(pszDriver) + 1;			//定位到下一个字符串.加一是为了跳过'\0'字符串.
						}

						int DType;
						int si = 0;
						BOOL fResult;
						unsigned _int64 i64FreeBytesToCaller;
						unsigned _int64 i64TotalBytes;
						unsigned _int64 i64FreeBytes;

						for (int i = 0; i < dwLen / 4; ++i)
							//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
						{
							DType = GetDriveType(v[i].c_str());
							//GetDriveType函数，可以获取驱动器类型，参数为驱动器的根目录
							fResult = GetDiskFreeSpaceEx(
								v[i].c_str(),
								(PULARGE_INTEGER)&i64FreeBytesToCaller,
								(PULARGE_INTEGER)&i64TotalBytes,
								(PULARGE_INTEGER)&i64FreeBytes);
							//GetDiskFreeSpaceEx函数，可以获取驱动器磁盘的空间状态,函数返回的是个BOOL类型数据
							if (fResult)//通过返回的BOOL数据判断驱动器是否在工作状态
							{
								totalspace = totalspace + (double)((double)i64TotalBytes / (double)1024 / (double)1024 / (double)1024);//磁盘总容量
								freespace = freespace + (double)((double)i64FreeBytesToCaller / (double)1024 / (double)1024 / (double)1024);//磁盘剩余空间
							}
							si += 4;
						}
						auto now = std::chrono::system_clock::now();
						long long nowimestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
						long long duration = std::chrono::steady_clock::now().time_since_epoch().count();
						string vname;
						OSVERSIONINFOEX os;
						os.dwOSVersionInfoSize = sizeof(os);
						int tempdda = GetVersionEx((OSVERSIONINFO*)&os);
						if (tempdda == 0) {
							MessageChain msg = MessageChain().Plain("An error occurred at GetVersionEx();");
							m.QuoteReply(msg);
							return;
						}
						//NtQuerySystemInformation();
						if (usernow.language == "en-us") {
							strStream << "Version : Inside Preview 0.85.96,Length of running time: " << endtime << " Second(s)\nOS : Windows " << os.dwMajorVersion << "." << os.dwMinorVersion << "." << os.dwBuildNumber << ",Length of OS normal running time : " << (double)((double)duration / (double)1000000 / (double)1000 / (double)60 / (double)60) << " Hour(s)\n" << "CPU usage : -1" << " %\n" << "Available RAM : " << (ms.dwAvailPhys / 1024 / 1024) << " MB / " << (ms.dwTotalPhys / 1024 / 1024) << " MB ( " << (100 - ms.dwMemoryLoad) << " % )\n" << "Available Disk Space : " << freespace << " GB / " << totalspace << " GB";
							text = strStream.str();
							MessageChain msg = MessageChain().Plain(text);
							m.QuoteReply(msg);
							return;
						}
						strStream << "版本 : Inside Preview 0.85.96,运行时间 : " << endtime << " Second(s)\n操作系统 : Windows " << os.dwMajorVersion << "." << os.dwMinorVersion << "." << os.dwBuildNumber << ",操作系统正常运行时长 : " << (double)((double)duration / (double)1000000 / (double)1000 / (double)60 / (double)60) << " Hour(s)\n" << "CPU占用 : -1" << " %\n" << "可用RAM : " << (ms.dwAvailPhys / 1024 / 1024) << " MB / " << (ms.dwTotalPhys / 1024 / 1024) << " MB ( " << (100 - ms.dwMemoryLoad) << " % )\n" << "可用磁盘空间 : " << freespace << " GB / " << totalspace << " GB";
						text = strStream.str();
						MessageChain msg = MessageChain().Plain(text);
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 18) == "/wm rootadmin ban ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 18, "");
						int tempaaaaaauser = writepermissionuser(fitstr, "Banned");
						MessageChain msg = MessageChain().Plain("已将 " + fitstr + " 的权限设置为 Banned");
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 20) == "/wm rootadmin unban ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 20, "");
						int tempaaaaaauser = writepermissionuser(fitstr, "None");
						MessageChain msg = MessageChain().Plain("已将 " + fitstr + " 的权限设置为 None");
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 30) == "/wm rootadmin Permission User ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 30, "");
						int tempaaaaaauser = writepermissionuser(fitstr, "User");
						MessageChain msg = MessageChain().Plain("已将 " + fitstr + " 的权限设置为 User");
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 39) == "/wm rootadmin Permission Administrator ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 39, "");
						int tempaaaaaauser = writepermissionuser(fitstr, "Administrator");
						MessageChain msg = MessageChain().Plain("已将 " + fitstr + " 的权限设置为 Administrator");
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 28) == "/wm rootadmin loopsendtest3 ") {
						double i;
						i = 0;
						string strdt;
						strdt = plain.replace(0, 28, "");
						while (i < 3) {
						    MessageChain msg = MessageChain().Plain(strdt);
						    m.QuoteReply(msg);
							i++;
						}
						return;
					}
					if (plain.substr(0, 28) == "/wm rootadmin loopsendtestR ") {
						double i;
						i = 0;
						string strdt;
						strdt = plain.replace(0, 28, "");
						while (i < 3) {
							MessageChain msg = MessageChain().Plain(strdt);
							bot.SendMessage(m.Sender.Group.GID, msg);
							i++;
						}
						return;
					}
					if (plain == "/wm rootadmin textout groupstatus")
					{
						string text;
						stringstream strStream;
						double numbercvc = 0;
						auto gMembers = bot.GetGroupMembers(m.Sender.Group.GID);
						strStream << m.Sender.Group.ToString() << "\n";
						for (const auto& gMem : gMembers)
						{
							strStream << "[" << numbercvc << "]" << gMem.QQ << ", " << gMem.MemberName << ", " << GroupPermissionStr(gMem.Permission);
							// 获取群成员的信息（群名片、群头衔）
							auto info = bot.GetGroupMemberInfo(gMem.Group.GID, gMem.QQ);
							strStream << ", 群名片: " << (info.Name.empty() ? "无" : info.Name)
								<< ", 群头衔: " << (info.SpecialTitle.empty() ? "无" : info.SpecialTitle) << endl;
							numbercvc = numbercvc + 1;
						}
						text = strStream.str();
						strStream.clear();
						try
						{
							textout << text << endl;
						}
						catch (const std::exception& ex)
						{
							stringstream strStream;
							strStream << "Fatal Error\nAt textout << text << endl;\n" << ex.what();
							MessageChain msg = MessageChain().Plain(strStream.str());
							m.QuoteReply(msg);
							return;
						}
						MessageChain msg = MessageChain().Plain("Done.");
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 30) == "/wm rootadmin settimeout send ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 30, "");
						double index;
						index = fitstr.find("=");
						string timeoutstr, stringsendmsg;
						stringsendmsg = fitstr.substr((index+1));
						timeoutstr = fitstr.assign(fitstr.c_str(), index);
						stringstream strstrstcm;
						strstrstcm << timeoutstr;
						double timeoutc;
						strstrstcm >> timeoutc;
						//cout << stringsendmsg << "," << timeoutc << endl;
						Sleep(timeoutc);
						MessageChain msg = MessageChain().Plain(stringsendmsg);
						bot.SendMessage(m.Sender.Group.GID, msg);
						return;

					}
					if (plain.substr(0, 30) == "/wm rootadmin planMINUTE send ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 30, "");
						double index;
						index = fitstr.find("=");
						string timeoutstr, stringsendmsg;
						stringsendmsg = fitstr.substr((index + 1));
						timeoutstr = fitstr.assign(fitstr.c_str(), index);
						stringstream strstrstcm;
						strstrstcm << timeoutstr;
						double timeoutc;
						strstrstcm >> timeoutc;
						time_t timenow = time(0);
						tm* ltm = localtime(&timenow);
						while (ltm->tm_min != timeoutc) {
							Sleep(20);
							timenow = time(0);
							ltm = localtime(&timenow);
						}
						MessageChain msg = MessageChain().Plain(stringsendmsg);
						bot.SendMessage(m.Sender.Group.GID, msg);
						return;
					}
					if (plain.substr(0, 28) == "/wm rootadmin planHOUR send ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 28, "");
						double index;
						index = fitstr.find("=");
						string timeoutstr, stringsendmsg;
						stringsendmsg = fitstr.substr((index + 1));
						timeoutstr = fitstr.assign(fitstr.c_str(), index);
						stringstream strstrstcm;
						strstrstcm << timeoutstr;
						double timeoutc;
						strstrstcm >> timeoutc;
						time_t timenow = time(0);
						tm* ltm = localtime(&timenow);
						while (ltm->tm_hour != timeoutc) {
							Sleep(20);
							timenow = time(0);
							ltm = localtime(&timenow);
						}
						MessageChain msg = MessageChain().Plain(stringsendmsg);
						bot.SendMessage(m.Sender.Group.GID, msg);
						return;
					}
					if (plain.substr(0, 27) == "/wm rootadmin planDAY send ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 27, "");
						double index;
						index = fitstr.find("=");
						string timeoutstr, stringsendmsg;
						stringsendmsg = fitstr.substr((index + 1));
						timeoutstr = fitstr.assign(fitstr.c_str(), index);
						stringstream strstrstcm;
						strstrstcm << timeoutstr;
						double timeoutc;
						strstrstcm >> timeoutc;
						time_t timenow = time(0);
						tm* ltm = localtime(&timenow);
						while (ltm->tm_mday != timeoutc) {
							Sleep(20);
							timenow = time(0);
							ltm = localtime(&timenow);
						}
						MessageChain msg = MessageChain().Plain(stringsendmsg);
						bot.SendMessage(m.Sender.Group.GID, msg);
						return;
					}
					if (plain == "/wm rootadmin service start LxBotAutoSign") {
						service_LxBotAutoSign = "ON";
						time_t timenow = time(0);
						tm* ltm = localtime(&timenow);
						MessageChain msg = MessageChain().Plain("服务 LxBotAutoSign 已启动");
						m.QuoteReply(msg);
						while (1) {
							Sleep(16);
							timenow = time(0);
							ltm = localtime(&timenow);
							if (ltm->tm_hour == 0) {
								if (ltm->tm_min == 0) {
									MessageChain msg = MessageChain().Plain("/b sign");
									bot.SendMessage(1151290186_gid, msg);
									stringstream crs;
									crs << "LxBotAutoSign Run" << ltm->tm_mday << ltm->tm_hour << ltm->tm_min;
									systemlog(crs.str());
									Sleep(60 * 1000);
								}
							}
							if (service_LxBotAutoSign == "END") {
								MessageChain msg = MessageChain().Plain("服务 LxBotAutoSign 已终止");
								m.QuoteReply(msg);
								return;
							}
						}
					}
					if (plain == "/wm rootadmin service exit LxBotAutoSign") {
						if (service_LxBotAutoSign == "END") {
							MessageChain msg = MessageChain().Plain("服务 LxBotAutoSign 没有运行");
							m.QuoteReply(msg);
						}
						service_LxBotAutoSign = "END";
						return;
					}
					if (plain == "/wm rootadmin service info LxBotAutoSign") {
						if (service_LxBotAutoSign == "END") {
							MessageChain msg = MessageChain().Plain("服务 LxBotAutoSign 没有运行");
							m.QuoteReply(msg);
							return;
						} else if (service_LxBotAutoSign == "ON") {
							MessageChain msg = MessageChain().Plain("服务 LxBotAutoSign 正在运行");
							m.QuoteReply(msg);
							return;
						} else {
							MessageChain msg = MessageChain().Plain("服务 LxBotAutoSign 状态错误");
							m.QuoteReply(msg);
							return;
						}
					}
				}
				if (usernow.permission == "Administrator") {
					if (plain == "/wm admin stat")
					{
						string text;
						stringstream strStream;
						append = clock();		//程序结束用时
						long double endtime = (append - appstart) / CLOCKS_PER_SEC;
						MEMORYSTATUS ms;
						::GlobalMemoryStatus(&ms);
						double totalspace = 0, freespace = 0;
						DWORD dwLen = GetLogicalDriveStrings(0, NULL);	//获取系统字符串长度.
						char* pszDriver = new char[dwLen];				//构建一个相应长度的数组.
						GetLogicalDriveStrings(dwLen, pszDriver);		//获取盘符字符串.
						vector<string> v;
						while (*pszDriver != '\0')
						{
							//strStream << pszDriver << " ---- " << endl;
							v.push_back(pszDriver);
							pszDriver += strlen(pszDriver) + 1;			//定位到下一个字符串.加一是为了跳过'\0'字符串.
						}

						int DType;
						int si = 0;
						BOOL fResult;
						unsigned _int64 i64FreeBytesToCaller;
						unsigned _int64 i64TotalBytes;
						unsigned _int64 i64FreeBytes;

						for (int i = 0; i < dwLen / 4; ++i)
							//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
						{
							DType = GetDriveType(v[i].c_str());
							//GetDriveType函数，可以获取驱动器类型，参数为驱动器的根目录
							fResult = GetDiskFreeSpaceEx(
								v[i].c_str(),
								(PULARGE_INTEGER)&i64FreeBytesToCaller,
								(PULARGE_INTEGER)&i64TotalBytes,
								(PULARGE_INTEGER)&i64FreeBytes);
							//GetDiskFreeSpaceEx函数，可以获取驱动器磁盘的空间状态,函数返回的是个BOOL类型数据
							if (fResult)//通过返回的BOOL数据判断驱动器是否在工作状态
							{
								totalspace = totalspace + (double)((double)i64TotalBytes / (double)1024 / (double)1024 / (double)1024);//磁盘总容量
								freespace = freespace + (double)((double)i64FreeBytesToCaller / (double)1024 / (double)1024 / (double)1024);//磁盘剩余空间
							}
							si += 4;
						}
						auto now = std::chrono::system_clock::now();
						long long nowimestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
						long long duration = std::chrono::steady_clock::now().time_since_epoch().count();
						string vname;
						OSVERSIONINFOEX os;
						os.dwOSVersionInfoSize = sizeof(os);
						int tempdda = GetVersionEx((OSVERSIONINFO*)&os);
						if (tempdda == 0) {
							MessageChain msg = MessageChain().Plain("An error occurred at GetVersionEx();");
							m.QuoteReply(msg);
							return;
						}
						//NtQuerySystemInformation();
						if (usernow.language == "en-us") {
							strStream << "Version : Inside Preview 0.85.96,Length of running time: " << endtime << " Second(s)\nOS : Windows " << os.dwMajorVersion << "." << os.dwMinorVersion << "." << os.dwBuildNumber << ",Length of OS normal running time : " << (double)((double)duration / (double)1000000 / (double)1000 / (double)60 / (double)60) << " Hour(s)\n" << "CPU usage : -1" << " %\n" << "Available RAM : " << (ms.dwAvailPhys / 1024 / 1024) << " MB / " << (ms.dwTotalPhys / 1024 / 1024) << " MB ( " << (100 - ms.dwMemoryLoad) << " % )\n" << "Available Disk Space : " << freespace << " GB / " << totalspace << " GB";
							text = strStream.str();
							MessageChain msg = MessageChain().Plain(text);
							m.QuoteReply(msg);
							return;
						}
						strStream << "版本 : Inside Preview 0.85.96,运行时间 : " << endtime << " Second(s)\n操作系统 : Windows " << os.dwMajorVersion << "." << os.dwMinorVersion << "." << os.dwBuildNumber << ",操作系统正常运行时长 : " << (double)((double)duration / (double)1000000 / (double)1000 / (double)60 / (double)60) << " Hour(s)\n" << "CPU占用 : -1" << " %\n" << "可用RAM : " << (ms.dwAvailPhys / 1024 / 1024) << " MB / " << (ms.dwTotalPhys / 1024 / 1024) << " MB ( " << (100 - ms.dwMemoryLoad) << " % )\n" << "可用磁盘空间 : " << freespace << " GB / " << totalspace << " GB";
						text = strStream.str();
						MessageChain msg = MessageChain().Plain(text);
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 14) == "/wm admin ban ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 14, "");
						ffffffffffruser << fitstr;
						string rtuserpermission = readpermissionuser(ffffffffffruser.str());
						ffffffffffruser.clear();
						if (rtuserpermission == "RootAdministrator") {
							MessageChain msg = MessageChain().Plain("你不能修改 RootAdministrator 组的权限");
							m.QuoteReply(msg);
							return;
						}
						if (rtuserpermission == "Administrator") {
							MessageChain msg = MessageChain().Plain("你不能修改 Administrator 组的权限");
							m.QuoteReply(msg);
							return;
						}
						int tempaaaaaauser = writepermissionuser(fitstr, "Banned");
						MessageChain msg = MessageChain().Plain("已将 " + fitstr + " 的权限设置为 Banned");
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 16) == "/wm admin unban ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 16, "");
						ffffffffffruser << fitstr;
						string rtuserpermission = readpermissionuser(ffffffffffruser.str());
						ffffffffffruser.clear();
						if (rtuserpermission == "RootAdministrator") {
							MessageChain msg = MessageChain().Plain("你不能修改 RootAdministrator 组的权限");
							m.QuoteReply(msg);
							return;
						}
						if (rtuserpermission == "Administrator") {
							MessageChain msg = MessageChain().Plain("你不能修改 Administrator 组的权限");
							m.QuoteReply(msg);
							return;
						}
						int tempaaaaaauser = writepermissionuser(fitstr, "None");
						MessageChain msg = MessageChain().Plain("已将 " + fitstr + " 的权限设置为 None");
						m.QuoteReply(msg);
						return;
					}
					if (plain.substr(0, 26) == "/wm admin Permission User ") {
						string fitstr = plain;
						fitstr = fitstr.replace(0, 26, "");
						ffffffffffruser << fitstr;
						string rtuserpermission = readpermissionuser(ffffffffffruser.str());
						ffffffffffruser.clear();
						if (rtuserpermission == "RootAdministrator") {
							MessageChain msg = MessageChain().Plain("你不能修改 RootAdministrator 组的权限");
							m.QuoteReply(msg);
							return;
						}
						if (rtuserpermission == "Administrator") {
							MessageChain msg = MessageChain().Plain("你不能修改 Administrator 组的权限");
							m.QuoteReply(msg);
							return;
						}
						int tempaaaaaauser = writepermissionuser(fitstr, "User");
						MessageChain msg = MessageChain().Plain("已将 " + fitstr + " 的权限设置为 User");
						m.QuoteReply(msg);
						return;
					}
				}
				string textrcc;
				stringstream strStreamrcc;
				strStreamrcc << m.Sender.Group.GID.ToInt64();
				textrcc = strStreamrcc.str();
				strStreamrcc.clear();
				strStreamrcc.str("");
				strStreamrcc << readpermissiongroup(textrcc);
				textrcc = strStreamrcc.str();
				strStreamrcc.clear();
				strStreamrcc.str("");
				if (textrcc == "None") {
					return;
				}
				if (plain == "/wm imghelp")
				{
					if (usernow.language == "en-us") {
						GroupImage gImg = bot.UploadGroupImage("X:\\WMProject1217\\WMBot\\Library\\Image\\Common\\help_en-us.png");
						m.QuoteReply(MessageChain().Image(gImg));
						return;
					}
					GroupImage gImg = bot.UploadGroupImage("X:\\WMProject1217\\WMBot\\Library\\Image\\Common\\help.png");
					m.QuoteReply(MessageChain().Image(gImg));
					return;
				}
				if (plain == "/wm help")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain("For more information about command, send /wm help [command name]\n/retcmd 随机老婆 Random a girl /wm splashes Random splashes /wm tarot random 1 Random a Big Acanataro card\n/wm user config firstname [string UserName] Set username /wm user config lastname [string lastname] Set last name /wm coin Show the coins you have /wm level Show your exp points /wm sign Sign\n/wm about Show about /wm ping Show the time from get message to completion processing");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain("有关某个命令的详细信息，请发送 /wm help 命令名\n/retcmd 随机老婆 随机一个老婆 /wm splashes 随机一条标语 /wm tarot random 1 随机一张大阿卡那塔罗牌\n/wm user config firstname [string UserName] 设置名称 /wm user config lastname [string lastname] 设置姓氏 /wm coin 显示当前用户持有的硬币 /wm level 显示当前用户的等级和经验值 /wm sign 签到\n/wm about 显示关于 /wm ping 显示从收到消息到处理完成的时间");
					m.QuoteReply(msg);
					return;
				}
				if (plain.substr(0, 9) == "/wm help ") {
					string fitstr = plain.replace(0, 9, "");
					if (fitstr == "/retcmd 随机老婆") {
						if (usernow.language == "en-us") {
							MessageChain msg = MessageChain().Plain("");
							m.QuoteReply(msg);
							return;
						}
						MessageChain msg = MessageChain().Plain("Random a girl\nUsed WemakeliAPI-randomgirl,Write from 随机老婆[花酱随机老婆草] By 花开花落 版本 0.0.1");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm splashes") {
						MessageChain msg = MessageChain().Plain("Random a splash\nUsed WemakeliAPI-splashes,as very same from the splashes of Minecraft(");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm tarot random 1") {
						MessageChain msg = MessageChain().Plain("Random a Big Acanataro card\nUsed WemakeliAPI-tarot,This randomly generated value should not be used as a true prediction");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm about") {
						MessageChain msg = MessageChain().Plain("Show about in text");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm help") {
						MessageChain msg = MessageChain().Plain("Show help in text\nAvaible when permission is not Banned or Locked");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm helpadmin") {
						MessageChain msg = MessageChain().Plain("显示Administrator指令组帮助\n只有权限为Administrator时才能查看");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm helprootadmin") {
						MessageChain msg = MessageChain().Plain("显示RootAdministrator指令组帮助\n只有权限为RootAdministrator时才能查看");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm user config firstname") {
						MessageChain msg = MessageChain().Plain("/wm user config firstname [string UserName]\n[string UserName] The first name you wanna\nSet username,this will be used in words");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm user config lastname") {
						MessageChain msg = MessageChain().Plain("/wm user config lastname [string lastname]\n[string lastname] The last name you wanna\nSet last name,this command is not commonly used");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm coin") {
						MessageChain msg = MessageChain().Plain("Show the coins you have\nIf you have none,this will show -1");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm level") {
						MessageChain msg = MessageChain().Plain("Show your exp points\nIf you have none,this will show -1");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm sign") {
						MessageChain msg = MessageChain().Plain("Sign\nAdd coins and exp points");
						m.QuoteReply(msg);
						return;
					} else if (fitstr == "/wm ping") {
						MessageChain msg = MessageChain().Plain("Show the time from get message to completion processing");
						m.QuoteReply(msg);
						return;
					}/* else if (fitstr == "/wm text out") {
						MessageChain msg = MessageChain().Plain("/wm text out [string rxct]\n[string rxct] 要写入的文本\n向textout.wmst中写入,不推荐使用此指令,因为其将被移除或修改");
						m.QuoteReply(msg);
						return;
					}*/
				}
				if (plain == "/wm about")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain("About - WMBot\nWMBot_QQ_CPP [Inside Preview Edition][Version 0.85.96]\nBy WMProject1217\nhttp://git.net.wm/WMProject1217/WMBot_QQ_CPP (内网)");
						m.QuoteReply(msg);
						return;
					}
					if (usernow.language == "iu-or") {
						MessageChain msg = MessageChain().Plain("Otiuysiys - WMBot\nWMBot_QQ_CPP [Inside Preview Edition][Version 0.85.96]\nBy WMProject1217\nLipoticia siys http://git.net.wm/WMProject1217/WMBot_QQ_CPP (内网)");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain("关于 - WMBot\nWMBot_QQ_CPP [Inside Preview Edition][Version 0.85.96]\nBy WMProject1217\n开源于 http://git.net.wm/WMProject1217/WMBot_QQ_CPP (内网)");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm stats local") {
					stringstream tmppppppd;
					tmppppppd << tenm;
					string ctm;
					ctm = "The send message number of local group in this thread : " + tmppppppd.str();
					MessageChain msg = MessageChain().Plain(ctm);
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm sign")
				{
					string text;
					stringstream strStream,ssra,ssrb,ssrc,ssrd;
					double coinget, expget;
					srand(time(NULL));
					coinget = rand() % 100;
					expget = rand() % 100;
					if (usernow.language == "en-us") {
						strStream << "Sign successful," << userfirstname << "\nGet " << coinget << " coins and " << expget << " exp points";
					} else if (usernow.language == "iu-or") {
						strStream << "Piusliyisiys limipiuiys," << userfirstname << "\nSiys " << coinget << " coins nioisiys " << expget << " exp points";
					} else {
						strStream << "签到成功了," << userfirstname << "\n获得 " << coinget << " 个硬币和 " << expget << " 点经验";
					}

					text = strStream.str();
					strStream.clear();
					double intcoin, intexp,intcoina,intexpa;
					ssra << usernow.coin;
					ssra >> intcoina;
					intcoin = intcoina + coinget;
					ssrb << intcoin;
					writecoinuser(usernow.useruid, ssrb.str());
					ssrc << usernow.exp;
					ssrc >> intexpa;
					intexp = intexpa + expget;
					ssrd << intexp;
					writeexpuser(usernow.useruid, ssrd.str());
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm coin")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain(userfirstname + " have " + usernow.coin + " coins");
						m.QuoteReply(msg);
						return;
					}
					if (usernow.language == "iu-or") {
						MessageChain msg = MessageChain().Plain(userfirstname + " siys " + usernow.coin + " coins");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain(userfirstname + "现在有 " + usernow.coin + " 个硬币");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm level")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain(userfirstname + " have " + usernow.exp + " exp points");
						m.QuoteReply(msg);
						return;
					}
					if (usernow.language == "iu-or") {
						MessageChain msg = MessageChain().Plain(userfirstname + " siys " + usernow.coin + " exp points");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain(userfirstname + "现在有 " + usernow.exp + " 点经验");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/td")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain(userfirstname + " unsubscribe");
						m.QuoteReply(msg);
						return;
					}
					if (usernow.language == "iu-or") {
						MessageChain msg = MessageChain().Plain(userfirstname + " inus-puiliconnicia");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain(userfirstname + "已退订");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/say 114514")
				{
					MessageChain msg = MessageChain().Plain("xn--7wraa62aaaaaaaaaaaaaaaaaaa");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "Ciallo～(∠ · ω< )⌒☆")
				{
					MessageChain msg = MessageChain().Plain(userfirstname + ",Ciallo～(∠ · ω< )⌒☆");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "Ciallo～")
				{
					MessageChain msg = MessageChain().Plain(userfirstname + ",Ciallo～(∠ · ω< )⌒☆");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "晚安")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain("Good night , wish " + userfirstname + " have a good dream~");
						m.QuoteReply(msg);
						return;
					}
					if (usernow.language == "iu-or") {
						MessageChain msg = MessageChain().Plain("Linpolisiys colicia, wiolisiys " + userfirstname + " nioisiys venlidia lopnicirickia~");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain("晚安，" + userfirstname + "也要好好休息呢");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "Good night")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain("Good night , wish " + userfirstname + " have a good dream~");
						m.QuoteReply(msg);
						return;
					}
					if (usernow.language == "iu-or") {
						MessageChain msg = MessageChain().Plain("Linpolisiys colicia, wiolisiys " + userfirstname + " nioisiys venlidia lopnicirickia~");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain("晚安，" + userfirstname + "也要好好休息呢");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "Linpolisiys colicia")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain("Good night , wish " + userfirstname + " have a good dream~");
						m.QuoteReply(msg);
						return;
					}
					if (usernow.language == "iu-or") {
						MessageChain msg = MessageChain().Plain("Linpolisiys colicia, wiolisiys " + userfirstname + " nioisiys venlidia lopnicirickia~");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain("晚安，" + userfirstname + "也要好好休息呢");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "早上好")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain("Good morning , " + userfirstname + ",today is also a day for struggle.");
						m.QuoteReply(msg);
						return;
					}
					if (usernow.language == "iu-or") {
						MessageChain msg = MessageChain().Plain("Mincloplist ciallo, wiolisiys " + userfirstname + " lipotidia nlisiys simmuitia~");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain("早上好，" + userfirstname + "，今天也要继续加油呢。");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "Good morning")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain("Good morning , " + userfirstname + ",today is also a day for struggle.");
						m.QuoteReply(msg);
						return;
					}
					if (usernow.language == "iu-or") {
						MessageChain msg = MessageChain().Plain("Mincloplist ciallo, wiolisiys " + userfirstname + " lipotidia nlisiys simmuitia~");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain("早上好，" + userfirstname + "，今天也要继续加油呢。");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "Mincloplist ciallo")
				{
					if (usernow.language == "en-us") {
						MessageChain msg = MessageChain().Plain("Good morning , " + userfirstname + ",today is also a day for struggle.");
						m.QuoteReply(msg);
						return;
					}
					if (usernow.language == "iu-or") {
						MessageChain msg = MessageChain().Plain("Mincloplist ciallo, wiolisiys " + userfirstname + " lipotidia nlisiys simmuitia~");
						m.QuoteReply(msg);
						return;
					}
					MessageChain msg = MessageChain().Plain("早上好，" + userfirstname + "，今天也要继续加油呢。");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm splashes")
				{
					string text;
					stringstream strStream;
					strStream << randomsplashes();
					text = strStream.str();
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm tarot random 1")
				{
					string text;
					stringstream strStream;
					strStream << randomtarot();
					text = strStream.str();
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				/*if (plain.substr(0, 13) == "/wm text out ") {
					string text;
					string fitstr = plain;
					fitstr = fitstr.replace(0, 13, "");
					try
					{
						textout << fitstr << endl;
					}
					catch (const std::exception& ex)
					{
						stringstream strStream;
						strStream << "Fatal Error\nAt textout << fitstr << endl;\n" << ex.what();
						MessageChain msg = MessageChain().Plain(strStream.str());
						m.QuoteReply(msg);
						return;
					}
					text = "Successful output";
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}*/
				if (plain.substr(0, 26) == "/wm user config firstname ") {
					string text;
					string fitstr = plain;
					fitstr = fitstr.replace(0, 26, "");
					if (fitstr.length() > 48) {
						MessageChain msg = MessageChain().Plain("Fatal Error\nAt writefirstnameuser(usernow.useruid,fitstr); [main.cpp Line1192]\nStack overflow");
						m.QuoteReply(msg);
						return;
					}
					writefirstnameuser(usernow.useruid,fitstr);
					if (usernow.language == "en-us") {
						text = "I will tell you " + fitstr + " after this~";
					} else if (usernow.language == "iu-or") {
						text = "I siys teplissiys jestlicia nioisiys " + fitstr + " dilopliynicia~";
					} else {
						text = "以后就叫你" + fitstr + "了呢";
					}
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain.substr(0, 25) == "/wm user config lastname ") {
					string text;
					string fitstr = plain;
					fitstr = fitstr.replace(0, 25, "");
					if (fitstr.length() > 48) {
						MessageChain msg = MessageChain().Plain("Fatal Error\nAt writelastnameuser(usernow.useruid,fitstr); [main.cpp Line1207]\nStack overflow");
						m.QuoteReply(msg);
						return;
					}
					writelastnameuser(usernow.useruid, fitstr);
					if (usernow.language == "en-us") {
						text = "Ciallo,dear " + fitstr;
					} else if (usernow.language == "iu-or") {
						text = "Ciallo,riacciys " + fitstr;
					} else {
						text = "你好啊,亲爱的" + fitstr;
					}
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain.substr(0, 25) == "/wm user config language ") {
					string text;
					string fitstr = plain;
					fitstr = fitstr.replace(0, 25, "");
					writelanguageuser(usernow.useruid, fitstr);
					text = "We has been set your default language to " + fitstr + "\n//We will use zh-cn instead if your language can not be use.";
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/retcmd 随机老婆") {
					string rtcx;
					rtcx = randomgirl(m.Sender.MemberName);
					MessageChain msg = MessageChain().Plain(rtcx);
					m.QuoteReply(msg);
					return;
				}
				/*if (plain == "/retcmd 玩蛇")
				{
					MessageChain msg = MessageChain().Plain("当前工程 WMBot_QQ_CPP 未准备指令 /retcmd 玩蛇");
					m.QuoteReply(msg);
					return;
				}*/
				if (plain.find("//The Banned String//", 0) != -1) {
					string text;
					stringstream strStream;
					strStream << "You have been sent a banned word";
					text = strStream.str();
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm user info") {
					stringstream strStream;
					if (usernow.language == "en-us") {
						strStream << "User ID:" << usernow.useruid << " ,First Name:" << usernow.firstname << " ,Last Name:" << usernow.lastname << " ,Default Language:" << usernow.language << "\nPermission:" << usernow.permission << " ,Coins:" << usernow.coin << " ,Exp Points:" << usernow.exp;
					} else if (usernow.language == "iu-or") {
						strStream << "Jestlicia LK:" << usernow.useruid << " ,Mipl-nioisiys Politsiys:" << usernow.firstname << " ,Nutl-nioisiys Politsiys:" << usernow.lastname << " ,Losl-siys:" << usernow.language << "\nQuntiocia:" << usernow.permission << " ,Coins:" << usernow.coin << " ,Exp Points:" << usernow.exp;
					} else {
						strStream << "识别编号:" << usernow.useruid << " ,名字:" << usernow.firstname << " ,姓氏:" << usernow.lastname << " ,默认语言:" << usernow.language << "\n权限:" << usernow.permission << " ,硬币:" << usernow.coin << " ,经验:" << usernow.exp;
					}
					MessageChain msg = MessageChain().Plain(strStream.str());
					strStream.clear();
					m.QuoteReply(msg);
					return;
				}
				if (plain.substr(0, 16) == "/wm wmscriptPHP ") {
					string text;
					string fitstr = plain;
					fitstr = fitstr.replace(0, 16, "");
					while (fitstr.find("\n") != fitstr.npos) {
						fitstr = fitstr.replace(fitstr.find("\n"), 1, "//endl//");
					}
					while (fitstr.find("##") != fitstr.npos) {
						fitstr = fitstr.replace(fitstr.find("##"), 2, "//rem//");
					}
					fitstr = wmscriptPHP(fitstr);
					text = fitstr;
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain.substr(0, 12) == "/wm netping ") {
					try {
						string text;
						string fitstr;
						fitstr = UTF8ToANSI(plain.replace(0, 12, ""));
						const char* charccc;
						charccc = fitstr.c_str();
						text = GetCmdInfo(charccc);
						MessageChain msg = MessageChain().Plain(text);
						m.QuoteReply(msg);
					} catch (const std::exception& ex) {
						cout << ex.what();
						MessageChain msg = MessageChain().Plain(ex.what());
						m.QuoteReply(msg);
					}
					return;
				}
				if (plain.substr(0, 13) == "/wm nslookup ") {
					try {
						string text;
						string fitstr;
						fitstr = UTF8ToANSI(plain.replace(0, 13, ""));
						const char* charccc;
						charccc = fitstr.c_str();
						text = GetCmdInfoI(charccc);
						MessageChain msg = MessageChain().Plain(text);
						m.QuoteReply(msg);
					}
					catch (const std::exception& ex) {
						cout << ex.what();
						MessageChain msg = MessageChain().Plain(ex.what());
						m.QuoteReply(msg);
					}
					return;
				}
				if (plain.substr(0, 19) == "/wm mcserverstatus ") {
					string text;
					string fitstr = plain;
					fitstr = fitstr.replace(0, 19, "");
					fitstr = wmbotmcserverstatus(fitstr.substr(0, fitstr.find(" ")), fitstr.substr(fitstr.find(" ")+1));
					text = fitstr;
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}

				if (plain.substr(0, 14) == "/wm rootadmin ") {
					MessageChain msg = MessageChain().Plain("Fatal Error : Neurons short-circuit. \nWarning : You has been recorded because you might had an overflow usage. Overflow usage is the action disabled in WMBot end-user rules. So all of your active will be recorded.Please stop the banned action. Your account will be blocked if you still skip this warning.");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm debug DistributedProcessing")
				{
					string text;
					stringstream strStream;
					strStream << "不能启动分布式处理 : 仅找到 1 个处理节点";
					text = strStream.str();
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm debug CurrentMessage")
				{
					string text;
					stringstream strStream;
					strStream << m.Sender.ToString();
					text = strStream.str();
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm debug rand")
				{
					string text;
					stringstream strStream;
					strStream << (rand() % 100) << "," << (rand() % 100) << "," << (rand() % 100) << "," << (rand() % 100) << "," << (rand() % 100) << "," << (rand() % 100) << "," << (rand() % 100) << "," << (rand() % 100) << "," << (rand() % 100) << "," << (rand() % 100) << "," << (rand() % 100) << "," << (rand() % 100);
					text = strStream.str();
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm debug virtual:universe -new -res default -pos 0")
				{
					string text;
					stringstream strStream;
					strStream << "Fatal Error\nAt universe.new();\nAt universe.wmscript[Line 7743]\nAt int main();\nAt main.cpp[Line 237]\nSystem fatal error during running WMBot.exe , contant your system admin.";
					text = strStream.str();
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm debug readpermissiongroup")
				{
					string text;
					stringstream strStream;
					strStream << m.Sender.Group.GID.ToInt64();
					text = strStream.str();
					strStream << "," << readpermissiongroup(text);
					text = strStream.str();
					strStreamtmp.clear();
					strStreamtmp.str("");
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				if (plain.substr(0, 22) == "/wm debug taskinfo id ") {
					string text;
					stringstream strStream;
					int intvald;
					string fitstr = plain;
					fitstr = fitstr.replace(0, 22, "");
					strStream << fitstr;
					strStream >> intvald;
					strStream.clear();
					strStream.str("");
					intvald = floor(intvald);
					if (intvald > 255) {
						text = "Error : Argument is not a intval";
						MessageChain msg = MessageChain().Plain(text);
						m.QuoteReply(msg);
						return;
					}
					if (intvald < 0) {
						text = "Error : Argument is not a intval";
						MessageChain msg = MessageChain().Plain(text);
						m.QuoteReply(msg);
						return;
					}
					if (tasklist[intvald].init == 0) {
						strStream << "Task not initialized";
					}
					else {
						strStream << "init:" << tasklist[intvald].init << ",id:" << tasklist[intvald].id << ",name:" << tasklist[intvald].name << ",description:" << tasklist[intvald].description;
					}
					MessageChain msg = MessageChain().Plain(strStream.str());
					strStream.clear();
					strStream.str("");
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm debug diskstatus") {
					DWORDLONG i64FreeBytesToCaller = 0;
					DWORDLONG i64TotalBytes = 0;
					DWORDLONG i64FreeBytes = 0;
					GetDiskFreeSpaceExA("C:\\", (PULARGE_INTEGER)&i64FreeBytesToCaller,
						(PULARGE_INTEGER)&i64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes);
					string text;
					stringstream strStream;
					strStream << "Total : " << (double)((double)i64TotalBytes / (double)1024 / (double)1024 / (double)1024) << " GB,Free : " << (double)((double)i64FreeBytes / (double)1024 / (double)1024 / (double)1024) << " GB";
					MessageChain msg = MessageChain().Plain(strStream.str());
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm debug diskstatus2") {
					stringstream strStream;
					DWORD dwLen = GetLogicalDriveStrings(0, NULL);	//获取系统字符串长度.
					char* pszDriver = new char[dwLen];				//构建一个相应长度的数组.
					GetLogicalDriveStrings(dwLen, pszDriver);		//获取盘符字符串.
					vector<string> v;
					while (*pszDriver != '\0')
					{
						//strStream << pszDriver << " ---- " << endl;
						v.push_back(pszDriver);
						pszDriver += strlen(pszDriver) + 1;			//定位到下一个字符串.加一是为了跳过'\0'字符串.
					}

					int DType;
					int si = 0;
					BOOL fResult;
					unsigned _int64 i64FreeBytesToCaller;
					unsigned _int64 i64TotalBytes;
					unsigned _int64 i64FreeBytes;

					for (int i = 0; i < dwLen / 4; ++i)
						//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
					{
						DType = GetDriveType(v[i].c_str());
						//GetDriveType函数，可以获取驱动器类型，参数为驱动器的根目录
						if (DType == DRIVE_FIXED)
						{
							strStream << "硬盘";
						}
						else if (DType == DRIVE_CDROM)
						{
							strStream << "光驱";
						}
						else if (DType == DRIVE_REMOVABLE)
						{
							strStream << "可移动式磁盘";
						}
						else if (DType == DRIVE_REMOTE)
						{
							strStream << "网络磁盘";
						}
						else if (DType == DRIVE_RAMDISK)
						{
							strStream << "虚拟RAM磁盘";
						}
						else if (DType == DRIVE_UNKNOWN)
						{
							strStream << "未知设备";
						}

						fResult = GetDiskFreeSpaceEx(
							v[i].c_str(),
							(PULARGE_INTEGER)&i64FreeBytesToCaller,
							(PULARGE_INTEGER)&i64TotalBytes,
							(PULARGE_INTEGER)&i64FreeBytes);
						//GetDiskFreeSpaceEx函数，可以获取驱动器磁盘的空间状态,函数返回的是个BOOL类型数据
						if (fResult)//通过返回的BOOL数据判断驱动器是否在工作状态
						{
							strStream << " totalspace:" << (double)((double)i64TotalBytes / (double)1024 / (double)1024 / (double)1024) << " GB";//磁盘总容量
							strStream << " freespace:" << (double)((double)i64FreeBytesToCaller / (double)1024 / (double)1024 / (double)1024) << " GB";//磁盘剩余空间
						}
						else
						{
							strStream << " 设备未准备好";
						}
						strStream << endl;
						si += 4;
					}
					MessageChain msg = MessageChain().Plain(strStream.str());
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm debug readpermissionuser")
				{
					string textrrr = usernow.permission;
					MessageChain msg = MessageChain().Plain("Your permission : " + textrrr);
					m.QuoteReply(msg);
					return;
				}
				if (plain == "/wm debug usernow")
				{
					stringstream strStream;
					strStream << "useruid:" << usernow.useruid << " firstname:" << usernow.firstname << " lastname:" << usernow.lastname << "\npermission:" << usernow.permission << " coin:" << usernow.coin << " exp:" << usernow.exp;
					MessageChain msg = MessageChain().Plain(strStream.str());
					strStream.clear();
					m.QuoteReply(msg);
					return;
				}
				/*if (plain == "/wm debug getDesktop") {
					m.QuoteReply(MessageChain().Plain(getScreenCapture()));
					return;
				}*/
				if (plain == "/wm debug guessc 0")
				{
					if (guesscinit != 0) 
					{
						MessageChain msg;
						msg = MessageChain().Plain("不允许同时执行多个guessc线程");
						m.QuoteReply(msg);
						return;
					}
					guesscinit = 1;
					guesscinitgroup = m.Sender.Group.GID.ToInt64();
					guesscanswer = "Never gonna give you up";
					guessccoverpath = "X:\\WMProject1217\\WMBot\\Library\\Image\\Common\\Cover\\0.png";
					GroupImage gImg = bot.UploadGroupImage(guessccoverpath);
					MessageChain msg;
					msg = MessageChain().Plain("曲绘竞猜:您有 32 秒的时间回答。") + MessageChain().Image(gImg);
					m.QuoteReply(msg);
					Sleep(32 * 1000);
					MessageChain msgi;
					msgi = MessageChain().Plain("正确答案: " + guesscanswer) + MessageChain().Image(gImg);
					m.QuoteReply(msgi);
					guesscinit = 0;
					return;
				}
				if (guesscinit == 1)
				{
					string guesscinitgrouptest = "";
					guesscinitgrouptest = m.Sender.Group.GID.ToInt64();
					if (guesscinitgroup == guesscinitgrouptest)
					{
						if (plain.find(guesscanswer, 0) != -1) {
							string text;
							stringstream strStream,ssra,ssrb;
							strStream << "恭喜，您是第一个回答正确的，获得 8 个硬币。";
							double coinget = 8;
							double intcoin, intcoina;
							ssra << usernow.coin;
							ssra >> intcoina;
							intcoin = intcoina + coinget;
							ssrb << intcoin;
							writecoinuser(usernow.useruid, ssrb.str());
							text = strStream.str();
							MessageChain msg = MessageChain().Plain(text);
							m.QuoteReply(msg);
							GroupImage gImg = bot.UploadGroupImage(guessccoverpath);
							guesscinit = 2;
							return;
						}
					}
				}

				if (plain.substr(0, 20) == "/wm joingroupverify ") {
					stringstream ssrc, ssrd;
					string fitstr = plain.replace(0, 20, "");
					ssrc << m.Sender.Group.GID.ToInt64();
					ssrd << m.Sender.QQ.ToInt64();
					int ff = joingroupverifycheck(ssrd.str(), ssrc.str(),fitstr);
					if (ff == 0) {
						MessageChain msg = MessageChain().Plain("Successful verify!");
						m.QuoteReply(msg);
						return;
					} else if (ff == -1) {
						//MessageChain msg = MessageChain().Plain(userfirstname + "看起来不需要使用此指令");
						MessageChain msg = MessageChain().Plain(userfirstname + " doesn't seem necessary to send this.");
						m.QuoteReply(msg);
						return;
					} else if (ff == 1) {
						MessageChain msg = MessageChain().Plain("Verify fail!");
						m.QuoteReply(msg);
						return;
					}
				}
				if (plain.substr(0, 5) == "/wm t") {
					MessageChain msg = MessageChain().Plain("Fatal Error : Neurons short-circuit. \nWarning : You has been recorded because you might had an overflow usage. Overflow usage is the action disabled in WMBot end-user rules. So all of your active will be recorded.Please stop the banned action. Your account will be blocked if you still skip this warning.");
					m.QuoteReply(msg);
					return;
					/*stringstream ssrd;
					string fitstr = plain.replace(0, 5, "");
					while (fitstr.find("\n") != fitstr.npos) {
						fitstr = fitstr.replace(fitstr.find("\n"), 1, "//endl//");
					}
					while (fitstr.find("##") != fitstr.npos) {
						fitstr = fitstr.replace(fitstr.find("##"), 2, "//rem//");
					}
					ssrd << m.Sender.QQ.ToInt64();
					string ff = wmbotmemory(ssrd.str(),  fitstr);
					MessageChain msg = MessageChain().Plain(ff);
					m.QuoteReply(msg);
					return;*/
				}
				if (m.Sender.Group.GID.ToInt64() == 859682537) {
					if (plain == "透我") {
						MessageChain msg = MessageChain().Plain("啪啪啪");
						m.QuoteReply(msg);
						return;
					}
				}
				if (plain == "/wm ping")
				{
					string text;
					stringstream strStream;
					timeend = clock();		//程序结束用时
					double endtime = (double)((double)timeend - (double)timestart) / CLOCKS_PER_SEC;
					if (usernow.language == "en-us") {
						strStream << "Cja ~~ pong! [" << endtime << "s][Debug:clockticks=" << (double)((double)timeend - (double)timestart) << ",CLOCKS_PER_SEC:" << CLOCKS_PER_SEC << ",start:" << timestart << ",end:" << timeend << "]";
					} else {
						strStream << "啪! [" << endtime << "s][Debug:clockticks=" << (double)((double)timeend - (double)timestart) << ",CLOCKS_PER_SEC:" << CLOCKS_PER_SEC << ",start:" << timestart << ",end:" << timeend << "]";
					}
					text = strStream.str();
					MessageChain msg = MessageChain().Plain(text);
					m.QuoteReply(msg);
					return;
				}
				return;
			}
			catch (const std::exception& ex)
			{
				systemlog(ex.what());
			}
		});
 
	bot.On<FriendMessage>(
		[&](FriendMessage fm)
		{
			systemlog(fm.ToString());
		});

	bot.On<MemberJoinRequestEvent>(
		[&](MemberJoinRequestEvent newMember)
		{
			systemlog(newMember.ToString());
		});

	bot.On<MemberJoinEvent>(
		[&](MemberJoinEvent e)
		{
			string textrcc;
			stringstream strStreamrcc,ssrc,ssrd;
			strStreamrcc << e.NewMember.Group.GID.ToInt64();
			textrcc = strStreamrcc.str();
			strStreamrcc.clear();
			strStreamrcc.str("");
			strStreamrcc << readpermissiongroup(textrcc);
			textrcc = strStreamrcc.str();
			strStreamrcc.clear();
			strStreamrcc.str("");
			if (textrcc == "None") {
				return;
			}
			systemlog(e.ToString());
			ssrc << e.NewMember.Group.GID.ToInt64();
			ssrd << e.NewMember.QQ.ToInt64();
			string aa = joingroupverify(ssrd.str(),ssrc.str());
			if (aa == "-1") {
				string memberName = e.NewMember.MemberName;
				bot.SendMessage(e.NewMember.Group.GID, MessageChain().Plain("本群加入 " + memberName + " 。"));
				return;
			} else {
				string memberName = e.NewMember.MemberName;
				bot.SendMessage(e.NewMember.Group.GID, MessageChain().Plain("本群加入 " + memberName + " 。\n发送 /wm joingroupverify " + aa + " 进行验证(这不是必须的)"));
				return;
			}
		});
 
	bot.On<MemberLeaveEventKick>(
		[&](MemberLeaveEventKick e)
		{
			string textrcc;
			stringstream strStreamrcc;
			strStreamrcc << e.Member.Group.GID.ToInt64();
			textrcc = strStreamrcc.str();
			strStreamrcc.clear();
			strStreamrcc.str("");
			strStreamrcc << readpermissiongroup(textrcc);
			textrcc = strStreamrcc.str();
			strStreamrcc.clear();
			strStreamrcc.str("");
			if (textrcc == "None") {
				return;
			}
			auto mc = MessageChain().Plain("本群踢出 " + e.Member.MemberName + " 。");
			bot.SendMessage(e.Member.Group.GID, mc);
			systemlog(e.ToString());
		});
 
	bot.On<MemberLeaveEventQuit>(
		[&](MemberLeaveEventQuit e)
		{
			string textrcc;
			stringstream strStreamrcc;
			strStreamrcc << e.Member.Group.GID.ToInt64();
			textrcc = strStreamrcc.str();
			strStreamrcc.clear();
			strStreamrcc.str("");
			strStreamrcc << readpermissiongroup(textrcc);
			textrcc = strStreamrcc.str();
			strStreamrcc.clear();
			strStreamrcc.str("");
			if (textrcc == "None") {
				return;
			}
			auto mc = MessageChain().Plain("本群离开 " + e.Member.MemberName + " 。");
			bot.SendMessage(e.Member.Group.GID, mc);
			systemlog(e.ToString());
		});

	bot.On<GroupRecallEvent>(
		[&](GroupRecallEvent e)
		{
			systemlog(e.ToString());
		});

	bot.On<MemberMuteEvent>([&](MemberMuteEvent e)
		{
			systemlog(e.ToString());
		});

	bot.On<MemberUnmuteEvent>([&](MemberUnmuteEvent e)
		{
			systemlog(e.ToString());
		});

	bot.On<GroupMuteAllEvent>([&](GroupMuteAllEvent e)
		{
			systemlog(e.ToString());
		});

	bot.OnEventReceived<NewFriendRequestEvent>(
		[&](NewFriendRequestEvent newFriend)
		{
			systemlog(newFriend.ToString());
			newFriend.Accept();
		});

	bot.On<BotMuteEvent>(
		[&](BotMuteEvent e)
		{
			systemlog(e.ToString());
		});
 
	bot.On<BotUnmuteEvent>(
		[&](BotUnmuteEvent e)
		{
			systemlog(e.ToString());
		});
 
	bot.On<BotLeaveEventKick>(
		[&](BotLeaveEventKick e)
		{
			systemlog(e.ToString());
		});
 
	bot.On<BotOnlineEvent>(
		[&](BotOnlineEvent e)
		{
			systemlog(e.ToString());
		});
 
	bot.On<BotOfflineEventActive>(
		[&](BotOfflineEventActive e)
		{
			systemlog(e.ToString());
		});
 
	bot.On<BotOfflineEventForce>(
		[&](BotOfflineEventForce e)
		{
			systemlog(e.ToString());
		});
 
	bot.On<BotOfflineEventDropped>(
		[&](BotOfflineEventDropped e)
		{
			systemlog(e.ToString());
		});
 
	bot.On<BotReloginEvent>(
		[&](BotReloginEvent e)
		{
			systemlog(e.ToString());
		});
 
	bot.EventLoop();
 
	return 0;
}