#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Rental{
    public:
    string name;
    string NoID;
    string PSseries;
    string rentdate;
    string returndate;

    Rental(string inputname, string inputNoID,
    string inputPSseries, string inputrentdate, string inputreturndate){
        Rental::name = inputname;
        Rental::NoID = inputNoID;
        Rental::PSseries = inputPSseries;
        Rental::rentdate = inputrentdate;
        Rental::returndate = inputreturndate;
    }

    string getString_name(){
        return Rental::name;
    }

    string getString_NoID(){
        return Rental::NoID;
    }

    string getString_PSseries(){
        return Rental::PSseries;
    }

    string getString_rentdate(){
        return Rental::rentdate;
    }

    string getString_returndate(){
        return Rental::returndate;
    }

};

class DBRental{
    public:
    ifstream rent_in;
    ofstream return_in;
    string nameOfile;

    DBRental(const char* nameOfile){
        DBRental::nameOfile = nameOfile;
    }
    
    void addRental(Rental rentData){
        DBRental::return_in.open(DBRental::nameOfile, ios::app);
        DBRental::return_in << rentData.getString_NoID() << endl;
        DBRental::return_in << rentData.getString_name() << endl;
        DBRental::return_in << rentData.getString_PSseries() << endl;
        DBRental::return_in << rentData.getString_rentdate() << endl;
        DBRental::return_in << rentData.getString_returndate() << endl << endl;
        DBRental::return_in.close();
    }
    
    void displayRental(Rental rentData){
        string NoID, name, PSseries, daterent, datereturn;
        unsigned short index = 1;

        DBRental::rent_in.open(DBRental::nameOfile, ios::in);

        while(!DBRental::rent_in.eof()){
            getline(DBRental::rent_in, NoID);
            if((NoID == "")){
                continue;
            }
            getline(DBRental::rent_in, name);
            getline(DBRental::rent_in, PSseries);
            getline(DBRental::rent_in, daterent);
            getline(DBRental::rent_in, datereturn);
            cout << "======================================" << endl;
            cout << "(" << index++ << "). " << endl;
            cout << "ID Number              : " << NoID << endl;
            cout << "Name                   : " << name << endl;
            cout << "PS Series (3,4,and 5)  : " << PSseries << endl;
            cout << "Rent Date              : " << daterent << endl;
            cout << "Return Date            : " << datereturn << endl;
        }
        DBRental::rent_in.close();
    }

    void pengembalian(Rental rentData){
        string NoID, line, temp;
        ofstream tempFile;
        DBRental::rent_in.open(DBRental::nameOfile);
        tempFile.open("TempPinjam.txt", ios::app);

        cout << "\n\n Returning Playstation" << endl;
        cout << "======================================" << endl;
        cout << "Insert your ID     : ";
        cin >> NoID;

        while(!DBRental::rent_in.eof()){
            getline(DBRental::rent_in, line);

            if(line == NoID){
                getline(DBRental::rent_in, line);
                getline(DBRental::rent_in, line);
                getline(DBRental::rent_in, line);
                getline(DBRental::rent_in, line);
                getline(DBRental::rent_in, line);
                getline(DBRental::rent_in, line);
            }

            tempFile << line << endl;
        }

        tempFile.close();
        DBRental::rent_in.close();

        remove("rentDatabase.txt");
        rename("TempPinjam.txt", "rentDatabase.txt");
    }
};

void get_displayRental(){
    string name, NoID, PSseries, daterent, datereturn;
    system("cls");
    cout << "           Rental Data" << endl;
    Rental rentData = Rental(name, NoID, PSseries, daterent, datereturn);
    DBRental RDatabase = ("rentDatabase.txt");
    RDatabase.displayRental(rentData);
}
void get_pengembalian(){
    string name, NoID, PSseries, daterent, datereturn;
    get_displayRental();

    Rental rentData = Rental(name, NoID, PSseries, daterent, datereturn);
    DBRental RDatabase = ("rentDatabase.txt");
    RDatabase.pengembalian(rentData);
}
void get_addRental(){
    string name, NoID, PSseries, daterent, datereturn;
    system("cls");

    cout << "          File a Rent" << endl;
    cout << "======================================" << endl;
    cout << "Insert your name       : ";
    getline(cin, name);
    cout << "Insert your ID         : ";
    getline(cin, NoID);
    cout << "PS Series (3,4,and 5)  : ";
    getline(cin, PSseries);
    cout << "Rent Date (d-m-y)      : ";
    getline(cin, daterent);
    cout << "Return Date (d-m-y)    : ";
    getline(cin, datereturn);

    DBRental RDatabase = ("rentDatabase.txt");
    Rental rentData = Rental(name, NoID, PSseries, daterent, datereturn);
    RDatabase.addRental(rentData);
}                                          
