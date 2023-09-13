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

void StaffManagement();
bool search(string filename, string s_name, string f_name);
void goBackOrQuit();