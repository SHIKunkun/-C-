#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define NUM_JUDGES 7
using namespace std;

class Singer
{
public:
    /*default constructor with no parameter*/
    Singer();

    /*Copy constructor*/
    Singer(const Singer& singer_object);

    /*get the final grade of a singer*/
    double get_average();

    /*display an object of class Singer*/
    void display();

    /*overloading assignment operator = */
    void operator = (Singer& right_side);
        
    /*friend function to overload << and >> operator*/
    friend istream& operator >> (istream& ins, Singer& right_side);
    friend ostream& operator << (ostream& outs, const Singer& right_side);

private:
    char name[20];
    double scores[NUM_JUDGES];
};

/* sort function for simple double type array and class array*/
void sort(double * array, int size);
void sort(Singer * array, int size);

int main(void)
{
    Singer singers[30];
    ifstream ins;
    
    ins.open("singerslist.txt");
    if(ins.fail())
    {
        cout<<"Error when open singers list file!\n";
        exit(1);
    }

    /*Initialization section*/
    for(int i = 0; i < 30; i++)
    {
        ins >> singers[i];
    }

    ins.close();

    sort(singers, 30);

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Here is the ranking table for 30 singers:\n " << endl;
    for(int i = 0; i <30; i++)
        singers[i].display();

    getchar();
    return 0;
}

Singer::Singer()
{
    /* initialize private member variable */
    name[0] = '\0';
    for(int i = 0; i < NUM_JUDGES; i++)
        scores[i] = 0;
}

Singer::Singer(const Singer& singer_object)
{
    strcpy(name, singer_object.name);
    for(int i = 0; i < NUM_JUDGES; i++)
        scores[i] = singer_object.scores[i];

}

double Singer::get_average()
{
    double sum = 0;
    double result;
    sort(scores,NUM_JUDGES);
    for(int i = 1; i < (NUM_JUDGES - 1); i++)
        sum += scores[i];
    result = sum / (NUM_JUDGES - 2);

    return result;
}

istream& operator >> (istream& ins, Singer& right_side)
{
    ins >> right_side.name;
    for(int i = 0; i < NUM_JUDGES; i++)
        ins >> right_side.scores[i];

    return ins;
}

ostream& operator << (ostream& outs, const Singer& right_side)
{
    outs << right_side.name;
    for(int i = 0; i < NUM_JUDGES; i++)
        outs << right_side.scores[i];

    return outs;
}

void Singer::display()
{
    cout << "---****---" << endl;
    cout << "Name：" << name << endl;
    cout << "Final score:" << get_average() << endl;
    cout << "Details: ";
    for(int i = 0 ; i < NUM_JUDGES; i++) // debug
        printf("%-8.2lf",scores[i]);
    cout << "\n---****---"<< endl;
    printf("\n");
}

void Singer::operator = (Singer& right_side)
{
    double * pt = right_side.scores;
    strcpy(name,right_side.name);
    for(int i = 0; i < NUM_JUDGES; i++)
    {
        scores[i] = pt[i];
    }

}

void sort(double * array, int size)
{
    double temp;
    for(int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if(array[j] > array[i])
            {
                temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
    }
}

void sort(Singer * singers, int size)
{
    Singer temp;
    for(int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if(singers[j].get_average() > singers[i].get_average())
            {
                temp = singers[j];
                singers[j] = singers[i];
                singers[i] = temp;
            }
        }
    }
}