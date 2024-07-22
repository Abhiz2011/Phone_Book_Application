#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <algorithm>

using namespace std;

class Person {
public:
    string name;
    string address;
    string father_name;
    string mother_name;
    string sex;
    string email;
    string citizen_no;
    long int mobile_no;

    void getData();
    void display() const;

    void serialize(ofstream &out) const;
    void deserialize(ifstream &in);
};

void menu();
void start();
void back();
void addRecord();
void listRecord();
void modifyRecord();
void deleteRecord();
void searchRecord();
void got(string &);

vector<Person> readFromFile();
void writeToFile(const vector<Person> &);

int main() {
    system("color 5f");
    start();
    return 0;
}

void back() {
    start();
}

void start() {
    menu();
}

void menu() {
    system("cls");
    cout << "\t\t**********WELCOME TO PHONEBOOK*************";
    cout << "\n\n\t\t\t  MENU\t\t\n\n";
    cout << "\t1. Add New   \t2. List   \t3. Exit  \n\t4. Modify \t5. Search\t6. Delete\n";

    switch (_getch()) {
    case '1':
        addRecord();
        break;
    case '2':
        listRecord();
        break;
    case '3':
        exit(0);
        break;
    case '4':
        modifyRecord();
        break;
    case '5':
        searchRecord();
        break;
    case '6':
        deleteRecord();
        break;
    default:
        system("cls");
        cout << "\nEnter 1 to 6 only";
        cout << "\n Enter any key";
        _getch();
        menu();
    }
}

void Person::getData() {
    cout << "\nEnter name: ";
    got(name);
    cout << "Enter the address: ";
    got(address);
    cout << "Enter father name: ";
    got(father_name);
    cout << "Enter mother name: ";
    got(mother_name);
    cout << "Enter phone no.: ";
    cin >> mobile_no;
    cin.ignore();
    cout << "Enter sex: ";
    got(sex);
    cout << "Enter e-mail: ";
    got(email);
    cout << "Enter citizen no: ";
    got(citizen_no);
}

void Person::display() const {
    cout << "\n\n\n YOUR RECORD IS\n\n ";
    cout << "\nName = " << name << "\nAddress = " << address
         << "\nFather name = " << father_name << "\nMother name = " << mother_name
         << "\nMobile no = " << mobile_no << "\nSex = " << sex
         << "\nE-mail = " << email << "\nCitizen no = " << citizen_no << '\n';
}

void Person::serialize(ofstream &out) const {
    size_t size = 0;

    size = name.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(name.c_str(), size);

    size = address.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(address.c_str(), size);

    size = father_name.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(father_name.c_str(), size);

    size = mother_name.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(mother_name.c_str(), size);

    size = sex.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(sex.c_str(), size);

    size = email.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(email.c_str(), size);

    size = citizen_no.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(citizen_no.c_str(), size);

    out.write(reinterpret_cast<const char*>(&mobile_no), sizeof(mobile_no));
}

void Person::deserialize(ifstream &in) {
    size_t size = 0;
    char *buffer = nullptr;

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    name = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    address = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    father_name = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    mother_name = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    sex = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    email = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    citizen_no = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&mobile_no), sizeof(mobile_no));
}

void addRecord() {
    system("cls");
    vector<Person> people = readFromFile();
    Person p;
    p.getData();
    people.push_back(p);
    writeToFile(people);
    cout << "\nRecord saved";
    cout << "\n\nEnter any key";
    _getch();
    system("cls");
    menu();
}

void listRecord() {
    system("cls");
    vector<Person> people = readFromFile();
    for (const auto &p : people) {
        p.display();
        _getch();
        system("cls");
    }
    cout << "\n Enter any key";
    _getch();
    system("cls");
    menu();
}

void searchRecord() {
    system("cls");
    vector<Person> people = readFromFile();
    string name;
    cout << "\nEnter name of person to search\n";
    got(name);
    bool found = false;
    for (const auto &p : people) {
        if (p.name == name) {
            cout << "\n\tDetail Information About " << name;
            p.display();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "File not found";
    }
    cout << "\n Enter any key";
    _getch();
    system("cls");
    menu();
}

void deleteRecord() {
    system("cls");
    vector<Person> people = readFromFile();
    string name;
    cout << "Enter CONTACT'S NAME: ";
    got(name);
    auto it = remove_if(people.begin(), people.end(), [&](const Person &p) {
        return p.name == name;
    });
    if (it != people.end()) {
        people.erase(it, people.end());
        writeToFile(people);
        cout << "RECORD DELETED SUCCESSFULLY.";
    } else {
        cout << "NO CONTACT'S RECORD TO DELETE.";
    }
    cout << "\n Enter any key";
    _getch();
    system("cls");
    menu();
}

void modifyRecord() {
    system("cls");
    vector<Person> people = readFromFile();
    string name;
    cout << "\nEnter CONTACT'S NAME TO MODIFY:\n";
    got(name);
    bool found = false;
    for (auto &p : people) {
        if (p.name == name) {
            cout << "\nEnter new details:\n";
            p.getData();
            found = true;
            break;
        }
    }
    if (found) {
        writeToFile(people);
        cout << "\nYour data is modified";
    } else {
        cout << "\nData not found";
    }
    cout << "\n Enter any key";
    _getch();
    system("cls");
    menu();
}

void got(string &str) {
    char c;
    str.clear();
    while ((c = _getch()) != 13) { // 13 is Enter key
        if (c == 8) { // 8 is Backspace key
            if (!str.empty()) {
                str.pop_back();
                cout << "\b \b";
            }
        } else {
            str.push_back(c);
            cout << c;
        }
    }
}

vector<Person> readFromFile() {
    ifstream file("project", ios::binary);
    vector<Person> people;
    if (file.is_open()) {
        while (file.peek() != EOF) {
            Person p;
            p.deserialize(file);
            people.push_back(p);
        }
        file.close();
    }
    return people;
}

void writeToFile(const vector<Person> &people) {
    ofstream file("project", ios::binary | ios::trunc);
    for (const auto &p : people) {
        p.serialize(file);
    }
    file.close();
}
