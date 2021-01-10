#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void ReadTxtFile(vector<string>& Accounts)
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
        string temp = users[i];
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
    Money = (ss.str());
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

void MoneyChange(float& money, string& Account, vector<string>& users)
{
    int counter = 0;
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
    unsigned tempNumb = 0;
    for (unsigned int j = 0; j < users.size(); ++j)
    {
        string temp = users[j];
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
    users[tempNumb] = Account;
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
    hash = hash % RandTablePERC;
    string PasswordHashed = (to_string(hash));

    return PasswordHashed;
}

void DeleteAccount(string Account, vector<string>& users)
{
    for (unsigned int i = 0; i < users.size(); ++i)
    {

        if (Account == users[i])
        {
            users.erase(users.begin() + i);
        }
    }
}