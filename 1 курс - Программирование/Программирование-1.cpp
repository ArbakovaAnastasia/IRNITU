#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	
	short a, b, c, d, f, x0, x1, x2, x3, x4;
	
cout << "Введите 5 цифр: " << endl;
cin >> a;
cin >> b;
cin >> c;
cin >> d;
cin >> f;
if (((1<=a) && (a<=13)) && ((1<=b) && (b<=13)) && ((1<=c)&& (c<=13)) && ((1<=d) && (d<=13)) && ((1<=f) && (f<=13))) {
		 const int length = 5;
		 int array[length] = { a, b, c, d, f };
		 std::sort(array, array+length);
		 x0 = array[0];
		 x1 = array[1];
		 x2 = array[2];
		 x3 = array[3];
		 x4 = array[4]; //сортировка с 17 по 24 строку//
		 if ((x0==(x1-1)) && (x1==(x2-1)) && (x2==(x3-1)) && (x3==(x4-1))) {
		 	cout << "Straight" << endl;
		} else if ((x0==x1) && (x1==x2) && (x2==x3) && (x3==x4)){
			cout << "Impossible" << endl;
		} else if (((x0==x1) && (x1==x2) && (x2==x3)) || ((x1==x2) && (x2==x3) && (x3==x4))){
			cout << "Four of a Kind" << endl;
		} else if (((x0==x1) && (x2==x3) && (x3==x4)) || ((x0==x1) && (x1==x2) && (x3==x4))){
			cout << "Full House" << endl;
		} else if (((x0==x1) && (x1==x2)) || ((x1==x2) && (x2==x3)) || ((x2==x3) && (x3==x4))){
			cout << "Three of a Kind" << endl;
		} else if (((x0==x1) && ((x2==x3) || (x3==x4))) || ((x1==x2) && (x3==x4))){
			cout << "Two Pairs" << endl;
		} else if ((x0==x1) || (x1==x2) || (x2==x3) || (x3==x4)){
			cout << "One Pair" << endl;
		} else {
			cout << "Nothing" << endl;
		}
	} else {
		cout << "Неправильные цифры";
}
	return 0;
	
}

