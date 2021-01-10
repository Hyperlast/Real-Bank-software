#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include"Functionals.h"
#include"Validations.h"

using namespace std;

void MainScreen(char input, vector<string>& users);//Main screen and the operations in it

void LoginScreen(char choice, vector<string>& users);//Login menu screen

void LoggedinScreen(float& money, string& LoggedAccount, vector<string>& users);//The screen that comes up after login

void RegisterScreen(char choice, vector<string>& users);//The screen that comes up when asked to register

void CancelAccountScreen(float& money, string& LoggedAccount, vector<string>& users);//The screen that comes up after you chose to cancel the account

void LogoutScreen(float& money, string& LoggedAccount, vector<string>& users);//The screen that comes up after logout command 

void Deposit(float& money, string& LoggedAccount, vector<string>& users);//Deposit screen

void Transfer(float& money, string& LoggedAccount, vector<string>& users);//Transfer money in another account screen

void Withdraw(float& money, string& LoggedAccount, vector<string>& users);//Withdraw screen