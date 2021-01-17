/*
 Book.h File Work Breakdown:
    -Jessica: Made the class. 
    -Amanda, Jessica, and Ramisa = worked together on borrow, return, reserve, etc
*/
#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Student.h"
#include "Teacher.h"
#include "Librarian.h"
using namespace std;


class Book {
private:
    int id, isbn;
    string title, author, category, readers_name;
    clock_t brwDate;
    int MAXbrw;
public:
    Book();
    Book(string bktitle, string auth, string categor, int identitynum, int code, clock_t brw_BK_Day, int Maxbrw);

    //GET FUNCTIONS//
    string getTitle();
    string getAuthor();
    string getCategory();
    int getID();
    int getISBN();
    string getUserName();
    int getRowNumber(Reader& reader);
    clock_t getbrwDate();
    int getMAXbrw();

    //SET FUNCTIONS//
    void setTitle(string title_name);
    void setAuthor(string author_name);
    void setCategory(string cat);
    void setUserName(string human); 
    void setID(int IDnum);
    void setISBN(int code);
    void setbrwDate(int bookID);
    void setMAXbrw(int nMAXbrw);
    void setBook(int bookID);

    //CLOCK FUNCTIONS//
    void storeBrwDate(clock_t brrwDate, int bookID);
    
    //Experation date (basically the max borrowing period)
    void storeExpDate(int MAXbrw, int bookID);
    int getExpDate(int bookID);
    int findMAXbrw(Reader& reader, int bookID);

    //READ FUNCTIONS
    void readBookList();
    void readBorrowedBook();
    void readReservedBook();
    void readReserveeOrder();
    void readUsertxt();

    //CHECKING FUNCTIONS//
    bool isBookBorrowed(int ID);
    bool isBookReserved(int ID);
    bool UserBorrowed(int ID, Reader& reader);
    bool UserReserved(int ID, Reader& reader);

    //PRINT FUNCTIONS//
    void printBorrowedBook();
    void printReservedBook();
    void printReserveeOrder();
    void printBookList();
    void printUsertxt();

    //MAIN FUNCTIONS//
    bool borrowbooks(int ID_num, Reader& reader);
    bool returnbooks(int ID, Reader& reader);
    bool reservebooks(int ID, Reader& reader);
    bool renewbooks(int ID, Reader& reader);
    bool cancelReservation(int ID, Reader& reader);
    int addPenalties(Reader& reader);
    bool verifyID(int bookID);
    bool checkOverdue(Reader& reader, Book book);
    void recommendedbook();

    //SEARCH FUNCTIONS//
    bool searchISBN(string ISBN);
    bool searchTitle(string title);
    bool searchAuthor(string author);
    bool searchCategory(string category);
    void searchID(string ID);
    void sortSearch(int k);

    //MY INFORMATION FUNCTIONS//
    void myInfoReader(Reader& reader);
    void myInfoUser(string reader);
    int prevBorrowBook(Reader& reader);
};