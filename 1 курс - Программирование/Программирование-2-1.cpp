#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

int test()
{
  if(cin.fail() != 0)
    {
      cout << "������! ������� �����.\n";
      cin.clear();
      cin.ignore(332767, '\n');
      return false;
    }
    return true;
}

  const float pi=M_PI;

void cherezk()
{
  int i,k;
  float y,u,x,a;
  cout<<"������� x = ";
  do
  cin>>x;
  while (test() != true);
  cout<<"������� a = ";
  do
  cin>>a;
  while (test() != true);
  cout<<"������� (k>2) k = ";
  do
  cin>>k;
  while (test() != true);
  
  y=0;
  u=1;
  cout<<"�"<<"     �������� ����� ����"<<"      ����� ����"<<endl;
  if (fabs(x)<1)
  { if (k>2)
  {
  for(i=0; i<k+1; i++)
  {
    if(i!=0){
    u=u*x/i;  
    y=y+(u*cos(a+(i)*pi/2));
    cout<<"�"<<setw(10)<<left<<i<<setw(10)<<u<<setw(20)<<std::right<<y<<endl;
  }else{
    y=cos(a);
  }
  
  }
  cout<<"y = "<<y;
  } else cout<<"������ k<2";
} else
{
cout<<"������ x>1";
}
} 

void cherezeps()
{
  int i;
  double y,u,x,a,eps;
  
  cout<<"������� x = ";
  do
  cin>>x;
  while (test() != true);
  cout<<"������� a = ";
  do
  cin>>a;
  while (test() != true);
  cout<<"������� eps = ";
  do
  cin>>eps;
  while (test() != true);
  y=cos(a);
  u=1;
  i=1;
  cout<<"�"<<"     �������� ����� ����"<<"      ����� ����"<<endl;
  if (fabs(x)<1)
  {
    if((eps<1) && (eps>0))
    {
  while(fabs(u) >= eps)
  {
    u=(u*x)/i;  
    y=y+(u*cos(a+(i)*pi/2));
    cout<<"�"<<setw(10)<<std::left<<i<<setw(10)<<u<<setw(20)<<std::right<<y<<endl;
    i++;
  }
  cout<<"y = "<<y;
} else
{
cout<<"������ eps>1";
} 
} else
{
cout<<"������ x>1";
}
}

void analitic()
{
  float y,x,a;
  cout<<"������� x = ";
  do
  cin>>x;
  while (test() != true);
  cout<<"������� a = ";
  do
  cin>>a;
  while (test() != true);
  if (fabs(x)<1)
  {
  y=cos(x+a);
  cout<<"y = "<<y;
}
else
{
cout<<"������ x>1";
}
}
int main ()
{
  int menu=1;
  setlocale(LC_ALL, "rus");
  while (menu)
  {
 cout<<"\n�������� ������:\n1. � �������� ������ k ������ ������ ����.\n2. � �������� ������������ eps.\n3. �� ������������� �������.\n0. �����"<<endl;
 do
  cin>>menu;
  while (test() != true);
switch (menu)
{
  case 1:
    cherezk();
    break;
  case 2:
    cherezeps();
    break;
  case 3:
    analitic();
    break;
  case 0:
    return 0;
    break;
}
} return 0;
}

