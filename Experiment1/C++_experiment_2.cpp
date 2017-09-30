#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

class Student_info
{
public:
    /*default constructor*/
    Student_info();

    /*destructor*/
    ~Student_info();

    /*method to get the dynamic string's pointer*/
    char * get_name() const;

    /*method to access student number*/
    long get_stuID() const;

    /*formatted output for object*/
    void display() const;

    /*overload extract operator*/
    friend istream& operator >> (istream& ins, Student_info& right_side);

    /*overload insertion operator*/
    friend ostream& operator << (ostream& outs, const Student_info& right_side);

private:
    char *name, *major;
    long stuID;
    int class_num;
    int max_size; // the max size for dynamic string
};

/*auxiliary function*/
void new_line();

int main(void)
{
    Student_info students[30]; // declare a class array which contains 30 elements
    char name[20];
    long ID;
    bool isfound;
    int index;
    char ch = 'a'; // declare a char and initialize it

    ifstream ins;

    ins.open("stulist.txt");
    if(ins.fail())
    {
        cout<<"Error when open student list file!\n";
        exit(1);
    }

    /* read the list and store students' information in class array*/
    for(int i = 0; i < 30; i++)
    {
        ins >> students[i];
    }

    /*debug: check if read operation is done properly*/
    // for(int i = 0; i < 30; i++)
    // {
    //     cout << students[i] << endl;
    // }

    /*serach the student in name list*/
    cout << "Enter student's name and student number:\n";
    while( ch != '\n')
    {
        isfound = false;
        cin >> name >> ID;

        printf("name now is : %s\n",name); //debug
        printf("stuID now is : %ld\n",ID);

        new_line(); // discard extra characters
        for(int i = 0 ; i < 30; i++)
        {
            if(!strcmp(name, students[i].get_name()) && (ID == students[i].get_stuID())) // strcmp() return zero if name is the same as get_name()
            {
                isfound = true;
                index = i;
                break;
            }
        }

        if(isfound)
        {
            cout << "Student found in name list, Here is the information.\n";
            students[index].display();
            cout << "Press Enter to quit or new name and ID to continue.\n";
        }

        else
        {
            cout << "Student not found in name list, press Enter to quit or new name and ID to continue.\n";
        }

        cin.get(ch);
        cin.putback(ch); // Put back the char got into stream
    }

    cout << "Byebye!" <<endl;
    ins.close();

    getchar();
    return 0;
}

Student_info::Student_info(): stuID(0),class_num(0),max_size(30)
{
    name = new char[max_size];
    name[0] = '\0';
    major = new char[max_size];
    major[0] = '\0';
}

Student_info::~Student_info()
{
    delete [] name;
    delete [] major;
}

char * Student_info::get_name() const
{
    return name;
}

long Student_info::get_stuID() const
{
    return stuID;
}

void Student_info::display() const
{
    char temp1[max_size],temp2[max_size];
    strcpy(temp1,name);
    strcpy(temp2,major);
    cout << "------------------------------\n";
    cout << "Name : " << temp1 <<endl;
    cout << "stuID :" << stuID << endl;
    cout << "Major : " << temp2 << endl;
    cout << "Class : " << class_num << endl;
    cout << "------------------------------\n";
}

istream& operator >> (istream& ins, Student_info& right_side)
{
    char temp[right_side.max_size];
    ins >> temp ; 
    strcpy(right_side.name,temp); 
    ins >>  right_side.stuID;
    ins >> temp ; 
    strcpy(right_side.major,temp);
    ins >> right_side.class_num;
    return ins;
}

ostream& operator << (ostream& outs, const Student_info& right_side)
{
    char temp1[right_side.max_size],temp2[right_side.max_size];
    strcpy(temp1,right_side.name);
    strcpy(temp2,right_side.major);
    outs << temp1 << " " << right_side.stuID << " " << temp2 << " " << right_side.class_num;
    return outs;
}

void new_line()
{
    char symbol;
    do {
        cin.get(symbol);
    } while(symbol != '\n');
}