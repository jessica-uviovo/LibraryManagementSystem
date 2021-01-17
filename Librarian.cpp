/*
 Librarian.cpp File Work Breakdown:
    -Amanda: Made the class.
*/
#include "Librarian.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

//BOOK.TXT ARRAY//
string libBookList[100][6];
int libBookRow = 0, libBookCol = 6;
int idNumberlib[100], idNumber_Rowlib = 0;

//USER.TXT ARRAY//
string userArraylib[100][4];
int uRow = 0, uCol = 4;
int searchRow = -1;

//BORROWED BOOKS ARRAY//
int BorrowBookslib[100][10], borRowlib = 100, borCollib = 10;

//RESERVED BOOKS ARRAY//
int ReserveBookslib[100][5], resRowlib = 100, resCollib = 5;

//RESERVEE ORDER ARRAY//
int resOrderlib[100][50], resOrderlibCol = 50;


//CONSTRUCTORS//
Librarian::Librarian()
{
    libUsername = "";
    libPassword = "";
}

Librarian::Librarian(string userlib, string passlib) {
    libUsername = userlib;
    libPassword = passlib;
}


//GET FUNCTIONS//
string Librarian::getLibUse() {
    return libUsername;
}

string Librarian::getLibPass() {
    return libPassword;
}


//SET FUNCTIONS//
void Librarian::setLibUse(string libUser) {
    this->libUsername = libUser;
}

void Librarian::setLibPass(string libPass) {
    this->libPassword = libPass;
}


//READ FUNCTIONS//
//Reads the book.txt
void Librarian::readLibBookList() {
    ifstream input("book.txt");
    if (input.fail()) {
        cerr << "ERROR: book.txt could not be opened." << endl;
        exit(1);
    }
    //resets row to 0 to start in beginning
    libBookRow = 0;

    //reads through the txt and stores into array
    while (!input.eof()) {
        for (int j = 0; j < libBookCol; j++) {
            input >> libBookList[libBookRow][j];
        }
        libBookRow++;
    }
    libBookRow--;
    
    //making the ID not go by rows
    string test;
    for (int i = 0; i < libBookRow; i++) {
        test = libBookList[i][0];
    }
    idNumber_Rowlib = stoi(test);

    input.seekg(0, ios::beg);
    input.close();
}

//reads borrowedbook.txt
void Librarian::readLibBorrowedBook() {
    int i, j;
    ifstream brw_Bks_File("borrowedbooks.txt");
    if (brw_Bks_File.fail())
    {
        cerr << "ERROR: borrowedbooks.txt could not be opened." << endl;
        exit(1);
    }

    //reads the file and stores into array
    while (!brw_Bks_File.eof())
    {
        for (i = 0; i < borRowlib; i++)
            for (j = 0; j < borCollib; j++)
            {
                brw_Bks_File >> BorrowBookslib[i][j];
            }
    }
    brw_Bks_File.seekg(0, ios::beg);
    brw_Bks_File.close();
}

//reads reservedbooks.txt
void Librarian::readLibReservedBook()
{
    ifstream reservedFile("reservedbooks.txt");
    if (reservedFile.fail())
    {
        cerr << "ERROR: reservedbooks.txt could not be opened." << endl;
        exit(1);
    }

    //reads the file and stores into array
    while (!reservedFile.eof())
    {
        for (int i = 0; i < resRowlib; i++)
            for (int j = 0; j < resCollib; j++)
            {
                reservedFile >> ReserveBookslib[i][j];
            }
    }
    reservedFile.seekg(0, ios::beg);
    reservedFile.close();
}

//reads reserveeorder.txt
void Librarian::readLibReserveeOrder()
{
    ifstream inFile("reserveeOrder.txt");
    if (inFile.fail())
    {
        cerr << "ERROR: orderReserved.txt could not be opened." << endl;
        exit(1);
    }

    //reads the file and stores it into array
    while (!inFile.eof())
    {
        for (int i = 0; i < libBookRow; i++) {
            for (int j = 0; j < resOrderlibCol; j++)
            {
                inFile >> resOrderlib[i][j];
            }
        }
    }
    inFile.seekg(0, ios::beg);
    inFile.close();
}

//reads the user from user.txt
void Librarian::readUser() {
    ifstream input("User.txt");
    if (input.fail()) {
        cerr << "ERROR: User.txt could not be opened." << endl;
        exit(1);
    }
    uRow = 0;
    while (!input.eof()) {
        for (int j = 0; j < uCol; j++) {
            input >> userArraylib[uRow][j];
        }
        uRow++;
    }
    input.seekg(0, ios::beg);
    input.close();
}


//PRINT FUNCTIONS//
//prints to book.txt
void Librarian::printBookList()
{
    ofstream Bks_File("book.txt");
    if (Bks_File.fail())
    {
        cerr << "Error: book.txt could not be opened to print." << endl;
        exit(1);
    }

    for (int i = 0; i < libBookRow; i++) {
        for (int j = 0; j < libBookCol; j++)
        {
            Bks_File << libBookList[i][j] << " ";
        }
        Bks_File << endl;
    }//

    Bks_File.seekp(ios::beg);
    Bks_File.close();
}

//prints to borrowedbooks.txt
void Librarian::printLibBorrowedBook()
{
    fstream brw_Bks_File("borrowedbooks.txt");
    if (brw_Bks_File.fail())
    {
        cerr << "Error. borrowedbooks.txt could not be opened." << endl;
        exit(1);
    }
    for (int i = 0; i < borRowlib; i++)
    {
        for (int j = 0; j < borCollib; j++)
        {
            brw_Bks_File << BorrowBookslib[i][j] << " ";
        }
        brw_Bks_File << endl;
    }
    brw_Bks_File.seekp(0, ios::beg);
    brw_Bks_File.close();
}

//prints into reserveeorder.txt
void Librarian::printLibReserveeOrder()
{
    ofstream outFile("orderReserved.txt");
    if (outFile.fail())
    {
        cerr << "Error. orderReserved.txt could not be opened." << endl;
        exit(1);
    }
    for (int i = 0; i < libBookRow; i++)
    {
        for (int j = 0; j < resOrderlibCol; j++)
        {
            outFile << resOrderlib[i][j] << " ";
        }
        outFile << endl;
    }
    outFile.seekp(0, ios::beg);
    outFile.close();
}

//prints into reservedbook.txt
void Librarian::printLibReservedBook()
{
    ofstream reservedBooksFile("reservedbooks.txt");
    if (reservedBooksFile.fail())
    {
        cerr << "Error. reservedbooks.txt could not be opened." << endl;
        exit(1);
    }
    for (int i = 0; i < resRowlib; i++)
    {
        for (int j = 0; j < resCollib; j++)
        {
            reservedBooksFile << ReserveBookslib[i][j] << " ";
        }
        reservedBooksFile << endl;
    }
    reservedBooksFile.seekp(0, ios::beg);
    reservedBooksFile.close();
}

//prints the user into user.txt
void Librarian::printUser()
{
    ofstream input("User.txt");
    if (input.fail())
    {
        cerr << "Error: User.txt could not be opened to print." << endl;
        exit(1);
    }

    for (int i = 0; i < uRow; i++) {
        for (int j = 0; j < uCol; j++)
        {
            input << userArraylib[i][j] << " ";
        }
        input << endl;
    }
    input.close();
}


//MAIN FUNCTIONS//
//adds books to book.txt
void Librarian::addBooks(string ISBN, string title, string authorName, string category)
{   
    //reads the files
    readLibBookList();
    readLibReserveeOrder();

    int pop = 0;
    idNumber_Rowlib++;
    //getting the id
    libBookRow++;
    // prints the book
    libBookList[libBookRow - 1][0] = to_string(idNumber_Rowlib);
    libBookList[libBookRow - 1][1] = title;
    libBookList[libBookRow - 1][2] = authorName;
    libBookList[libBookRow - 1][3] = category;
    libBookList[libBookRow - 1][4] = ISBN;
    libBookList[libBookRow - 1][5] = to_string(pop);
    //adding 0 for popularity
    resOrderlib[libBookRow - 1][0] = idNumber_Rowlib;

    for (int i = 1; i < resOrderlibCol; i++)
    {
        resOrderlib[libBookRow - 1][i] = 0;
    }
    //printing to book.txt
    printLibReserveeOrder();
    printBookList();
    cout << "\nBook Added: " << to_string(idNumber_Rowlib) << " " << title << " " << authorName << " " << category << " " << ISBN << " " << pop << endl;
}

//serches books by ID
int Librarian::searchBookID(string ID) {
    readLibBookList();
    
    int k = 0;
    bool flag = false;

    for (int i = 0; i < libBookRow; i++)
    {
        if (ID.compare(libBookList[i][0]) == 0)
        {
            cout << "Book has been found!" << endl;
            flag = true;

            return i; // if book was found
        }
    }

    if (!flag) {
        cout << "Error: There is no book with ID " << ID << endl;
        return -1;
    }

    return -1;
}

//deletes books from book.txt
void Librarian::deleteBooks(string ID) {
    //Id for temp = row of book
    int temp;
    temp = searchBookID(ID);
    //reads the files
    readLibBorrowedBook();
    readLibReservedBook();
    readLibReserveeOrder();

    bool flag = true;
    //looks for book
    for (int i = 0; i < borRowlib; i++) {
        for (int j = 0; j < borCollib; j++) {
            if (stoi(ID) == BorrowBookslib[i][j]) {
                cout << "ERROR: Book is borrowed. Cannot delete a borrowed book" << endl;
                flag = false; //book cant be deleted
                break;
            }
        }
    }
    //if book doesn't exist
    if (temp == -1) {
        cout << "ERROR: Book does not exist." << endl;
    }
    else if (flag) {
        //getting rid of book from reserve
        for (int i = 0; i < resRowlib; i++) {
            for (int j = 0; j < resCollib; j++) { //if book is reserved, cancel reservations
                if (stoi(ID) == ReserveBookslib[i][j]) {
                    ReserveBookslib[i][j] = 0; 
                }
            }
        }
        // print to reserve book the 0s.
        printLibReservedBook();

        // same for reservee order.txt
        for (int i = 0; i < libBookRow; i++) {
            for (int j = 0; j < resOrderlibCol; j++) {
                if (stoi(ID) == resOrderlib[i][j]) {
                    resOrderlib[i][j] = resOrderlib[i+1][j]; 
                }
            }
        }
        
        cout << "\nBook Deleted: " << ID << " " << libBookList[temp][1] << " " << libBookList[temp][2] << " " << libBookList[temp][3] << " " << 
            libBookList[temp][4] << " " << libBookList[temp][5] << endl;

        //deletes the book from book.txt
        for (int i = temp; i < libBookRow; i++) {
            for (int j = 0; j < libBookCol; j++) {
                libBookList[i][j] = libBookList[i + 1][j]; 
            }
        }
        libBookRow--;
        //prints to files
        printLibReserveeOrder();       
        printBookList();
    }
}

//searches for users
bool Librarian::searchUsers(string username)
{
    readUser();
    int flag = 0;
    searchRow = -1;
    //Finds the user in array
    for (int i = 0; i < uRow; i++)
    {
        if (username == userArraylib[i][0])
        {
            //User found
            if (userArraylib[i][2] == "1")
            {
                cout << "\nUser is a Librarian" << endl;
                cout << "Username: " << userArraylib[i][0] << endl;
                cout << "Password: " << userArraylib[i][1] << endl;
                searchRow = i;
                flag = 1;
            }
            else if (userArraylib[i][2] == "2")
            {
                cout << "\nUser is a Teacher" << endl;
                cout << "Username: " << userArraylib[i][0] << endl;
                cout << "Password: " << userArraylib[i][1] << endl;
                searchRow = i;
                flag = 1;
            }
            else if (userArraylib[i][2] == "3") 
            {
                cout << "\nUser is a Student" << endl;
                cout << "Username: " << userArraylib[i][0] << endl;
                cout << "Password: " << userArraylib[i][1] << endl;
                searchRow = i;
                flag = 1;
            }
        }
    }
    //if user doesn't exist
    if (flag == 0) {
        cout << "ERROR: User does not exist." << endl;
        searchRow = -1;
        return false;
    }
    return true;
}

//add users into user.txt
void Librarian::addUser(string username, string password, string who)
{
    readUser();
    bool flag = true;
    //if inputs same username as another user
    for (int i = 0; i < uRow; i++)
    {
        if (username == userArraylib[i][0])
        {
            cout << "ERROR: This username has already been taken" << endl;
            flag = false;
            break;
        }
    }
    //prints into user.txt
    if (flag) {
        userArraylib[uRow - 1][0] = username;
        userArraylib[uRow - 1][1] = password;
        userArraylib[uRow - 1][2] = who;
        userArraylib[uRow - 1][3] = "0";
        printUser();
        cout << "\nUser Added: " << username << " " << password << " " << who << " 0" << endl;
    }

}

//delete users from user.txt
void Librarian::deleteUser(string username)
{
    searchUsers(username);
    cout << "\nDeleting User..." << endl;
    bool flag = true;
    //reads the files
    readLibBookList();
    readLibBorrowedBook();
    readLibReservedBook();
    readLibReserveeOrder();
    
    //if no user found
    if (searchRow == -1) {
        cout << "\nERROR: User does not exist" << endl;
        flag = false;
    }
    else if (searchRow != -1){//if user is found
        
        //if user exists check if they borrowed a book(s)
        for (int j = 0; j < uCol; j++) {
            if (BorrowBookslib[searchRow][j] != 0) {//if there is a book borrowed
                cout << "ERROR: User has books borrowed. Cannot delete user with borrowed books!" << endl;
                flag = false;
                break;
            }
        }

        if (flag) {
            //update reserve txt
            for (int i = searchRow; i < resRowlib; i++) {//remove from reservation list
                for (int j = 0; j < resCollib; j++) {
                    ReserveBookslib[i][j] = ReserveBookslib[i + 1][j];
                }
            }

            //update reservee order
            for (int i = 0; i < libBookRow; i++) {//remove from order res
                for (int j = 0; j < resOrderlibCol; j++) {
                    if ((searchRow+1 == resOrderlib[i][j]) && (j != 0)) {
                        //shifting
                        if (resOrderlib[i][j + 1] != 0) {//if next number in same row is not 0
                            for (int k = j; k < libBookRow; k++) {//goes through rest of row
                                resOrderlib[i][k] = resOrderlib[i][k+1];
                            }
                            resOrderlib[i][resOrderlibCol -1] = 0;
                        }
                    }
                }
            }
            cout << "User Deleted!" << endl;
            //deletes the user
            for (int i = searchRow; i < uRow; i++) {
                for (int j = 0; j < uCol; j++) {
                    userArraylib[i][j] = userArraylib[i + 1][j];
                }
            }
            uRow--;
            printLibReserveeOrder();
            printLibReservedBook();
            printUser();
        }
        
    }
    
}
