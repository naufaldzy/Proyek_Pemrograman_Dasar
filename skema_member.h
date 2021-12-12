#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;

class memberset{
    public:
    string name;
    string telephone_number;
    string NoID;

    memberset(string inputname, string inputtelephone_number, string inputNoID){
        memberset::name = inputname;
        memberset::telephone_number = inputtelephone_number;
        memberset::NoID = inputNoID;

    }

    string getString_name(){
        return memberset::name;
    }

    string getString_telephone(){
        return memberset::telephone_number;
    }

    string getString_NoID(){
        return memberset::NoID;
    }


};

class DBMemberset{
    public:
    ifstream Database1;
    ofstream Database2;
    string nameOfile;

    DBMemberset(const char* nameOfile){
        DBMemberset::nameOfile = nameOfile;
    }

    void addDataMember(memberset data){
        DBMemberset::Database2.open(DBMemberset::nameOfile, ios::app);
        DBMemberset::Database2 << data.getString_NoID() << endl;
        DBMemberset::Database2 << data.getString_name() << endl;
        DBMemberset::Database2 << data.getString_telephone() << endl << endl;
        DBMemberset::Database2.close();
    }

    void displayDataMember(memberset data){
        string name, nomor, NoID;
        unsigned short index = 1;
        DBMemberset::Database1.open(DBMemberset::nameOfile, ios::in);
        
        while(!DBMemberset::Database1.eof()){
            getline(DBMemberset::Database1, NoID);
            if((NoID == "")){
                continue;
            }
            getline(DBMemberset::Database1, name);
            getline(DBMemberset::Database1, nomor);
            cout << "======================================" << endl;
            cout << "[" << index++ << "]. " << endl;
            cout << "ID Number                  : " << NoID << endl;
            cout << "Name                       : " << name << endl;
            cout << "Telephone Number           : " << nomor << endl;
        }
        DBMemberset::Database1.close();
    }

    void editDataMember(memberset data){
        string name, nomor, line, NoID, temp;
        ofstream tempFile;
        DBMemberset::Database1.open(DBMemberset::nameOfile);
        tempFile.open("Temp.txt", ios::app);

        cout << " \n\n      Editing Member Data" << endl;
        cout << "======================================" << endl;
        cout << "Enter your ID                  : ";
        cin >> NoID;

        while(!DBMemberset::Database1.eof()){
            getline(DBMemberset::Database1, line);

            if(line == NoID){
                tempFile << line << endl;
                getline(DBMemberset::Database1, line);
                cout << "Old Name               : " << line << endl;
                cout << "New Name               : ";
                cin.ignore(1,'\n');
                getline(cin, name);
                if (name == "-"){
                    tempFile << line << endl;
                    goto change1;
                }
                line.replace(0, line.length(), name);
                tempFile << line << endl;

                change1:
                getline(DBMemberset::Database1, line);
                cout << "Old Telephone Number   : " << line << endl;
                temp = line;
                cout << "New Telephone Number   : ";
                getline(cin, nomor);
                if (nomor == "-"){
                    goto next_step;
                }
                line.replace(0, line.length(), nomor);
            }

            next_step:
            tempFile << line << endl;
        }

        tempFile.close();
        DBMemberset::Database1.close();

        remove("memberDatabase.txt");
        rename("Temp.txt", "memberDatabase.txt");
    }

    void deleteDataMember(memberset data){
        string NoID, line, is_continue, temp;
        ofstream tempFile;
        DBMemberset::Database1.open(DBMemberset::nameOfile);
        tempFile.open("Temp.txt", ios::app);

        cout << "\n\n      Delete Data Member" << endl;
        cout << "======================================" << endl;
        cout << "Insert your ID : ";
        cin >> NoID;

        while(!DBMemberset::Database1.eof()){
            getline(DBMemberset::Database1, line);
            temp = line;
            
            if(line == NoID){
                getline(DBMemberset::Database1, line);

                cout << "Delete Member [" << line << "](Yes/No)?: ";
                cin.ignore(1,'\n');
                getline(cin, is_continue);
                if((is_continue == "Yes")|(is_continue == "yes")){
                    getline(DBMemberset::Database1, line);
                    getline(DBMemberset::Database1, line);
                    getline(DBMemberset::Database1, line);
                    cout << "[  Member Deleted  ]" << endl;
                    goto continue1;
                }else if((is_continue == "No")|(is_continue == "no")){
                    tempFile << temp << endl;
                    goto continue1;
                }else{
                    cout << "Command Canceled" << endl;
                    tempFile << temp << endl;
                    goto continue1;
                }
            }

            continue1:
            tempFile << line << endl;
        }

        tempFile.close();
        DBMemberset::Database1.close();

        remove("memberDatabase.txt");
        rename("Temp.txt", "memberDatabase.txt");


    }
};

int getOption();
void get_DataMember();
void get_DisplayDataMember();
void get_editDataMember();
void get_deleteDataMember();
string getNoID(string nomor);


void skema_member(){

    int option = getOption();
    string is_continue;
    enum Option{ADD = 1, DISPLAY, EDIT, DELETE, BACK};

    while(option != BACK){

        switch(option){
            case ADD:
                get_DataMember();
                break;
            case DISPLAY:
                get_DisplayDataMember();
                break;
            case EDIT:
                get_editDataMember();
                break;
            case DELETE:
                get_deleteDataMember();
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
            option = getOption();
        } else if((is_continue == "No")|(is_continue == "no")){
            break;
        } else{
            cout << "Invalid Input: Program can't be run"<< endl;
            goto continue1;
        }
    }
}

string getNoID(string nomor){

	string NoID = "";
	for (short i = 0; i < 4; i++){
		NoID = NoID + nomor[rand()%12];
	}

    return NoID;
}

//pengambilan opsi
int getOption(){
    int input;

    system("cls");
    cout << "                Member" << endl;
    cout << "======================================" << endl;
    cout << "1. Add new Member" << endl;
    cout << "2. Display Data Member" << endl;
    cout << "3. Change Data Member" << endl;
    cout << "4. Delete Data Member" << endl;
    cout << "5. Main Menu" << endl;
    cout << "======================================" << endl;
    cout << "Submit your selection : ";
    cin >> input;
    cin.ignore(1,'\n');

    return input;
}

void get_DataMember(){
    string name, telephone_number, NoID;
    system("cls");

    cout << "             Add New Member" << endl;
    cout << "======================================" << endl;

    cout << "Insert your name           : ";
    getline(cin, name);
    cout << "Insert telephone number    : ";
    getline(cin, telephone_number);
    NoID = getNoID(telephone_number);

    DBMemberset database = ("memberDatabase.txt");
    memberset dataMember = memberset(name, telephone_number, NoID);
    database.addDataMember(dataMember);
}

void get_DisplayDataMember(){
    string name, telephone_number, NoID;
    system("cls");
    cout << "           Member" << endl;
    memberset dataMember = memberset(name, telephone_number, NoID);
    DBMemberset database = ("memberDatabase.txt");
    database.displayDataMember(dataMember);
}

void get_editDataMember(){
    string name, telephone_number, NoID;
    get_DisplayDataMember();

    memberset dataMember = memberset(name, telephone_number, NoID);
    DBMemberset database = ("memberDatabase.txt");
    database.editDataMember(dataMember);
}

void get_deleteDataMember(){
    string name, telephone_number, NoID;
    get_DisplayDataMember();

    memberset dataMember = memberset(name, telephone_number, NoID);
    DBMemberset database = ("memberDatabase.txt");
    database.deleteDataMember(dataMember);
}