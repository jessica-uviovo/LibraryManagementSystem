/*
 Reader.h File Work Breakdown:
    -Ramisa: Made the class.
*/
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "User.h"
using namespace std;

class Reader : public User {
private:
    int copyAmount, listCopy[10];
public:
    Reader();
    
    //SET FUNCTIONS//
    void setCopies(int copyNum);

    //GET FUNCTIONS//
    int getCopies();
};

