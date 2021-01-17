/*
User.cpp File Work Breakdown:
    -Jessica: Made the class.
*/
#include "User.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//login verification array
string loginVer[100][4];
int logRow = 100, logCol = 4;

User::User() {
    string user = "";
    string pword = "";
    string type;
    string penalT;
    int maxCpy = 0; //-> mostly for after penaties
}//constructor

//GET FUNCTIONS//
string User::getusername() {
    return user;
}

string User::getpassword() {
    return pword;
}

string User::getPenalty() {
    return penalT;
}

int User::getmaxCpy() {
    return maxCpy;
}

string User::getType() { 
    return type;
}

//SET FUNCTIONS//
void User::setusername(string newUser) {
    this->user = newUser;
}

void User::setpassword(string newPword) {
    this->pword = newPword;
}

void User::setType(string userType) {
    this->type = userType;
}

void User::setPenalty(string penaltie) {
    this->penalT = penaltie;
}

void User::setmaxCpy(int maxcopy) {
    maxCpy = maxcopy;
}

void User::readUsertxt() {
    ifstream input;
    string file_name = "User.txt";
    //Opens the File
    input.open(file_name);
    if (input.fail()) {
        cerr << "ERROR: User.txt could not be opened." << endl;
        exit(1);
    } // Checks if file opens

    // Stores into array loginVer
    while (!input.eof()) {
        for (int i = 0; i < logRow; i++)
            for (int j = 0; j < logCol; j++)
            {
                input >> loginVer[i][j];
            }
    }
    //move cursor back to the beginning of file
    input.seekg(0, ios::beg); 
    input.close();
}

void User::printUsertxt()
{
    ofstream input("User.txt");
    if (input.fail())
    {
        cerr << "Error: User.txt could not be opened to print." << endl;
        exit(1);
    }

    // prints into array loginVer
    for (int i = 0; i < logRow; i++) {
        for (int j = 0; j < logCol; j++)
        {
            input << loginVer[i][j] << " ";
        }
        input << endl;
    }//

    input.close();
}

//OTHER FUNTIONS//
// Verifies if the user is in the user txt
bool User::verifyUser(string user_att1, string pass_att1) {
    int i, j;
    for (i = 0; i < logRow; i++)
        for (j = 0; j < logCol - 1; j++) {
            if ((user_att1 == loginVer[i][j]) && (pass_att1 == loginVer[i][j + 1])) {
                this->type = loginVer[i][j + 2];
                this->penalT = loginVer[i][j + 3];
                return true;
            }
        }//checks if verified user
    cout << "\nERROR: Incorrect Username or Password Entered" << endl;
    return false;
}

// Changes the Password
void User::changePw(User& userCurr, string old, string newPass) {
    readUsertxt();
    int currentURow = 0;
    for (int i = 0; i < logRow; i++) {
        if (loginVer[i][0] == userCurr.getusername()) {
            currentURow = i;
        }
    }

    //if  the old password is correct then do this
    if (old.compare(loginVer[currentURow][1]) == 0) {
        loginVer[currentURow][1] = newPass; 
        
        //check if the new password is == to the old
        if (old.compare(newPass) == 0) {
            cout << "ERROR: New Password is the same as the Old Password." << endl;
           
        }
        else {
            cout << "\nPassword Changed!" << endl;
        }
    }
    else { // if the old password is wrong
        cout << "\nERROR: Wrong Password Entered." << endl;
    }

    printUsertxt();
}

// Shows the My Information part
void User::myInfo(User& userCurr) {
    readUsertxt();

    // current row gets user's row
    int currentURow = 0;
    for (int i = 0; i < logRow; i++) {
        if (loginVer[i][0] == userCurr.getusername()) {
            currentURow = i;
        }
    }
    // if its librarian/teacher/student
    if (loginVer[currentURow][2].compare("1") == 0) {
        cout << "\nThis is a Librarian Account." << endl;
    }
    else if (loginVer[currentURow][2].compare("2") == 0) {
        cout << "\nThis is a Teacher Account." << endl;
    }
    else if (loginVer[currentURow][2].compare("3") == 0) {
        cout << "\nThis is a Student Account." << endl;
    }

    cout << "Username: " << loginVer[currentURow][0] << endl;
    cout << "Password: " << loginVer[currentURow][1] << endl;
}