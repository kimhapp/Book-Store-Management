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

		system("cls");

		cout << "\t\t\t____________________________________________________________________\n\n\n";
		cout << "\t\t\t             Welcome to the Login Page of The Bookstore!            \n\n\n";
		cout << "\t\t\t____________________________     MENU    ___________________________\n\n\n";
		cout << "\t|	Enter 1 for LOGIN                      |" << endl;
		cout << "\t|	Enter 2 for REGISTER                   |" << endl;
		cout << "\t|	Enter 3 for EXIT                       |" << endl;
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
			system("PAUSE");
		}
	}

	//The Bookstore Page
	while (IsLoggedIn)
	{
		string user_choice;

		system("cls");

		cout << "\t\t\t____________________________________________________________________\n\n\n";
		cout << "\t\t\t             Welcome to the Main Page of The Bookstore!            \n\n\n";
		cout << "\t\t\t____________________________     MENU    ___________________________\n\n\n";
		cout << "\t|	Enter 1 for STAFF MANAGING                       |" << endl;
		cout << "\t|	Enter 2 for STORE MANAGING                       |" << endl;
		cout << "\t|	Enter 3 if you wanna know more what our store    |" << endl;
		cout << "\t|	Enter 4 for EXIT                                 |" << endl;
		cout << "\n\t\t\tPlease enter your choice: ";
		cin >> user_choice;
		cin.ignore();
		cout << endl;

		if (user_choice == "1")
		{
			StaffManagement();
		}
		else if (user_choice == "2")
		{
			cout << "\t\t\t Sorry, feature available soon!\n";
			system("PAUSE");
		}
		else if (user_choice == "3")
		{
			cout << "\t\t\t Sorry, feature available soon!\n";
			system("PAUSE");
		}
		else if (user_choice == "4")
		{
			cout << "\t\t\t Thank you!! Have a great day!";
			IsLoggedIn = false;
		}
		else
		{
			system("cls");
			cout << "\t\t\t Please enter the given option above!\n\n";
			system("PAUSE");
		}
	}
}

//Functions here
void openFail()
{
	system("cls");
	cout << "\t\t\t Cannot open user data files!\n\n\n";
	cout << "\t\t\t Please try again!";
	system("PAUSE");
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
				system("PAUSE");
			}
			else
			{
				cout << "\t\t\t Login failed! Please check your username and password!\n\n\n";
				system("PAUSE");
				login(result);
			}
			filein.close();
		}
	}
}

void registration()
{
	int found = 0;
	string r_Username, r_Password, r_user;
	system("cls");
	cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
	cout << "\t\t\t Enter the username: ";
	cin >> r_Username;
	cout << "\t\t\t Enter the password: ";
	cin >> r_Password;

	if (r_Username == "exit" || r_Password == "exit")
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
			while (getline(filein, r_user))
			{
				if (r_user.find(r_Username) != string::npos)
				{
					found += 1;
					break;
				}
			}
			filein.close();

			if (found == 1)
			{
				cout << "\t\t\t User has already been added!\n";
				system("PAUSE");
				registration();
			}
			else 
			{
				ofstream fileout("user_data.txt", ios::app | ios::binary);
				fileout << r_Username << ' ' << r_Password << endl;
				system("cls");
				cout << "\t\t\t You are now registered!\n\n";
				system("PAUSE");
			}
		}
	}
}