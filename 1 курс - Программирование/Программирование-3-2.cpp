#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

//тест на буквы, символы
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

//компаратор
int comp1 (const void * a, const void * b)
{
  return ( *(int*)b - *(int*)a );
}

//1 вариант с ручным вводом
int matr()
{
 int M[10][10], A[10], B[10];
 int n, m, i, j, p, s;

 cout <<"Введите количество строк матрицы (0<n<=10), n: ";
 do
  cin>>n;
 while (test() != true);

 cout <<"Введите количество столбцов матрицы (0<m<=10), m: ";
 do
  cin>>m;
 while (test() != true);

 if ((n<=10) && (n>0) && (m>0) && (m<=10))
 {
 for (i=0; i<n; i++)
   for (j=0; j<m; j++)
    {
       cout<<"M["<<i+1<<","<<j+1<<"] = ";
        cin>>M[i][j];
    }

//сумма
s=0;
      for (i=0; i<n; i++)
        {
        for (j=0; j<m; j++)
        {
        s=s+M[i][j];
        }
        A[i]=s;
        s=0;
        }
p=0;
for (i=0; i<n; i++)
{
  B[p]=A[i];
  p=p+1;
}

//сортировка
p=0;
qsort(B, n, sizeof(int), comp1);

//вывод матриц
     cout <<endl<<endl<<"Введенная матрица"<<endl;
     for (i=0; i<n; i++)
     {
       for (j=0; j<m; j++)
        {
         cout.width(4);
         cout<<M[i][j];
        }
        cout<<endl;
     }
cout<<endl;
for (i=0; i<n; i++)
cout<<"Сумма строки №"<<i+1<<" = "<<A[i]<<endl;

cout <<endl<<"Отсортированная матрица по убыванию значений сумм элементов строк"<<endl;
for (p=0; p<n; p++)
{
  for (i=0; i<n; i++)
   if (B[p]==A[i])
   {
     for (j=0; j<n; j++)
     {
       cout.width(4);
       cout<<M[i][j];
     }
     cout<<endl;
   }
}
i=0;
cout<<endl;
for (p=0; p<n; p++)
{
  cout<<"Сумма строки №"<<i+1<<" = "<<B[p]<<endl;
  i=i+1;
}
//максимальный элемент и значение
    int max = M[0][0], 
        max_i = 0,
        max_j = 0;
 
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
        {
            if ((M[i][j] > max) || ((M[i][j] == max) && (i + j > max_i + max_j)))
            {
                max = M[i][j];
                max_i = i;
                max_j = j;
            }
        }
    cout<<endl<<"Индекс максимального элемента матрицы и его значение: "<<max<<"\t M["<<++max_i<<"]["<<++max_j<<"]"<<endl;
 } else
 cout<<"Ошибка! Неверно введена размерность матрицы. Введите число от 0 до 10.";
return 0;
}

//2 вариант в рандом
int randomize()
{
 int M[10][10], A[10], B[10];
 int n, m, i, j, p, s;

 cout <<"Введите количество строк матрицы (0<n<=10), n: ";
 do
  cin>>n;
 while (test() != true);

 cout <<"Введите количество столбцов матрицы (0<m<=10), m: ";
 do
  cin>>m;
 while (test() != true);

if ((n<=10) && (n>0) && (m>0) && (m<=10))
 {
 srand(time(NULL)); 
 for (i=0; i<n; i++)
   for (j=0; j<m; j++)
    {
       M[i][j]=(rand() % 20100 - 10000)/100.0;
       cout<<"M["<<i+1<<","<<j+1<<"] = "<<M[i][j]<<endl;
    }
     cout <<endl<<"Введенная матрица"<<endl;
     for (i=0; i<n; i++)
     {
       for (j=0; j<m; j++)
        {
         cout.width(4);
         cout<<M[i][j];
        }
        cout<<endl;
     }

//сумма
s=0;
      for (i=0; i<n; i++)
        {
        for (j=0; j<m; j++)
        {
        s=s+M[i][j];
        }
        A[i]=s;
        s=0;
        }
  
cout<<endl;
for (i=0; i<n; i++)
cout<<"Сумма строки №"<<i+1<<" = "<<A[i]<<endl;

p=0;
for (i=0; i<n; i++)
{
  B[p]=A[i];
  p=p+1;
}
//сортировка
p=0;
qsort(B, n, sizeof(int), comp1);

//отсортированная
cout <<endl<<"Отсортированная матрица по убыванию значений сумм элементов строк"<<endl;
for (p=0; p<n; p++)
{
  for (i=0; i<n; i++)
   if (B[p]==A[i])
   {
     for (j=0; j<n; j++)
     {
       cout.width(4);
       cout<<M[i][j];
     }
     cout<<endl;
   }
}

i=0;
cout<<endl;
for (p=0; p<n; p++)
{
  cout<<"Сумма строки №"<<i+1<<" = "<<B[p]<<endl;
  i=i+1;
}

//макс значение
    int max = M[0][0], 
        max_i = 0,
        max_j = 0;
 
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
        {
            if ((M[i][j] > max) || ((M[i][j] == max) && (i + j > max_i + max_j)))
            {
                max = M[i][j];
                max_i = i;
                max_j = j;
            }
        }
    cout<<endl<<"Индекс максимального элемента матрицы и его значение: "<<max<<"\t M["<<++max_i<<"]["<<++max_j<<"]"<<endl;
  } else
 cout<<"Ошибка! Неверно введена размерность матрицы. Введите число от 0 до 10.";
 return 0;
}


//меню
int main ()
{
  cout<<"Программа матрицы.\nВыводит индекс максимального элемента матрицы и его значение.\nСортирует строки по убыванию значений сумм элементов строк.";
  int menu=1;
  setlocale(LC_ALL, "rus");
  while (menu)
  {
 cout<<"\n\nВыберите способ:\n1. Ввести матрицу вручную. \n2. Рандомное заполнение матрицы. \n0. Выход"<<endl;
  do
  cin>>menu;
  while (test() != true);
switch (menu)
{
  case 1:
    matr();
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

