#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;
bool MainValidation(char& choice);//Validation for the first command key
bool LoggedInValidation(char& choice2);//Validating for the command you give after login
void MainScreen(char input);//Main screen and the operations in it
void LoginScreen(char choice);//Login menu screen
void LoggedinScreen(int& money);//The screen that comes up after login
void RegisterScreen(char choice);//The screen that comes up when asked to register
void CancelAccountScreen(char& choice,int& money);//The screen that comes up after you chose to cancel the account
void LogoutScreen(char& choice, int& money);//The screen that comes up after logout command 
int main()
{
    char input = 1;//needed for the function that shows the Mainscreen
    
    MainScreen(input);//Main screen of the program

    return 0;
}
void MainScreen(char input)
{  

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

void LoginScreen(char choice)
{
   //make login possible
    string username;
    string password;
    int money;
    money = 10;
    cout << "Login\n\n";
    cout << "username:";
    cin >> username;
    cout << "\npassword:";
    cin >> password;

    system("CLS");
    LoggedinScreen(money);

}
void RegisterScreen(char choice)
{
    cout << "Please Register\n\n\n";
    cout << "Enter your username:";
    //enter username
    cout << "\nEnter your password:";
    //enter password
    cout << "\nConfirm password:";
    //check if password is the same
    //make the amount of money in the account 0 to begin with
}
void CancelAccountScreen(char& choice,int& money)
{
    int CancelChoice;
    cout << "Are you sure you want to cancel your account?\n";
    cout << "1-Yes\n";
    cout << "2-No\n";
    cin >> CancelChoice;
    while (CancelChoice != 1 && CancelChoice != 2)
    {
        cout << "Unrecognised command,try again: \n";
        cin >> CancelChoice;
    }
   
    system("CLS");
    if (CancelChoice == 1)
    {
        cout << "Enter password to confirm: \n";
        //delete account
    }
    if (CancelChoice == 2)
    {
        LoggedinScreen(money);
    }
}
void LogoutScreen(char& choice,int& money)
{
    int LogoutChoice;
    cout << "Are you sure you wish to logout?\n";
    cout << "1-Yes\n";
    cout << "2-No\n";
    cin >> LogoutChoice;
    while (LogoutChoice != 1 && LogoutChoice != 2)
    {
        cout << "Unrecognised command,try again: \n";
        cin >> LogoutChoice;
    }
    system("CLS");
    if (LogoutChoice == 1)
    {
        MainScreen(choice);
    }
    if (LogoutChoice == 2)
    {
        LoggedinScreen(money);
    }
}
void LoggedinScreen(int& money)
{
    char choice2;
    int Amount = money;
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
            //deposit
            break;
        case 'L':
            LogoutScreen(choice2, Amount);
            break;
        case 'T':
            //transfer
            break;
        case 'W':
            //withdraw
            break;
    }
}
