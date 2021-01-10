#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool MainValidation(char& choice)
{
    if (choice == 'l' || choice == 'r' || choice == 'q')
    {
        choice -= ('`' - '@');
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
    for (unsigned int i = 0; i < users.size(); ++i)
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
        if ((username[i] < '!') || (username[i] > '/' && username[i] <= ':') || username[i] > '~' || username[i] == '?')
            return false;
    }

    return true;
}

bool RegisterPasswordValidation(string password)
{
    if (password.size() < 5)
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
    int LowerCaseCounter = 0;
    int UpperCaseCounter = 0;
    int Symbol = 0;
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
            int counter = 0;
            while (counter != 2)
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