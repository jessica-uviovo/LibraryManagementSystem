/*
 Teacher.h File Work Breakdown:
    -Ramisa: Made the class.
*/
#pragma once
#include "Reader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Teacher : public Reader {
private:
    string teachUsername;
    string teachPassword;
    int maxTeachCopy;
    int maxTBrwPeriod;
    int listTeachBrw[10];
    int listTeachRes[5];
    int teachPenal;
public:
    Teacher();
    Teacher(
        string teachUser,
        string teachPass,
        int maxTeachCop,
        int maxTBrwPer,
        int teachPen
    );

    //GET FUNCTIONS//
    string getTeachUse();
    string getTeachPass();
    int getMaxTeachCpy();
    int getMaxTBrwPer();
    int getTeachPenalty();

    //SET FUNCTIONS//
    void setTeachUse(string teachUser);
    void setTeachPass(string teachPass);
    void setMaxTeachCpy(int maxteachCop);
    void setMaxTBrwPer(int maxBrwPer);
    void setlistTeachCpy(int bookID);
    void setlistTeachRes(int bookID);
    void setTeachPenalty(int teachPen);
    
    //PENALTY
    void calcTeachPenalty(int penal);
};
