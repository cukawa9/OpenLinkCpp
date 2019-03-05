// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;



//extern int add(int a,int b);
_declspec(dllimport) int add(int a, int b);
_declspec(dllimport) int subtract(int a, int b);
_declspec(dllimport) void openlink(string url);
_declspec(dllimport) void openlink_shell(std::string myurl);
_declspec(dllimport) string readlink(string filename);
_declspec(dllimport) string readlinkfromxml(string filename);

int main()
{
	/*string str = "http://www.baidu.com";
	openlink_shell(str);*/
	string filename = "C:\\GitRepo\\OpenLinkCpp\\WindowsCpp\\Test\\test.xml";
	/*string content = readlink(filename);
	cout << content.c_str() << endl;*/
	//TCHAR dbserver[1000];
	//::GetPrivateProfileString(L"link", L"address", 0, dbserver, sizeof(dbserver) / sizeof(dbserver[0]), LPCWSTR(filename.c_str()));
	//wstring ws(dbserver);
	//// your new String
	//string str(ws.begin(), ws.end());
	//cout << str.c_str() << endl;

	
	string address = readlinkfromxml(filename);
	cout << address.c_str() << endl;
	openlink_shell(address);
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
