#include<iostream>
#include<fstream>
#include<string>
#include "proto/addressbook.pb.h"

using namespace std;

void CreatePerson(tutorial::Person* person)
{
    cout << "Enter person id: ";
    int id;
    cin >> id;
    person->set_id(id);

    cout << "Enter name: ";
    cin >> *person->mutable_name();
    
    cout << "Enter email: ";
    string email;
    getline(cin, email);
    person->set_email(email);

    while (true)
    {
        cout << "Enter a phone number: ";
        string number;
        getline(cin, number);
        if (number.empty())
        {
            break;
        }
        tutorial::Person::PhoneNumber* phone_number = person->add_phones();
        phone_number->set_number(number);
        
        cout << "Is this a mobile, home, or work phone?";
        string type;
        getline(cin, type);
        if (type == "mobile")
        {
            phone_number->set_type(tutorial::Person::MOBILE);
        }
        else if (type == "home")
        {
            phone_number->set_type(tutorial::Person::HOME);
        }
        else if (type == "work")
        {
            phone_number->set_type(tutorial::Person::WORK);
        }
    }   
}

void ListPeople(const tutorial::AddressBook& addr_book)
{
    for (int i = 0; i < addr_book.people_size(); i++)
    {
        const tutorial::Person& person = addr_book.people(i);
        cout << "Id: " << person.id() << endl;
        cout << "Name: " << person.name() << endl;
        if (person.has_email()) {
           cout << "E-mail address: " << person.email() << endl;
        }
        for (int j = 0; j < person.phones_size(); j++) {
            const tutorial::Person::PhoneNumber& phone_number = person.phones(j);

            switch (phone_number.type()) {
                case tutorial::Person::MOBILE:
                    cout << "Mobile phone #: ";
                    break;
                case tutorial::Person::HOME:
                    cout << "Home phone #: ";
                    break;
                case tutorial::Person::WORK:
                    cout << "Work phone #: ";
                    break;
            }
            cout << phone_number.number() << endl;
        }
    }
}

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    string filename = "../address.txt";
    tutorial::AddressBook addr_book;
    {
        fstream input(filename, ios::in | ios::binary);
        if (!input)
        {
            cout << "fstream error!";
            return 0;
        }
        else if (!addr_book.ParseFromIstream(&input))
        {
            cout << "parse error!";
            return 0;
        }
    }
    ListPeople(addr_book);
    CreatePerson(addr_book.add_people());

    {
        fstream output(filename, ios::out | ios::binary | ios::trunc);
        if (!addr_book.SerializeToOstream(&output))
        {
            cout << "serialize error!";
            return 0;
        }
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}