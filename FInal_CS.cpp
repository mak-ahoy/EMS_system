#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string>
#include <fstream>
#include <vector>
//#include<emoji>
using namespace std;
int count = 30;
fstream files, file_temp,file_sal;


int display();

void home(){
    int opt;
    cout<<"\nENTER (1) TO RETURN TO HOME          ENTER (2) TO EXIT PROGRAM\n>>";
    cin>>opt;
    switch (opt)
    {
    case 1:
        system("cls");
        display();
        break;
    
    case 2:
        cout<<"\nBYE BYE!";
        exit(0);
        break;
    default:
        cout<<"\nInvalid Entry\n";
        home();
        break;
    }


}


double card_billing(int amount)
{
    double total;
    total = amount * 1.05;
    return total;
}
double cash_billing(int amount)
{
    double total;
    total = amount * 1.16;
    return total;
}

bool check_id(string id)
{ // checks if id generated exists in db
    files.open("main.txt", ios::in);
    if (files.is_open())
    {
        // cin.ignore(10000,'\n');
        string line;
        while (!files.eof())
        {
            getline(files, line);
            if (line.substr(0, 4) == id)
            {
                files.close();
                return true;
            }
        }
    }
    files.close();
    return false;
}

void get_attend()
{ // gets attendace of user id
    string id, month, year_insearch;

    cout << "Enter User Id: ";
    cin >> id;
    while (!check_id(id))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter Valid User Id: ";
        cin >> id;
    }
    cout << "Enter Month: ";
    cin >> month;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter User Id: ";
        cin >> month;
    }
    cout << "Enter Year: ";
    cin >> year_insearch;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter User Id: ";
        cin >> year_insearch;
    }

    files.open("attendance.txt", ios::in);
    string line;
    int presents = 0;
    // files>>line;
    getline(files, line);
    // int counter=0;
    while (!files.eof())
    { // && !line.length()==0
        //  cout<<++counter<<". "<<line<<"\n";
        if (line.substr(27, 4) == year_insearch && id == line.substr(0, 4) && month == line.substr(11, 3) && line.substr(5, 1) == "P")
        { ///**** MAJOR BUG WHICH GONNA BUG FOREVER.

            // cout<<line;
            //  cout<<line.substr(27,4);
            //   cout <<line.length() << '\n';
            presents++;
        }
        getline(files, line);
    }
    cout << presents;

    files.close();
    // presents;
}

void mark_attend()
{ // marks attendace
    string id, mark;

    cout << "Enter User ID: ";
    cin >> id;

    if (check_id(id) && id.length() == 4)
    {
        cout << "Enter 'P' for present: ";
        cin >> mark;

        time_t now = time(0);
        string date_time = ctime(&now);

        files.open("attendance.txt", ios::app);

        files << id << " " << mark << " " << date_time;
        cout << "Attendance Marked!";
        files.close();
        home();
    }

    else
    {
        cout << "Invalid user id! Retry." << endl;
        mark_attend();
    }
}

string id_gen()
{ // generates 4 digit id
    srand(time(0));
    string u_id = "";
    for (int i = 0; i < 4; i++)
    {
        int random = rand() % (10);
        u_id = u_id + to_string(random);
    }
    return u_id;
}

bool login()
{ // login for security
    string pass, user;
    cout << "Enter user name: " << endl;
    cin >> user;
    cout << "Enter password: " << endl;
    cin >> pass;

    if (pass == "admin" && user == "admin")
    {
        return true;
    }
    else
    {
        return false;
    }
}

int search(string data)
{ // searching index : requires debuggng when trying to integrate
    string element;
    files.open("main.txt", ios::in);
    int index = 1;

    while (!files.eof())
    {
        getline(files, element);

        if (element.substr(0, 4) == data)
        {
            files.close();
            return index;
        }

        index++;
    }
    files.close();
    return 0;
}

void print_attend()
{
    string line;
    string fileA = "attendance.txt";
    cout << "\nUIDs | MARK | DAY | MONTH | TIME \n";
    files.open(fileA, ios::in);
    while (getline(files, line))
    {
        cout << line << endl;
    }
    files.close();

    home();
}

void ems_attend()
{
    // attendance module
}

void salries()
{ // claculates salaries based on year of service
    // saleries
    const double BASE_SALALRY = 200; // dollars will be used in the entirity.
    const double HOUSE_RENT = 200;
    const double MEDICAL_ALLOWANCE = 200;
    const double CAR_ALLOWANCE = 200;
    const double INCREMENT = 0.05;
    // Employment Type
    double final_salary = 0;
    string ID;

    cout << " ENTER EMPLOYEE NO: ";
    cin >> ID;
    while (!check_id(ID) && !cin.fail())
    {
        cout << " INVALID ID! try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> ID;
    }

    // calculating the year differnce.
    string line;
    files.open("main.txt", ios::in);
    while (!files.eof())
    {
        getline(files, line);
        // cout<<line.substr(0,4);
        // cout<<line<<endl;
        if (line.substr(0, 4) == ID)
        {
            // cout<<"   "<<line.substr(line.length()-2,2);
            int joining = stoi(line.substr(line.length() - 2, 2)); // stoi convetion required
            // cout<<"Joining: "<<joining;
            time_t now = time(0);
            string date_time = ctime(&now);
            int current_year = stoi(date_time.substr(date_time.length() - 3, 2)); // stoi()
            // cout<<"CY:"<<current_year;
            int diff = abs(joining - current_year);
            // cout<<"Diff:"<<diff;

            if (diff >= 3)
            {
                final_salary = BASE_SALALRY + HOUSE_RENT + MEDICAL_ALLOWANCE + CAR_ALLOWANCE;
            }
            else if (diff >= 2)
            {
                final_salary = BASE_SALALRY + HOUSE_RENT + MEDICAL_ALLOWANCE;
            }
            else
            { /// get conditions checked
                final_salary = BASE_SALALRY + HOUSE_RENT;
            }
            break;
        }
    }
    cout << "$" << final_salary;
}

string salries(string ID) // method overloading used.
{                         // claculates salaries based on year of service
    // saleries
    const double BASE_SALALRY = 200; // dollars will be used in the entirity.
    const double HOUSE_RENT = 200;
    const double MEDICAL_ALLOWANCE = 200;
    const double CAR_ALLOWANCE = 200;
    const double INCREMENT = 0.05;
    // Employment Type
    double final_salary = 0;
    // string ID;

    // calculating the year differnce.
    string line1;

    files.close();
    files.open("main.txt", ios::in);
    while (getline(files, line1))
    {
        if (line1.substr(0, 4) == ID)
        {
            int joining = stoi(line1.substr(line1.length() - 2, 2)); // stoi convetion required
            // cout<<"Joining: "<<joining;
            time_t now = time(0);
            string date_time = ctime(&now);
            int current_year = stoi(date_time.substr(date_time.length() - 3, 2)); // stoi()
            // cout<<"CY:"<<current_year;
            int diff = abs(joining - current_year);
            // cout<<"Diff:"<<diff;

            if (diff >= 3)
            {
                final_salary = BASE_SALALRY + HOUSE_RENT + MEDICAL_ALLOWANCE + CAR_ALLOWANCE;
            }
            else if (diff >= 2)
            {
                final_salary = BASE_SALALRY + HOUSE_RENT + MEDICAL_ALLOWANCE;
            }
            else
            { /// get conditions checked
                final_salary = BASE_SALALRY + HOUSE_RENT;
            }
            break;
        }
    }
    file_sal.close();

    return "$" + to_string(static_cast<int>(final_salary));
}

void print_salaries()
{

    string line, print_line = "", newstr = "";
    int sterik = 0, j, i;
    // int index=0;
    // cout<<salries("7414");
    files.open("main.txt", ios::in);

    cout << "ID   |   NAME   |   SALARY" << endl;

    while (getline(files, line))
    {
        // cout<<"TEST 1 passed\n";
        int var = 0;
        string id = "";
        string name = "";
        for (i = 0; i < line.length(); i++)
        {
            if (line[i] == '*')
            {
                sterik++;
                if (sterik == 1)
                {
                    id = line.substr(0, i);
                    var = i + 1;
                }
                else if (sterik == 2)
                {
                    name = line.substr(var, i - var);
                    sterik = 0;
                    break;
                }
            }
        }
        // files.close();
        cout << id << "   " << name << "        "<< salries(line.substr(0, 4)) << endl;
        // files.open("main.txt", ios::in);

        //    for (j=0; j<=(line.substr(0,i)).length();j++){
        //            if (line[j]=='*'){
        //                newstr=newstr+"    ";
        //            }
        //            else{
        //                newstr=newstr+line[j];
        //            }
    }
    // print_line=print_line+line.substr(0,4)+" "+line.substr(j, line.length()-(i+1))+" "+salries(line.substr(0,4));
    // string test=line.substr(0,4);
    // cout<<salries("7414");

    //          string payments=salries(line.substr(0,4));

    //         cout<<payments;
    //    cout<<newstr<<"    "<<payments<<endl;
    //     newstr="";
    //  cout<<print_line;

    files.close();
}

void fetch()
{ // does something
    string file;
    files.open("main.txt", ios::in);
    while ( getline(files, file))
    {
        // files>>file;
        cout << file << endl;
    }
    home();
}

void update_main()
{ // DONE!
    string update;
    string element;
    int data;
    string line;
    string name, age, descrip;
    int index = 1;
    vector<string> temp;
    string fileA = "main.txt";

    cout << "Enter data ID to update: ";
    cin >> update;

    int found_index = int(search(update)); // search("5691")// if 0 data dne

    cout << "----- UPDATE -----" << endl;
    cout << "1. Name\n2. Age\n3. Job description\n>> "; // requires reevaluation
    cin >> data;
    // Name age decription
    int flags[] = {0, 0, 0};
    switch (data)
    {
    case 1:
        cout << "ENTER NEW NAME: ";
        cin.clear();
        cin.ignore(10000, '\n');
        getline(cin, name);
        flags[0] = 1;
        break;
    case 2:
        cout << "ENTER NEW AGE: ";
        cin >> age;
        flags[1] = 1;
        break;
    case 3:
        cout << "ENTER NEW DESCRIPTION: ";
        cin >> descrip;
        flags[2] = 1;
        break;
    }

    int x = 1;
    string newstr = "";
    int i, j;
    int sterik = 0;
    files.open(fileA);
    // file_temp.open(fileB, ios::in |ios::out);
    while (getline(files, line))
    {
        // cout << x << endl;
        if (x == found_index)
        {
            if (flags[0] == 1)
            { // change name only
                for (i = 0; i < line.length(); i++)
                {
                    if (line[i] == '*')
                    {
                        sterik++;
                        if (sterik == 2)
                        {
                            break;
                        }
                    }
                }
                newstr = newstr + line.substr(0, 5) + name + line.substr(i, line.length() - (i));
              //  cout << newstr;
            }
            else if (flags[1] == 1)
            { // change age only
                for (i = 0; i < line.length(); i++)
                {
                    if (line[i] == '*')
                    {
                        sterik++;
                        if (sterik == 2)
                        {
                            break;
                        }
                    }
                }
                newstr = newstr + line.substr(0, i + 1) + age + line.substr(i + 3, line.length() - (i) + 3);
                //cout << newstr;
            }
            else
            { // change description only
                for (i = 0; i < line.length(); i++)
                {
                    if (line[i] == '*')
                    {
                        sterik++;
                        if (sterik == 3)
                        {
                            j = i;
                        }
                        if (sterik == 4)
                        {
                            
                            break;
                        }
                    }
                }
                newstr = newstr + line.substr(0, j + 1) + descrip + line.substr(i, line.length() - (i));
                //cout << newstr;
            }
            // cout << "Plz work";
            x++;
            // continue;
            temp.push_back(newstr);
        }
        else
        {
            // cout<<"Test 2";
            temp.push_back(line);
            x++;
        }
    }
    flags[0] = 0;
    flags[1] = 0;
    flags[2] = 0;
    sterik = 0;
    files.close();

    files.open(fileA, ios::out);

    // cout << "SIZE: " << temp.size();
    if (temp.size() == 0)
    {
        cout << "NO> MORE DATA TO UPDATE!";
        home();
       // return; // enter option here to exit the program or to main maenu
    }
    else
    {
        for (int i = 0; i < temp.size(); i++)
        {
            // cout << temp[i] << endl;
            if (i == temp.size() - 1)
            {
                files << temp[i];
            }
            else
            {
                // cout << temp[i];
                files << temp[i] << endl;
            }
        }
        cout << "DATA UPDATED SUCESSFULLY!" << endl;
    }
    files.close();
    // system("cls");
    // update_main();
    home();
}

void delte()
{ // @parms string file_name, string item_to_delete  : deletes a line based upon the customer id. { requuirs testing and is in phase of debugging}

    string element;
    string data;
    string line;
    int index = 1;
    vector<string> temp;
    string fileA = "main.txt";
    cout << "Enter item to delete: ";
    cin >> data;

    int found_index = int(search(data)); // search("5691")
    int x = 1;
    files.open(fileA);

    while (getline(files, line))
    {
        // cout << x << endl;
        if (x == found_index)
        {
            // cout << "Plz work";
            x++;
            continue;
        }
        else
        {
            // cout<<"Test 2";
            temp.push_back(line);
            x++;
        }
    }
    files.close();

    files.open(fileA, ios::out);

    // cout << "SIZE: " << temp.size();
    if (temp.size() == 0)
    {
        cout << "NO> MORE DATA TO DELETE!";
        return; // enter option here to exit the program or to main maenu
    }
    else
    {
        for (int i = 0; i < temp.size(); i++)
        {

            cout << temp[i] << endl;

            if (i == temp.size() - 1)
            {
                files << temp[i];
            }
            else
            {
                // cout << temp[i];
                files << temp[i] << endl;
            }
        }
        cout << "DATA DELETED SUCESSFULLY!" << endl;
    }
    files.close();
    home();
}



void addnew()
{ // adding new staff entry  : validations and testing required for data entered.
    // biodata
    string name, doj, jd;
    int age;
    cout << "Enter full name : ";
    // cin.clear();
    // cin.ignore(10000,'\n');
    getline(cin, name);
    cout << "Enter age : ";
    cin >> age;
    while (!(age > 15 && age < 70) || cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter valid age : ";
        cin >> age;
    }
    string str_age = to_string(age);
    cout << "Enter job description : ";
    cin >> jd;
    cout << "Date of joining (DD/MM/YY):";
    cin >> doj;
    // check for year validation
    while(doj.length()!=8 || stoi(doj.substr(0,2))>31 && stoi(doj.substr(0,2))<0 || stoi(doj.substr(3,2))>12 && stoi(doj.substr(3,2))<0 || (stoi(doj.substr(6,2))>22 && stoi(doj.substr(6,2))<17))
    {
        cout << "Enter right format Date of joining :- (DD/MM/YY):";
        cin >> doj;
    }
    string temp_id = id_gen();
    while (check_id(temp_id))
    { // gernating a u_id for new staffmember , checking if id already exits.
        temp_id = id_gen();
    }

    string line_data;

    line_data = line_data + temp_id + "*" + name + "*" + str_age + "*" + jd + "*" + doj;

    files.open("main.txt", ios::app);
    files << endl
          << line_data;
    cout << "data uploaded!";
    files.close();

    // adding the new created id to record

    files.open("u_ids.txt", ios::app);
    files << temp_id << "\n";
    files.close();
    home();
}



void feedback()
{
    string feed;
    cout << "\n\n";
    cout << "-----------------------------FEEDBACK FORM----------------------------------\n";
    cout << "ENTER FEEDBACK : ";
    cin.clear();
    cin.ignore(10000, '\n'); // clearing the input stream for getline
    getline(cin, feed);
    // cout<<feed;  // testing the feed stream
    files.open("feedback.txt", ios::app); // wrinting the feed back in the file.
    // send feed to local database;
    if (files.is_open())
    {
        files << feed << endl;
        cout << " GOOD BYE ! WE WILL BE WAITING FOR YOU!!";
        files.close();
    }
    else
    {
        cout << "ERROR :( ";
    }

    home();

   // display();
}

int display()
{
    int portal;
    cout << "================================================\n";
    cout << "            Welcome to LUMS cafe\n";
    cout << "================================================\n\n\n";
    cout << "Please enter the number for your desired portal\n\n";
    cout << "|Billing and menu editing| >> (1)\n|Employee management system| >> (2)\n|Feedback form| >> (3)\n\n================================================\n\n";
    cout << "Portal: ";
    cin >> portal;
    cout << "\n================================================" << endl;
    if (portal == 1)
    {
        int j;
        cout << "Enter 1 for billing or 2 for menu editing: ";
        cin >> j;
        while ((j != 1 && j != 2 && j != -1 && j != -2) || cin.fail())
        {
            cout << "Please enter appropriate option! \n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Enter 1 for billing or 2 for menu editing: ";
            cin >> j;
        }
        if (j == -1)
        {
            system("cls");
            display();
        }
        if (j == -2)
        {
            cout << "GOODBYE!";
            return 0;
        }
        if (j == 2)
        {
            int second = 0;
            cout << "Enter 1 for editing price or 2 for deletion: ";
            cin >> second;
            while ((second != 1 && second != 2) || cin.fail())
            {
                cout << "Entered option not avaliable!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Enter 1 for editing price or 2 for deletion: ";
                cin >> second;
            }
            if (second == 1)
            {
            }
        }

        if (j == 1)
        {
            system("cls");
            int line_number = 0;
            int bill = 0;
            string receipt;
            fstream display;
            display.open("display.txt", ios::in);
            if (display.is_open())
            {

                for (int i = 1; i <= count; i++)
                {
                    string menu;
                    getline(display, menu);
                    cout << menu << endl;
                }
                display.close();
                cout << "================================================" << endl
                     << endl;
                ;
            }

            while (true)
            {
                cout << "Enter the code of item to add to bill or 0 to finish billing ";
                cin >> line_number;
                bool c = true;

                while (line_number < 0 || line_number > count || cin.fail())
                {
                    cout << "Invalid entry\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Enter the code of item to add to bill or 0 to finish billing ";
                    cin >> line_number;
                }
                if (line_number == 0)
                {
                    break;
                }
                fstream myfile_1, myfile_2;
                myfile_1.open("prices.txt", ios::in);
                myfile_2.open("menu.txt", ios::in);
                if (myfile_1.is_open() && myfile_2.is_open())
                {
                    string line, item;
                    for (int i = 1; i <= line_number; i++)
                    {
                        getline(myfile_1, line);
                        getline(myfile_2, item);
                    }
                    myfile_1.close();
                    myfile_2.close();
                    receipt += item + "  " + line + "\n";
                    bill += stoi(line);
                }
            }

            int payment;
            double total;
            system("cls");
            cout << "\n\n";
            cout << "Press 1 for card payment and 2 for cash payment: ";
            cin >> payment;
            while (payment < 1 || payment > 2 || cin.fail())
            {
                cout << "Invalid Choice\n";
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Press 1 for card payment and 2 for cash payment: ";
                cin >> payment;
            }

            if (payment == 1)
            {
                total = card_billing(bill);
                cout << "\n\n";
                cout << "=============================\n";
                cout << receipt << endl;
                cout << "Total: " << bill << endl
                     << "Tax 5%: " << 0.05 * bill << endl;
                cout << "Total bill with tax: " << total << endl;
                cout << "=============================\n   'Come Back Again Soon'\n";
                cout << "=============================";
            }
            if (payment == 2)
            {
                total = cash_billing(bill);

                cout << "\n\n";
                cout << "=============================\n";
                cout << receipt << endl;
                cout << "Total: " << bill << endl
                     << "Tax 16%: " << 0.16 * bill << endl;
                cout << "Total bill with tax: " << total << endl;
                cout << "=============================\n   'Come Back Again Soon'\n";
                cout << "=============================";
            }
        }
    }

    if (portal == 2)
    {
        system("cls");
        cout << "\n\n";
        cout << "**********        | LOGIN PAGE |          **********\n";
        if (login() == true)
        {
            int option;
            cout << "1. ADD NEW DATA \n2. ATTENDANCE \n3. DELETE DATA\n4. UPDATE DATA\n";
            cout << "Enter option: ";
            cin >> option;

            switch (option)
            {
            case 1:
                system("cls");
                addnew();
                break;
            case 2:
                system("cls");
                int choice;
                cout << "\n\n";
                cout << "1. MARK ATTENDANCE \n2. GET ATENDANCE\nENTER CHOICE: ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                    mark_attend();
                    break;

                case 2:
                    get_attend();
                    break;
                }

                break;
            case 3:
                delte();
                break;
            case 4:
                update_main();
                break;
            }
        }
        else{
            cout<<"Authentication failed retry!\n";
            display();
        }
    }
    if (portal == 3)
    {
        system("cls");
        feedback();
    }
    
}

int main()
{ //:
    system("cls");
    cout << endl;
    cout << endl;
    display();
    return 0;
}
