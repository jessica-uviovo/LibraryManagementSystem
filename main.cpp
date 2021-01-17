/*
Group Members: Ramisa Fatima, Jessica Uviovo, and Amanda Tang

 LIBRARY MANAGEMENT SYSTEM FINAL PROJECT

 Main File Work Breakdown:
    -Jessica: User and Book Class (big functions in book class were worked on together)
    -Ramisa: Reader, Teacher, Student Class
    -Amanda: Librarian Class 

Written Report: Work done by Ramisa, Jessica, and Amanda.
Formating and making the code concise: Ramisa

 */

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include "User.h"
#include "Librarian.h"
#include "Reader.h"
#include "Teacher.h"
#include "Student.h"
#include "Book.h"

using namespace std;

clock_t counter[1000];
double timeB;

void controlPanel1(istream& input, Book& book, Librarian& libraraian);
void controlPanel2(istream& input, Book& book, Teacher& teacher);
void controlPanel3(istream& input, Book& book, Student& student);

int main() {

    string username, password;
    cout << "Library Management System" << endl;

    char login = 'a';
    while (login != 'q') {
        cout << "\n\t\t(l) -- Login" << endl;
        cout << "\t\t(q) -- Quit" << endl;
        cout << "Enter: ";
        cin >> login;

        if (login == 'q')
            exit(1);
        if (login == 'l') {

            cout << "\nUsername: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            User user;
            Book book;
            user.setusername(username);
            user.setpassword(password);
            user.readUsertxt();
            if (user.verifyUser(username, password)) {
                string userType = user.getType();
                string penal = user.getPenalty();
                char type = userType[0];
                int penalTea = stoi(penal);
                if (type == '1') {
                    Librarian lib;
                    lib.setusername(username);
                    lib.setpassword(password);
                    lib.readUsertxt();
                    lib.setType(userType);
                    controlPanel1(cin, book, lib);
                }
                else if (type == '2') {
                    Teacher teach;
                    teach.setusername(username);
                    teach.setpassword(password);
                    teach.readUsertxt();
                    teach.setType(userType);

                    teach.setTeachPenalty(penalTea);
                    teach.calcTeachPenalty(teach.getTeachPenalty());
                    int Tprevious = book.prevBorrowBook(teach);
                    teach.setCopies(Tprevious);
                    controlPanel2(cin, book, teach);
                }
                else if (type == '3') {
                    Student student;
                    student.setusername(username);
                    student.setpassword(password);
                    student.readUsertxt();
                    student.setType(userType);
                    student.setStudPenalty(penalTea);
                    student.calcStudPenalty(student.getStudPenalty());
                    int Sprevious = book.prevBorrowBook(student);
                    student.setCopies(Sprevious);
                    controlPanel3(cin, book, student);
                }
                else
                    cout << "\nIncorrect user type" << endl;
            }
        }
        else
            cout << "Incorrect option" << endl;
    }

    return 0;
}

void controlPanel1(istream& input, Book& book, Librarian& librarian)
{
    cout << "\n-------------------------------------" << endl;
    cout << "\n       Welcome to My Library!" << endl;
    cout << "\n-------------------------------------" << endl;
    cout << endl;
    cout << "\nWelcome Back, Librarian " << librarian.getusername()<< endl;
   
    int oper = 1;
    while (oper != 0) {
        cout << "\nPlease Choose: " << endl;
        cout << "\t\t1 -- Search Books" << endl;
        cout << "\t\t2 -- Add Books" << endl;
        cout << "\t\t3 -- Delete Books" << endl;
        cout << "\t\t4 -- Search Users" << endl;
        cout << "\t\t5 -- Add Users" << endl;
        cout << "\t\t6 -- Delete Users" << endl;
        cout << "\t\t7 -- My Information" << endl;
        cout << "\t\t8 -- Change Password" << endl;
        cout << "\t\t0 -- Log Out" << endl;
        cout << "Enter Option Number: ";
        cin >> oper;

        switch (oper) {
        case 1:
        {
            int num;
            cout << "\nSearching for a book..." << endl;
            cout << "How do you want to search for a book?" << endl;
            cout << "\t\t1 -- Search by ISBN" << endl;
            cout << "\t\t2 -- Search by Title" << endl;
            cout << "\t\t3 -- Search by Author Name" << endl;
            cout << "\t\t4 -- Search by Category" << endl;
            cout << "\nEnter Option Number: ";
            cin >> num;

            if (num == 1) {
                string isbn;
                cout << "Enter the ISBN: ";
                cin >> isbn;
                book.searchISBN(isbn);
            }
            else if (num == 2) {
                string titleName;
                cout << "Enter the title: ";
                cin >> titleName;
                book.searchTitle(titleName);
            }
            else if (num == 3) {
                string auth;
                cout << "Enter the author: ";
                cin >> auth;
                book.searchAuthor(auth);
            }
            else if (num == 4) {
                string cat;
                cout << "Enter the category: ";
                cin >> cat;
                book.searchCategory(cat);
            }
            else {
                cout << "Error: Incorrect Choice Number. Try Again!" << endl;
                break;
            }
        }
            break;
        
        case 2:
        {
            string ISBN;
            string title, authorName, category;
            cout << "\nAdding a new book ..." << endl;
            cout << "Enter the ISBN: ";
            cin >> ISBN;
            cout << "Enter the title of the book: ";
            cin >> title;
            cout << "Enter the author name: ";
            cin >> authorName;
            cout << "Enter the category: ";
            cin >> category;
            librarian.addBooks(ISBN, title, authorName, category);
        }
            break;
        
        case 3:
        {
            string id;
            cout << "\nDeleting a Book . . ." << endl;
            cout << "Enter the ID number of the book: ";
            cin >> id;
            librarian.deleteBooks(id);
        }
            break;
        case 4:
        {
            string user;
            cout << "\nSearch Users . . ." << endl;
            cout << "Enter the username: ";
            cin >> user;
            if (librarian.searchUsers(user))
                book.myInfoUser(user);
        }
            break;
        case 5:
        {
            string user, pass, who;
            cout << "\nAdding New User . . . " << endl;
            cout << "Enter the new username: ";
            cin >> user;
            cout << "Enter the new user's password: ";
            cin >> pass;
            cout << "What is this user's identity?" << endl;
            cout << "\nEnter the number corresponding to the identity:" << endl;
            cout << "\t\t1 -- Librarian" << endl;
            cout << "\t\t2 -- Teacher" << endl;
            cout << "\t\t3 -- Student" << endl;
            cout << "\nEnter your choice: ";
            cin >> who;
            librarian.addUser(user, pass, who);
        }
            break;
       
        case 6:
        {
            string user;
            cout << "\nEnter the user you want to delete: ";
            cin >> user;
            librarian.deleteUser(user);
        }
            break;
        case 7:
        {
            cout << "My Information . . ." << endl;
            librarian.myInfo(librarian);
        }
            break;

        case 8:
        {
            string old, newPass;
            cout << "\nChanging Password . . . " << endl;
            cout << "\nEnter your current password: ";
            cin >> old;

            cout << "\nEnter your new password: ";
            cin >> newPass;
 
            librarian.changePw(librarian, old, newPass);

        }
            break;
       
        case 0:
            break;
       
        default: 
            cout << "\nNo such option exists. Please enter another option." << endl;
            break;
        }
    }
}

void controlPanel2(istream& input, Book& book, Teacher& teacher)
{
    cout << "\n-------------------------------------" << endl;
    cout << "\n       Welcome to My Library!" << endl;
    cout << "\n-------------------------------------" << endl;
    cout << endl;
    cout << "\nWelcome Back, Teacher " <<  teacher.getusername()<<endl;

    int oper = 1, ID_num;

    while (oper != 0) {
        cout << "\nPlease Choose: " << endl;
        cout << "\t\t1 -- Search Books" << endl;
        cout << "\t\t2 -- Borrow Books" << endl;
        cout << "\t\t3 -- Return Books" << endl;
        cout << "\t\t4 -- Reserve Books" << endl;
        cout << "\t\t5 -- Cancel Reservations" << endl;
        cout << "\t\t6 -- Renew Books" << endl;
        cout << "\t\t7 -- My Information" << endl;
        cout << "\t\t8 -- Change Password" << endl;
        cout << "\t\t9 -- Recommend Random Books" << endl;
        cout << "\t\t0 -- Log Out" << endl;
        cout << "Enter Option Number: ";
        cin >> oper;

        switch (oper) {
        case 1:
        {
            int num1;
            cout << "\nSearching for a book..." << endl;
            cout << "How do you want to search for a book?" << endl;
            cout << "\t\t1 -- Search by ISBN" << endl;
            cout << "\t\t2 -- Search by Title" << endl;
            cout << "\t\t3 -- Search by Author Name" << endl;
            cout << "\t\t4 -- Search by Category" << endl;
            cout << "\nEnter Option Number: ";
            cin >> num1;

            if (num1 == 1) {
                string isbn;
                cout << "Enter the ISBN: ";
                cin >> isbn;
                book.searchISBN(isbn);
            }
            else if (num1 == 2) {
                string titleName;
                cout << "Enter the title: ";
                cin >> titleName;
                book.searchTitle(titleName);
            }
            else if (num1 == 3) {
                string auth;
                cout << "Enter the author: ";
                cin >> auth;
                book.searchAuthor(auth);
            }
            else if (num1 == 4) {
                string cat;
                cout << "Enter the category: ";
                cin >> cat;
                book.searchCategory(cat);
            }
            else {
                cout << "Error: Incorrect Choice Number. Try Again!" << endl;
                break;
            }
        }
        break;
        case 2:
            cout << "Borrowing a Book . . ." << endl;
            cout << "\nEnter book ID: ";
            cin >> ID_num;
            if (book.borrowbooks(ID_num, teacher) != false) {
                counter[ID_num] = clock();
                book.storeBrwDate(counter[ID_num], ID_num);
                cout << "Timer Has Started.\n";
            }
            else {
                break;
            }
            break;

        case 3:
            cout << "Returning a Book . . ." << endl;
            cout << "\n Enter book ID: ";
            cin >> ID_num;

            if (book.returnbooks(ID_num, teacher) != false) {
                cout << "Timer has Ended. \n";

                counter[ID_num] = clock() - counter[ID_num];
                timeB = (((double)counter[ID_num]) / CLOCKS_PER_SEC) / 5; // calculate the elapsed time

                if (timeB >= book.getExpDate(ID_num)) {
                    cout << "Your book was overdue!" << endl;
                    teacher.calcTeachPenalty(book.addPenalties(teacher));
                }

                cout << "This book is returned after " << timeB << " days." << endl;

            }
            break;
        case 4:
            //reserve books
            cout << "Enter Book ID: ";
            cin >> ID_num;
            book.reservebooks(ID_num, teacher);
            break;

        case 5:
            //cancel reservation
            cout << "Enter Book ID: ";
            cin >> ID_num;
            book.cancelReservation(ID_num, teacher);
            break;

        case 6:
            cout << "Enter Book ID: ";
            cin >> ID_num;
            if (book.renewbooks(ID_num, teacher) != false) {
                counter[ID_num] = clock();
                book.storeBrwDate(counter[ID_num], ID_num);
                cout << "Timer Has Started.\n";
            }
            else {
                break;
            }
            break;

        case 7:
        {
            cout << "My Information . . ." << endl;
            teacher.myInfo(teacher);
            book.myInfoReader(teacher);
        }
        break;

        case 8:
        {
            string old, newPass;
            cout << "\nChanging Password . . . " << endl;
            cout << "\nEnter your current password: ";
            cin >> old;

            cout << "\nEnter your new password: ";
            cin >> newPass;

            teacher.changePw(teacher, old, newPass);

        }

        break;
        case 9:
            cout << "Recommending Books . . ." << endl;
            book.recommendedbook();
            break;

        case 0:
            break;
        default: cout << "\nNo such option exists. Please enter another option." << endl;
            break;
        }
    }
}

void controlPanel3(istream& input, Book& book, Student& student)
{
    cout << "\n-------------------------------------" << endl;
    cout << "\n       Welcome to My Library!" << endl;
    cout << "\n-------------------------------------" << endl;
    cout << endl;
    cout << "\nWelcome Back, Student " << student.getusername()<<endl;

    int oper = 1, ID_num;
    //clock_t counter[1000];
    //double time;

    while (oper != 0) {
        cout << "\nPlease Choose: " << endl;
        cout << "\t\t1 -- Search Books" << endl;
        cout << "\t\t2 -- Borrow Books" << endl;
        cout << "\t\t3 -- Return Books" << endl;
        cout << "\t\t4 -- Reserve Books" << endl;
        cout << "\t\t5 -- Cancel Reservations" << endl;
        cout << "\t\t6 -- Renew Books" << endl;
        cout << "\t\t7 -- My Information" << endl;
        cout << "\t\t8 -- Change Password" << endl;
        cout << "\t\t9 -- Recommend Books" << endl;
        cout << "\t\t0 -- Log Out" << endl;
        cout << "Enter Option Number: ";
        cin >> oper;

        switch (oper) {
        case 1:
        {
            int num;
            cout << "\nSearching for a book..." << endl;
            cout << "How do you want to search for a book?" << endl;
            cout << "\t\t1 -- Search by ISBN" << endl;
            cout << "\t\t2 -- Search by Title" << endl;
            cout << "\t\t3 -- Search by Author Name" << endl;
            cout << "\t\t4 -- Search by Category" << endl;
            cout << "\nEnter Option Number: ";
            cin >> num;

            if (num == 1) {
                string isbn;
                cout << "Enter the ISBN: ";
                cin >> isbn;
                book.searchISBN(isbn);
            }
            else if (num == 2) {
                string titleName;
                cout << "Enter the title: ";
                cin >> titleName;
                book.searchTitle(titleName);
            }
            else if (num == 3) {
                string auth;
                cout << "Enter the author: ";
                cin >> auth;
                book.searchAuthor(auth);
            }
            else if (num == 4) {
                string cat;
                cout << "Enter the category: ";
                cin >> cat;
                book.searchCategory(cat);
            }
            else {
                cout << "Error: Incorrect Choice Number. Try Again!" << endl;
                break;
            }
        }
        break;

        case 2:
            cout << "Borrowing a Book . . ." << endl;
            cout << "\nEnter book ID: ";
            cin >> ID_num;
            if (book.borrowbooks(ID_num, student) != false) {
                counter[ID_num] = clock();
                book.storeBrwDate(counter[ID_num], ID_num);
                cout << "Timer Has Started.\n";
            }
            else {
                break;
            }
            break;

        case 3:
            cout << "Returning a Book . . ." << endl;
            cout << "\n Enter book ID: ";
            cin >> ID_num;

            if (book.returnbooks(ID_num, student) != false) {
                cout << "Timer has Ended. \n";
                counter[ID_num] = clock() - counter[ID_num];

                timeB = (((double)counter[ID_num]) / CLOCKS_PER_SEC) / 5; // calculate the elapsed time
                if (timeB >= book.getExpDate(ID_num)) {
                    cout << "Your book was overdue!" << endl;
                    
                    student.calcStudPenalty(book.addPenalties(student));
                }
                cout << "This book is returned after " << timeB << " days." << endl;

            }
            break;
        case 4:
            //reserve books
            cout << "Enter Book ID: ";
            cin >> ID_num;
            book.reservebooks(ID_num, student);
            break;

        case 5:
            //cancel reservation
            cout << "Enter Book ID: ";
            cin >> ID_num;
            book.cancelReservation(ID_num, student);
            break;

        case 6:
            cout << "Enter Book ID: ";
            cin >> ID_num;
            if (book.renewbooks(ID_num, student) != false) {
                counter[ID_num] = clock();
                book.storeBrwDate(counter[ID_num], ID_num);
                cout << "Timer Has Started.\n";
            }
            else {
                break;
            }
            break;

        case 7:
        {
            cout << "My Information . . ." << endl;
            student.myInfo(student);
            book.myInfoReader(student);
        }
        break;

        case 8:
        {
            string old, newPass;
            cout << "\nChanging Password . . . " << endl;
            cout << "\nEnter your current password: ";
            cin >> old;

            cout << "\nEnter your new password: ";
            cin >> newPass;

            student.changePw(student, old, newPass);

        }
              
        break;
        case 9:
            cout << "Recommending Books . . ." << endl;
            book.recommendedbook();
            break;

        case 0:
            break;
        default: cout << "\nNo such option exists. Please enter another option." << endl;
            break;
        }
    }
}
