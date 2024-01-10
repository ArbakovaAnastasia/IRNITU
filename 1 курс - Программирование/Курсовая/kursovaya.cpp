#include <iostream>
#include <fstream>
#include <istream >
#include <string>
#include <Windows.h>
#include <iomanip>
#include <list>
#include <iterator>
using namespace std;

struct polyclinic
{
	int numberList; //порядковый номер
	string FIOpatient; //фио пациента
	int birthDay; //день р пациента
	int birthMonth; //месяц р пациента
	int birthYear; //год р пациента
	int policyNumber; //номер полиса
	string diagnosis; // диагноз
	string FIOdoctor; //фио доктора
	int visitDay; //день посещения
	int visitMonth; //месяц посещения
	int visitYear; //год посещения
	
	polyclinic* next;
};
int InputNumberFromConsole(int min, int max, string ask)  //ввод числа для меню в диапазоне
{
    int number;
    bool check;
    do{
        cout << ask;
        check = false;
        cin >> number;
        if (cin.peek() != '\n'){
            cout << "Ошибка. Попробуйте снова.\n" << endl;
            cin.clear();
            cin.ignore(2147483647, '\n');
            check = true;
        }
        if (!check && (number < min || number > max)){
            cout << "Недопустимый диапазон. Попробуйте снова.\n";
            cin.clear();
            cin.ignore(2147483647, '\n');
            check = true;
        }
    } while (check);
    return number;
}
void openGuide(){ //открытие руководства из текстового файла
	cout<<"РУКОВОДСТВО ПОЛЬЗОВАТЕЛЯ:\n";
	ifstream file;
	file.open("Guide.txt");
	if (!file){
		cout<<"Отсутствует файл для открытия!\n";
	}
	else{
		string str;
		while(!file.eof()){
			str="";
			getline(file,str);
			cout<<str<<endl;}
	cout<<endl;
	file.close();
	}
}
int number = 0;
int dayP;
int monthP;
int yearP;
int dayVisit;
int monthVisit;
int yearVisit;
int policyP;
string fioP;
string diagnosisP;
string fioD;
void addListByNumber(polyclinic** pHead) //добавление элемента в структуру
{
	cout << "ДОБАВЛЕНИЕ ЭЛЕМЕНТА В СПИСОК\n";
	number++;
	
	cout<<"Пациент: ";
	cin.ignore(332767,'\n');
	getline(cin,fioP);
	
	cout<<"Дата рождения(день, месяц, год):\n";
	dayP = InputNumberFromConsole(1, 31, "День: ");
	monthP = InputNumberFromConsole(1, 12, "Месяц: ");
	yearP = InputNumberFromConsole(1900, 2022, "Год: ");
	int policy=9999999999999999;
	policyP = InputNumberFromConsole(1, policy, "Номер полиса: ");
	
	cout<<"Диагноз: ";
	cin.ignore(332767,'\n');
	getline(cin,diagnosisP);
	
	dayVisit = InputNumberFromConsole(1, 31, "День: ");
	monthVisit = InputNumberFromConsole(1, 12, "Месяц: ");
	yearVisit = InputNumberFromConsole(1900, 2022, "Год: ");
	
	cout<<"Доктор: ";
	cin.ignore(332767,'\n');
	getline(cin,fioD);
	
	if (*pHead==0){
		*pHead = new polyclinic{number, fioP, dayP, monthP, yearP, policyP, diagnosisP, fioD, dayVisit, monthVisit, yearVisit, 0};
	}
	else{
		polyclinic* ch = *pHead;
		while (ch->next) ch=ch->next;
		ch->next=new polyclinic{number, fioP, dayP, monthP, yearP, policyP, diagnosisP, fioD, dayVisit, monthVisit, yearVisit, 0};
	}
}
void printList (polyclinic* head, polyclinic** pHead) //вывод структуры
{
	number=0;
	cout << "ИМЕЮЩИЙСЯ СПИСОК:\n";
	if (*pHead==0){
		cout<<"Список пуст.\n";
	}
	else{
		cout<<setw(2)<<"№ "<<setw(12)<<"Пациент"<<setw(18)<<"Дата Рождения(ДД."<<setw(3)<<"ММ."<<setw(5)<<"ГГГГ)"<<setw(13)<<"Номер полиса"<<setw(12)<<"Диагноз"<<setw(13)<<"Доктор"<<setw(19)<<"День посещения(ДД."<<setw(3)<<"ММ."<<setw(5)<<"ГГГГ)\n";
		while(head){
			number++;
			cout<<setw(2)<<number<<setw(12)<<head->FIOpatient<<setw(18)<<head->birthDay<<setw(3)<<head->birthMonth<<setw(5)<<head->birthYear<<setw(13)<<head->policyNumber<<setw(12)<<head->diagnosis<<setw(13)<<head->FIOdoctor<<setw(19)<<head->visitDay<<setw(3)<<head->visitMonth<<setw(5)<<head->visitYear<<"\n";
			head = head->next;
		}
	}
	cout<<endl;
}
int num(polyclinic** pHead) //для проверки функции удаления, подсчет количества элементов в структуре
{
	int number = 1;
	polyclinic* ptr = *pHead;
	polyclinic* temp = *pHead;
		do{
			ptr = temp;
			temp = temp->next;
			number++;
		} while (temp->next != NULL);
    return number;
}
int delByNumber(polyclinic** pHead, int number1) //удаление по номеру
{
	if (*pHead==0)
		return false;
	polyclinic* ptr = *pHead;
	polyclinic* temp = *pHead;
    int  number = num(pHead);
	if (number1 > number)
		return false;
	else{
		for (int i = 1; i < number1; i++){
			ptr = temp;
			temp = temp->next;
		}
		if (number1 == 1)
			*pHead = (*pHead)->next;
		ptr->next = temp->next;
		delete temp;
		return true;
	}
	return false;
}
void saveList(polyclinic** pHead, polyclinic* head){ //сохранение структуры в файл
	if (*pHead==0){
		cout<<"Невозможно сохранить пустой список. (СПИСОК ПУСТ)\n";
	}
	else{
		ofstream file;
		file.open("newfile.txt");
		number=0;
		while(head){
			number++;
			file<<number<<" "<<head->FIOpatient<<" "<<head->birthDay<<" "<<head->birthMonth<<" "<<head->birthYear<<" "<<head->policyNumber<<" "<<head->diagnosis<<" "<<head->FIOdoctor<<" "<<head->visitDay<<" "<<head->visitMonth<<" "<<head->visitYear<< " "<<"\n";
			head = head->next;
		}
		file.close();
	}
}
void openList(polyclinic** pHead, polyclinic* head){ //открытие файла
	ifstream file;
	file.open("newfile.txt");
	if (!file){
		cout<<"Отсутствует файл для открытия!\n";
	}
	else{
		*pHead = 0;
		while(!file.eof()){
    	number=0;
		file>>number;
		file>>fioP;
		file>>dayP; file>>monthP; file>>yearP;
		file>>policyP;
		file>>diagnosisP;
		file>>fioD;
		file>>dayVisit; file>>monthVisit; file>>yearVisit;
		if (number == 0)
		break;
		if (*pHead==0){
			*pHead = new polyclinic{number, fioP, dayP, monthP, yearP, policyP, diagnosisP, fioD, dayVisit, monthVisit, yearVisit, 0};
		}
		else{
			polyclinic* ch = *pHead;
			while (ch->next) ch=ch->next;
			ch->next=new polyclinic{number, fioP, dayP, monthP, yearP, policyP, diagnosisP, fioD, dayVisit, monthVisit, yearVisit, 0};
			}
		}
	}
	file.close();
}
class wLoadOne{ //для 1 подзадачи
	public:
		string FIOdoctor;
		int PatientCount=0;
		wLoadOne(string Doc){
			FIOdoctor=Doc;
			PatientCount=1;}
		void print(){
			cout<<"Доктор "<<FIOdoctor<<" имеет "<<PatientCount<<" записей пациентов.\n";}
};
void WorkLoad1 (polyclinic* head, polyclinic** pHead) //1 подзадача по выводу нагрузки врачей
{
	cout<< "НАГРУЗКА ВРАЧЕЙ:\n";
	list <wLoadOne> loadList;
	list <wLoadOne> :: iterator i;
	if (*pHead==0){
		cout<<"Список пуст.\n";
	}
	else{
		bool founded=false;
		while(head){
			founded=false;
			for (i=loadList.begin(); i != loadList.end();++i)
				if ((*i).FIOdoctor==head->FIOdoctor){
					(*i).PatientCount+=1;
					founded=true;
				}
			if (founded==false){
				loadList.push_back(wLoadOne(head->FIOdoctor));}
			head = head->next;
		}
	}
	for (i=loadList.begin(); i != loadList.end();++i)
		(*i).print();
	cout<<endl;
}
class wLoadTwo{ //для 2 подзадачи
	public:
		string diagnosis;
		int diagnosisCount=0;
		wLoadTwo(string Dia){
			diagnosis=Dia;
			diagnosisCount=1;}
		void print(){
			cout<<"Заболевание "<<diagnosis<<" выявленно у пациентов "<<diagnosisCount<<" раз.\n";}
};
void WorkLoad2 (polyclinic* head, polyclinic** pHead) //2 подзадача по выводу статистики по заболеваниям
{
	cout<< "СТАТИСТИКА ЗАБОЛЕВАНИЙ:\n";
	list <wLoadTwo> loadList;
	list <wLoadTwo> :: iterator i;
	if (*pHead==0){
		cout<<"Список пуст.\n";
	}
	else{
		bool founded=false;
		while(head){
			founded=false;
			for (i=loadList.begin(); i != loadList.end();++i)
				if ((*i).diagnosis==head->diagnosis){
					(*i).diagnosisCount+=1;
					founded=true;
				}
			if (founded==false){
				loadList.push_back(wLoadTwo(head->diagnosis));}
			head = head->next;
		}
	}
	for (i=loadList.begin(); i != loadList.end();++i)
		(*i).print();
	cout<<endl;
}
class wLoadThree{ //для 3 подзадачи
	public:
		string FIOpatient;
		string diagnosis;
		int diagnosisCount=0;
		int visitYear=0;
		wLoadThree(string Pat, string Dia, int vYear){
			FIOpatient=Pat;
			diagnosis=Dia;
			diagnosisCount=1;
			 visitYear=vYear;}
		void print(){
			if (diagnosisCount>3)
			cout<<"Заболевание "<<diagnosis<<" выявленно у "<<FIOpatient<<" "<<diagnosisCount<<" раз в течении "<<visitYear<< " года.\n";}
};
void WorkLoad3 (polyclinic* head, polyclinic** pHead) //3 подзадача по выводу хронических заболеваний пациентов
{
	cout<< "СПИСОК ПАЦИЕНТОВ С ХРОНИЧЕСКИМИ ЗАБОЛЕВАНИЯМИ:\n";
	list <wLoadThree> loadList;
	list <wLoadThree> :: iterator i;
	if (*pHead==0){
		cout<<"Список пуст.\n";
	}
	else{
		bool founded=false;
		while(head){
			founded=false;
			for (i=loadList.begin(); i != loadList.end();++i){
				if (((*i).diagnosis==head->diagnosis) && ((*i).FIOpatient==head->FIOpatient) && ((*i).visitYear==head->visitYear)){
					(*i).diagnosisCount+=1;
					founded=true;
				}
			}
			if (founded==false){
				loadList.push_back(wLoadThree(head->FIOpatient, head->diagnosis, head->visitYear));}
			head = head->next;
		}
	}
	for (i=loadList.begin(); i != loadList.end();++i)
		(*i).print();
	cout<<endl;
}
int main()
{
	SetConsoleCP(1251); //русский язык в консоли на ввод и вывод
	SetConsoleOutputCP(1251);

	int mainMenu, menu, menu1;
	bool check = true, check1 = true, check2 = true;   //флажок для do while заканчивается при выходе из программы
	polyclinic* head = 0;
	int number1, number2;
	do{
    	cout << "\nГЛАВНОЕ МЕНЮ:\n1. Постановка задачи (условие).\n2. Работа со списком. \n3. Общие сведения о программе.\n0. Выйти из программы.";
    	mainMenu = InputNumberFromConsole(0, 3, "\n\nВЫБЕРИТЕ ПУНКТ МЕНЮ: ");
		system("cls"); //очищает консоль
		switch (mainMenu) 
		{
			case 1: //Вывод условия задания
				cout << "29 ВАРИАНТ.\nНаписать программу, регистрирующую следующие сведения о посетителях поликлиники: Ф.И.О., дата рождения, номер полиса, диагноз, Ф.И.О. лечащего врача, дата посещения.\nОпределить нагрузку каждого врача, выдать статистику по заболеваниям, сформировать список пациентов, страдающих хроническими заболеваниями (т.е. обращавшихся к врачу более 3 раз в течение года с одним и тем же диагнозом).\n"; 
				break;
			case 2: //Действия задачи
				do{
					printList (head, &head);
					cout << "РАБОТА СО СПИСКОМ:\n1. Добавить элемент списка.\n2. Изменить элемент списка. \n3. Удалить элемент списка.\n4. Сохранить список в файл.\n5. Открыть файл со списком.\nЗАДАНИЯ:\n6. Определить нагрузку каждого врача.\n7. Выдать статистику по заболеваниям.\n8. Сформировать список пациентов, страдающих хроническими заболеваниями.\n0. Выход в главное меню.";
					menu = InputNumberFromConsole(0, 8, "\n\nВЫБЕРИТЕ ПУНКТ МЕНЮ: ");
					system("cls");
					switch (menu)
					{
						case 1: // Добавить элемент списка
							addListByNumber(&head);
							system("cls");
							break;
						case 2: // Изменить элемент списка
							number2 = InputNumberFromConsole(1, 99, "ВВЕДИТЕ НОМЕР ДЛЯ ИЗМЕНЕНИЯ: ");
							if (delByNumber(&head, number2) == false){
								cout << "Такого элемента не существует. Введите правильный номер элемента.\n\n";
								break;
							}
							number = 0;
							addListByNumber(&head);
							system("cls");
							break;
						case 3: // Удалить элемент списка
							number1 = InputNumberFromConsole(1, 99, "ВВЕДИТЕ НОМЕР ДЛЯ УДАЛЕНИЯ: ");
							if (delByNumber(&head, number1) == false){
								cout << "Такого элемента не существует. Введите правильный номер элемента.\n\n";
							}
							number = 0;
							break;
						case 4: // Сохранить в файл список
							saveList(&head, head);
							break;
						case 5: // Открыть файл
							openList(&head, head);
							break;
						case 6: // Нагрузка каждого врача
							WorkLoad1 (head, &head);
							break;
						case 7: // Статистика заболеваний
							WorkLoad2 (head, &head);
							break;
						case 8: // Список пациентов с хроническими
							WorkLoad3 (head, &head);
							break;
						case 0:
							check1 = false; //выход в главное меню
							system("cls");
							break;
					}
				} while (check1);
				break;
			case 3: //руководство и информация
				do{
					cout << "ОБЩИЕ СВЕДЕНИЯ О ПРОГРАММЕ:\n1. Руководство пользователя.\n2. Информация о программе. \n0. Выйти в главное меню.";
					menu1 = InputNumberFromConsole(0, 2, "\n\nВЫБЕРИТЕ ПУНКТ МЕНЮ: ");
					system("cls");
					switch (menu1)
					{
						case 1: // Руководство
							openGuide();
							break;
						case 2: // Информация
							cout << "ИНФОРМАЦИЯ О ПРОГРАММЕ:\nBaseOfPolyclinic\n15.03.2022\nCopyright © 2022 AnastasiaArbakova. All rights reserved.\nРоссия, г. Иркутск.\nПочта:arbakova.nastya@gmail.ru\n\n";
							break;
						case 0: //Выход в гл меню
							check2 = false;
		    			    system("cls");
							break;
					}
	    		} while(check2);
     			break;
			case 0: // Выход из программы
				check = false;
				system("cls");
				break;
		}
	} while(check);
	return 0;
}
