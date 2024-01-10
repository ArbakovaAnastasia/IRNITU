#include <iostream>
#include <windows.h>
using namespace std;
int main()
{
	char *delimiters = ", ";
	char *gluh = "кпстфхцчшщ";
	char txt[256];
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 

	cout << "Введите последовательность слов через запятую ( . - конец ввода): (пример) Арбуз, мандарин, апельсин, гранат. " << endl;
	cin.getline(txt, 256);
	CharLowerBuffA(txt, strlen(txt));
	cout << "Множество букв, входящих в текст не менее 2 раз: ";
	for (int i = 0; txt[i]!=0&& txt[i] != '.'; i++)
	{
		if ((txt[i] >= 'а'&&txt[i] <= 'я') || txt[i] == 'ё')
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
	cout << "Множество глухих согласных букв, которые входят в каждое нечетное слово и не входят хотя бы в одно четное слово: ";
	for (int k = 0; gluh[k]!=0; k++)
	{
		int nw = 0;
		bool alleven = true;
		bool allodd = true;
		for (int i = 0; txt[i] != 0 && txt[i] != '.';)
		{
			//ищем начало слова
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

