#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool MainValidation(char& choice);//Validation for the first command key
bool LoggedInValidation(char& choice2);//Validating for the command you give after login
bool RegisterUsernameValidation(string username);//Validation of the Username accepted characters 
bool RegisterPasswordValidation(string password);//Validation of the Password accepted and
bool UsernameLoginValidation(string username, vector<string>& users);
bool LoginPasswordValidation(string username, string password, vector<string>& users);
bool CancelAccountPassValidation(string account, string password);
float RoundMoney(float& money);//Rounds the money that is deposited transferred or withdrawn
void ReadTxtFile(vector<string>& Accounts);//rewrites text file into the vector 
void MainScreen(char input, vector<string>&users);//Main screen and the operations in it
void LoginScreen(char choice, vector<string>&users);//Login menu screen
void LoggedinScreen(float& money, string &LoggedAccount, vector<string>&users);//The screen that comes up after login
void RegisterScreen(char choice, vector<string>&users);//The screen that comes up when asked to register
void CancelAccountScreen(float& money, string& LoggedAccount, vector<string>&users);//The screen that comes up after you chose to cancel the account
void LogoutScreen( float& money, string& LoggedAccount, vector<string>&users);//The screen that comes up after logout command 
void Deposit(float& money, string& LoggedAccount, vector<string>&users);//Deposit screen
void Transfer(float& money, string& LoggedAccount, vector<string>& users);//Transfer money in another account screen
void Withdraw(float& money, string& LoggedAccount, vector<string>&users);//Withdraw screen
string MoneyInUserAccount(string username, vector<string>& users);//returns the money in a specific users account as a string 
void DeleteAccount(string Account, vector<string>& users);//deletes the account from the vector database
void MoneyChange(float& money, string& Account,vector<string> &users);//Solidifies the changes in users money
string ShowFullAccount(string username, vector<string>& users);
string HashPassword(string password);

int main()
{
    char input = 1;//needed for the function that shows the Mainscreen
    vector<string>accounts;
    ReadTxtFile(accounts);
    MainScreen(input,accounts);//Main screen of the program

    return 0;
}

string HashPassword(string password)
{
    const int RandTablePERC = 404;
    const int RandSeed = 232;
    unsigned long hash = 0;
    for (unsigned int i = 0; i < password.size(); ++i)
    {
        hash = (hash * RandSeed) + password[i];
    }
    hash=hash%RandTablePERC;
    string PasswordHashed=(to_string(hash));

    return PasswordHashed;
}

void MainScreen(char input,vector<string>&users)
{   
    cout << "Welcome to Sevastopol Bank" << endl << endl << endl;
    cout << "L-Login" << endl;
    cout << "R=Register" << endl;
    cout << "Q=Quit" << endl;

    char choice;//User choice
    cin >> choice;
    while (!MainValidation(choice))
    {
        cout << "\n Unrecognised command,try again: \n";
        cin >> choice;
    }

    system("CLS");//clears the screen for the next menu

    switch (choice)
    {
        case 'L':
            LoginScreen(choice,users);
            break;

        case 'R':
            RegisterScreen(choice,users);
            break;
        case 'Q':
            ofstream txtFile;
            txtFile.open("users.txt", ofstream::out | ofstream::trunc);
            if (!txtFile.is_open())
            {
                cout << "Something went wrong with the users.txt file please look at it and relaunch the program.Press character key to continue:\n ";
                char temp;
                cin >> temp;
            }
            txtFile.close();

            txtFile.open("users.txt", ofstream::out);
            if (txtFile.is_open())
            {
                for (unsigned int i = 0; i < users.size(); ++i)
                {
                    txtFile << users[i] << endl;
                }
            }
            break;

    }
}

void ReadTxtFile(vector<string> &Accounts)
{
    string buffer;
    fstream file;
    file.open("users.txt", fstream::in);
    if (!file.is_open())
    {
        system("CLS");
        cout << "The users.txt file can't be opened please check for it and try again";
    }
    while (getline(file, buffer))
    {
        Accounts.push_back(buffer);
    }
    file.close();
}

bool MainValidation(char& choice)
{
    if (choice == 'l' || choice == 'r' || choice == 'q')
    {
        choice -= ('`'-'@');
        return true;
    }
    if (choice != 'L' && choice != 'R' && choice != 'Q')
    {
        return false;
    }

    return true;
}

bool LoggedInValidation(char& choice2)
{
    if (choice2 == 'c' || choice2 == 'd' || choice2 == 'l' || choice2 == 't' || choice2 == 'w')
    {
        choice2 -= ('`' - '@');
        return true;
    }
    if (choice2 != 'C' && choice2 != 'D' && choice2 != 'L' && choice2 != 'T' && choice2 != 'W')
    {
        return false;
    }
    return true;
}

bool UsernameLoginValidation(string username, vector<string>& users)
{
    for ( unsigned int i = 0; i < users.size(); ++i)
    {
        {
            string temp = users[i];
            string UsernameVar;
            int j = 0;
            while (temp[j] != ':')
            {
                UsernameVar += temp[j];
                ++j;
            }
            if (username == UsernameVar)
            {
                return true;
            }
        }
    }
    return false;
}

bool RegisterUsernameValidation(string username)
{
   
    for (unsigned int i = 0; i < username.size(); ++i)
    {
        if ((username[i] < '!') || (username[i] > '/' && username[i] <= ':')|| username[i] >'~'||username[i]=='?')
            return false;
    }

    return true;
}

bool RegisterPasswordValidation(string password)
{
    if ( password.size() < 5)
    {
        return false;
    }
    for (unsigned int i = 0; i < password.size(); ++i)
    {
        if ((password[i] < '@' || password[i]>'Z') && (password[i] < 'a' || password[i]>'z'))
        {
            if (password[i] < '0' || password[i]>'9')
            {
                if ((password[i] != '!' && password[i] != '*' && password[i] != '^') && (password[i] < '#' || password[i]>'&'))
                {
                    return false;
                }
            }
        }
    }
    int LowerCaseCounter=0;
    int UpperCaseCounter=0;
    int Symbol=0;
    for (unsigned int i = 0; i < password.size(); ++i)
    {
        if (password[i] >= 'a' && password[i] <= 'z')
        {
            LowerCaseCounter++;
        }
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            UpperCaseCounter++;
        }
        if (password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$' || password[i] == '%')
        {
            Symbol++;
        }
        if (password[i] == '^' || password[i] == '&' || password[i] == '*')
        {
            Symbol++;
        }
    }
    if (LowerCaseCounter < 1 || UpperCaseCounter < 1 || Symbol < 1)
    {
        return false;
    }
    return true;
}

bool LoginPasswordValidation(string username, string password, vector<string>& users)
{
    string UserWPass;
    UserWPass += username;
    UserWPass += ':';
    UserWPass += password;
    UserWPass += ':';
    for (unsigned int i = 0; i < users.size(); ++i)
    {
        {
            string temp = users[i];
            string UsernameVar;
            int j = 0;
            int counter=0;
            while (counter!=2)
            {
                if (temp[j] == ':')
                {
                    counter++;
                }

                UsernameVar += temp[j];
                ++j;
            }
            if (UserWPass == UsernameVar)
            {
                return true;
            }
        }
    }
    return false;
}

bool CancelAccountPassValidation(string account, string password)
{
    string FullAccountVal;
    string username;
    unsigned int i = 0;
    while (account[i] != ':')
    {
        username += account[i];
        i++;
    }
    FullAccountVal += username;
    FullAccountVal += ':';
    FullAccountVal += password;
    FullAccountVal += ':';
    FullAccountVal += '0';
    if (FullAccountVal == account)
    {
        return true;
    }
    return false;
    
}

void DeleteAccount(string Account, vector<string> &users)
{   
    for (unsigned int i = 0; i < users.size(); ++i)
    {
       
        if (Account == users[i])
        {
            users.erase(users.begin() + i);
        }
    }
}

float RoundMoney(float& money)
{
    float value = roundf(money * 100);
    return value / 100;
}

string MoneyInUserAccount(string username, vector<string>& users)
{
    string FindMoneyInAccount;
    bool AccountFound = false;
    unsigned int i = 0;
    for (; i < users.size(); ++i)
    {
        if (AccountFound)
        {
            break;
        }
        string temp=users[i];
        string checker;
        int j = 0;
        while (temp[j] != ':')
        {
            checker += temp[j];
            j++;
        }
        if (checker == username)
        {
            FindMoneyInAccount += users[i];
            AccountFound = true;
        }
    }
    string Money;
    float MoneyDecVal;
    int counter = 0;
    for (unsigned int i = 0; i < FindMoneyInAccount.size(); ++i)
    {
        if (counter == 2)
        {
            Money += FindMoneyInAccount[i];
        }
        if (FindMoneyInAccount[i] == ':')
        {
            counter++;
        }
    }
    MoneyDecVal = stof(Money);
    MoneyDecVal = RoundMoney(MoneyDecVal);
    ostringstream ss;
    ss << MoneyDecVal;
    Money=(ss.str());
    return Money;
}

string ShowFullAccount(string username, vector<string>& users)
{
    for (unsigned int i = 0; i < users.size(); ++i)
    {
        string temp = users[i];
        string AccountChecker;
        unsigned int j = 0;
        while (temp[j] != ':')
        {
            AccountChecker += temp[j];
            j++;
        }
        if (AccountChecker == username)
        {
            AccountChecker = users[i];
            return AccountChecker;
        }
    }
    return username;
}

void MoneyChange(float& money, string& Account,vector<string>&users)
{
    int counter=0;
    for (unsigned int i = 0; i < Account.size(); ++i)
    {
        if (counter == 2)
        {
            Account.erase(Account.begin() + i, Account.end());
        }
        if (Account[i] == ':')
        {
            counter++;
        }
    }
   
    ostringstream ss;
    ss << money;
    string MoneyDiff(ss.str());
    unsigned tempNumb=0;
    for (unsigned int j = 0; j < users.size(); ++j)
    {
        string temp=users[j];
        string Checker;
        int counter = 0;
        int k = 0;
        while (counter != 2)
        {
            if (temp[k] == ':')
            {
                counter++;
            }
            Checker += temp[k];
            k++;
        }
        
        if (Account == Checker)
        {
            tempNumb = j;
        }
    }
    Account += MoneyDiff;
    users[tempNumb]=Account;
}

void LoginScreen(char choice, vector<string>&users)
{
    string FullUser;
    string username;
    string password;
    float money;
    cout << "Login\n\n";
    cout << "username:";
    cin >> username;
    while (!UsernameLoginValidation(username, users))
    {
        cout << "\nUsername does not exist in the database,try again:\n";
        cin >> username;
    }
    cout << "\npassword:";
    cin >> password;
    password = HashPassword(password);
    while (!LoginPasswordValidation(username, password, users))
    {
        cout << "\nPassword incorrect please try again:\n";
        cin >> password;
        password = HashPassword(password);
    }
     
    system("CLS");
    string StringMoney = MoneyInUserAccount(username, users);
    money = stof(StringMoney);
    FullUser += username;
    FullUser += ':';
    FullUser += password;
    FullUser += ':';
    FullUser += StringMoney;
    LoggedinScreen(money,FullUser,users);
}

void RegisterScreen(char choice, vector<string>&users)
{
    string Name;
    string Password;
    string Passwordtemp;
    string money = "0";
    cout << "Please Register\n\n\n";
    
    cout << "Enter your username:";
    cin >> Name;
    while (UsernameLoginValidation(Name, users)||!RegisterUsernameValidation(Name))
    {
        cout << "\nThat Username is already taken or you have used a forbidden symbol please try again:\n";
        cin >> Name;
    }
    cout << "\nEnter your password that has atleast 1 Large 1 small letter and 1 symbol:";
    cin >> Password;
    while (!RegisterPasswordValidation(Password))
    {
        cout << "\nThe password you've created is either invalid or too short(5 symbols min).\nPlease use only English characters,numbers or !@#$%^&*\n";
        cin >> Password;
    }
    cout << "\nConfirm password:";
    cin >> Passwordtemp;
    while (Passwordtemp != Password)
    {
        cout << "\nPassword validation incorrect,try to confirm your passowrd again:";
        cin >> Passwordtemp;
    }
    Password = HashPassword(Password);
    string FullAccount = Name;
    FullAccount += ":";
    FullAccount += Password;
    FullAccount += ":";
    FullAccount += money;
    
    users.push_back(FullAccount);
    system("CLS");
    MainScreen(choice,users);
}

void CancelAccountScreen(float& money, string& LoggedAccount, vector<string>&users)
{
    string password;
    char CancelChoice;
    cout << "Are you sure you want to cancel your account?\n";
    cout << "1-Yes\n";
    cout << "2-No\n";
    cin >> CancelChoice;
    while (CancelChoice != '1' && CancelChoice != '2')
    {
        cout << "Unrecognised command,try again: \n";
        cin >> CancelChoice;
    }
   
    system("CLS");
    if (CancelChoice == '1')
    {
        if (money != 0)
        {
            cout << "Cannot Delete account.You have " << money << " BGN in it.";
            LoggedinScreen(money, LoggedAccount, users);
        }
        cout << "Enter password to confirm: \n";
        cin >> password;
        password = HashPassword(password);
        while (!CancelAccountPassValidation(LoggedAccount, password))
        {
            cout << "\nThe password doesn't match please try again:\n";
            cin >> password;
            password = HashPassword(password);
        }

        DeleteAccount(LoggedAccount, users);
        system("CLS");
        MainScreen(CancelChoice, users);
    }
    if (CancelChoice == '2')
    {
        LoggedinScreen(money, LoggedAccount, users);
    }
}

void Deposit(float& money, string& LoggedAccount, vector<string>& users)
{
    float deposit;
    cout << "How much would you like to deposit?";
    cin >> deposit;
    while (deposit < 0 || cin.fail())
    {
        cout << "Please deposit a real amount";
        cin >> deposit;
        cin.clear();
    }
    deposit = RoundMoney(deposit);
    money += deposit;

    MoneyChange(money, LoggedAccount, users);
    system("CLS");
    LoggedinScreen(money, LoggedAccount, users);
}

void LogoutScreen(float& money, string& LoggedAccount, vector<string>& users)
{
    char LogoutChoice;
    cout << "Are you sure you wish to logout?\n";
    cout << "1-Yes\n";
    cout << "2-No\n";
    cin >> LogoutChoice;
    while (LogoutChoice != '1' && LogoutChoice != '2')
    {
        cout << "Unrecognised command,try again: \n";
        cin >> LogoutChoice;
    }
    system("CLS");
    if (LogoutChoice == '1')
    {
        MainScreen(LogoutChoice, users);
    }
    if (LogoutChoice == '2')
    {
        LoggedinScreen(money, LoggedAccount, users);
    }
}

void Withdraw(float& money, string& LoggedAccount, vector<string>& users)
{
    float withdraw;
    cout << "How much would you like to withdraw?\n";
    cin >> withdraw;
    while (withdraw < 0 || cin.fail())
    {
        cout << "\nCannot withdraw this ammount,please try again: ";
        cin >> withdraw;
        cin.clear();
    }
    withdraw = RoundMoney(withdraw);

    while (((money - withdraw) < -10000) || (withdraw < 0) || cin.fail())
    {
        cout << "Cannot withdraw that amount because your balance is " << money << " try again:";
        cin >> withdraw;
        withdraw = RoundMoney(withdraw);
        cin.clear();

    }
    money -= withdraw;
    MoneyChange(money, LoggedAccount, users);
    system("CLS");
    LoggedinScreen(money, LoggedAccount, users);
}

void Transfer(float& money, string& LoggedAccount, vector<string>& users)
{
    string SecondAccount;
    float Transfer;
    cout << "In which Account would you like to transfer money: ";
    cin >> SecondAccount;
    while (!UsernameLoginValidation(SecondAccount, users))
    {
        cout << "This account has not been found in the database,try again: ";
        cin >> SecondAccount;
    }
    cout << "How much money would you like to transfer: ";
    cin >> Transfer;
    while (Transfer < 0 || cin.fail())
    {
        cout << "Cannot transfer this ammount,try again: ";
        cin >> Transfer;
    }
    while (((money - Transfer) < -10000) || (Transfer < 0) || cin.fail())
    {
        cout << "You dont have enough funds in your account\nCurrent funds "<<money<<" BGN,try again: ";
        cin >> Transfer;
    }
    Transfer=RoundMoney(Transfer);
    money -= Transfer;
   
    string StringMoneySecAc = MoneyInUserAccount(SecondAccount, users);
    cout << StringMoneySecAc;

    float MoneyInSecAcc=stof(StringMoneySecAc);
    MoneyInSecAcc += Transfer;

    string FullSecAccount;
    FullSecAccount = ShowFullAccount(SecondAccount, users);

    MoneyChange(money, LoggedAccount, users);
    MoneyChange(MoneyInSecAcc, FullSecAccount, users);

    system("CLS");
    LoggedinScreen(money, LoggedAccount, users);
}

void LoggedinScreen(float& money,string &LoggedAccount, vector<string>&users)
{
    char choice2;
    
    cout << "You have " << money << " BGN. Choose one of the following options:" << endl;
    cout << "C - Cancel account"<<endl;
    cout << "D - deposit" << endl;
    cout << "L - logout " << endl;
    cout << "T - transfer" << endl;
    cout << "W - withdraw" << endl;
    cin >> choice2;

    while (!LoggedInValidation(choice2))
    {
        cout << "\n Unrecognised command,try again: \n";
        cin >> choice2;
    }
    system("CLS");
    switch (choice2)
    {
        case 'C':
            CancelAccountScreen(money,LoggedAccount,users);
            break;
        case 'D':
            Deposit(money,LoggedAccount,users);
            break;
        case 'L':
            LogoutScreen(money,LoggedAccount,users);
            break;
        case 'T':
            Transfer(money, LoggedAccount, users);
            break;
        case 'W':
            Withdraw(money,LoggedAccount,users);
            break;
    }
}