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
string adminsFileName = "adminsData.txt";



struct stClientRecord {
	string accountNumber, pinCode, clientName, phone;
	double balance;
};

struct stUserRecord {
	string userName, passWord;
	int permissions;
};


enum enMainMenu { showList = 1, addClient = 2, deleteClient = 3, updateClient = 4, findClient = 5,transactions = 6 , manageUsers = 7, Exit = 8};
enum enTransactions { Deposit = 1, Withdraw = 2, totalBalances = 3, mainMenu = 4};
enum enManageUsersMenu { listOfUsers = 1, addNewUser = 2, deleteUser = 3, updateUser = 4, findUser = 5, mainMenuGo = 6 };
enum enMainMenuPermissions{ eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClients = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64 };
//___________________________________________________________________________________________________

// Functions Declaration

void showMainMenu(vector<stClientRecord>& vClientsRecord, vector<stUserRecord>& vUsersRecord, stUserRecord &activeUserRecord);
bool isAccountNumberExist(vector<stClientRecord>& vClientsRecord, string accountNumber, short& accountPosition);

void performTransactionsOptions(enTransactions selectChoice, vector<stClientRecord>& vClientsRecord, short& accountPosition, vector<stUserRecord> &vUsersRecord, stUserRecord& activeUserRecord);
void showTransactionScreen(vector<stClientRecord>& vClientsRecord, short& accountPosition, vector<stUserRecord> &vUsersRecord, stUserRecord& activeUserRecord);


void performManageUsersOptions(enManageUsersMenu selectChoice, vector<stUserRecord> &vUsersRecord, short& accountPosition, vector<stClientRecord> vClientsRecord, short& userAccountPosition, stUserRecord& activeUserRecord);
void showManageUsersScreen(vector<stUserRecord> &vUsersRecord, short& accountPosition, vector<stClientRecord> vClientsRecord, short& userAccountPosition, stUserRecord& activeUserRecord);



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
		vrecords.push_back(clientRecordLine.substr(0, clientRecordLine.length()));
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

// Files Functions (Users/Admins)

string fromStUserRecordToLine(stUserRecord& userRecord, string seperator = "#//#") {


	string userRecordLine = "";

	userRecordLine += userRecord.userName + seperator;
	userRecordLine += userRecord.passWord + seperator;
	userRecordLine += to_string(userRecord.permissions);


	return userRecordLine;
}

stUserRecord fromLinetoStUserRecord(string userRecordLine, string seperator = "#//#") {

	stUserRecord userRecord;


	// from string line to vector of lines (strings) [split] ....

	vector<string> vrecords;
	short pos = 0;

	while ((pos = userRecordLine.find(seperator)) != string::npos) {

		vrecords.push_back(userRecordLine.substr(0, pos));
		userRecordLine.erase(0, pos + seperator.length());
	}

	if ((pos = userRecordLine.find(seperator)) == string::npos) {
		vrecords.push_back(userRecordLine.substr(0, userRecordLine.length()));
	}
	// from vector of lines (strings) to record ....

	userRecord.userName = vrecords[0];
	userRecord.passWord = vrecords[1];
	userRecord.permissions = stoi(vrecords[2]);

	return userRecord;
}

void loadDataFromVectorTofile(string adminsFileName, vector<stUserRecord>& vUsersRecord) {

	fstream myFile;
	myFile.open(adminsFileName, ios::out);

	if (myFile.is_open()) {

		for (stUserRecord record : vUsersRecord) {

			myFile << fromStUserRecordToLine(record) << endl;
		}
		myFile.close();
	}
}

vector<stUserRecord> loadDataFromAdminsFileToStVector(string adminsFileName) {

	vector<stUserRecord> vUsersRecord;
	fstream myFile;
	myFile.open(adminsFileName, ios::in);

	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			vUsersRecord.push_back(fromLinetoStUserRecord(line));
		}
	}
	return vUsersRecord;
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

void returnToMainMenu(vector<stClientRecord>& vClientsRecord, vector<stUserRecord>& vUsersRecord, stUserRecord& activeUserRecord) {
	cout << "\n\nPress Enter to go back to Main Menu..." << endl;
	system("pause>0");
	showMainMenu(vClientsRecord,vUsersRecord,activeUserRecord);
}

void exitProgram(vector<stClientRecord>& vClientsRecord, vector<stUserRecord>& vUsersRecord, stUserRecord& activeUserRecord) {

	cout << "\nAre you sure you want to Exit the program? y/n\n";
	if (readChar() == 'y') {
		exit(0);
	}
	else {
		returnToMainMenu(vClientsRecord,vUsersRecord,activeUserRecord);
	}
}

void performMainMenuOption(enMainMenu selectChoice, vector<stClientRecord>& vClientsRecord, vector<stUserRecord>& vUsersRecord, stUserRecord& activeUserRecord) {
	
	string accountNumber = "";
	short accountPosition = 0;
	short userAccountPosition = 0;

	switch (selectChoice) {
	case enMainMenu::showList: system("cls"); printAllRecords(vClientsRecord); returnToMainMenu(vClientsRecord,vUsersRecord,activeUserRecord); break;
	case enMainMenu::addClient: system("cls"); addClients(vClientsRecord,accountPosition); returnToMainMenu(vClientsRecord,vUsersRecord,activeUserRecord); break;
	case enMainMenu::findClient: system("cls"); cout << "Enter Account Number: "; accountNumber = readString();if (!isAccountNumberExist(vClientsRecord, accountNumber, accountPosition)) { cout << "Account " << accountNumber << " doesn't exist.."; }; returnToMainMenu(vClientsRecord,vUsersRecord,activeUserRecord); break;
	case enMainMenu::deleteClient: system("cls"); deleteClientByAccountNumber(vClientsRecord,accountPosition); returnToMainMenu(vClientsRecord,vUsersRecord,activeUserRecord); break;
	case enMainMenu::updateClient: system("cls"); updateClientByAccountNumber(vClientsRecord,accountPosition); returnToMainMenu(vClientsRecord,vUsersRecord,activeUserRecord); break;
	case enMainMenu::transactions: system("cls"); showTransactionScreen(vClientsRecord, accountPosition,vUsersRecord,activeUserRecord); system("pause>0"); break;
	case enMainMenu::manageUsers: system("cls"); showManageUsersScreen(vUsersRecord, accountPosition,vClientsRecord,userAccountPosition,activeUserRecord); system("pause>0"); break;
	case enMainMenu::Exit: system("cls"); loadDataFromVectorTofile(fileName, vClientsRecord); loadDataFromVectorTofile(adminsFileName,vUsersRecord); exitProgram(vClientsRecord, vUsersRecord,activeUserRecord); break;

	}
}

void showMainMenu(vector<stClientRecord>& vClientsRecord, vector<stUserRecord>& vUsersRecord, stUserRecord &activeUserRecord) {

	system("cls");

	cout << "Welcome Back " << activeUserRecord.userName << "...\n";
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
	cout << "           " << "[7] Manage Users.\n";
	cout << "           " << "[8] Exit.\n";


	for (int i = 0; i < 50; i++) {
		cout << "=";
	}

	cout << "\n           Select your option [1] - [8]\n";
	performMainMenuOption(enMainMenu(readNumberFromTo(1, 8)), vClientsRecord, vUsersRecord,activeUserRecord);
}

//___________________________________________________________________________________
// Bank Extension

void showTransactionScreen(vector<stClientRecord>& vClientsRecord, short& accountPosition, vector<stUserRecord> &vUsersRecord, stUserRecord& activeUserRecord) {


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

	performTransactionsOptions(enTransactions(readNumberFromTo(1, 4)), vClientsRecord, accountPosition,vUsersRecord,activeUserRecord);
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

void returnToTransactionMenu(vector<stClientRecord>& vClientsRecord, short& accountPosition, vector<stUserRecord> &vUsersRecord, stUserRecord& activeUserRecord) {

	cout << "\n press any key to go back...";
	system("pause>0");
	showTransactionScreen(vClientsRecord, accountPosition,vUsersRecord,activeUserRecord);
}

void performTransactionsOptions(enTransactions selectChoice, vector<stClientRecord>& vClientsRecord, short& accountPosition, vector<stUserRecord>& vUsersRecord, stUserRecord& activeUserRecord){
	
	switch (selectChoice) {
	case enTransactions::Deposit:system("cls"); deposit(vClientsRecord, accountPosition);returnToTransactionMenu(vClientsRecord,accountPosition,vUsersRecord,activeUserRecord) ; break;
	case enTransactions::Withdraw:system("cls"); withdraw(vClientsRecord, accountPosition);returnToTransactionMenu(vClientsRecord,accountPosition,vUsersRecord,activeUserRecord) ; break;
	case enTransactions::totalBalances:system("cls"); cout << "\n\nTotal Balances of ALL accounts is: " << calcTotalBalances(vClientsRecord);returnToTransactionMenu(vClientsRecord,accountPosition,vUsersRecord,activeUserRecord); break;
	case enTransactions::mainMenu:returnToMainMenu(vClientsRecord,vUsersRecord,activeUserRecord); break;

	}
}

//_____________________________________________________________________________________________
// Manage Users

void showManageUsersScreen(vector<stUserRecord>& vUsersRecord, short& accountPosition, vector<stClientRecord> vClientsRecord, short& userAccountPosition, stUserRecord& activeUserRecord) {


	system("cls");

	for (int i = 0; i < 50; i++) {
		cout << "=";
	}
	cout << "\n";
	cout << "           " << "Manage USers Menu Screen\n";

	for (int i = 0; i < 50; i++) {
		cout << "=";
	}

	cout << "\n";

	cout << "           " << "[1] List Users.\n";
	cout << "           " << "[2] Add New User.\n";
	cout << "           " << "[3] Delete User.\n";
	cout << "           " << "[4] Update User.\n";
	cout << "           " << "[5] Find User.\n";
	cout << "           " << "[6] Main Menu.\n";


	for (int i = 0; i < 50; i++) {
		cout << "=";
	}

	cout << "\n           Select your option [1] - [6]\n";

	performManageUsersOptions(enManageUsersMenu(readNumberFromTo(1, 6)), vUsersRecord, accountPosition,vClientsRecord,userAccountPosition,activeUserRecord);
}

void printUserRecord(stUserRecord userRecord) {


	cout << "|  " << setw(30) << left << userRecord.userName;
	cout << "|  " << setw(10) << left << userRecord.passWord;
	cout << "|  " << setw(10) << left << userRecord.permissions;

}

void printAllUsersRecords(vector<stUserRecord> vUsersRecord) {
	cout << "\n";
	cout << "                            " << "Users List (" << vUsersRecord.size() << ") " << "Users." << endl;
	for (int i = 0; i < 80; i++) {
		cout << "_";
	}
	cout << "\n\n";
	cout << "|  " << left << setw(30) << "User-Name";
	cout << "|  " << left << setw(10) << "Password";
	cout << "|  " << left << setw(10) << "Permissions";
	cout << "\n";

	for (stUserRecord& record : vUsersRecord) {
	
		printUserRecord(record);
		cout << endl;
	}
}

bool isUserNameExist(vector<stUserRecord>& vUsersRecord, string userName, short& userAccountPosition) {

	for (short i = 0; i < vUsersRecord.size(); i++) {

		if (vUsersRecord[i].userName == userName) {
			cout << "\n\n";
			cout << "|  " << left << setw(30) << "User-Name";
			cout << "|  " << left << setw(10) << "Password";
			cout << "|  " << left << setw(10) << "Permissions";
			cout << "\n";
			printUserRecord(vUsersRecord[i]);
			cout << "\n";
			userAccountPosition = i;
			return true;
		}
	}
	return false;
}

void findUserByUserName(vector<stUserRecord>& vUsersRecord, short& userAccountPosition) {

	cout << "Enter User Name: ";
	string userName = readString();

	if (!isUserNameExist(vUsersRecord, userName, userAccountPosition)) {
		cout << "User Name " << userName << " does not exist...\n";
	}
}

void addUser(vector<stUserRecord>& vUserRecord, short& userAccountPosition) {

	stUserRecord stNewUser;
	enMainMenuPermissions enUserPermission;

	do {

		system("cls");
		cout << "Adding New User ..\n";
		cout << "Enter User's Name: ";
		stNewUser.userName = readString();

		while (isUserNameExist(vUserRecord, stNewUser.userName, userAccountPosition)) {
			system("cls");
			cout << "User-name " << stNewUser.userName << " already exist..\n";
			cout << "\nPlease entre a different user name: ";
			stNewUser.userName = readString();
		}

		cout << "Enter Client's Password: ";
		stNewUser.passWord = readString();

		cout << "Do you want to give full access? y/n ";

		if (readChar() == 'y') {
			
			stNewUser.permissions = -1;

		}

		else {

			stNewUser.permissions = 0;
			cout << "Do you want to give access to....\n";
			cout << "Show Clients List? y/n \n";

			if (readChar() == 'y') {

				stNewUser.permissions |= enMainMenuPermissions::pListClients;
			
			}

			cout << "Add Client? y/n \n";

			if (readChar() == 'y') {

				stNewUser.permissions |= enMainMenuPermissions::pAddNewClient;
				
			}

			cout << "Delete Client? y/n \n";

			if (readChar() == 'y') {

				stNewUser.permissions |= enMainMenuPermissions::pDeleteClient;
				
			}

			cout << "Update Client? y/n \n";

			if (readChar() == 'y') {

				stNewUser.permissions |= enMainMenuPermissions::pUpdateClients;
				
			}

			cout << "Find Clients? y/n \n";

			if (readChar() == 'y') {

				stNewUser.permissions |= enMainMenuPermissions::pFindClient;
				
			}

			cout << "Transactions? y/n \n";

			if (readChar() == 'y') {

				stNewUser.permissions |= enMainMenuPermissions::pTransactions;
				
			}

			cout << "Manage Users? y/n \n";

			if (readChar() == 'y') {

				stNewUser.permissions |= enMainMenuPermissions::pManageUsers;
				
			}

		}

		cout << stNewUser.permissions;

		vUserRecord.push_back(stNewUser);
		cout << "\n\nUser added successfully...\n";
		cout << "Do you want to Add more users? y/n\n\n";


	} while (readChar() == 'y');


}

void deleteUserByAccountNumber(vector<stUserRecord>& vUserRecord, short& userAccountPosition) {

	cout << "Entre User-name you want to delete: ";
	string userName = readString();

	if (isUserNameExist(vUserRecord, userName, userAccountPosition)) {


		cout << "\nAre you sure you want to delete this user? y/n\n";
		if (readChar() == 'y') {
			vUserRecord.erase(vUserRecord.begin() + userAccountPosition);
			cout << "\nAccount " << userName << " deleted successfully";

		}


	}
	else {
		cout << "User name " << userName << " doesn't exist..";
	}
}

void updateUserByUserName(vector<stUserRecord>& vUserRecord, short& userAccountPosition) {

	cout << "Entre User-name you want to update: ";
	string userName = readString();

	if (isUserNameExist(vUserRecord, userName, userAccountPosition)) {

		cout << "\nAre you sure you want to update this user? y/n\n";
		if (readChar() == 'y') {
			cout << "Update user's info...\n";
			cout << "Update Name: ";
			vUserRecord[userAccountPosition].userName = readString();
			cout << "Update Password: ";
			vUserRecord[userAccountPosition].passWord = readString();
			cout << "Update Permissions: ";
			vUserRecord[userAccountPosition].permissions = readPositiveNumber();
			cout << "\nUser Updated successfully...";

		}
	}
	else {
		cout << "Account " << userName << " doesn't exist..";
	}
}

void returnToManageUsersMenu(vector<stUserRecord>& vUsersRecord, short& accountPosition, vector<stClientRecord> vClientsRecord, short& userAccountPosition, stUserRecord& activeUserRecord) {

	cout << "\n press any key to go back...";
	system("pause>0");
	showManageUsersScreen(vUsersRecord, accountPosition,vClientsRecord,userAccountPosition,activeUserRecord);
}

void performManageUsersOptions(enManageUsersMenu selectChoice, vector<stUserRecord>& vUsersRecord, short& accountPosition, vector<stClientRecord> vClientsRecord, short& userAccountPosition, stUserRecord& activeUserRecord) {

	switch (selectChoice) {
	case enManageUsersMenu::listOfUsers:system("cls"); printAllUsersRecords(vUsersRecord); returnToManageUsersMenu(vUsersRecord, accountPosition,vClientsRecord,userAccountPosition,activeUserRecord); break;
	case enManageUsersMenu::addNewUser:system("cls");addUser(vUsersRecord,userAccountPosition); returnToManageUsersMenu(vUsersRecord, accountPosition, vClientsRecord, userAccountPosition,activeUserRecord); break;
	case enManageUsersMenu::findUser:system("cls");findUserByUserName(vUsersRecord,userAccountPosition); returnToManageUsersMenu(vUsersRecord, accountPosition, vClientsRecord,userAccountPosition,activeUserRecord); break;
	case enManageUsersMenu::updateUser:system("cls");updateUserByUserName(vUsersRecord,userAccountPosition); returnToManageUsersMenu(vUsersRecord, accountPosition, vClientsRecord, userAccountPosition,activeUserRecord); break;
	case enManageUsersMenu::deleteUser:system("cls");deleteUserByAccountNumber(vUsersRecord,userAccountPosition); returnToManageUsersMenu(vUsersRecord, accountPosition, vClientsRecord, userAccountPosition,activeUserRecord); break;
	case enManageUsersMenu::mainMenuGo:system("cls"); returnToMainMenu(vClientsRecord,vUsersRecord,activeUserRecord); break;

	}
}

//_____________________________________________________________________________________
// Log In

void lodInScreen() {

	cout << "===========================================================\n";
	cout << "                       LOG IN SCREEN\n";
	cout << "===========================================================\n";
}

void logIn() {

	lodInScreen();
	vector<stClientRecord> vClientsRecord = loadDataFromFileToStVector(fileName);
	vector<stUserRecord> vUsersRecord = loadDataFromAdminsFileToStVector(adminsFileName);

	short userCounter = 0;

	do {
		cout << "User Name: ";
		string userName = readString();
		short passCounter = 0;

		for (int i = 0; i < vUsersRecord.size(); i++) {

			if (userName == vUsersRecord[i].userName) {

				do {
					cout << "Password: ";

					string password = readString();

					if (password == vUsersRecord[i].passWord) {
						stUserRecord activeUserRecord = vUsersRecord[i];
						showMainMenu(vClientsRecord, vUsersRecord,activeUserRecord);
						break;
					}
					passCounter++;
					cout << "Wrong Password..." << "\nyou have used " << passCounter << " of 3 trials\n";
				}

				while (passCounter < 3);
				cout << "\n\nAccount locked... please contact your admin..\n";
				exit(0);
			}
		}
		userCounter++;
		cout << "User name " << userName << " doesn't exist ... you have used " << userCounter << " of 3 trials\n";
	} while (userCounter < 3);

	cout << "\n\nAccount locked... please contact your admin..\n";
}

int main() {

	logIn();

	system("pause>0");
	return 0;

}




