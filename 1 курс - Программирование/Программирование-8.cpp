#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int test()
{
	if (cin.fail() != 0)
	{
		cout << "Ошибка! Введите число.\n";
		cin.clear();
		cin.ignore(332767, '\n');
		return false;
	}
	return true;
}


struct node
{
	int number;
	string fio;
	int n;
	int st;
	int ok;
	string spec;

	node* r;
};

void add(node** pHead, int number, string fio, int n, int st, int ok, string spec)
{
	if (*pHead == 0)
	{
		*pHead = new node{ number, fio,  n,  st,  ok,  spec, 0 };
	}
	else
	{
		node* ch = *pHead;
		while (ch->r) ch = ch->r;
		ch->r = new  node{ number, fio,  n,  st,  ok,  spec, 0 };
	}
}

void print_list1(node* head, int numb)
{
	while (head)
	{
		numb++;
		cout << "Номер №" << numb << ". ";
		cout << head->fio << ", " << head->n << ", " << head->st << ", "<< head->ok << ", " << head->spec << endl;

		head = head->r;
		
	}
}
void print_list2(node* head, int a, int b, string spec, int numb)
{
	while (head)
	{
		if ((head->st >= a) && (head->st <= b) && (head->spec == spec))
		{
			numb++;
			cout << "Номер №" << numb << ". ";
			cout << head->fio << ", " << head->n << ", " << head->st << ", " << head->ok << ", " << head->spec<<endl;
			
		}
		head = head->r;
	}
}


void del_n(node** pHead, int number1)
{
	node* ptr = *pHead;
	node* temp = *pHead;
	for (int i = 1; i < number1; i++) {
		ptr = temp;
		temp = temp->r;
	}
	if (number1 == 1)
		*pHead = (*pHead)->r;
	

	ptr->r = temp->r;
	delete temp;
}


int main()
{
	int menu = 1;
	int number = 0;
	int number1;
	int a = 0, b = 0;
	int numb = 0;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string fio;
	string spec;
	node* head = 0;
	while (menu)
	{
		cout << endl << "Задание - Структура элемента однонаправленного списка: Фамилия И.,О., табельный номер, стаж работы, оклад, специальность. Вывести на печать те элементы списка, в которых стаж работы содержится в заданных пределах и специальность совпадает с заданной. Добавление в конец и удаление по номеру. " << endl;
		cout << endl;
		numb = 0;
		print_list1(head, numb);
		cout << endl;
		cout << "\nВыберите:\n1. Добавить элемент в конец. \n2. Удалить элемент по номеру. \n3. Продолжить с имеющимся списком. \n0. Выход из программы." << endl;

		do
			cin >> menu;
		while (test() != true);

		switch (menu)
		{
		case 1:
			//добавление в конец
			number++;

			cout << "Ф.И.О: ";
			cin.ignore(332767, '\n');
			getline(cin, fio);
			
			cout << endl;

			int n = 0;
			cout << "Табельный номер = ";
do
			cin >> n;
while (test() != true);
			int st = 0;
			cout << "Стаж = ";
do
			cin >> st;
while (test() != true);
			int ok  = 0;
			cout << "Оклад = ";
do
			cin >> ok;
while (test() != true);
			cout << "Специальность = ";
			cin.ignore(332767, '\n');
			getline(cin, spec);
			
			cout << endl;

			numb++;

			cout << endl;
			add(&head, number, fio, n, st, ok, spec);
			break;
		case 2:
			cout << "Введите номер для удаления: ";
			cin >> number1;
if (number1 > number)
				cout << "Такого элемента не существует. Введите правильный номер элемента." << endl;
			else
				del_n(&head, number1);		
break;
		case 3:
			cout << "Введите стаж от a до b." << endl << "a = ";
			cin >> a;
			cout << endl << "b = ";
			cin >> b;
			cout << endl << "Введите специальность: ";
			cin >> spec;
			cout << endl<< "Имеющиеся в списке со стажем от "<< a << " до " << b << " и со специальностью - " << spec <<  " : " << endl;
			numb = 0;
			print_list2(head, a, b, spec, numb);
			cout << endl;
			break;
		case 0:
			return 0;
			break;
		}
	} return 0;
}

