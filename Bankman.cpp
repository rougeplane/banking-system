#include <iostream>
#include <fstream>	// for file streaming
#include<iomanip>
#include<stdlib.h>
using namespace std;
//====================================================//
/*Creating a struct for using variables multiple times*/
//====================================================//
struct bankaccounts
{
	char name[50];
	int accno;
	double amount;
};

//=======================================//
//    FUNCTIONS TO BE USED IN CODE       //
//=======================================//

//Fuction to write to file (create account)//
//=========================================//
void writeBankaccount(bankaccounts data, int ac){
	ofstream fileToSave;
	fileToSave.open("Accountdetails.txt",ios::app);  // ios append prevents overwritting of file everytime.
	fileToSave.write(reinterpret_cast<char *> (&data), sizeof(bankaccounts));//reinterpret_cast is a type of casting operator used in C++
	fileToSave.close();
}

//Fuction to read from file//
//     Balance enquiry    //
//========================//
void readAccountData(int accNO){
	bankaccounts data;
	ifstream fileToRead;
	bool flag = false;
	fileToRead.open("Accountdetails.txt");
	if(!fileToRead)
	{
		cout<<"File could not be opened !!!!!!!! Press any Key to cointinue...";
		return;
	}
	while(fileToRead.read(reinterpret_cast<char *> (&data), sizeof(bankaccounts))){
		if (data.accno == accNO){
			cout << "The data we have for account number " << accNO << " is:" << endl;
			cout << "Name of account holder: " << data.name << endl;
			cout << "Balance: " << data.amount << endl;
			flag = true;
			return;
		}
	}
	fileToRead.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";

}
//Fuction to retrieve all accounts information//
//============================================//
void displayAllAccounts(){
	bankaccounts data;
	ifstream fileToRead;
	fileToRead.open("Accountdetails.txt");
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.          NAME               Balance\n";
	cout<<"====================================================\n";
	while(fileToRead.read(reinterpret_cast<char *> (&data), sizeof(bankaccounts))){
		cout << data.accno << setw(20) << data.name << setw(23) << data.amount << endl;
	}
	fileToRead.close();
}



// Function to close account //
//===========================//
void close_account(int del)
{
	bankaccounts data;
	ifstream enterfile;
	ofstream outputfile;
	enterfile.open("Accountdetails.txt");
	if(!enterfile)
	{
		cout<<"File could not be opened !!!!! Press any Key to continue...";
		return;
	}
	outputfile.open("Temporary.txt");
	enterfile.seekg(0,ios::beg);
	while(enterfile.read(reinterpret_cast<char *> (&data), sizeof(bankaccounts)))
	{
		if(data.accno != del)
		{
			outputfile.write(reinterpret_cast<char *> (&data), sizeof(bankaccounts));
		}
	}
	enterfile.close();
	outputfile.close();
	remove("Accountdetails.txt");
	rename("Temporary.txt" , "Accountdetails.txt");
	cout<< endl << endl << "\tRecord Deleted ..";
}

// Function to deposit amount //
// ===========================//
void deposit(int accNo, int dep){
	bool flag = false;
	bankaccounts data;
	fstream File;
	File.open("Accountdetails.txt");
	if(!File)
	{
		cout<<"File could not be opened !!!!! Press any Key to continue...";
		return;
	}
	while (!File.eof() && flag == false)
	{
		File.read(reinterpret_cast<char *> (&data), sizeof(bankaccounts));
			if(data.accno == accNo){
				data.amount += dep;
				int pos=(-1)*static_cast<int>(sizeof(data));    // Takes the data size and turns the output -ve 
				File.seekp(pos,ios::cur); // moves the cursor back by one data size
				File.write(reinterpret_cast<char *> (&data), sizeof(bankaccounts)); // writes the updated values and continues on.
				cout<<"\n\n\t Amount deposited \n\n";
				flag=true;
			}
	}
	File.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";

}

// Function to withdraw amount //
// ============================//

void withdraw(int accNo, int dep){
	bool flag = false;
	bankaccounts data;
	fstream File;
	File.open("Accountdetails.txt");
	if(!File)
	{
		cout<<"File could not be opened !!!!! Press any Key to continue...";
		return;
	}
	while (!File.eof() && flag == false) // ! is used to reverse .eof() output.
	{
		File.read(reinterpret_cast<char *> (&data), sizeof(bankaccounts));
			if(data.accno == accNo){
				data.amount -= dep;
				int pos=(-1)*static_cast<int>(sizeof(data)); // Takes the data size and turns the output -ve 
				File.seekp(pos,ios::cur); // moves the cursor back by one data size
				File.write(reinterpret_cast<char *> (&data), sizeof(bankaccounts)); // writes the updated values and continues on.
				cout<<"\n\n\t Amount withdrawn \n\n";
				flag=true;
			}
	}
	File.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";

}


//Credits//
//=======//
void credits()
{
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tMANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nMADE BY : Ahmed & Daniyal";
	cout<<"\n\nUniversity : LUMS";
	cin.get();
}


//=======================================//
//             Main code                 //
//=======================================//




int main () {
	struct bankaccounts  data;
	int aNo;
	int add;
	int i;
	credits();
	while(true) {
		i = 0;
		cout << "\n\n****************** M A I N  M E N U ********************* \n";		
		cout << "Select 1 for creating account\n";
		cout << "Select 2 for deposit\n";
		cout << "Select 3 for withdrawl\n";
		cout << "Select 4 for enquiry of account details\n";
		cout << "Select 5 for list of all accounts\n";
		cout << "Select 6 for closing account\n";
		cout << "Select 7 for Exit the menu\n";
		cout << "\n************************************************************ \n\n";		
		cin >> i;
		if (i <= 0 || i > 7) {
			cout << "Invalid option selected";
		} else if( i == 1) {
			cout << "Enter account number: ";
			cin >> data.accno;
			aNo = data.accno;
			cout << "Enter your name: ";
			cin.ignore();
			cin.getline(data.name,50);
			do{
				cout << "Enter deposit amount more than 500: ";
				cin >> data.amount;
				if(data.amount <=500){
					cout << "Insufficient amount used!!!!!!!\n\n";
				}
			}
			while (data.amount <= 500);
			cout << "========Account created========\n\n";
			writeBankaccount(data, aNo);
		} else if ( i == 2) {
			cout << "Enter the account number to deposit: ";
			cin >> aNo;
			cout << "Enter amount to be deposited: ";
			cin >> add;
			deposit(aNo, add);
		}else if ( i == 3) {
			cout << "Enter the account number to withdraw: ";
			cin >> aNo;
			cout << "Enter amount to be withdrawn: ";
			cin >> add;
			withdraw(aNo, add);
		}else if (i == 4) {
			cout << "\nAcount Number: ";
			cin >> aNo;
			readAccountData(aNo);
		} else if ( i == 5) {
			displayAllAccounts();
		}else if ( i == 6) {
			cout << "Enter account number to close: ";
			cin >> aNo;
			close_account(aNo);
		}else if ( i == 7) {
			cout<<"=====Thanks for using BANK MANAGEMENT SYSTEM====="<<endl;
			exit(0);
		}
		
		char a;
		cout << "Press any key to continue"<< endl;
		cin >> a;
		system("CLS");
	}
	return 0;
}


//***************************************************************
//    			END OF PROJECT😄
//***************************************************************