/*
User.h File Work Breakdown:
    -Jessica: Made the class.
*/
#pragma once
#include <iostream>
#include <string>
using namespace std;

class User {
private:
    string user, pword;
    string type, penalT;
    int maxCpy;//max borrowing period -> moslty for after penaties are appied
public:
    User();

    //GET FUNCTIONS//
    string getusername();
    string getpassword();
    string getPenalty();
    int getmaxCpy();
    string getType();

    //SET FUNCTIONS//
    void setusername(string newUser);
    void setpassword(string newPword);
    void setType(string userType);
    void setPenalty(string penaltie);
    void setmaxCpy(int Cpy);

    //OTHER FUNCTIONS//
    void readUsertxt();
    void printUsertxt();
    bool verifyUser(string user_att1, string pass_att1);
    void changePw(User& userCurr, string old, string newPass);
    void myInfo(User& userCurr);
};
