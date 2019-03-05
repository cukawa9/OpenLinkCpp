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

//system open the command line, need ignore it.
_declspec(dllexport) void openlink(std::string myurl) {
	system(std::string("start " + myurl).c_str());
}

_declspec(dllexport) void openlink_shell(std::string myurl) {
	ShellExecute(NULL, L"open", LPCWSTR(myurl.c_str()), NULL, NULL, SW_SHOW);
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