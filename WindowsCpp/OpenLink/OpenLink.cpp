// OpenLink.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <shellapi.h>
#include <iostream>
#include <string>
#include "SimpleIni.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

_declspec(dllexport) int add(int a, int b)
{
	return a + b;
}

_declspec(dllexport) int subtract(int a, int b)
{
	return a - b;
}


std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}


//system open the command line, need ignore it.
_declspec(dllexport) void openlink(std::string myurl) {
	system(std::string("start " + myurl).c_str());
}

_declspec(dllexport) void openlink_shell(std::string myurl) {
	//ShellExecute(NULL, L"open", LPCWSTR(myurl.c_str()), NULL, NULL, SW_SHOW);
	std::wstring stemp = s2ws(myurl);
	LPCWSTR address = stemp.c_str();

	string open = "open";
	std::wstring opentemp = s2ws(open);
	LPCWSTR openlw = opentemp.c_str();

	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = openlw;
	ShExecInfo.lpFile = address;
	cout << myurl.c_str() << endl;
	ShExecInfo.lpParameters = (LPCWSTR)"";
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
	LPDWORD lpExitCode = 0;
	GetExitCodeProcess(ShExecInfo.hProcess, lpExitCode);
}



_declspec(dllexport) string readlink(string filename) {
	CSimpleIni ini;
	ini.SetUnicode();
	ini.LoadFile(LPCWSTR(filename.c_str()));
	const wchar_t * pVal = ini.GetValue(L"link", L"address", NULL);

	// Your wchar_t*
	wstring ws(pVal);
	// your new String
	string str(ws.begin(), ws.end());
	// Show String
	return str;
}

_declspec(dllexport) string readlinkfromxml(string filename) {
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());
	tinyxml2::XMLElement *info = doc.RootElement();
	const char *address = info->FirstChildElement("address")->GetText();

	return address;
}