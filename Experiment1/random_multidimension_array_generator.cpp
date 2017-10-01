#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define SIZE 10
using namespace std;
void ran_array_generator(double array[], int size);

int main(void)
{
    double array[30][SIZE]; // 30 arrays with each array includes 10 double datas
    srand((unsigned int)time(NULL)); // the random seed only need to be set once before the main assignment loop
    for(int i = 0; i < 30; i++)
    {
        ran_array_generator(array[i],SIZE);
    }
    cout << "Here is the random array you just created ：\n" << endl;
    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < SIZE; j++)
            printf("%-8.2lf",array[i][j]);
        printf("\n");
    }
    getchar();
    system("pause");
    return 0;
}

void ran_array_generator(double array[], int size)
{
    double list[100];

    for (int i = 0; i < 100; i++) {
        list[i] = i;
    }

    for (int i = 0; i < 100; i++) {
        int j = i + rand() % (100-i); //j是一个随机的数组索引
        int temp = list[i];
        list[i] = list[j];
        list[j] = temp; //list[i] 与 list[j] 的值互换
    }

    for (int i = 0; i < size; i++) {
        array[i] = list[i];
    }
}