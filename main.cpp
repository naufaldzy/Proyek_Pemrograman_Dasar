#include <iostream>
#include "skema_member.h"
#include "skema_peminjaman.h"
using namespace std;

int getMainOption();

int main(){
    
    int option = getMainOption();
    string is_continue;
    enum Option{RENT = 1, RETURN, DISPLAY, MEMBER, EXIT};

    while(option != EXIT){
        switch(option){
            case RENT:
                cout << "Rent Playstation" << endl;
                get_addRental();
                break;
            case RETURN:
                get_pengembalian();
                break;
            case DISPLAY:
                get_displayRental();
                break;
            case MEMBER:
                skema_member();
                break;
            default:
                cout << "Invalid Input: Program can't be run" << endl;
                break;
        }

        continue1:
        cout << "======================================" << endl;
        cout << "\nContinue?[Yes/No] : ";
        cin >> is_continue;
        cin.ignore(1,'\n');
        if ((is_continue == "Yes")|(is_continue == "yes")){
            option = getMainOption();
        } else if((is_continue == "No")|(is_continue == "no")){
            break;
        } else{
            cout << "Invalid Input: Program can't be run"<< endl;
            goto continue1;
        }

    }

    return 0;
}

int getMainOption(){
    int input;

    system("cls");
    cout << "   Playstation Rental [LAKAKA Store]" << endl;
    cout << "======================================" << endl;
    cout << "1. Rent Playstation" << endl;
    cout << "2. Return Playstation" << endl;
    cout << "3. Display Rental Data" << endl;
    cout << "4. Membership" << endl;
    cout << "5. Exit" << endl;
    cout << "======================================" << endl;
    cout << "Submit your selection : ";
    cin >> input;
    cin.ignore(1,'\n');

    return input;
}