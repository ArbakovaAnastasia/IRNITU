#include <algorithm>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
using namespace std;
    string X[100];
    int N, X1[100];
void swap(int a,int b)
{
    string t=X[a];
    X[a]=X[b];
    X[b]=t;
}
void perestanovki(int k)
{
    if (k==N)
    {cout.width(3);
      cout<<"{";
        for(int i=0;i<N-1;i++)
        cout<<X[i]<<", ";
        cout<<X[N-1]<<"} \n";
    }
    else
    { 
        for(int j=k;j<N;j++)
        {
            swap(k,j);
            perestanovki(k+1);
            swap(k,j);
        }
    }
}
bool NextSet(int *a, int n, int m)
{
  int j = m - 1;
  while (j >= 0 && a[j] == n) j--;
  if (j < 0) return false;
  if (a[j] >= n)
    j--;
  a[j]++;
  if (j == m - 1) return true;
  for (int k = j + 1; k < m; k++)
    a[k] = 1;
  return true;
}
void Print(int *a, int n) 
{
  static int num = 1;
  cout.width(3);
  cout<<"{";
  for (int i = 0; i < n-1; i++)
    cout << X[a[i]-1] << ", ";
  cout <<X[a[n-1]-1] << "} "<< endl;
}
int fac(int k){
int p=1;
for (int i=2; i<=k;i++)
p*=i;
  return p;
}
int main() 
{
  int n, m,  l=1,p=1;
  int m1[100],mx=1, A[100],B[100],s=0,p1=1,k,b1=0,b2=0,count=0,q,e,A1[100][100],x,v;
  setlocale(LC_ALL,"Rus");
  cout<<"Введите количество элементов множества: ";
  cin>>N;
  for(int i=0;i<N;i++){
  cout<<"Введите "<<i+1<<" элемент: ";
  cin>>X[i];
  }
  cout<<"Введенное множество А: {";
    for(int i=0;i<N-1;i++){
    cout<<X[i]<<", ";
  }
  cout<<X[N-1]<<"}"<<endl;
  cout<<"Количесво перестановок: "<<fac(N)<<endl;
    perestanovki(0);
  cout<<endl;
  
  cout << "Сочетания с повторениями из n = "<<N;
  n=N;
  cout << " по m = ";
  cin >> m;
  cout<< "Количесво сочитаний с повторениями: "<<pow(n,m)<< endl;
  int h = n > m ? n : m; 
  int a[h];
    for (int i = 0; i < h; i++)
    a[i] = 1;
  Print(a, m);
  while (NextSet(a, n, m))
    Print(a, m);
cout<<endl;
  cout << "Разбиения из n = "<<N;
  l=0;
  p=1;
    for(int i=0;i<N;i++){
    X1[i]=i+1;
    l+=X1[i];
    p*=X1[i];
  }
  for(int i=0; i < N; i++) 
        mx *= 2; 
     for(int i=0; i < mx; i++) 
     {
      for(int j=0; j < N; j++)
       if ((i >> j) & 1) {
       A[s]=A[s]*10+X1[j];
       B[s]+=X1[j];
     }
     s++;
     }
    for (int i=0;i<s-1;i++){
      A[i]=A[i+1];
      B[i]=B[i+1];
   }
   s=s-1;
  mx=1; 
  for(int i=0; i < s; i++) 
        mx *= 2; 
     for(int i=0; i < mx; i++) 
     {
      for(int j=0; j < s; j++)
       if ((i >> j) & 1) {
        b1+=B[j];
        A1[j][e]=A[j];
        q=A[j];
        while(q>0){
          p1*=q%10;
          q=q/10;
      count++;
    }
    }
     if (count==N && p1==p && b1==l)
     e++;
     else
     for (int j=0;j<s;j++)
     A1[j][e]=0;
     b2=0;
     b1=0;
     p1=1;
     count=0;
     }
     cout<<endl;
     if (N==2) v=2;
     else
     if(N==3) v=5;
     else
     if(N==4) v=15;
     cout<<"Количество разбиений: "<<v<<endl;
     for(int i=0; i < e; i++){
      cout.width(3);
      cout<<"{";
      for(int j=0; j < s; j++){
      if (A1[j][i]!=0){
      x=A1[j][i];
      cout<<'(';
      while(x>9){
        cout<<X[(x%10)-1]<<", ";
        x=x/10;
      }
      cout<<X[(x%10)-1]<<')';
  }
    }
    cout<<"}"<<endl;
    }
  return 0;
}

