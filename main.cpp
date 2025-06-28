#include <iostream>
#include <string>
#include<fstream>
#include<cctype>
#include<vector>
#include<sstream>
#include<algorithm>
using namespace std;
class patient {
public:   
//members 
    string name;
    int age;
    string  phoneNumber;
    string doctor;
    string illness;   
    string visitDate;
//functions
    void input();
    void display()const;
    bool isValidName(const string &str);
    bool isValidDate(const string &date);
    bool isValidPhoneNumber(const string &number);
    
};
void patient::input(){
//name input
    do{
        cout<<"Enter patient name :";
        getline(cin>>ws,name);
        if(!isValidName(name)){
            cout<<"\nInvalid name!\n";

        }
        
    }while(!isValidName(name));
    //age input
    do{
        cout<<"Enter patient age(0-120) :";
        cin>>age;
        if(cin.fail()|| age<0||age>120){
            cout<<"\nInvalid age!\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    }while(age<0||age>120||cin.fail());
     //phone number input
    do{
        cout<<"Enter 10-digit phone number: ";
        getline(cin>>ws,phoneNumber);
    }while(!isValidPhoneNumber(phoneNumber));
    //illness inout
    do{
        cout<<"Enter patient illness :";
        getline(cin>>ws,illness);
        if(!isValidName(illness)){
            cout<<"\nInvalid illness!\n";
        }
    }while(!isValidName(illness));
    //doctor name
    do{
        cout<<"Enter doctor name :";
        getline(cin>>ws,doctor);
        if(!isValidName(doctor)){
            cout<<"\nInvalid doctor name!"<<endl;

        }
    }while(!isValidName(doctor));
    //input visitDate
    do{
        cout<<"Enter visit date :";
        getline(cin>>ws,visitDate);
        if(!isValidDate(visitDate)){
            cout<<"\nInvalid visitdate!\n";

        }
    }while(!isValidDate(visitDate));
}
       
bool patient::isValidName(const string &str){
    if(str.empty()){
        return false;
    }
    for(char ch:str){
        if(!isalpha(ch)&&ch!=' '){
            return false;
        }
    }
    return true;
}
bool patient ::isValidDate(const string &date){
    if(date.length()!=10||date[4]!='-'||date[7]!='-'){
        return false;
    }for(int i=0;i<date.size();++i){
        if(i==4||i==7){
            continue;
        }
        if((!isdigit(date[i]))){
            return false;
        }
    }
    return true;
    
}
bool patient:: isValidPhoneNumber(const string &number){
    if(number.length()!=10){
        cout<<"\nphone number must be 10 - digit\n";
        return false;
    }
    else if(number[0]=='0'){
        cout<<"\nphone number can not start with 0 \n";
        return false;
    }
    for(char c:number){
        if(!isdigit(c)){
        cout<<"phone number contains only digit.\n";
        return false;
        }
    }
    return true;
}
void patient::display() const{
    cout<<"\n--patient details--\n";
    cout<<" Name:  "<<name<<endl;
    cout<<" Age: "<<age<<endl;
    cout<<" phone number: "<<phoneNumber<<endl;
    cout<<" Illness: "<<doctor<<endl;
    cout<<" Doctor: "<<illness<<endl;
    cout<<"Visit Date: "<<visitDate<<endl;

}
//save patient details to file(write in file)
void savePatient(const patient &p){
    ofstream file("clinicManage.txt",ios::app);
    if(file.is_open()){
        file<<p.name<<","<<p.age<<","<<p.phoneNumber<<","<<p.doctor<<","<<p.illness<<","<<p.visitDate<<"\n";
    }else{
        cout<<"Error ! could not open file.\n";
    }
}
//read from file
vector<patient>
readPatientsFromFile() {
    vector<patient> patients;
    ifstream file("clinicManage.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        patient p;
        string ageStr;
        
        if(getline(ss, p.name, ',') &&
            getline(ss,ageStr,',')&&
            getline(ss,p.phoneNumber,',')&&
            getline(ss, p.doctor, ',') &&
            getline(ss,p.illness,',') &&
            getline( ss,p.visitDate,',')){
            try {
                p.age = stoi(ageStr);
            
                patients.push_back(p);
            } catch (...) {
                cout << "Warning: Corrupted line skipped.\n";
            }
        }
    }
    return patients;
}
//writeToFile(after update delete)


void saveAllPatientsToFile(const vector<patient>& patients) {
    ofstream file("clinicManage.txt");
    for (const auto& p : patients) {
        file << p.name << "," << p.age << "," << p.doctor << "," << p.illness << "," << p.visitDate << "\n";
    }
    file.close();
}

// View all patients
void viewPatients() {
    vector<patient> patients = readPatientsFromFile();
    if (patients.empty()) {
        cout << "No patient records found.\n";
        return;
    }
    cout << "\n Patient List:\n";
    for (const auto & p : patients) {
        p.display();
    }
}

// Update patient by name
void updatePatient() {
    vector<patient> patients = readPatientsFromFile();
    string updateName;
    cout << "Enter name of patient to update: ";
    getline(cin, updateName);

    bool found = false;
    for (auto& p : patients) {
        if (p.name == updateName) {
            cout << "Patient found. Enter new details:\n";
            p.input();
            found = true;
            break;
        }
    }

    if (found) {
        saveAllPatientsToFile(patients);
        cout << " Patient updated successfully.\n";
    } else {
        cout << "Patient not found.\n";
    }
}

// Delete patient by name
void deletePatient() {
    vector<patient> patients = readPatientsFromFile();
    string updateName;
    cout << "Enter name of patient to delete: ";
    getline(cin, updateName);

    int originalSize = patients.size();
    patients.erase(remove_if(patients.begin(), patients.end(),
        [&](patient& p) { return p.name == updateName; }), patients.end());

    if (patients.size() < originalSize) {
        saveAllPatientsToFile(patients);
        cout << " Patient deleted successfully.\n";
    } else {
        cout << " Patient not found.\n";
    }
}

int main() {
    while (true) {
        cout << "\n===== Clinic Patient Management =====\n";
        cout << "1. Add Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Update Patient\n";
        cout << "4. Delete Patient\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            patient p;
            p.input();
            savePatient(p);
            cout << "Patient added successfully.\n";
        } else if (choice == "2") {
            viewPatients();
        } else if (choice == "3") {
            updatePatient();
        } else if (choice == "4") {
            deletePatient();
        } else if (choice == "5") {
            cout << " Exiting program. !\n";
            break;
        } else {
            cout << "Invalid choice!. \n";
        }
    }
    return 0;
}

