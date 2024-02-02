#include<iostream>
#include <string>
#include <list>
#include<Windows.h>
#include<fstream>
using namespace std;
struct user_info {
	float id_number;
	char age[50];//Date of birth
	string name;
	double amount_deposit = NULL, total_amount = 0;
};
struct admin {
	string username, password;
};
void write_to_file(list<user_info>l)
{
	fstream bank_data;
	bank_data.open("BANKDATA.txt", ios::out | ios::app);
	if (!bank_data.is_open())
	{
		cout << "ERROR..FILE NOT OPENED......" << endl;
	}
	else
	{
		list<user_info>::iterator i;

		for (i = l.begin(); i != l.end(); i++)
		{

			bank_data << (*i).id_number << "  ";
			bank_data << (*i).name << " ";
			bank_data << (*i).age << " ";
			bank_data << (*i).amount_deposit << " ";
			(*i).total_amount = ((*i).amount_deposit + (*i).total_amount);
			bank_data << (*i).total_amount << endl;


		}

		bank_data.close();
	}
}
void read_data_from_file(user_info u)
{
	ifstream bank_data;
	bank_data.open("BANKDATA.txt", ios::in);

	if (bank_data.is_open())
	{
		bank_data >> u.id_number >> u.name >> u.age >> u.amount_deposit >> u.total_amount;
		while (!bank_data.eof())
		{
			cout << "\nUser's Name is: \t";
			cout << u.name;
			cout << "\nUser's ID number is: \t";
			cout << u.id_number;
			cout << "\nUser's Age is: \t";
			cout << u.age;
			cout << "\nTotal amount in account is: \t";
			cout << u.total_amount;
			cout << endl << endl;
			bank_data >> u.id_number >> u.name >> u.age >> u.amount_deposit >> u.total_amount;

		}
		bank_data.close();
	}


}
void search_user(user_info u, float x)
{
	int a = 0;
	ifstream bank_data;
	bank_data.open("BANKDATA.txt", ios::in);

	if (bank_data.is_open())
	{
		bank_data >> u.id_number >> u.name >> u.age >> u.amount_deposit >> u.total_amount;
		while (!bank_data.eof())
		{
			if (x == u.id_number)
			{
				cout << "\nUser's Name is: \t";
				cout << u.name;
				cout << "\nUser's ID number is: \t";
				cout << u.id_number;
				cout << "\nUser's Date of birth is: \t";
				cout << u.age;
				cout << "\nTotal amount in account is: \t";
				cout << u.total_amount;
				cout << endl << endl;
				a++;
			}
			bank_data >> u.id_number >> u.name >> u.age >> u.amount_deposit >> u.total_amount;
		}

		bank_data.close();
		if (a == 0)
		{
			cout << "ID NOT FOUND.." << endl;
		}
	}

}
void insert_data(user_info n, list<user_info>& l)
{
	cout << "Enter User's ID number:\t";
	cin >> n.id_number;
	cout << "\nEnter User's Name(Without spaces):\t";
	cin >> n.name;
	cout << "\nEnter user's Date of birth(DD-MM-YYYY):\t";
	cin >> n.age;
	cout << "\nEnter the amount to deposit:\t";
	cin >> n.amount_deposit;
	l.push_back(n);
	write_to_file(l);

	cout << endl << endl;


}
void delete_user(user_info u, float rem_id)
{

	int a = 0;
	fstream temp, bank_data;
	bank_data.open("BANKDATA.txt", ios::in);
	if (!bank_data.is_open())
	{
		cout << "\nERROR IN OPENING FILE.........." << endl;
	}
	else
	{

		temp.open("temp1.txt", ios::app | ios::out);
		bank_data >> u.id_number >> u.name >> u.age >> u.amount_deposit >> u.total_amount;
		while (!bank_data.eof())
		{
			if (rem_id == u.id_number)
			{
				cout << "\t\t\t\tRECORD DELETED........" << endl;
				a++;
			}
			else
			{
				temp << u.id_number << " " << u.name << " " << u.age << " " << u.amount_deposit << " " << u.total_amount << endl;
			}
			bank_data >> u.id_number >> u.name >> u.age >> u.amount_deposit >> u.total_amount;
		}
		bank_data.close();
		temp.close();
		remove("BANKDATA.txt");
		rename("temp1.txt", "BANKDATA.txt");
		if (a == 0)
		{
			cout << "ID NOT FOUND.........." << endl;
		}
	}





}
void reset()
{
	string a;
	cout << "DO YOU WISH TO RESET ALL THE RECORDS (y/n)?\t";
	cin >> a;
	if (a == "y")
	{


		fstream bank_data("BANKDATA.txt", ios::out);
		string data, mssg;
		mssg = { " " };
		if (bank_data.is_open())
		{
			bank_data << mssg;



		}
	}
	else if (a == "n")
	{
		cout << "\t\t\t\tABORTING.........";
	}
}
void main_interface(admin n, user_info u, list<user_info>l)
{
	int a = 0;
	string b;
	while (a != 6)
	{
		cout << "\n\n\n\t\t\t\tWhich operation do you want to perform?\n\n\n\n";
		cout << "Press 1 if you want to Add a new user...\nPress 2 if you want to delete an existing User's data...\nPress 3 if you want to search a user...\nPress 4 if you want to display all records...\nPress 5 to Reset......\nPress 6 to exit...\nChoose your desired option:\t";
		cin >> a;
		if (a == 1)
		{
			system("cls");
			insert_data(u, l);

		}
		if (a == 2)
		{
			system("cls");
			float x;
			cout << "\n\nEnter ID number to delete:  ";
			cin >> x;
			delete_user(u, x);

		}
		if (a == 3)
		{
			system("cls");
			float x;
			cout << "Enter the ID number you want to search:\t";
			cin >> x;
			cout << "\n\n\t\t\t\t\t\tDISPLAYING RECORD....\n\t\t\t===========================================================================\n\n\n\n\n";
			search_user(u, x);
		}
		if (a == 4)
		{
			system("cls");
			cout << "\t\t\t\t\t\tDISPLAYING ALL RECORDS....\n\t\t\t==========================================================================\n\n\n\n\n";

			read_data_from_file(u);


		}

		if (a == 5)
		{
			reset();
			cout << "\t\t\t\tRESET COMPELETE.....";
		}
		string x;
		cout << "\nPress ok to continue....";
		cin >> x;
		if (a == 6)
		{
			cout << "Logging out...";


		}

		system("cls");

	}

}
void Admin(admin n, user_info u, list<user_info>l)
{

	cout << "\n\t\t\t\t\t\tACCOUNT LOGIN\n\t\t\t=====================================================================";
	cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter Username:\t";
	cin >> n.username;
	cout << "\n\t\t\t\t\t\tEnter Password:\t";
	cin >> n.password;
	if (n.username == "1" && n.password == "1")
	{
		system("cls");

		cout << "WELCOME BACK........\n\n\n" << endl;

		main_interface(n, u, l);

	}
	else
	{
		cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tUsername or password is incorrect....\n\t\t\t\t\tTRY AGAIN......" << endl;
		Admin(n, u, l);
	}

}
void deposit_money(user_info u)
{
	double x;
	fstream temp, bank_data;
	bank_data.open("BANKDATA.txt", ios::in);
	/*if (!bank_data.is_open())
	{
		cout << "\nERROR IN OPENING FILE.........." << endl;
	}
	else
	{
		cout << "How much do you want to deposit?  ";
		cin >> x;
		bank_data >> u.id_number >> u.name >> u.age >> u.amount_deposit >> u.total_amount;
		u.total_amount = x + u.total_amount;
		string data;
		while (getline(bank_data, data))
		{
			
			temp << u.id_number << " " << u.name << " " << u.age << " " << u.amount_deposit << " " << u.total_amount << endl;

			bank_data >> u.id_number >> u.name >> u.age >> u.amount_deposit >> u.total_amount;
		}*/
		temp.open("temp12.txt", ios::out | ios::app);
		bank_data.close();
		temp.close();
		remove("BANKDATA.txt");
		rename("temp12.txt", "BANKDATA.txt");


	
}
void user(user_info u)
{
	int a = 0, y = -1, x;
	float num;
	system("cls");
	cout << "Enter you ID number:\t";
	cin >> num;
	fstream bank_data;
	bank_data.open("BANKDATA.txt", ios::in | ios::out);
	bank_data >> u.id_number >> u.name >> u.age >> u.amount_deposit >> u.total_amount;
	if (!bank_data.is_open())
	{
		cout << "\n\n\t\t\t\t\tERROR FILE NOT OPENED SUCCESSFULLY......\n";
	}
	else
	{
		while (!bank_data.eof())
		{
			if (num == u.id_number)
			{
				while (y != 0)
				{
					cout << "Press 1 for account details......\nPress 2 to deposit amount\nPress 3 to withdraw amount\nPress 0 to exit\nSelect your choice:\t";
					cin >> y;
					if (y == 1)
					{
						cout << "\nUser's Name is: \t";
						cout << u.name;
						cout << "\nUser's ID number is: \t";
						cout << u.id_number;
						cout << "\nUser's Date of birth is: \t";
						cout << u.age;
						cout << "\nTotal amount in account is: \t";
						cout << u.total_amount;
						cout << endl << endl;


					}
					if (y == 2)
					{

						deposit_money(u);

					}
					if (y == 0)
					{
						exit(0);
					}
					if (y == 0)
					{
						exit(0);
					}
				}

				a++;
				cout << "PRESS 0 TO EXIT......\t";


			}
			bank_data >> u.id_number >> u.name >> u.age >> u.amount_deposit;
		}

		bank_data.close();
		if (a == 0)
		{
			cout << "\n\n\t\t\t\tID NOT FOUND...\n\t\t\t\tExiting the program........." << endl;
			exit(0);


		}
	}
}
int main()
{
	int m = 0;

	user_info n;
	admin a;
	list<user_info> l;
	cout << "\n\t\t\t\t\tWELCOME TO BANK MANAGEMENT SYSTEM\n\t\t\t=====================================================================" << endl << endl << endl;
	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\tPress 1 for admin interface\n\t\t\t\t\tPress 2 for User interface\n\t\t\t\t\tPress 3 to exit\n\t\t\t\t\tEnter your choice:\t";
	cin >> m;
	if (m == 1)
	{
		system("cls");
		Admin(a, n, l);
	}
	if (m == 2)
	{
		user(n);
	}
	if (m == 3)
	{
		exit(0);
	}






}