#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<vector>
#include<iomanip>

using namespace std;

//___________________________________________________________________________________________________

string fileName = "clientsData.txt";

struct stClientRecord {
	string accountNumber, pinCode, clientName, phone;
	double balance;
};

enum enMainMenu { showList = 1, addClient = 2, deleteClient = 3, updateClient = 4, findClient = 5,transactions = 6 ,Exit = 7 };
enum enTransactions { Deposit = 1, Withdraw = 2, totalBalances = 3, mainMenu = 4};
//___________________________________________________________________________________________________

// Functions Declaration

void showMainMenu(vector<stClientRecord>& vClientsRecord);
bool isAccountNumberExist(vector<stClientRecord>& vClientsRecord, string accountNumber, short& accountPosition);

void performTransactionsOptions(enTransactions selectChoice, vector<stClientRecord>& vClientsRecord, short& accountPosition);
void showTransactionScreen(vector<stClientRecord>& vClientsRecord, short& accountPosition);

//___________________________________________________________________________________________________

// Files Functions

string fromStclientRecordToLine(stClientRecord& clientRecord, string seperator = "#//#") {


	string clientRecordLine = "";

	clientRecordLine += clientRecord.accountNumber + seperator;
	clientRecordLine += clientRecord.clientName + seperator;
	clientRecordLine += clientRecord.pinCode + seperator;
	clientRecordLine += clientRecord.phone + seperator;
	clientRecordLine += to_string(clientRecord.balance);

	return clientRecordLine;
}

stClientRecord fromLinetoStClientRecord(string clientRecordLine, string seperator = "#//#") {

	stClientRecord clientRecord;


	// from string line to vector of lines (strings) [split] ....

	vector<string> vrecords;
	short pos = 0;

	while ((pos = clientRecordLine.find(seperator)) != string::npos) {

		vrecords.push_back(clientRecordLine.substr(0, pos));
		clientRecordLine.erase(0, pos + seperator.length());
	}

	if ((pos = clientRecordLine.find(seperator)) == string::npos) {
		vrecords.push_back(clientRecordLine.substr(0, clientRecordLine.length() - 1));
	}
	// from vector of lines (strings) to record ....

	clientRecord.accountNumber = vrecords[0];
	clientRecord.clientName = vrecords[1];
	clientRecord.pinCode = vrecords[2];
	clientRecord.phone = vrecords[3];
	clientRecord.balance = stod(vrecords[4]);
	return clientRecord;
}

void loadDataFromVectorTofile(string fileName, vector<stClientRecord>& vClientsRecord) {

	fstream myFile;
	myFile.open(fileName, ios::out);

	if (myFile.is_open()) {

		for (stClientRecord record : vClientsRecord) {

			myFile << fromStclientRecordToLine(record) << endl;
		}
		myFile.close();
	}
}

vector<stClientRecord> loadDataFromFileToStVector(string fileName) {

	vector<stClientRecord> vClientsRecord;
	fstream myFile;
	myFile.open(fileName, ios::in);

	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			vClientsRecord.push_back(fromLinetoStClientRecord(line));
		}
	}
	return vClientsRecord;
}

//___________________________________________________________________________________________________

int readNumberFromTo(int from, int to) {

	int number;

	do {
		cin >> number;

		if (number < from || number > to || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please entre a number between " << from << "-" << to << " : ";
		}

	} while (number < from || number > to);

	return number;
}

string readString() {

	string myString;
	getline(cin >> ws, myString);
	return myString;
}

float readPositiveNumber() {

	float number;
	bool inputFail = false;

	do {
		cin >> number;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input... Please entre a number: ";
			inputFail = true;
		}

		if (number < 0) {
			cout << "Please Entre a Positive Number! .... ";
			inputFail = false;
		}

	} while (number < 0 || inputFail);

	return number;
}

char readChar() {

	char myChar;
	bool isValidInput = false;

	do {
		cin >> myChar;
		myChar = tolower(myChar);

		if (myChar != 'y' && myChar != 'n') {
			cout << "Please Entre y or n ...\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			isValidInput = true;
		}

	} while (!isValidInput);

	return myChar;
}

void printClientRecord(stClientRecord clientRecord) {


	cout << "|  " << setw(15) << left << clientRecord.accountNumber;
	cout << "|  " << setw(10) << left << clientRecord.pinCode;
	cout << "|  " << setw(40) << left << clientRecord.clientName;
	cout << "|  " << setw(12) << left << clientRecord.phone;
	cout << "|  " << setw(12) << left << clientRecord.balance;
}

void printAllRecords(vector<stClientRecord> vClientsRecord) {

	cout << "           " << "Client List (" << vClientsRecord.size() << ") " << "Clients." << endl;
	for (int i = 0; i < 100; i++) {
		cout << "_";
	}
	cout << "\n\n";
	cout << "|  " << left << setw(15) << "Account-number";
	cout << "|  " << left << setw(10) << "Pin-code";
	cout << "|  " << left << setw(40) << "Name";
	cout << "|  " << left << setw(12) << "Phone";
	cout << "|  " << left << setw(12) << "Balance";
	cout << "\n";

	for (stClientRecord& record : vClientsRecord) {
		printClientRecord(record);
		cout << endl;
	}
}

void printClientCard(stClientRecord stClientrecord) {
	for (int i = 0; i < 50; i++) {
		cout << "=";
	}
	cout << "\n";
	cout << setw(30) << "   The Following Are The Client's Details..\n";
	cout << "\n       Account Number : " << stClientrecord.accountNumber;
	cout << "\n       Pin Code       : " << stClientrecord.pinCode;
	cout << "\n       Name           : " << stClientrecord.clientName;
	cout << "\n       Phone          : " << stClientrecord.phone;
	cout << "\n       Account Balance: " << stClientrecord.balance;
	cout << endl;
	for (int i = 0; i < 50; i++) {
		cout << "=";
	}
	cout << "\n";
}

void addNewClient(vector<stClientRecord>& vClientsRecord, short &accountPosition) {

	stClientRecord stNewClient;


	do {

		system("cls");
		cout << "Adding New Client ..\n";
		cout << "Enter Client's Name: ";
		stNewClient.clientName = readString();
		cout << "Enter Client's Account Number: ";
		stNewClient.accountNumber = readString();

		while (isAccountNumberExist(vClientsRecord, stNewClient.accountNumber,accountPosition)) {
			system("cls");
			cout << "Account " << stNewClient.accountNumber << " already exist..\n";
			cout << "\nPlease entre a different account number: ";
			stNewClient.accountNumber = readString();
		}

		
		cout << "Enter Client's Pin-Code: ";
		stNewClient.pinCode = readString();
		cout << "Enter Client's Phone Number: ";
		stNewClient.phone = readString();
		cout << "Enter Client's Balance: ";
		stNewClient.balance = readPositiveNumber();

		vClientsRecord.push_back(stNewClient);
		cout << "\n\nClient added successfully...\n";
		cout << "Do you want to Add more clients? y/n\n\n";


	} while (readChar() == 'y');


}

void addClients(vector<stClientRecord>& vClientsRecord, short& accountPosition) {

	addNewClient(vClientsRecord,accountPosition);

}

void deleteClientByAccountNumber(vector<stClientRecord>& vClientsRecord, short& accountPosition) {

	cout << "Entre Account Number you want to delete: ";
	string accountNumber = readString();

	if (isAccountNumberExist(vClientsRecord, accountNumber,accountPosition)) {
		
	
			cout << "\nAre you sure you want to delete this client? y/n\n";
			if (readChar() == 'y') {
				vClientsRecord.erase(vClientsRecord.begin() + accountPosition);
				cout << "\nAccount " << accountNumber << " deleted successfully";
				
			}
		
		
	}
	else {
		cout << "Account " << accountNumber << " doesn't exist..";
	}
}

void updateClientByAccountNumber(vector<stClientRecord>& vClientsRecord, short& accountPosition) {

	cout << "Entre Account Number you want to update: ";
	string accountNumber = readString();

	if (isAccountNumberExist(vClientsRecord, accountNumber,accountPosition)) {

			cout << "\nAre you sure you want to update this client? y/n\n";
			if (readChar() == 'y') {
				cout << "Update client's info...\n";
			    cout << "Update Name: ";
				vClientsRecord[accountPosition].clientName = readString();
				cout << "Update Pin-Code: ";
				vClientsRecord[accountPosition].pinCode = readString();
				cout << "Update Phone: ";
				vClientsRecord[accountPosition].phone = readString();
				cout << "Update Balance: ";
				vClientsRecord[accountPosition].balance = readPositiveNumber();
				cout << "\nAccount " << accountNumber << " Updated successfully";
				
			}
	}
	else {
		cout << "Account " << accountNumber << " doesn't exist..";
	}
}

bool isAccountNumberExist(vector<stClientRecord>& vClientsRecord, string accountNumber, short &accountPosition) {

	for (short i = 0; i < vClientsRecord.size(); i++ ) {

		if (vClientsRecord[i].accountNumber == accountNumber) {
			accountPosition = i;
			printClientCard(vClientsRecord[i]);
			return true;
		}
	}
	return false;
}

void returnToMainMenu(vector<stClientRecord>& vClientsRecord) {
	cout << "\n\nPress Enter to go back to Main Menu..." << endl;
	system("pause>0");
	showMainMenu(vClientsRecord);
}

void exitProgram(vector<stClientRecord>& vClientsRecord) {

	cout << "\nAre you sure you want to Exit the program? y/n\n";
	if (readChar() == 'y') {
		exit(0);
	}
	else {
		returnToMainMenu(vClientsRecord);
	}
}

void performMainMenuOption(enMainMenu selectChoice, vector<stClientRecord>& vClientsRecord) {
	
	string accountNumber = "";
	short accountPosition = 0;

	switch (selectChoice) {
	case enMainMenu::showList: system("cls"); printAllRecords(vClientsRecord); returnToMainMenu(vClientsRecord); break;
	case enMainMenu::addClient: system("cls"); addClients(vClientsRecord,accountPosition); returnToMainMenu(vClientsRecord); break;
	case enMainMenu::findClient: system("cls"); cout << "Enter Account Number: "; accountNumber = readString();if (!isAccountNumberExist(vClientsRecord, accountNumber, accountPosition)) { cout << "Account " << accountNumber << " doesn't exist.."; }; returnToMainMenu(vClientsRecord); break;
	case enMainMenu::deleteClient: system("cls"); deleteClientByAccountNumber(vClientsRecord,accountPosition); returnToMainMenu(vClientsRecord); break;
	case enMainMenu::updateClient: system("cls"); updateClientByAccountNumber(vClientsRecord,accountPosition); returnToMainMenu(vClientsRecord); break;
	case enMainMenu::transactions: system("cls"); showTransactionScreen(vClientsRecord,accountPosition); system("pause>0"); break;
	case enMainMenu::Exit: system("cls");loadDataFromVectorTofile(fileName,vClientsRecord); exitProgram(vClientsRecord); break;
	}
}

void showMainMenu(vector<stClientRecord>& vClientsRecord) {

	system("cls");

	for (int i = 0; i < 50; i++) {
		cout << "=";
	}
	cout << "\n";
	cout << "                   " << "Main Menu\n";

	for (int i = 0; i < 50; i++) {
		cout << "=";
	}

	cout << "\n";

	cout << "           " << "[1] Show Client List.\n";
	cout << "           " << "[2] Add New Client.\n";
	cout << "           " << "[3] Delete Client.\n";
	cout << "           " << "[4] Update Client Info.\n";
	cout << "           " << "[5] Find Client.\n";
	cout << "           " << "[6] Transactions.\n";
	cout << "           " << "[7] Exit.\n";

	for (int i = 0; i < 50; i++) {
		cout << "=";
	}

	cout << "\n           Select your option [1] - [7]\n";
	performMainMenuOption(enMainMenu(readNumberFromTo(1, 7)), vClientsRecord);
}

//___________________________________________________________________________________
// Bank Extension

void showTransactionScreen(vector<stClientRecord>& vClientsRecord, short& accountPosition) {


	system("cls");

	for (int i = 0; i < 50; i++) {
		cout << "=";
	}
	cout << "\n";
	cout << "           " << "Transactions Menu Screen\n";

	for (int i = 0; i < 50; i++) {
		cout << "=";
	}

	cout << "\n";

	cout << "           " << "[1] Deposit.\n";
	cout << "           " << "[2] Withdraw.\n";
	cout << "           " << "[3] Total Balances.\n";
	cout << "           " << "[4] Main Menu.\n";


	for (int i = 0; i < 50; i++) {
		cout << "=";
	}

	cout << "\n           Select your option [1] - [4]\n";

	performTransactionsOptions(enTransactions(readNumberFromTo(1, 4)), vClientsRecord, accountPosition);
}

void deposit(vector<stClientRecord>& vClientsRecord, short& accountPosition) {
	cout << "Entre Account Number you want to Deposit to: ";
	string accountNumber = readString();

	if (isAccountNumberExist(vClientsRecord, accountNumber, accountPosition)) {
		double depositAmount = 0;
		cout << "Entre the amount you want to deposit: ";
		depositAmount = (readPositiveNumber());

		cout << "\nAre you sure you want to deposit " << depositAmount << " to client " << accountNumber << "? y/n\n";
		if (readChar() == 'y') {
			
			vClientsRecord[accountPosition].balance += depositAmount;
			cout << "\nTransaction Completed...\n";
		}
	}
	else {
		cout << "Account " << accountNumber << " doesn't exist..";
	}

}

void withdraw(vector<stClientRecord>& vClientsRecord, short& accountPosition) {
	cout << "Entre Account Number you want to withdraw from: ";
	string accountNumber = readString();

	if (isAccountNumberExist(vClientsRecord, accountNumber, accountPosition)) {
		double withdrawAmount = 0;
		cout << "\nyour current Balance is " << vClientsRecord[accountPosition].balance << endl;
		cout << "Entre the amount you want to withdraw: ";

			withdrawAmount = (readPositiveNumber());

			if (withdrawAmount > vClientsRecord[accountPosition].balance) {
				cout << " Not enough balance to proceed..";
			}
			else {
				cout << "\nAre you sure you want to withdraw " << withdrawAmount << " from client " << accountNumber << "? y/n\n";

				if (readChar() == 'y') {

					vClientsRecord[accountPosition].balance -= withdrawAmount;
					cout << "\nTransaction Completed...\n";
				}
			}

	}
	else {
		cout << "Account " << accountNumber << " doesn't exist..";
	}

}

float calcTotalBalances(vector<stClientRecord>& vClientsRecord) {

	float totalBalances = 0;

	for (int i = 0; i < vClientsRecord.size(); i++) {

		totalBalances += vClientsRecord[i].balance;
	}

	return totalBalances;
}

void returnToTransactionMenu(vector<stClientRecord>& vClientsRecord, short& accountPosition) {

	cout << "\n press any key to go back...";
	system("pause>0");
	showTransactionScreen(vClientsRecord, accountPosition);
}

void performTransactionsOptions(enTransactions selectChoice, vector<stClientRecord>& vClientsRecord, short& accountPosition){
	
	switch (selectChoice) {
	case enTransactions::Deposit:system("cls"); deposit(vClientsRecord, accountPosition);returnToTransactionMenu(vClientsRecord,accountPosition) ; break;
	case enTransactions::Withdraw:system("cls"); withdraw(vClientsRecord, accountPosition);returnToTransactionMenu(vClientsRecord,accountPosition) ; break;
	case enTransactions::totalBalances:system("cls"); cout << "\n\nTotal Balances of ALL accounts is: " << calcTotalBalances(vClientsRecord);returnToTransactionMenu(vClientsRecord,accountPosition); break;
	case enTransactions::mainMenu:returnToMainMenu(vClientsRecord); break;

	}
}


int main() {

	
	vector<stClientRecord> vClientsRecord = loadDataFromFileToStVector(fileName);
	showMainMenu(vClientsRecord);
	system("pause>0");
	return 0;

}




