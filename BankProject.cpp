#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool MainValidation(char& choice);//Validation for the first command key
bool LoggedInValidation(char& choice2);//Validating for the command you give after login
bool RegisterUsernameValidation(string username);//Validation of the Username accepted characters 
bool RegisterPasswordValidation(string password);//Validation of the Password accepted and
bool UsernameLoginValidation(string username, vector<string>& users);
bool LoginPasswordValidation(string username, string password, vector<string>& users);
float RoundMoney(float& money);//Rounds the money that is deposited transferred or withdrawn
void MainScreen(char input, vector<string>&users);//Main screen and the operations in it
void LoginScreen(char choice, vector<string>&users);//Login menu screen
void LoggedinScreen(float& money, vector<string>&users);//The screen that comes up after login
void RegisterScreen(char choice, vector<string>&users);//The screen that comes up when asked to register
void CancelAccountScreen(char& choice,float& money, vector<string>&users);//The screen that comes up after you chose to cancel the account
void LogoutScreen(char& choice, float& money, vector<string>&users);//The screen that comes up after logout command 
void Deposit(float& money, vector<string>&users);//Deposit screen
void Withdraw(float& money, vector<string>&users);//Withdraw screen
string MoneyInUserAccount(string username, vector<string>& users);

int main()
{
    char input = 1;//needed for the function that shows the Mainscreen
    vector<string>accounts;
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
        accounts.push_back(buffer);
    }
    file.close();

    MainScreen(input,accounts);//Main screen of the program

    return 0;
}

void MainScreen(char input,vector<string>&users)
{  
    for (unsigned int i = 0; i < users.size(); ++i)
    {
        cout << users[i]<<endl;
    }
    
    cout << "Welcome to Sevastopol Bank" << endl << endl << endl;
    cout << "L-Login" << endl;
    cout << "R=Register" << endl;
    cout << "Q=Quit" << endl;

    char choice;//Human choice 
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
            //save changes to registry and quit the text file ;
            break;

    }
}

bool MainValidation(char& choice)
{
    if (choice == 'l' || choice == 'r' || choice == 'q')
    {
        choice -= 32;
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
        choice2 -= 32;
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
            if (password[i] < '0' || password[i]>9)
            {
                if ((password[i] != '!' || password[i] != '*' || password[i] != '^') && (password[i] < '#' || password[i]>'&'))
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

float RoundMoney(float& money)
{
    float value = roundf(money * 100);
    return value / 100;
}

string MoneyInUserAccount(string username,string password, vector<string>& users)
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
    return Money;
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
    while (!LoginPasswordValidation(username, password, users))
    {
        cout << "\nPassword incorrect please try again:\n";
        cin >> password;
    }
     
    system("CLS");
    string StringMoney = MoneyInUserAccount(username, password, users);
    money = stof(StringMoney);
    LoggedinScreen(money,users);
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
    //hashpassword
    string FullAccount = Name;
    FullAccount += ":";
    FullAccount += Password;
    FullAccount += ":";
    FullAccount += money;
    
    users.push_back(FullAccount);
    system("CLS");
    MainScreen(choice,users);
}

void CancelAccountScreen(char& choice,float& money, vector<string>&users)
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
        cout << "Enter password to confirm: \n";
        //hash and validate 
        
        if (money != 0)
        {
            cout << "Cannot Delete account.You have " << money << " BGN in it.";
            LoggedinScreen(money,users);
        }
        //delete account
    }
    if (CancelChoice == '2')
    {
        LoggedinScreen(money,users);
    }
}

void Deposit(float& money, vector<string>&users)
{
    float deposit;
    cout << "How much would you like to deposit?";
    cin >> deposit;
    deposit=RoundMoney(deposit);
    money += deposit;
    system("CLS");
    LoggedinScreen(money,users);
}

void LogoutScreen(char& choice,float& money, vector<string>&users)
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
        MainScreen(choice,users);
    }
    if (LogoutChoice == '2')
    {
        LoggedinScreen(money,users);
    }
}

void Withdraw(float& money, vector<string>&users)
{
    float withdraw;
    cout << "How much would you like to withdraw?\n";
    cin >> withdraw;
    withdraw=RoundMoney(withdraw);
    
    while ((money - withdraw) < -10000)
    {
        cout << "Cannot withdraw that amount because your balance is "<<money<<" try again:";
        cin >> withdraw;
        withdraw=RoundMoney(withdraw);
    }
    money -= withdraw;

    system("CLS");
    LoggedinScreen(money,users);
}

void LoggedinScreen(float& money, vector<string>&users)
{
    char choice2;
    float Amount = money;
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
            CancelAccountScreen(choice2,Amount,users);
            break;
        case 'D':
            Deposit(money,users);
            break;
        case 'L':
            LogoutScreen(choice2, Amount,users);
            break;
        case 'T':
            //transfer
            break;
        case 'W':
            Withdraw(money,users);
            break;
    }
}
