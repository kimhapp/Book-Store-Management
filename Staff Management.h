#pragma once
#include <iostream>
#include <string>
using namespace std;

class staff
{
private:
	int changes = 0;
public:
	void add();
	void Remove();
	void openFail();
	void update();
	void Search();
	void display();
	void save();
	void quit();
};

string mainFile = "Staff.txt";
string tempFile = "Staff_Temp.txt";
string copyFile = "Staff_Temp1.txt";

void StaffManagement();
bool search(string filename, string s_name, string f_name);