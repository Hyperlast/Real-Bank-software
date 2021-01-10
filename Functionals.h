#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string MoneyInUserAccount(string username, vector<string>& users);//returns the money in a specific users account as a string 

void DeleteAccount(string Account, vector<string>& users);//deletes the account from the vector database

void MoneyChange(float& money, string& Account, vector<string>& users);//Solidifies the changes in users money

string ShowFullAccount(string username, vector<string>& users);//Returns full account for changes

string HashPassword(string password);//Hashes the password

float RoundMoney(float& money);//Rounds the money that is deposited transferred or withdrawn

void ReadTxtFile(vector<string>& Accounts);//rewrites text file into the vector 
