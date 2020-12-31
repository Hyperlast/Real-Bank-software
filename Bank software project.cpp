#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;
bool MainValidation(char& choice);//Validation for the first command key
bool LoggedInValidation(char& choice2);//Validating for the command you give after login
void MainScreen(char input);//Main screen and the operations in it
void LoginScreen(char choice);//Login menu screen
void LoggedinScreen(int money);//The screen that comes up after login
void RegisterScreen(char choice);//The screen that comes up when asked to register
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
    cout << "Please Register";
    cout << "";
}
void LoggedinScreen(int money)
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
    }
}
