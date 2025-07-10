#include <iostream>
#include <string>
#include<fstream>
#include<cctype>
#include<vector>
#include<sstream>
#include<algorithm>
using namespace std;
//class to store and manage patient details
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
    }
    while(!isValidName(name));
    //age input
    do{
        cout<<"Enter patient age(0-120) :";
        cin>>age;
        if(cin.fail()|| age<0||age>120){
            cout<<"\nInvalid age!\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    }
    while(age<0||age>120||cin.fail());
     //phone number input
    do{
        cout<<"Enter 10-digit phone number: ";
        getline(cin>>ws,phoneNumber);
    }
    while(!isValidPhoneNumber(phoneNumber));
    //illness input
    do{
        cout<<"Enter patient illness :";
        getline(cin>>ws,illness);
        if(!isValidName(illness)){
            cout<<"\nInvalid illness!\n";
        }
    }
    while(!isValidName(illness));
    //doctor name input
    do{
        cout<<"Enter doctor name :";
        getline(cin>>ws,doctor);
        if(!isValidName(doctor)){
            cout<<"\nInvalid doctor name!"<<endl;

        }
    }
    while(!isValidName(doctor));
    //input visitDate
    do{
        cout<<"Enter visit date :";
        getline(cin>>ws,visitDate);
        if(!isValidDate(visitDate)){
            cout<<"\nInvalid visitdate!\n";

        }
    }
    while(!isValidDate(visitDate));
}
//function to check validation name input      
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
//function to check validation date input      
bool patient ::isValidDate(const string &date){
    int year,month,day;
    char dash1,dash2;
    stringstream ss(date);
    ss>>year>>dash1>>month>>dash2>>day;
    if(dash1!='-'|| dash2!='-'||month<1||month>12||day<1||day>31){
        return false;
    }
    return true;

    // //if(date.length()!=10||date[4]!='-'||date[7]!='-'){
    //     return false;
    // }for(int i=0;i<date.size();++i){
    //     if(i==4||i==7){
    //         continue;
    //     }
    //     if((!isdigit(date[i]))){
    //         return false;
    //     }
    // }
    // return true;//
    
}
//function to check validation phone number input      
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
//display all patient details
void patient::display() const{
    cout<<"\n--patient details--\n";
    cout<<" Name:  "<<name<<endl;
    cout<<" Age: "<<age<<endl;
    cout<<" phone number: "<<phoneNumber<<endl;
    cout<<" Illness: "<<illness<<endl;
    cout<<" Doctor: "<<doctor<<endl;
    cout<<"Visit Date: "<<visitDate<<endl;

}
//save patient details to file(write in file)
void savePatient(const patient &p){
    ofstream file("clinicManage.txt",ios::app);
    if(file.is_open()){
        file<<p.name<<","<<p.age<<","<<p.phoneNumber<<","<<p.doctor<<","<<p.illness<<","<<p.visitDate<<"\n";
    }
    else{
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
//overwrite file with updated data
void saveAllPatientsToFile(const vector<patient>& patients) {
    ofstream file("clinicManage.txt");
    for (const auto& p : patients) {
        file << p.name << "," << p.age << "," <<p.phoneNumber<<","<< p.doctor << "," << p.illness << "," << p.visitDate << "\n";
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
    } 
    else {
        cout << "Patient not found.\n";
    }
}

// Delete patient record by name
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
    } 
    else {
        cout << " Patient not found.\n";
    }
}
// Search patient record by name,doctor,illness
void searchPatients() {
    vector<patient> patients = readPatientsFromFile();
    if (patients.empty()) {
        cout << "No patient records found.\n";
        return;
    }
    cout << "\nSearch by:\n";
    cout << "1. Name\n2. Doctor Name\n3. Illness\nEnter choice: ";
    string choice;
    getline(cin, choice);

    string keyword;
    cout << "Enter search keyword: ";
    getline(cin, keyword);

    bool found = false;
    for (const auto& p : patients) {
        if ((choice == "1" && p.name == keyword) ||
            (choice == "2" && p.doctor == keyword) ||
            (choice == "3" && p.illness == keyword)) {
            p.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No  patient found.\n";
    }
}
//sort patient record by name or age
void sortPatients() {
    vector<patient> patients = readPatientsFromFile();
    if (patients.empty()) {
        cout << "No patient records to sort.\n";
        return;
    }

    cout << "\nSort by:\n1. Name\n2. Age\nEnter choice: ";
    string choice;
    getline(cin, choice);

    if (choice == "1") {
        sort(patients.begin(), patients.end(), [](const patient &a, const patient &b) {
            return a.name < b.name;
        });
    } 
    else if (choice == "2") {
        sort(patients.begin(), patients.end(), [](const patient &a, const patient &b) {
            return a.age < b.age;
        });
    } 
    else {
        cout << "Invalid choice.\n";
        return;
    }

    for (const auto& p : patients) {
        p.display();
    }
}
//show visit summary
void todayVisitSummary() {
    vector<patient> patients = readPatientsFromFile();
    if (patients.empty()) {
        cout << "No patient records found.\n";
        return;
    }
    string todayDate;
    cout << "Enter today's date (YYYY-MM-DD): ";
    getline(cin, todayDate);

    bool found = false;
    cout << "\n-- Today's Visit Summary --\n";
    for (const auto& p : patients) {
        if (p.visitDate == todayDate) {
            p.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No data found for today.\n";
    }
}
//main menu for clinic patient management
int main() {
    while (true) {
        cout << "\n===== Clinic Patient Management Menu =====\n";
        cout << "1. Add Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Update Patient\n";
        cout << "4. Delete Patient\n";
        cout << "5. Search Patient\n";
        cout << "6. Sort Patients\n";
        cout << "7. Today's Visit Summary\n";
        cout << "8. Exit\n";
        cout << "Choose an option (1-8): ";

        int option;
        cin >> option;
        cin.ignore();  // clear newline after int input

        switch (option) {
            case 1: {
                patient p;
                p.input();
                savePatient(p);
                cout << "Patient added successfully.\n";
                break;
            }
            case 2:
                viewPatients();
                break;
            case 3:
                updatePatient();
                break;
            case 4:
                deletePatient();
                break;
            case 5:
                searchPatients();
                break;
            case 6:
                sortPatients();
                break;
            case 7:
                todayVisitSummary();
                break;
            case 8:
                cout << "Exiting program.!\n";
                return 0;
            default:
                cout << "Invalid option.\n";
        }
    }

    return 0;
}

