#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Validations.h"
#include "Functionals.h"
#include"Screens.h"


using namespace std;

int main()
{
    char input = 1;//needed for the function that shows the Mainscreen
    vector<string>accounts;
    ReadTxtFile(accounts);
    MainScreen(input,accounts);//Main screen of the program

    return 0;
}

