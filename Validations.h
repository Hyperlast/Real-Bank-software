#pragma once
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

bool UsernameLoginValidation(string username, vector<string>& users); //Validating if username exists

bool LoginPasswordValidation(string username, string password, vector<string>& users);//Password validation

bool CancelAccountPassValidation(string account, string password);//Validation of Password When you try to cancel the account 