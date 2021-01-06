#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

bool MainValidation(char& choice);//Validation for the first command key
bool LoggedInValidation(char& choice2);//Validating for the command you give after login
bool RegisterUsernameValidation(string username);
float RoundMoney(float& money);//Rounds the money that is deposited transferred or withdrawn
void MainScreen(char input);//Main screen and the operations in it
void LoginScreen(char choice);//Login menu screen
void LoggedinScreen(float& money);//The screen that comes up after login
void RegisterScreen(char choice);//The screen that comes up when asked to register
void CancelAccountScreen(char& choice,float& money);//The screen that comes up after you chose to cancel the account
void LogoutScreen(char& choice, float& money);//The screen that comes up after logout command 
void Deposit(float& money);//Deposit screen
void Withdraw(float& money);//Withdraw screen

int main()
{
    char input = 1;//needed for the function that shows the Mainscreen
    
    MainScreen(input);//Main screen of the program

    return 0;
}


void MainScreen(char input)
{  
    fstream file;
    file.open("users.txt" ,fstream::in);
    if (!file.is_open())
    {
        system("CLS");
        cout << "The users.txt file can't be opened please check for it and try again";
    }
    file.close();
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
            LoginScreen(choice);
            break;

        case 'R':
            RegisterScreen(choice);
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

bool RegisterUsernameValidation(string username)
{
   
    for (int i = 0; i < username.length(); ++i)
    {
        if ((username[i] < '!') || (username[i] > '/' && username[i] < ':')|| username[i] >'~'||username[i]=='?')
            return false;
    }

    return true;
}
float RoundMoney(float& money)
{
    float value = roundf(money * 100);
    return value / 100;
}

void LoginScreen(char choice)
{
   //make login possible
    string username;
    string password;
    float money;
    money = 0;
    cout << "Login\n\n";
    cout << "username:";
    cin >> username;
    //verify if it exists
    cout << "\npassword:";
    cin >> password;
    //verify if it matches
    // Change money to the amount in the account 
    system("CLS");
    LoggedinScreen(money);

}

void RegisterScreen(char choice)
{
    
    string Name;
    string Password;
    string Passwordtemp;
    string money = "0";
    cout << "Please Register\n\n\n";
    
    cout << "Enter your username:";
    cin >> Name;
    while (!RegisterUsernameValidation(Name))
    {
        cout << "\n You've used a symbol that is not allowed for a username please try again:\n";
        cin >> Name;
    }
    //validate
    cout << "\nEnter your password:";
    cin >> Password;
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
    cout << FullAccount;
    system("CLS");
    MainScreen(choice);
}

void CancelAccountScreen(char& choice,float& money)
{
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
            LoggedinScreen(money);
        }
        //delete account
    }
    if (CancelChoice == '2')
    {
        LoggedinScreen(money);
    }
}

void Deposit(float& money)
{
    float deposit;
    cout << "How much would you like to deposit?";
    cin >> deposit;
    deposit=RoundMoney(deposit);
    money += deposit;
    system("CLS");
    LoggedinScreen(money);
}

void LogoutScreen(char& choice,float& money)
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
        MainScreen(choice);
    }
    if (LogoutChoice == '2')
    {
        LoggedinScreen(money);
    }
}

void Withdraw(float& money)
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
    LoggedinScreen(money);
}

void LoggedinScreen(float& money)
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
            CancelAccountScreen(choice2,Amount);
            break;
        case 'D':
            Deposit(money);
            break;
        case 'L':
            LogoutScreen(choice2, Amount);
            break;
        case 'T':
            //transfer
            break;
        case 'W':
            Withdraw(money);
            break;
    }
}
