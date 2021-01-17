/*
 Reader.cpp File Work Breakdown:
    -Ramisa: Made the class.
*/
#include "Reader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Constructors
Reader::Reader()
{
    copyAmount = 0;
    for (int i = 0; i < 5; i++)
        listCopy[i] = 0;
}//default

//SET FUNCTIONS//
void Reader::setCopies(int copyNum) {
    copyAmount = copyNum;
}

//GET FUNCTIONS//
int Reader::getCopies() {
    return copyAmount;
}