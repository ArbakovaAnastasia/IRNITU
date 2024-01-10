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
	int numberList; //���������� �����
	string FIOpatient; //��� ��������
	int birthDay; //���� � ��������
	int birthMonth; //����� � ��������
	int birthYear; //��� � ��������
	int policyNumber; //����� ������
	string diagnosis; // �������
	string FIOdoctor; //��� �������
	int visitDay; //���� ���������
	int visitMonth; //����� ���������
	int visitYear; //��� ���������
	
	polyclinic* next;
};
int InputNumberFromConsole(int min, int max, string ask)  //���� ����� ��� ���� � ���������
{
    int number;
    bool check;
    do{
        cout << ask;
        check = false;
        cin >> number;
        if (cin.peek() != '\n'){
            cout << "������. ���������� �����.\n" << endl;
            cin.clear();
            cin.ignore(2147483647, '\n');
            check = true;
        }
        if (!check && (number < min || number > max)){
            cout << "������������ ��������. ���������� �����.\n";
            cin.clear();
            cin.ignore(2147483647, '\n');
            check = true;
        }
    } while (check);
    return number;
}
void openGuide(){ //�������� ����������� �� ���������� �����
	cout<<"����������� ������������:\n";
	ifstream file;
	file.open("Guide.txt");
	if (!file){
		cout<<"����������� ���� ��� ��������!\n";
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
void addListByNumber(polyclinic** pHead) //���������� �������� � ���������
{
	cout << "���������� �������� � ������\n";
	number++;
	
	cout<<"�������: ";
	cin.ignore(332767,'\n');
	getline(cin,fioP);
	
	cout<<"���� ��������(����, �����, ���):\n";
	dayP = InputNumberFromConsole(1, 31, "����: ");
	monthP = InputNumberFromConsole(1, 12, "�����: ");
	yearP = InputNumberFromConsole(1900, 2022, "���: ");
	int policy=9999999999999999;
	policyP = InputNumberFromConsole(1, policy, "����� ������: ");
	
	cout<<"�������: ";
	cin.ignore(332767,'\n');
	getline(cin,diagnosisP);
	
	dayVisit = InputNumberFromConsole(1, 31, "����: ");
	monthVisit = InputNumberFromConsole(1, 12, "�����: ");
	yearVisit = InputNumberFromConsole(1900, 2022, "���: ");
	
	cout<<"������: ";
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
void printList (polyclinic* head, polyclinic** pHead) //����� ���������
{
	number=0;
	cout << "��������� ������:\n";
	if (*pHead==0){
		cout<<"������ ����.\n";
	}
	else{
		cout<<setw(2)<<"� "<<setw(12)<<"�������"<<setw(18)<<"���� ��������(��."<<setw(3)<<"��."<<setw(5)<<"����)"<<setw(13)<<"����� ������"<<setw(12)<<"�������"<<setw(13)<<"������"<<setw(19)<<"���� ���������(��."<<setw(3)<<"��."<<setw(5)<<"����)\n";
		while(head){
			number++;
			cout<<setw(2)<<number<<setw(12)<<head->FIOpatient<<setw(18)<<head->birthDay<<setw(3)<<head->birthMonth<<setw(5)<<head->birthYear<<setw(13)<<head->policyNumber<<setw(12)<<head->diagnosis<<setw(13)<<head->FIOdoctor<<setw(19)<<head->visitDay<<setw(3)<<head->visitMonth<<setw(5)<<head->visitYear<<"\n";
			head = head->next;
		}
	}
	cout<<endl;
}
int num(polyclinic** pHead) //��� �������� ������� ��������, ������� ���������� ��������� � ���������
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
int delByNumber(polyclinic** pHead, int number1) //�������� �� ������
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
void saveList(polyclinic** pHead, polyclinic* head){ //���������� ��������� � ����
	if (*pHead==0){
		cout<<"���������� ��������� ������ ������. (������ ����)\n";
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
void openList(polyclinic** pHead, polyclinic* head){ //�������� �����
	ifstream file;
	file.open("newfile.txt");
	if (!file){
		cout<<"����������� ���� ��� ��������!\n";
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
class wLoadOne{ //��� 1 ���������
	public:
		string FIOdoctor;
		int PatientCount=0;
		wLoadOne(string Doc){
			FIOdoctor=Doc;
			PatientCount=1;}
		void print(){
			cout<<"������ "<<FIOdoctor<<" ����� "<<PatientCount<<" ������� ���������.\n";}
};
void WorkLoad1 (polyclinic* head, polyclinic** pHead) //1 ��������� �� ������ �������� ������
{
	cout<< "�������� ������:\n";
	list <wLoadOne> loadList;
	list <wLoadOne> :: iterator i;
	if (*pHead==0){
		cout<<"������ ����.\n";
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
class wLoadTwo{ //��� 2 ���������
	public:
		string diagnosis;
		int diagnosisCount=0;
		wLoadTwo(string Dia){
			diagnosis=Dia;
			diagnosisCount=1;}
		void print(){
			cout<<"����������� "<<diagnosis<<" ��������� � ��������� "<<diagnosisCount<<" ���.\n";}
};
void WorkLoad2 (polyclinic* head, polyclinic** pHead) //2 ��������� �� ������ ���������� �� ������������
{
	cout<< "���������� �����������:\n";
	list <wLoadTwo> loadList;
	list <wLoadTwo> :: iterator i;
	if (*pHead==0){
		cout<<"������ ����.\n";
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
class wLoadThree{ //��� 3 ���������
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
			cout<<"����������� "<<diagnosis<<" ��������� � "<<FIOpatient<<" "<<diagnosisCount<<" ��� � ������� "<<visitYear<< " ����.\n";}
};
void WorkLoad3 (polyclinic* head, polyclinic** pHead) //3 ��������� �� ������ ����������� ����������� ���������
{
	cout<< "������ ��������� � ������������ �������������:\n";
	list <wLoadThree> loadList;
	list <wLoadThree> :: iterator i;
	if (*pHead==0){
		cout<<"������ ����.\n";
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
	SetConsoleCP(1251); //������� ���� � ������� �� ���� � �����
	SetConsoleOutputCP(1251);

	int mainMenu, menu, menu1;
	bool check = true, check1 = true, check2 = true;   //������ ��� do while ������������� ��� ������ �� ���������
	polyclinic* head = 0;
	int number1, number2;
	do{
    	cout << "\n������� ����:\n1. ���������� ������ (�������).\n2. ������ �� �������. \n3. ����� �������� � ���������.\n0. ����� �� ���������.";
    	mainMenu = InputNumberFromConsole(0, 3, "\n\n�������� ����� ����: ");
		system("cls"); //������� �������
		switch (mainMenu) 
		{
			case 1: //����� ������� �������
				cout << "29 �������.\n�������� ���������, �������������� ��������� �������� � ����������� �����������: �.�.�., ���� ��������, ����� ������, �������, �.�.�. �������� �����, ���� ���������.\n���������� �������� ������� �����, ������ ���������� �� ������������, ������������ ������ ���������, ���������� ������������ ������������� (�.�. ������������ � ����� ����� 3 ��� � ������� ���� � ����� � ��� �� ���������).\n"; 
				break;
			case 2: //�������� ������
				do{
					printList (head, &head);
					cout << "������ �� �������:\n1. �������� ������� ������.\n2. �������� ������� ������. \n3. ������� ������� ������.\n4. ��������� ������ � ����.\n5. ������� ���� �� �������.\n�������:\n6. ���������� �������� ������� �����.\n7. ������ ���������� �� ������������.\n8. ������������ ������ ���������, ���������� ������������ �������������.\n0. ����� � ������� ����.";
					menu = InputNumberFromConsole(0, 8, "\n\n�������� ����� ����: ");
					system("cls");
					switch (menu)
					{
						case 1: // �������� ������� ������
							addListByNumber(&head);
							system("cls");
							break;
						case 2: // �������� ������� ������
							number2 = InputNumberFromConsole(1, 99, "������� ����� ��� ���������: ");
							if (delByNumber(&head, number2) == false){
								cout << "������ �������� �� ����������. ������� ���������� ����� ��������.\n\n";
								break;
							}
							number = 0;
							addListByNumber(&head);
							system("cls");
							break;
						case 3: // ������� ������� ������
							number1 = InputNumberFromConsole(1, 99, "������� ����� ��� ��������: ");
							if (delByNumber(&head, number1) == false){
								cout << "������ �������� �� ����������. ������� ���������� ����� ��������.\n\n";
							}
							number = 0;
							break;
						case 4: // ��������� � ���� ������
							saveList(&head, head);
							break;
						case 5: // ������� ����
							openList(&head, head);
							break;
						case 6: // �������� ������� �����
							WorkLoad1 (head, &head);
							break;
						case 7: // ���������� �����������
							WorkLoad2 (head, &head);
							break;
						case 8: // ������ ��������� � ������������
							WorkLoad3 (head, &head);
							break;
						case 0:
							check1 = false; //����� � ������� ����
							system("cls");
							break;
					}
				} while (check1);
				break;
			case 3: //����������� � ����������
				do{
					cout << "����� �������� � ���������:\n1. ����������� ������������.\n2. ���������� � ���������. \n0. ����� � ������� ����.";
					menu1 = InputNumberFromConsole(0, 2, "\n\n�������� ����� ����: ");
					system("cls");
					switch (menu1)
					{
						case 1: // �����������
							openGuide();
							break;
						case 2: // ����������
							cout << "���������� � ���������:\nBaseOfPolyclinic\n15.03.2022\nCopyright � 2022 AnastasiaArbakova. All rights reserved.\n������, �. �������.\n�����:arbakova.nastya@gmail.ru\n\n";
							break;
						case 0: //����� � �� ����
							check2 = false;
		    			    system("cls");
							break;
					}
	    		} while(check2);
     			break;
			case 0: // ����� �� ���������
				check = false;
				system("cls");
				break;
		}
	} while(check);
	return 0;
}
