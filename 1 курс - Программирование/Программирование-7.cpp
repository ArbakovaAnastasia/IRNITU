#include <iostream>
using namespace std;
int test()
{
 if(cin.fail() != 0)
 {
 cout << "������, ������� ����� (i>=0).\n";
 cin.clear();
 cin.ignore(332767, '\n');
 return false;
 }
 return true;
}
unsigned long int fib(unsigned long int i)
{
if ((i==0) || (i==1))
return i;
else 
return(fib(i-1)+fib(i-2));
}
int main()
{
setlocale(LC_ALL, "rus");
int i=0;
cout<<"��������� ������� ����������� ������� ���������� i-�� ����� ���������."<<endl<<"������� i = ";
do
cin>>i;
 while (test() != true);
cout<<endl<<i<<"-� ����� ��������� = "<< fib(i);
}
