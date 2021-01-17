/*
 Student.cpp File Work Breakdown:
    -Ramisa: Made the class.
*/
#include "Student.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//CONSTRUCTORS//
Student::Student() {
    studUsername = "";
    studPassword = "";
    maxStudCopy = 5;
    maxSBrwPeriod = 30;
    for (int i = 0; i < 5; i++)
        listStudBrw[i] = 0;
    for (int i = 0; i < 5; i++)
        listStudRes[i] = 0;
    studPenal = 5;
};

Student::Student(string studUser, string studPass, int maxStudCop, int maxBrwPer, int studPen) {
    studUsername = studUser;
    studPassword = studPass;
    maxStudCopy = maxStudCop;
    maxSBrwPeriod = maxBrwPer;
    studPenal = studPen;
}

//GET FUNCTIONS//
string Student::getStudUse() {
    return studUsername;
}

string Student::getStudPass() {
    return studPassword;
}

int Student::getMaxStudCpy() {
    return maxStudCopy;
}

int Student::getMaxSBrwPer() {
    return maxSBrwPeriod;
}

int Student::getStudPenalty() {
    return studPenal;
}

//SET FUNCTIONS//
void Student::setStudUse(string studUser) {
    this->studUsername = studUser;
}

void Student::setStudPass(string studPass) {
    this->studPassword = studPass;
}

void Student::setMaxStudCpy(int maxStudCpy) {
    maxStudCopy = maxStudCpy;
}

void Student::setMaxSBrwPer(int maxBrwPer) {
    maxSBrwPeriod = maxBrwPer;
}

void Student::setlistStudCpy(int bookID) {
    for (int i = 0; i < 5; i++) {
        if (listStudBrw[i] == 0) {
            listStudBrw[i] = bookID;
            break;
        }
    }
}

void Student::setlistStudRes(int bookID) {
    for (int i = 0; i < 5; i++) {
        if (listStudRes[i] == 0) {
            listStudRes[i] = bookID;
            break;
        }
    }
}

void Student::setStudPenalty(int studPen) {
    studPenal = studPen;
}

//PENALTY FUNCTION//
void Student::calcStudPenalty(int penalt) {
     int booksOff = penalt / 5; // will get the solution of pen / 5
     setmaxCpy(getMaxStudCpy() - booksOff);
     if (getmaxCpy() == 0)
     {
         cout << "You can not borrow any books at this library due to many penalties!!" << endl;
         exit(1);
     }
}

