#include <iostream>
using namespace std;

int i;
int kola, kolb, kolc, koll;
int A[10], B[10], C[10], M[10];
int N[10], P[10];

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

void vvod(int M[])
{
	int n = 0, i = 0;
	while (i < 10)
	{
		cout << "[" << i + 1 << "]= ";
		do
			cin >> n;
		while (test() != true);
		if ((n == 0) || (n == 1))
		{
			M[i] = n;
			i++;
		}
		else
			cout << endl << "Введите число еще раз (1 или 0)" << endl << endl;
	}

}

void kol(int M[], int& koll)
{
	koll = 0;
	for (i = 0; i < 10; i++)
	{
		if (M[i] == 0)
			koll++;
	}
}

void zamena(int M[], int N[], int P[])
{
	for (i = 0; i < 10; i++)
		M[i] = N[i] | P[i];
}

void max(int kola, int kolb, int kolc)
{
	if ((kola > kolb) && (kola > kolc))
	{
		zamena(A, B, C);
		cout << endl << "Произведена замена вектора A на логическую сумму векторов B и C: ";
		for (i = 0; i < 10; i++)
			cout << A[i] << " ";
	}
	if ((kolb > kola) && (kolb > kolc))
	{
		zamena(B, A, C);
		cout << endl << "Произведена замена вектора B на логическую сумму векторов A и C: ";
		for (i = 0; i < 10; i++)
			cout << B[i] << " ";
	}
	if ((kolc > kolb) && (kolc > kola))
	{
		zamena(C, A, B);
		cout << endl << "Произведена замена вектора C на логическую сумму векторов A и B: ";
		for (i = 0; i < 10; i++)
			cout << C[i] << " ";
	}
}

void vivod(int A[], int B[], int C[])
{
	cout << endl;
	cout << "A: ";
	for (i = 0; i < 10; i++)
		cout << A[i] << " ";
	cout << endl;
	cout << "B: ";
	for (i = 0; i < 10; i++)
		cout << B[i] << " ";
	cout << endl;
	cout << "C: ";
	for (i = 0; i < 10; i++)
		cout << C[i] << " ";
	cout << endl << endl;
}
void randomize(int M[])
{
	for (i = 0; i < 10; i++)
		M[i] = rand() % 2;
}

int main()
{
	int menu = 1;

	setlocale(LC_ALL, "rus");
	while (menu)
	{
		cout << "Даны векторы A[10], B[10], C[10], каждый элемент которых имеет значение 1 или 0. Значение каждой компоненты вектора, имеющего максимальное число компонент со значением 0 (в предположении, что такой вектор только 1), заменить логической суммой значений соответствующих компонент двух других векторов." << endl;
		cout << "\nВыберите способ:\n1. Ручной ввод. \n2. Рандомный ввод. \n0. Выход из программы." << endl;

		do
			cin >> menu;
		while (test() != true);

		switch (menu)
		{
		case 1:
			do
			{
				cout << endl << "Максимальное количество нулей должно быть единственнным, иначе программа выдаст ввод значений заново." << endl;
				cout << endl << "Введите вектор A:" << endl;
				vvod(A);
				cout << endl << "Вектор A: ";
				for (i = 0; i < 10; i++)
					cout << A[i] << " ";

				cout << endl << endl << "Введите вектор B:" << endl;
				vvod(B);
				cout << endl << "Вектор B: ";
				for (i = 0; i < 10; i++)
					cout << B[i] << " ";

				cout << endl << endl << "Введите вектор C:" << endl;
				vvod(C);
				cout << endl << "Вектор C: ";
				for (i = 0; i < 10; i++)
					cout << C[i] << " ";

				kol(A, kola);
				kol(B, kolb);
				kol(C, kolc);

				cout << endl << endl;
				cout << endl << "Количество нулей в векторе А: " << kola;
				cout << endl << "Количество нулей в векторе B: " << kolb;
				cout << endl << "Количество нулей в векторе C: " << kolc;
				cout << endl;

			} while (((kola == kolb) && (kola > kolc)) || ((kola == kolc) && (kola > kolb)) || ((kolb == kolc) && (kolb > kola)) || ((kola == kolb) && (kola == kolc)));
			
			max(kola, kolb, kolc);
			cout << endl << endl << "Конечные векторы: ";

			vivod(A, B, C);
			break;
		case 2:
			do
			{
				cout << endl << "Максимальное количество нулей должно быть единственным, иначе программа задаст значения заново." << endl;
				cout << endl << "Вектор A: ";
				randomize(A);
				for (i = 0; i < 10; i++)
					cout << A[i] << " ";
				cout << endl << "Вектор B: ";
				randomize(B);
				for (i = 0; i < 10; i++)
					cout << B[i] << " ";
				cout << endl << "Вектор C: ";
				randomize(C);
				for (i = 0; i < 10; i++)
					cout << C[i] << " ";

			kol(A, kola);
			kol(B, kolb);
			kol(C, kolc);

			cout << endl << endl;
			cout << endl << "Количество нулей в векторе А: " << kola;
			cout << endl << "Количество нулей в векторе B: " << kolb;
			cout << endl << "Количество нулей в векторе C: " << kolc;
			cout << endl;

			} while (((kola == kolb) && (kola > kolc)) || ((kola == kolc) && (kola > kolb)) || ((kolb == kolc) && (kolb > kola)) || ((kola == kolb) && (kola == kolc)));
			
			max(kola, kolb, kolc);
			cout << endl << endl << "Конечные векторы: ";

			vivod(A, B, C);
			break;
		case 0:
			return 0;
			break;
		}
	} return 0;
}

