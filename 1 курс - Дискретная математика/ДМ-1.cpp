#include <iostream>
#include <windows.h>
using namespace std;
int main()
{
	char *delimiters = ", ";
	char *gluh = "����������";
	char txt[256];
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 

	cout << "������� ������������������ ���� ����� ������� ( . - ����� �����): (������) �����, ��������, ��������, ������. " << endl;
	cin.getline(txt, 256);
	CharLowerBuffA(txt, strlen(txt));
	cout << "��������� ����, �������� � ����� �� ����� 2 ���: ";
	for (int i = 0; txt[i]!=0&& txt[i] != '.'; i++)
	{
		if ((txt[i] >= '�'&&txt[i] <= '�') || txt[i] == '�')
		{
			int cnt_let = 0;	
			for (int j = 0; txt[j] != 0 && txt[j] != '.'; j++)
			{
				if (txt[i] == txt[j])
				{
					if (j < i)
						break;	
					cnt_let++;
				}
			}
			if (cnt_let >= 2)
				cout << " " << txt[i];
		}
	}
	cout << endl;
	cout << "��������� ������ ��������� ����, ������� ������ � ������ �������� ����� � �� ������ ���� �� � ���� ������ �����: ";
	for (int k = 0; gluh[k]!=0; k++)
	{
		int nw = 0;
		bool alleven = true;
		bool allodd = true;
		for (int i = 0; txt[i] != 0 && txt[i] != '.';)
		{
			//���� ������ �����
			for (; txt[i] != 0 && txt[i] != '.' && strchr(delimiters, txt[i]); i++);
			if (txt[i] != 0 && txt[i] != '.')	
			{
				nw++;	
				bool is_in_word = false;
				for (; txt[i] != 0 && txt[i] != '.' && strchr(delimiters, txt[i]) == NULL; i++)
				{
					if (txt[i] == gluh[k])
					{
						is_in_word = true;
					}
				}
				if (nw % 2 == 1)
				{
					if (!is_in_word)
						allodd = false;	
				}
				else
				{
					if (!is_in_word)
						alleven = false;
				}
			}
		}
		if (allodd && !alleven)
			cout << " " << gluh[k];
	}
	cout << endl;
	system("pause");
	return 0;
}

