#include <iostream>
#include <math.h>
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

int chot()
{
  setlocale (LC_ALL, "rus");
  int n, x, y, z;
  int r=0;
  cout<<"Введите N = ";
  do
  cin>>n;
  while (test() != true);
  if (n>0)
  {
    for (x=1; x<n; x++)
    {
      for (y=1; y<n; y++)
      {
        for (z=1; z<n; z++)
        {
          if (pow(x,2)+pow(y,2)+pow(z,2)==n)
          {
            cout<<"x = "<<x<<endl;
            cout<<"y = "<<y<<endl;
            cout<<"z = "<<z<<endl;
            cout<<"Тройка найдена"<<endl<<endl;
         } else r=1;
        }
        r=1;
      }
      r=1;
    }
    r=1;
  } else
  {
  cout<<"Неправильное число N, введите новое";
  }
  if (r==1)
  {
  cout<<"Больше троек не найдено";
  }
  return 0;
} 

int main()
{
  int menu=1;
  setlocale(LC_ALL, "rus");
  cout<<"Дано натуральное число N. Найти такие x,y,z удовлетворяющие выражению x^2+y^2+z^2=N.";
  while (menu)
  {
 cout<<"\n1. Ввести N\n0. Выход"<<endl;
 cin>>menu;
switch (menu)
{
  case 1:
    chot();
    break;
  case 2:
    return 0;
    break;
}
  }
}

