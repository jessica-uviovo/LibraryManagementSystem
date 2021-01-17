/*
 Student.h File Work Breakdown:
    -Ramisa: Made the class.
*/
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Reader.h"
using namespace std;

class Student : public Reader{
private:
    string studUsername;
    string studPassword;
    int maxStudCopy;
    int maxSBrwPeriod;
    int listStudBrw[5];
    int listStudRes[5];
    int studPenal;
public:
    Student();
    Student(
        string studUser,
        string studPass,
        int maxStudCop,
        int maxSBrwPer,
        int studPen
    );

    //GET FUNCTIONS//
    string getStudUse();
    string getStudPass();
    int getMaxStudCpy();
    int getMaxSBrwPer();
    int getStudPenalty();

    //SET FUNCTIONS//
    void setStudUse(string studUser);
    void setStudPass(string studPass);
    void setMaxStudCpy(int maxStudCop);
    void setMaxSBrwPer(int maxBrwPer);
    void setlistStudCpy(int bookID);
    void setlistStudRes(int bookID);
    void setStudPenalty(int studPen);

    //PENALTY
    void calcStudPenalty(int penal);

};
