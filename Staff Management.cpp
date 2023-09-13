#include "Staff Management.h"
#include <fstream>
#include <cstdio>

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
	cin.ignore();

	if (name == "exit" || age == "exit" || email == "exit" || role == "exit" || phone == "exit")
	{
		StaffManagement();
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

		cin.get();
		StaffManagement();
	}

}
void staff::Remove()
{
	string r_name, name;
	system("cls");
	cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
	cout << "\t\t\t Please enter the staff's name you want to remove: "; cin >> name;
	cin.ignore();

	if (name == "exit")
	{
		StaffManagement();
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
					r_name.replace(r_name.find(name), r_name.length(), "");

					if (!r_name.empty())
					{
						file_r1 << r_name << endl;
					}
				}
				cout << "\t\t\t Staff " << name << " has now been removed.\n\n";
				changes += 1;
				file_r.close();
				file_r1.close();

				const char* f_r = tempFile.c_str();
				const char* f_r1 = copyFile.c_str();
				std::remove(f_r);
				std::rename(f_r1, f_r);

				cin.get();
				StaffManagement();
			}
		}
		else
		{
			cout << "\t\t\t This staff is not in this file.\n\n";
			cin.get();
			Remove();
		}
	}
}
void staff::update()
{
	string u_name, name, age, email, role, phone, u_info;
	system("cls");
	cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
	cout << "\t\t\t Please enter the staff's name you want to update: "; cin >> u_name;
	cin.ignore();

	if (u_name == "exit")
	{
		StaffManagement();
	}
	else
	{
		if (search(tempFile, u_name, u_info) == true)
		{
			system("cls");
			cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
			cout << "\t\t\t Please enter staff's info!\n\n";
			cout << "\t\t\t Staff's name: "; cin >> name;
			cout << "\t\t\t Staff's age: "; cin >> age;
			cout << "\t\t\t Staff's email: "; cin >> email;
			cout << "\t\t\t Staff's role: "; cin >> role;
			cout << "\t\t\t Staff's phone: "; cin >> phone;
			cin.ignore();

			if (name == "exit" || age == "exit" || email == "exit" || role == "exit" || phone == "exit")
			{
				StaffManagement();
			}
			else
			{
				ofstream file_u1(copyFile, ios::app | ios::binary);
				ifstream file_u(tempFile, ios::in | ios::binary);
				if (!file_u)
				{
					openFail();
				}
				else
				{
					while (getline(file_u, u_info))
					{
						u_info.replace(u_info.find(u_name), u_info.length(), "");
						if (!u_info.empty())
						{
							file_u1 << u_info << endl;
						}
						else
						{
							file_u1 << name << " " << age << " " << email << " " << role << " " << phone << endl;
						}
					}
					cout << "\t\t\t Staff " << name << " has now been updated.\n\n";
					changes += 1;
					file_u.close();
					file_u1.close();

					const char* f_u = tempFile.c_str();
					const char* f_u1 = copyFile.c_str();
					std::remove(f_u);
					std::rename(f_u1, f_u);

					cin.get();
					StaffManagement();
				}
			}
		}
		else
		{
			cout << "\t\t\t This staff is not in this file.\n\n";
			cin.get();
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

	cin.get();
	StaffManagement();
}
void staff::openFail()
{
	system("cls");
	cout << "\t\t\t Cannot open user data files!\n\n\n";
	cout << "\t\t\t Please try again!";
	cin.get();
	StaffManagement();
}
void staff::save()
{
	system("cls");

	if (changes > 0 )
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

	cin.get();
	StaffManagement();
}
void staff::Search()
{
	string nameDisplay, staffInfo, staffName, staffAge, staffEmail, staffRole, staffPhone;
	system("cls");
	cout << "\t\t\t You can go back by typing \"exit\"!\n\n";
	cout << "\t\t\t Please enter the staff's name you want to display: "; cin >> nameDisplay;
	cin.ignore();

	if (nameDisplay == "exit")
	{
		StaffManagement();
	}
	else
	{
		if (search(tempFile, nameDisplay, staffName) == true)
		{
			ifstream file_ind(tempFile, ios::in | ios::binary);
			if (!file_ind)
			{
				openFail();
			}
			else
			{
				while (getline(file_ind, staffInfo))
				{
					if (staffInfo.find(nameDisplay) != string::npos)
					{
						fstream file_temp(copyFile, ios::app | ios::in | ios::binary);
						file_temp << staffInfo;
						while (file_temp >> staffName >> staffAge >> staffEmail >> staffRole >> staffPhone)
						{
							cout << "\t\t\t Staff's name: " << staffName << endl;
							cout << "\t\t\t Staff's age: " << staffAge << endl;
							cout << "\t\t\t Staff's email: " << staffEmail << endl;
							cout << "\t\t\t Staff's role: " << staffRole << endl;
							cout << "\t\t\t Staff's phone: " << staffPhone << "\n\n\n";
						}
						file_temp.close();

						const char* f = copyFile.c_str();
						std::remove(f);
					}
				}
				file_ind.close();

				cin.get();
				StaffManagement();
			}
		}
		else
		{
			cout << "\t\t\t This staff is not in this file.\n\n";
			cin.get();
			Search();
		}
	}
}
void staff::quit()
{
	system("cls");
	if (changes > 0)
	{

	}
	else
	{

	}

}
bool search(string filename, string s_name, string list_name)
{
	staff Staff;
	fstream file_find(filename, ios::app | ios::in | ios::binary);
	if (!file_find)
	{
		Staff.openFail();
	}
	else
	{
		while (getline(file_find, list_name))
		{
			if (list_name.find(s_name) != string::npos)
			{
				return true;
				break;
			}
			else
			{
				return false;
			}
		}
		file_find.close();
	}
}
void StaffManagement()
{
	staff staff;
	string copy_line;
	ifstream fileorig(mainFile, ios::app | ios::binary);
	ofstream filecopy(tempFile, ios::in | ios::binary);
	if (!fileorig || !filecopy)
	{
		staff.openFail();
	}
	else
	{
		while (getline(fileorig, copy_line))
		{
			filecopy << copy_line << "\n";
		}
	}
	fileorig.close();
	filecopy.close();
}
