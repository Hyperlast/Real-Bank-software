#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include"Functionals.h"
#include"Validations.h"
#include"Screens.h"

using namespace std;

void MainScreen(char input, vector<string>& users)
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
        LoginScreen(choice, users);
        break;

    case 'R':
        RegisterScreen(choice, users);
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

void LoginScreen(char choice, vector<string>& users)
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
    LoggedinScreen(money, FullUser, users);
}

void RegisterScreen(char choice, vector<string>& users)
{
    string Name;
    string Password;
    string Passwordtemp;
    string money = "0";
    cout << "Please Register\n\n\n";

    cout << "Enter your username:";
    cin >> Name;
    while (UsernameLoginValidation(Name, users) || !RegisterUsernameValidation(Name))
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
    MainScreen(choice, users);
}

void CancelAccountScreen(float& money, string& LoggedAccount, vector<string>& users)
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
            cout << "Cannot Delete account.You have " << money << " BGN in it.\n";
            char AnyKey;
            cout << "Press any Character key to continue: ";
            cin >> AnyKey;
            system("CLS");
            LoggedinScreen(money, LoggedAccount, users);
        }
        else
        {
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
        cout << "You dont have enough funds in your account\nCurrent funds " << money << " BGN,try again: ";
        cin >> Transfer;
    }
    Transfer = RoundMoney(Transfer);
    money -= Transfer;

    string StringMoneySecAc = MoneyInUserAccount(SecondAccount, users);
    cout << StringMoneySecAc;

    float MoneyInSecAcc = stof(StringMoneySecAc);
    MoneyInSecAcc += Transfer;

    string FullSecAccount;
    FullSecAccount = ShowFullAccount(SecondAccount, users);

    MoneyChange(money, LoggedAccount, users);
    MoneyChange(MoneyInSecAcc, FullSecAccount, users);

    system("CLS");
    LoggedinScreen(money, LoggedAccount, users);
}

void LoggedinScreen(float& money, string& LoggedAccount, vector<string>& users)
{
    char choice2;

    cout << "You have " << money << " BGN. Choose one of the following options:" << endl;
    cout << "C - Cancel account" << endl;
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
        CancelAccountScreen(money, LoggedAccount, users);
        break;
    case 'D':
        Deposit(money, LoggedAccount, users);
        break;
    case 'L':
        LogoutScreen(money, LoggedAccount, users);
        break;
    case 'T':
        Transfer(money, LoggedAccount, users);
        break;
    case 'W':
        Withdraw(money, LoggedAccount, users);
        break;
    }
}