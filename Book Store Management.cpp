#include "Staff Management.h"
#include "Store Management.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void openFail();
void login(bool& result);
void registration();

int main()
{
	//Login page
	bool IsLoggedIn = false;
	while (!IsLoggedIn)
	{
		string choice;
		cout << "\t\t\t____________________________________________________________________\n\n\n";
		cout << "\t\t\t             Welcome to the Login Page of The Bookstore!            \n\n\n";
		cout << "\t\t\t____________________________     MENU    ___________________________\n\n\n";
		cout << "\t|	Press 1 for LOGIN                      |" << endl;
		cout << "\t|	Press 2 for REGISTER                   |" << endl;
		cout << "\t|	Press 3 for EXIT                       |" << endl;
		cout << "\n\t\t\tPlease enter your choice: ";
		cin >> choice;
		cin.ignore();
		cout << endl;

		if (choice == "1")
		{
			login(IsLoggedIn);
		}
		else if (choice == "2")
		{
			registration();
		}
		else if (choice == "3")
		{
			cout << "\t\t\t Thank you!! Have a great day!";
			exit(0);
		}
		else
		{
			system("cls");
			cout << "\t\t\t Please enter the given option above!\n\n";
			cin.get();
		}
	}

	//The Bookstore Page
	cout << "\t\t\t Please wait for the next feature!!!";
}

//Functions here
void openFail()
{
	system("cls");
	cout << "\t\t\t Cannot open user data files!\n\n\n";
	cout << "\t\t\t Please try again!";
	cin.get();
}

void login(bool& result)
{
	int success = 0;
	string username, password, user, pass;
	system("cls");
	cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
	cout << "\t\t\t Please enter username and password!\n";
	cout << "\t\t\t Username: ";
	cin >> username;
	cout << "\t\t\t Password: ";
	cin >> password;
	cin.ignore();

	if (username == "exit" || pass == "exit")
	{
		main();
	}
	else
	{
		ifstream filein("user_data.txt", ios::in | ios::binary);
		if (!filein)
		{
			openFail();
		}
		else
		{
			while (filein >> user >> pass)
			{
				if (user == username && pass == password)
				{
					success = 1;
					break;
				}
			}
			system("cls");
			filein.close();

			if (success == 1)
			{
				cout << "\t\t\t Login successfully as user: " << username << endl;
				result = true;
				cin.get();
			}
			else
			{
				cout << "\t\t\t Login failed! Please check your username and password!\n\n\n";
				cin.get();
				login(result);
			}
			filein.close();
		}
	}
}

void registration()
{
	string r_Username, r_Password, r_user;
	system("cls");
	cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
	cout << "\t\t\t Enter the username: ";
	cin >> r_Username;
	cout << "\t\t\t Enter the password: ";
	cin >> r_Password;
	cin.ignore();

	if (r_Username == "exit" || r_Password == "exit")
	{
		main();
	}
	else
	{
		fstream fileout("user_data.txt", ios::app | ios::in | ios::binary);
		if (!fileout)
		{
			openFail();
		}
		else
		{
			while (getline(fileout, r_user))
			{
				if (r_user.find(r_Username) != string::npos)
				{
					cout << "\t\t\t User has already been added!\n";
					cin.get();
					registration();
				}
				else
				{
					fileout << r_Username << ' ' << r_Password << endl;
					system("cls");
					cout << "\t\t\t You are now registered!\n\n";
					cin.get();
				}
			}
			fileout.close();
		}
	}
}