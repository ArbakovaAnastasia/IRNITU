#include <iostream>
#include <time.h>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	const int size = 10;
	int a, n, m;
	string s;
	int A[size], B[size];
	cout << "��������� ������� �������� ��������� R=A*B, ��� a>=b.\n";
	cout << "\n������������ ������ ����? ������� Yes ��� No: ";
	cin >> s;
	cout << "\n������� ���-�� ��������� ��������� A: ";
	while (!(cin >> n) || (n > size || n < 1))
	{
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "\a������ �����! ������� ����� (1, 10): ";
	}
	cout << "\n" << "��������� A[" << n << "]: ";
	if (s == "NO" || s == "no" || s == "No") {
		srand(time(NULL));
		cout << "{  ";
		for (int i = 0; i < n; i++) {
			A[i] = rand() % 10;
		}
		int temp;
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (A[j] > A[j + 1]) {
					temp = A[j];
					A[j] = A[j + 1];
					A[j + 1] = temp;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			cout << A[i] << "  ";
		}
		cout << "}";
	}

	else if (s == "YES" || s == "yes" || s == "Yes") {
		for (int i = 0; i < n; i++) {
			cout <<"\nA[" << i << "] = ";
			while (!(cin >> A[i]))
			{
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cout << "\a������ �����! ������� �����: ";
			}
		}
		int temp2;
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (A[j] > A[j + 1]) {
					temp2 = A[j];
					A[j] = A[j + 1];
					A[j + 1] = temp2;
				}
			}
		}
		cout << "{";
		for (int i = 0; i < n; i++) { cout << A[i] << " "; }
		cout << "}";
	}
	  cout<<"\n";
	cout<<"\n"<<"������� ���-�� ��������� ��������� B: ";
	while (!( cin >> m) || (m > size || m < 1))
		{ cin.clear();
				while (cin.get() != '\n')
					continue;
		  cout << "\a������ �����! ������� ����� (1, 10): ";
		}
		cout <<"\n"<< "��������� B["<<n<<"]: ";
		if (s == "NO" || s == "no" || s == "No") {
			srand(time(NULL));
		cout<<"{ ";
			for (int i = 0; i < m; i++) {
				B[i]=rand()%10;}
		  int temp1;
	  for(int i=0;i<m-1;i++){
	for(int j=0; j<m-i-1;j++){
	  if(B[j]>B[j+1]){
		temp1=B[j];
		B[j]=B[j+1];
		B[j+1]=temp1;
	  }
	 }
	}
		for(int i=0; i<m;i++ ){
				cout << B[i] << "  ";}

		cout<<"}";
		}
		else if (s == "YES" ||  s == "yes" || s == "Yes") {
			 for (int i = 0; i < m; i++) {
				cout << "B[" << i << "] = ";
				while (!(cin >> B[i]))
				{
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "\a������ �����! ������� �����: ";
				}
			 }

	  int temp3;
	  for(int i=0;i<m-1;i++){
	for(int j=0; j<m-i-1;j++){
	  if(B[j]>B[j+1]){
		temp3=A[j];
		B[j]=B[j+1];
		B[j+1]=temp3;
	  }
	 }
	}
	cout<<"{";
	for (int i=0;i<m;i++){cout<<B[i]<<" ";}
	cout<<"}";}
	cout << "\n";
	cout << "\n" << "������� �������� ��������� R: \n";
	int R[10][10];
	for (int i = 0; i < m; i++) {
		cout << "| ";
		for (int j = 0; j < n; j++) {
			if (A[i] >= B[i])
				R[i][j] = 1;
			else R[i][j] = 0;
			cout << R[i][j] << " ";
		}
		cout << "|";
		cout << "\n";
	}

	if (R[0][0] == 1 && R[1][1] == 1 && R[2][2] == 1 && R[3][3] == 1 && R[4][4] == 1) { cout << "\n��������� �����������.\n��������� �����������.\n"; }
	else { cout << "\n��������� �� �����������, �� �����������.\n"; }
	{
		if (A[1] >= A[2] && A[2] >= A[3] && A[1] >= A[3])
		{
			cout << "��������� �����������.\n";
		}
		else cout << "��������� �� �����������.\n";
	}
	if (R[0][0] == 0 && R[1][1] == 0 && R[2][2] == 0 && R[3][3] == 0 && R[4][4] == 0) {
		cout << "O�������� ���������������.\n";
	}
	else cout << "��������� �� ���������������.\n";

	return 0;
}

