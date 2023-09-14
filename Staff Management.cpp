#include "Staff Management.h"
#include <fstream>
#include <cstdio>

string mainFile = "Staff.txt";
string tempFile = "Staff_Temp.txt";
string copyFile = "Staff_Temp1.txt";

void staff::add()
{
	string s_info, name, age, email, role, phone;
	system("cls");
	cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
	cout << "\t\t\t Please enter staff's info!\n\n";
	cout << "\t\t\t Staff's name: "; cin >> name;
	cout << "\t\t\t Staff's age: "; cin >> age;
	cout << "\t\t\t Staff's email: "; cin >> email;
	cout << "\t\t\t Staff's role: "; cin >> role;
	cout << "\t\t\t Staff's phone: "; cin >> phone;
	cout << endl;

	if (name == "exit" || age == "exit" || email == "exit" || role == "exit" || phone == "exit")
	{
		system("PAUSE");
	}
	else
	{
		if (search(tempFile, name, s_info) == true)
		{
			cout << "\t\t\t Staff is already in the data.\n";
		}
		else
		{
			ofstream file_a(tempFile, ios::app | ios::binary);
			file_a << name << ' ' << age << ' ' << email << ' ' << role << ' ' << phone << endl;
			file_a.close();
			cout << "\t\t\t Staff " << name << " has now been added to the data.\n\n";
			changes += 1;
		}

		system("PAUSE");
	}

}
void staff::Remove()
{
	int line = 0, lineFound = 0;
	string r_name, name;
	system("cls");
	cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
	cout << "\t\t\t Please enter the staff's name you want to remove: "; cin >> name;
	cout << endl;
	cin.ignore();

	if (name == "exit")
	{
		system("PAUSE");
	}
	else
	{
		if (search(tempFile, name, r_name) == true)
		{
			ofstream file_r1(copyFile, ios::app | ios::binary);
			ifstream file_r(tempFile, ios::in | ios::binary);
			if (!file_r)
			{
				openFail();
			}
			else
			{
				while (getline(file_r, r_name))
				{
					line++;
					if (r_name.find(name) != string::npos)
					{
						lineFound = line;
					}
				}

				for (int i = 0; i < line; i++)
				{
					if (i != lineFound)
					{
						file_r1 << r_name << endl;
					}

					cout << "\t\t\t Staff " << name << " has now been removed.\n\n";
					changes += 1;
					file_r.close();
					file_r1.close();

					const char* f_r = tempFile.c_str();
					const char* f_r1 = copyFile.c_str();
					std::remove(f_r);
					std::rename(f_r1, f_r);

					system("PAUSE");
				}
			}
		}
		else
		{
			cout << "\t\t\t This staff is not in this file.\n\n";
			system("PAUSE");
			Remove();
		}
	}
}
void staff::update()
{
	int line = 0, lineFound = 0 ;
	string name, u_name, age, u_age , email, u_email, role, u_role, phone, u_phone, u_info;
	system("cls");
	cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
	cout << "\t\t\t Please enter the staff's name you want to update: "; 
	cin >> name;

	if (u_name == "exit")
	{
		system("PAUSE");
	}
	else
	{
		if (search(tempFile, name, u_name) == true)
		{
			ofstream file_u1(copyFile, ios::app | ios::binary);
			ifstream file_u(tempFile, ios::in | ios::binary);
			if (!file_u)
			{
				openFail();
			}
			else
			{
				while (file_u >> u_name >> u_age >> u_email >> u_role >> u_phone)
				{
					line++;
					if (u_name == name)
					{
						lineFound = line;
					}
				}
				line = 0;

				while (getline(file_u, u_info))
				{
					line++;
					if (line != lineFound)
					{
						file_u1 << u_info << endl;
					}
				}

				system("cls");
				cout << "\t\t\t You cannot go back during updating the list.\n\n";
				cout << "\t\t\t Please enter staff's info!\n\n";
				cout << "\t\t\t Staff's name: "; cin >> name;
				cout << "\t\t\t Staff's age: "; cin >> age;
				cout << "\t\t\t Staff's email: "; cin >> email;
				cout << "\t\t\t Staff's role: "; cin >> role;
				cout << "\t\t\t Staff's phone: "; cin >> phone;

				file_u1 << name << " " << age << " " << email << " " << role << " " << phone << endl;
				cout << "\t\t\t Staff " << name << " has now been updated.\n\n";
				changes += 1;
				file_u.close();
				file_u1.close();

				const char* f_u = tempFile.c_str();
				const char* f_u1 = copyFile.c_str();
				std::remove(f_u);
				std::rename(f_u1, f_u);

				system("PAUSE");
			}
		}
		else
		{
			cout << "\t\t\t This staff is not in this file.\n\n";
			system("PAUSE");
			update();
		}
	}
}
void staff::display()
{
	string staffName, staffAge, staffEmail, staffRole, staffPhone;
	system("cls");
	cout << "\t\t\t Here is list of all staffs\n\n";

	ifstream file_All(tempFile, ios::in | ios::binary);
	if (!file_All)
	{
		openFail();
	}
	else
	{
		while (file_All >> staffName >> staffAge >> staffEmail >> staffRole >> staffPhone)
		{
			cout << "\t\t\t Staff's name: " << staffName << endl;
			cout << "\t\t\t Staff's age: " << staffAge << endl;
			cout << "\t\t\t Staff's email: " << staffEmail << endl;
			cout << "\t\t\t Staff's role: " << staffRole << endl;
			cout << "\t\t\t Staff's phone: " << staffPhone << "\n\n\n";
		}
		file_All.close();
	}

	system("PAUSE");
}
void staff::openFail()
{
	system("cls");
	cout << "\t\t\t Cannot open user data files!\n\n\n";
	cout << "\t\t\t Please try again!";
	system("PAUSE");
	StaffManagement();
}
void staff::save()
{
	system("cls");

	if (changes > 0)
	{
		const char* main_f = mainFile.c_str();
		const char* temp_f = tempFile.c_str();

		std::remove(main_f);
		std::rename(temp_f, main_f);

		cout << "\t\t\t Saved successully!\n";
		changes = 0;
	}
	else
	{
		cout << "\t\t\t You have made 0 change, no need to save!\n";
	}

	system("PAUSE");
}
void staff::Search()
{
	int found = 0;
	string nameDisplay, staffInfo, staffName, staffAge, staffEmail, staffRole, staffPhone;
	system("cls");
	cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
	cout << "\t\t\t Please enter the staff's name you want to display: "; cin >> nameDisplay;

	if (nameDisplay == "exit")
	{
		system("PAUSE");
	}
	else
	{
		if (search(tempFile, nameDisplay, staffName) == true)
		{
			ifstream file_inD(tempFile, ios::in | ios::binary);
			if (!file_inD)
			{
				openFail();
			}
			else
			{
				ofstream file_temp(copyFile, ios::app | ios::binary);
				while (getline(file_inD, staffInfo))
				{
					if (staffInfo.find(nameDisplay) != string::npos)
					{
						file_temp << staffInfo;
						found += 1;
						break;
					}
				}
				file_inD.close();
				file_temp.close();

				if (found == 1)
				{
					ifstream file_temp1(copyFile, ios::in | ios::binary);
					while (file_temp1 >> staffName >> staffAge >> staffEmail >> staffRole >> staffPhone)
					{
						cout << "\t\t\t Staff's name: " << staffName << endl;
						cout << "\t\t\t Staff's age: " << staffAge << endl;
						cout << "\t\t\t Staff's email: " << staffEmail << endl;
						cout << "\t\t\t Staff's role: " << staffRole << endl;
						cout << "\t\t\t Staff's phone: " << staffPhone << "\n\n\n";
						system("PAUSE");
					}
					file_temp1.close();

					const char* f = copyFile.c_str();
					std::remove(f);
				}
			}
		}
		else
		{
			cout << "\t\t\t This staff is not in this file.\n\n";
			system("PAUSE");
			Search();
		}
	}
}
void staff::quit()
{
	string answer;
	system("cls");
	if (changes > 0)
	{
		cout << "\t\t\t There are some changes you have made recently, do you want to save first before quitting?\n\t\t\t Please type yes or no or cancel: ";
		cin >> answer;
		cin.ignore();

		if (answer == "yes")
		{
			save();

			goBackOrQuit();
		}
		else if (answer == "no")
		{
			const char* temp_f = tempFile.c_str();

			remove(temp_f);
			changes = 0;
			
			goBackOrQuit();
		}
		else if (answer == "cancel")
		{
			cout << "\t\t\t Returning to Staff Main Menu!\n";
			system("PAUSE");
			StaffManagement();
		}
		else
		{
			cout << "\t\t\t Please input a valid answer!\n";
			system("PAUSE");
			quit();
		}
	}
	else
	{
		goBackOrQuit();
	}
}
void goBackOrQuit()
{
	string choice;
	while (choice != "quit" || choice != "back")
	{
		cout << "\t\t\t Do you want to return back to the Main Page or quit the program?\n\t\t\t Please type quit or back: ";
		cin >> choice;

		system("cls");
		if (choice == "quit")
		{
			cout << "\t\t\t Thank you!! Have a great day!\n\n\n";
			exit(0);
		}
		else if (choice == "back")
		{
			cout << "\t\t\t Returning to Main Page!\n\n\n";
			system("PAUSE");
		}
		else
		{
			cout << "\t\t\t Please input a valid answer!\n\n\n";
			system("PAUSE");
		}
	}
}
bool search(string filename, string s_name, string list_name)
{
	int found = 0;
	staff Staff;
	fstream file_find(filename, ios::app | ios::in | ios::binary);
	if (!file_find)
	{
		Staff.openFail();
		return false;
	}
	else
	{
		while (getline(file_find, list_name))
		{
			if (list_name.find(s_name) != string::npos)
			{
				found += 1;
				break;
			}
		}
		file_find.close();

		if (found == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

//The Staff Management Page
void StaffManagement()
{
	staff staff;
	string copyLine;
	ifstream fileorig(mainFile, ios::in | ios::binary);
	ofstream filecopy(tempFile, ios::app | ios::binary);
	while (getline(fileorig, copyLine))
	{
		filecopy << copyLine << "\n";
	}
	fileorig.close();
	filecopy.close();

	string staffChoice;

	while (staffChoice != "7")
	{
		system("cls");
		cout << "\t\t\t____________________________________________________________________\n\n\n";
		cout << "\t\t\t             Welcome to the Staff Page of The Bookstore!            \n\n\n";
		cout << "\t\t\t____________________________     MENU    ___________________________\n\n\n";
		cout << "\t|	Enter 1 for DISPLAY LIST               |" << endl;
		cout << "\t|	Enter 2 for SEARCH STAFF               |" << endl;
		cout << "\t|	Enter 3 for ADD STAFF                  |" << endl;
		cout << "\t|	Enter 4 for UPDATE STAFF               |" << endl;
		cout << "\t|	Enter 5 for REMOVE STAFF               |" << endl;
		cout << "\t|	Enter 6 for SAVE                       |" << endl;
		cout << "\t|	Enter 7 for QUIT                       |" << endl;
		cout << "\n\t\t\tPlease enter your choice: ";
		cin >> staffChoice;
		cin.ignore();
		cout << endl;

		if (staffChoice == "1")
		{
			staff.display();
		}
		else if (staffChoice == "2")
		{
			staff.Search();
		}
		else if (staffChoice == "3")
		{
			staff.add();
		}
		else if (staffChoice == "4")
		{
			staff.update();
		}
		else if (staffChoice == "5")
		{
			staff.Remove();
		}
		else if (staffChoice == "6")
		{
			staff.save();
		}
		else if (staffChoice == "7")
		{
			staff.quit();
		}
		else
		{
			system("cls");
			cout << "\t\t\t Please enter the given option above!\n\n";
			system("PAUSE");
		}
	}
}
