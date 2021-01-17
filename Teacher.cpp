/*
 Teacher.cpp File Work Breakdown:
    -Ramisa: Made the class.
*/
#include "Teacher.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//CONSTRUCTORS//
Teacher::Teacher()
{
    teachUsername = "";
    teachPassword = "";
    maxTeachCopy = 10;
    maxTBrwPeriod = 50;
    for (int i = 0; i < 10; i++)
        listTeachBrw[i] = 0;
    for (int i = 0; i < 5; i++)
        listTeachRes[i] = 0;
    teachPenal = 10;
}

Teacher::Teacher(string teachUser, string teachPass, int maxteachCop, int maxBrwPer, int teachPen) {
    teachUsername = teachUser;
    teachPassword = teachPass;
    maxTeachCopy = maxteachCop;
    maxTBrwPeriod = maxBrwPer;
    teachPenal = teachPen;
}

//GET FUNCTIONS//
string Teacher::getTeachUse() {
    return teachUsername;
}

string Teacher::getTeachPass() {
    return teachPassword;
}

int Teacher::getMaxTeachCpy() {
    return maxTeachCopy;
}

int Teacher::getMaxTBrwPer() {
    return maxTBrwPeriod;
}

int Teacher::getTeachPenalty() {
    return teachPenal;
}

//SET FUNCTIONS//
void Teacher::setTeachUse(string teachUser) {
    this->teachUsername = teachUser;
}

void Teacher::setTeachPass(string teachPass) {
    this->teachPassword = teachPass;
}

void Teacher::setMaxTeachCpy(int maxteachCpy) {
    maxTeachCopy = maxteachCpy;
}

void Teacher::setMaxTBrwPer(int maxBrwPer) {
    maxTBrwPeriod = maxBrwPer;
}

void Teacher::setlistTeachCpy(int bookID) {
    for (int i = 0; i < 10; i++) {
        if (listTeachBrw[i] == 0) {
            listTeachBrw[i] = bookID;
            break;
        }
    }
}

void Teacher::setlistTeachRes(int bookID) {
    for (int i = 0; i < 5; i++) {
        if (listTeachRes[i] == 0) {
            listTeachRes[i] = bookID;
            break;
        }
    }
}

void Teacher::setTeachPenalty(int teachPen) {
    teachPenal = teachPen;
}

//PENALTY FUNCTION//
void Teacher::calcTeachPenalty(int penal) {
    int booksOff = penal / 5; // will get the solution of pen / 5
    setmaxCpy(getMaxTeachCpy() - booksOff);
    if (getmaxCpy() == 0)
    {
        cout << "You can not borrow any books at this library due to many penalties!!" << endl;
        exit(1);
    }
}