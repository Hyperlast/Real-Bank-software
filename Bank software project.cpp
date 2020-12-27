#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool MainValidation(char choice);//Validation for the first command key
void MainScreen(char main);
void LoginScreen(char Login);//The screen that comes up after login
void SwitchChoice(char choice);

int main()
{
    char choice;//The command choice
    MainScreen(choice);//Main screen of the program
    cin >> choice;
    while (!MainValidation)
    {
        cin >> choice;
    }

    SwitchChoices(choice);
    
    return 0;
}
void MainScreen(char main)
{  

    cout << "Welcome to Sevastopol Bank" << endl << endl << endl;
    cout << "L-Login" << endl;
    cout << "R=Register" << endl;
    cout << "Q=Quit" << endl;
    
}
bool MainValidation(char choice)
{

    if (choice != 'L' || choice != 'R' || choice != 'Q')
        return false;

    return true;
}
void SwitchChoices(char choice)
{
    switch (choice)
    {
        case 'L':
           
            break;

        case 'R':
           
            break;
        case 'Q':
            
            break;

    }
  
}

void LoginScreen(int money)
{
    cout << "You have " << money << " BGN. Choose one of the following options:" << endl;
    cout << "C - Cancel account"<<endl;
    cout << "D - deposit" << endl;
    cout << "L - logout " << endl;
    cout << "T - transfer" << endl;
    cout << "W - withdraw" << endl;

}
