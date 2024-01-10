
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <cmath>

using namespace std;

int test()
{
  if(cin.fail() != 0)
    {
      cout << "Ошибка! Введите число.\n";
      cin.clear();
      cin.ignore(332767, '\n');
      return false;
    }
    return true;
}

bool dvoiki(int K)
{

while(fabs(K%2)==0)
{
 
 if(fabs(K/=2)==1)
    return true;
}
return false;
 
}

int massive()
{
 int X[16];
 int N,i=0;
do
 {
 cout <<"Введите количество элементов от 1 до 16: ";
 do
  cin>>N;
 while (test() != true);
 }

while (N<1 || N>17);
 cout <<"В массиве "<< N <<" элементов\n";

 for (i=0; i<N; i++)
 {
 cout<<"X["<<i+1<<"] = ";
 cin>>X[i];
 }

 cout<<"Массив: ";

 for (i=0;i<N;i++)
 cout<<X[i]<<" ";

int max, j;
  for (i=0; i<N-1; i++) 
  {
    max = i;
    for (j=i+1; j<N; j++)
    {
      if (X[j]>X[max])
        max=j;
    }
    swap(X[i], X[max]);
  }

  cout << endl << "Отсортированный массив: ";
  for(i=0; i<N; i++)
  {
    X[N]=X[i];

    cout <<X[N]<<" ";
  }
int check=false;
cout<<endl<<"Cтепени 2-ки: ";
 for (i=0; i<N; i++)
 if (dvoiki(X[i])==true)
 {
   cout<<" "<<X[i];
    check = true;
 }
 if (check == 0)
 cout<<"Степеней 2-ки нет.";
return 0;
}

int randomize()
{
  int X[16];
  int N,i=0;
  
do

  {
  cout <<"Введите количество элементов от 1 до 16: ";
  do
  cin>>N;
  while (test() != true);
  }

while (N<1 || N>16);
  cout <<"В массиве "<< N <<" элементов\n";

  srand(time(NULL)); 

  for (i=0; i<N; i++)
  X[i]=(rand() % 20100 - 10000)/100.0;

  for (i=0;i<N;i++)
  cout<<"X["<<i+1<<"] = "<<X[i]<<endl;

  cout<<"Массив: ";

  for (i=0;i<N;i++)
  cout<<X[i]<<" ";

  int max, j;
  for (i=0; i<N-1; i++) 
  {
    max = i;
    for (j=i+1; j<N; j++)
    {
      if (X[j] > X[max])
        max = j;
    }
    swap(X[i], X[max]);
  }

  cout << endl << "Отсортированный массив: ";
  for(i = 0; i < N; i++)
  {
    X[N]=X[i];

    cout <<X[N]<<" ";
  }
int check=false;
cout<<endl<<"Степени 2-ки: ";
 for (i=0; i<N; i++)
 if (dvoiki(X[N])==true)
 {
   cout<<" "<<X[N];
    check = true;
 }
 if (check == 0)
 cout<<"Степеней 2-ки нет.";
return 0;
}


int main ()
{
  cout<<"Программа создает массив (или он вводится вручную), сортируя его по убыванию и выводит степени 2-ки в данном массиве.";
  int menu=1;
  setlocale(LC_ALL, "rus");
  while (menu)
  {
 cout<<"\n\nВыберите способ:\n1. Ввести массив вручную. \n2. Рандомный массив. \n0. Выход"<<endl;
 cin>>menu;
 test();
switch (menu)
{
  case 1:
    massive();
    break;
  case 2:
    randomize();
    break;
  case 0:
    return 0;
    break;
}
} return 0;
}

