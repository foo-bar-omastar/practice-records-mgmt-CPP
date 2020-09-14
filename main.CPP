#include<fstream.h>
#include<conio.h>
#include<stdio.h>      //Included for remove and rename functions...
#include<string.h>
#include<dos.h>        //Included for delay function...
#include<graphics.h>

void welcomescreen()

{

	gotoxy(31,5);cout<<"PATIENT CARE"<<endl<<endl;
	gotoxy(30,7);cout<<"Hospital Management System"<<endl<<endl;
	gotoxy(34,10);cout<<"24x7 Service"<<endl;
	delay(3000);
	clrscr();

}

class employee
{
	char name[50], sex, dept[30];
	long age, sal, ino;
public:
	void menu();
	void enter();
	void init();
	void search();
	void del();
	void modify();
	void dispp();
}obj2;

void employee :: menu()
{
	int ch;
	do
	{
	clrscr();
	cout<<"Welcome to Employee Database\n\n";
	cout<<"Enter the choice number"<<endl;
	cout<<"1 : New Employee Registration"<<endl;
	cout<<"2 : View Details of Employee(s)"<<endl;
	cout<<"3 : Delete an Employee Account"<<endl;
	cout<<"4 : Modify an Employee Account"<<endl;
	cout<<"5 : Return to Main Menu"<<endl;
	cin>>ch;
	switch(ch)
	{
		case 1: enter();
			break;
		case 2: search();
			break;
		case 3: del();
			break;
		case 4: modify();
			break;
		case 5: return;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	}while(ch != 5);
}

void employee :: enter()
{
	fstream fout;
	fout.open("EMP.txt",ios::out|ios::app);
	char ch='y';
	while(ch != 'n' && ch != 'N')
	{
		cin.get();
		init();
		fout.write((char*)&obj2,sizeof(obj2));
		cout<<"Want to add more records (y/n) : ";
		cin>>ch;
	}
	fout.close();
	return;
}

void employee :: init()
{
	cout<<"Enter the following information"<<endl;
	cout<<"Enter NAME : ";
	cin.getline(name,50);
	cout<<"Enter ID No. : ";
	cin>>ino;
	cout<<"Enter AGE : ";
	cin>>age;
	cout<<"Enter SEX (M/F) : ";
	cin>>sex;
	cin.get();
	cout<<"Enter DEPARTMENT NAME : ";
	cin.getline(dept,30);
	cout<<"Enter the SALARY : ";
	cin>>sal;
}

void employee :: search()
{
	char namet[50];
	long idt;
	int ch;
	int ii = 0;
	cout<<endl<<endl<<"Enter the choice number"<<endl;
	cout<<"1 : SEARCH BY NAME"<<endl;
	cout<<"2 : SEARCH BY ID"<<endl;
	cout<<"3 : DISPLAY ALL"<<endl;
	cout<<"4 : EXIT"<<endl;
	cin>>ch;
	fstream fin;
	fin.open("EMP.txt",ios::in);
	if(!fin)
	{
		cout<<endl<<endl<<"No Records Saved";
		getch();
		return;
	}
	fin.seekg(0,ios::beg);
	switch(ch)
	{
		case 1: cout<<"Enter Name : ";
			gets(namet);
			while(!fin.eof())
			{
				fin.read((char*)&obj2,sizeof(obj2));
				if(strcmp(namet,name) == 0 && !fin.eof())
				{
					dispp();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 2: cout<<"Enter ID No. : ";
			cin>>idt;
			while(!fin.eof())
			{
				fin.read((char*)&obj2,sizeof(obj2));
				if(idt == ino && !fin.eof())
				{
					dispp();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 3: while(!fin.eof())
			{
				fin.read((char*)&obj2,sizeof(obj2));
				if(!fin.eof())
				{
					dispp();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 4: break;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	fin.close();
	return;
}

void employee :: dispp()
{
	cout<<endl;
	cout<<"NAME       : "<<name<<endl;
	cout<<"ID No      : "<<ino<<endl;
	cout<<"AGE        : "<<age<<endl;
	cout<<"SEX        : "<<sex<<endl;
	cout<<"DEPARTMENT : "<<dept<<endl;
	cout<<"SALARY     : "<<sal<<endl;
}

void employee :: del()
{
	char namet[50];
	long idt;
	int ch;
	int ii = 0;
	cout<<endl<<endl<<"Enter the choice number"<<endl;
	cout<<"1 : SEARCH BY NAME"<<endl;
	cout<<"2 : SEARCH BY ID"<<endl;
	cout<<"3 : EXIT"<<endl;
	cin>>ch;
	fstream fin, fout;
	fin.open("EMP.txt", ios::in);
	if(!fin)
	{
		cout<<endl<<endl<<"No Records Saved";
		getch();
		return;
	}
	fin.seekg(0,ios::beg);
	fout.open("temp.txt", ios::out);
	fout.seekp(0,ios::beg);
	switch(ch)
	{
		case 1: cout<<"Enter Name : ";
			gets(namet);
			while(!fin.eof())
			{
				fin.read((char*)&obj2,sizeof(obj2));
				if(strcmp(namet,name) != 0 && !fin.eof())
					fout.write((char*)&obj2,sizeof(obj2));
				else
				{
					ii = 1;
					cout<<endl<<"RECORD DELETED";
				}

			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 2: cout<<"Enter ID No. : ";
			cin>>idt;
			while(!fin.eof())
			{
				fin.read((char*)&obj2,sizeof(obj2));
				if(idt != ino && !fin.eof())
					fout.write((char*)&obj2,sizeof(obj2));
				else
				{
					ii = 1;
					cout<<endl<<"RECORD DELETED";
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 3: break;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	fin.close();
	fout.close();
	remove("EMP.txt");
	rename("temp.txt","EMP.txt");
	return;
}

void employee :: modify()
{
	char namet[50];
	long idt;
	int ch;
	int ii = 0;
	cout<<endl<<endl<<"Enter the choice number"<<endl;
	cout<<"1 : SEARCH BY NAME"<<endl;
	cout<<"2 : SEARCH BY ID"<<endl;
	cout<<"3 : EXIT"<<endl;
	cin>>ch;
	fstream fin, fout;
	fin.open("EMP.txt", ios::in);
	if(!fin)
	{
		cout<<endl<<endl<<"No Records Saved";
		getch();
		return;
	}
	fin.seekg(0,ios::beg);
	fout.open("temp.txt", ios::out);
	fout.seekp(0,ios::beg);
	switch(ch)
	{
		case 1: cout<<"Enter Name : ";
			gets(namet);
			while(!fin.eof())
			{
				fin.read((char*)&obj2,sizeof(obj2));
				if(strcmp(namet,name) == 0 && !fin.eof())
				{
					ii = 1;
					init();
					cout<<endl<<"RECORD MODIFIED";
				}
				if(!fin.eof())
					fout.write((char*)&obj2,sizeof(obj2));
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 2: cout<<"Enter ID No. : ";
			cin>>idt;
			cin.get();
			while(!fin.eof())
			{
				fin.read((char*)&obj2,sizeof(obj2));
				if(idt == ino && !fin.eof())
				{
					ii = 1;
					init();
					cout<<endl<<"RECORD MODIFIED";
				}
				if(!fin.eof())
					fout.write((char*)&obj2,sizeof(obj2));
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 3: break;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	fin.close();
	fout.close();
	remove("EMP.txt");
	rename("temp.txt","EMP.txt");
	return;
}

class doctor
{
	char name[50], sex, dept[30], spe[50], reg[20];
	long age, ino;
public:
	void menu();
	void enter();
	void init();
	void search();
	void del();
	void modify();
	void dispp();
}obj3;

void doctor :: menu()
{
	int ch;
	do
	{
	clrscr();
	cout<<"Welcome to Doctor Database\n\n";
	cout<<"Enter the choice number"<<endl;
	cout<<"1 : New Doctor Registration"<<endl;
	cout<<"2 : View Details of Doctor(s)"<<endl;
	cout<<"3 : Delete an Doctor Account"<<endl;
	cout<<"4 : Modify an Doctor Account"<<endl;
	cout<<"5 : Return to Main Menu"<<endl;
	cin>>ch;
	switch(ch)
	{
		case 1: enter();
			break;
		case 2: search();
			break;
		case 3: del();
			break;
		case 4: modify();
			break;
		case 5: return;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	}while(ch != 5);
}

void doctor :: enter()
{
	fstream fout;
	fout.open("DOCTOR.txt",ios::out|ios::app);
	char ch='y';
	while(ch != 'n' && ch != 'N')
	{
		cin.get();
		init();
		fout.write((char*)&obj3,sizeof(obj3));
		cout<<"Want to add more records (y/n) : ";
		cin>>ch;
	}
	fout.close();
	return;
}

void doctor :: init()
{
	cout<<"Enter the following information"<<endl;
	cout<<"Enter NAME : Dr. ";
	cin.getline(name,50);
	cout<<"Enter ID No. : ";
	cin>>ino;
	cout<<"Enter AGE : ";
	cin>>age;
	cout<<"Enter SEX (M/F) : ";
	cin>>sex;
	cin.get();
	cout<<"Enter DEPARTMENT NAME : ";
	cin.getline(dept,30);
	cout<<"Enter the Specialization : ";
	cin.getline(spe,50);
	cout<<"Enter the Registration No. : ";
	cin.getline(reg,20);
}

void doctor :: search()
{
	char namet[50];
	long idt;
	int ch;
	int ii = 0;
	cout<<endl<<endl<<"Enter the choice number"<<endl;
	cout<<"1 : SEARCH BY NAME"<<endl;
	cout<<"2 : SEARCH BY ID"<<endl;
	cout<<"3 : DISPLAY ALL"<<endl;
	cout<<"4 : EXIT"<<endl;
	cin>>ch;
	fstream fin;
	fin.open("DOCTOR.txt",ios::in);
	if(!fin)
	{
		cout<<endl<<endl<<"No Records Saved";
		getch();
		return;
	}
	fin.seekg(0,ios::beg);
	switch(ch)
	{
		case 1: cout<<"Enter Name : ";

			gets(namet);
			while(!fin.eof())
			{
				fin.read((char*)&obj3,sizeof(obj3));
				if(strcmp(namet,name) == 0 && !fin.eof())
				{
					dispp();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 2: cout<<"Enter ID No. : ";
			cin>>idt;
			while(!fin.eof())
			{
				fin.read((char*)&obj3,sizeof(obj3));
				if(idt == ino && !fin.eof())
				{
					dispp();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 3: while(!fin.eof())
			{
				fin.read((char*)&obj3,sizeof(obj3));
				if(!fin.eof())
				{
					dispp();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 4: break;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	fin.close();
	return;
}

void doctor :: dispp()
{
	cout<<endl;
	cout<<"NAME             : Dr. "<<name<<endl;
	cout<<"ID No            : "<<ino<<endl;
	cout<<"AGE              : "<<age<<endl;
	cout<<"SEX              : "<<sex<<endl;
	cout<<"DEPARTMENT       : "<<dept<<endl;
	cout<<"SPECIALIZATION   : "<<spe<<endl;
	cout<<"REGISTRATION NO. : "<<reg<<endl;
}

void doctor :: del()
{
	char namet[50];
	long idt;
	int ch;
	int ii = 0;
	cout<<endl<<endl<<"Enter the choice number"<<endl;
	cout<<"1 : SEARCH BY NAME"<<endl;
	cout<<"2 : SEARCH BY ID"<<endl;
	cout<<"3 : EXIT"<<endl;
	cin>>ch;
	fstream fin, fout;
	fin.open("DOCTOR.txt", ios::in);
	if(!fin)
	{
		cout<<endl<<endl<<"No Records Saved";
		getch();
		return;
	}
	fin.seekg(0,ios::beg);
	fout.open("temp.txt", ios::out);
	fout.seekp(0,ios::beg);
	switch(ch)
	{
		case 1: cout<<"Enter Name : ";
			gets(namet);
			while(!fin.eof())
			{
				fin.read((char*)&obj3,sizeof(obj3));
				if(strcmp(namet,name) != 0 && !fin.eof())
					fout.write((char*)&obj3,sizeof(obj3));
				else
				{
					ii = 1;
					cout<<endl<<"RECORD DELETED";
				}

			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 2: cout<<"Enter ID No. : ";
			cin>>idt;
			while(!fin.eof())
			{
				fin.read((char*)&obj3,sizeof(obj3));
				if(idt != ino && !fin.eof())
					fout.write((char*)&obj3,sizeof(obj3));
				else
				{
					ii = 1;
					cout<<endl<<"RECORD DELETED";
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 3: break;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	fin.close();
	fout.close();
	remove("DOCTOR.txt");
	rename("temp.txt","DOCTOR.txt");
	return;
}

void doctor :: modify()
{
	char namet[50];
	long idt;
	int ch;
	int ii = 0;
	cout<<endl<<endl<<"Enter the choice number"<<endl;
	cout<<"1 : SEARCH BY NAME"<<endl;
	cout<<"2 : SEARCH BY ID"<<endl;
	cout<<"3 : EXIT"<<endl;
	cin>>ch;
	fstream fin, fout;
	fin.open("DOCTOR.txt", ios::in);
	if(!fin)
	{
		cout<<endl<<endl<<"No Records Saved";
		getch();
		return;
	}
	fin.seekg(0,ios::beg);
	fout.open("temp.txt", ios::out);
	fout.seekp(0,ios::beg);
	switch(ch)
	{
		case 1: cout<<"Enter Name : ";
			gets(namet);
			while(!fin.eof())
			{
				fin.read((char*)&obj3,sizeof(obj3));
				if(strcmp(namet,name) == 0 && !fin.eof())
				{
					ii = 1;
					init();
					cout<<endl<<"RECORD MODIFIED";
				}
				if(!fin.eof())
					fout.write((char*)&obj3,sizeof(obj3));
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 2: cout<<"Enter ID No. : ";
			cin>>idt;
			cin.get();
			while(!fin.eof())
			{
				fin.read((char*)&obj3,sizeof(obj3));
				if(idt == ino && !fin.eof())
				{
					ii = 1;
					init();
					cout<<endl<<"RECORD MODIFIED";
				}
				if(!fin.eof())
					fout.write((char*)&obj3,sizeof(obj3));
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 3: break;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	fin.close();
	fout.close();
	remove("DOCTOR.txt");
	rename("temp.txt","DOCTOR.txt");
	return;
}

class patient
{
	char name[50], sex, ailm[101], dept[30], doc[50], date[12];
	long age, bno;
	char room[10],food[10];
	float n,bill;
public:
	void menu();
	void enter();
	void init();
	void search();
	void del();
	void modify();
	void dispp();
	void calcbill();
	void calc();
}obj1;

void patient :: menu()
{
	int ch;
	do
	{
	clrscr();
	cout<<"Welcome to Patient Database\n\n";
	cout<<"Enter the choice number"<<endl;
	cout<<"1 : New Patient Registration"<<endl;
	cout<<"2 : View Details of Patient(s)"<<endl;
	cout<<"3 : Delete an Patient Account"<<endl;
	cout<<"4 : Modify an Patient Account"<<endl;
	cout<<"5 : View bill of Patient"<<endl;
	cout<<"6 : Return to Main Menu"<<endl;
	cin>>ch;
	switch(ch)
	{
		case 1: enter();
			break;
		case 2: search();
			break;
		case 3: del();
			break;
		case 4: modify();
			break;
		case 5: calcbill();
			break;
		case 6: return;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	}while(ch != 6);
}

void patient :: enter()
{
	fstream fout;
	fout.open("PATIENTS.txt",ios::out|ios::app);
	char ch='y';
	while(ch != 'n' && ch != 'N')
	{
		cin.get();
		init();
		fout.write((char*)&obj1,sizeof(obj1));
		cout<<"Want to add more records (y/n) : ";
		cin>>ch;
	}
	fout.close();
	return;
}

void patient :: init()
{
	cout<<"Enter the following information"<<endl;
	cout<<"Enter NAME : ";
	cin.getline(name,50);
	cout<<"Enter Patient BED No. : ";
	cin>>bno;
	cout<<"Enter AGE : ";
	cin>>age;
	cout<<"Enter SEX (M/F) : ";
	cin>>sex;
	cin.get();
	cout<<"Enter Ailment (max 100 char) : ";
	cin.getline(ailm,101);
	cout<<"Enter DEPARTMENT NAME : ";
	cin.getline(dept,30);
	cout<<"Enter Doctor's Name : Dr. ";
	cin.getline(doc,50);
	cout<<"Date of Registration (DD/MM/YYYY) : ";
	cin.getline(date,12);
	cout<<"Food(veg/nonveg) : ";
	cin.getline(food,10);
	cout<<"Type of room(VIP/ICU/General) : ";
	cin.getline(room,10);
}

void patient :: search()
{
	char namet[50];
	long bdt;
	int ch;
	int ii = 0;
	cout<<endl<<endl<<"Enter the choice number"<<endl;
	cout<<"1 : SEARCH BY NAME"<<endl;
	cout<<"2 : SEARCH BY BED NO."<<endl;
	cout<<"3 : DISPLAY ALL"<<endl;
	cout<<"4 : EXIT"<<endl;
	cin>>ch;
	fstream fin;
	fin.open("PATIENTS.txt",ios::in);
	if(!fin)
	{
		cout<<endl<<endl<<"No Records Saved";
		getch();
		return;
	}
	fin.seekg(0,ios::beg);
	switch(ch)
	{
		case 1: cout<<"Enter Name : ";
			gets(namet);
			while(!fin.eof())
			{
				fin.read((char*)&obj1,sizeof(obj1));
				if(strcmp(namet,name) == 0 && !fin.eof())
				{
					dispp();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 2: cout<<"Enter BED No. : ";
			cin>>bdt;
			while(!fin.eof())
			{
				fin.read((char*)&obj1,sizeof(obj1));
				if(bdt == bno && !fin.eof())
				{
					dispp();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 3: while(!fin.eof())
			{
				fin.read((char*)&obj1,sizeof(obj1));
				if(!fin.eof())
				{
					dispp();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 4: break;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	fin.close();
	return;
}

void patient :: dispp()
{
	cout<<endl;
	cout<<"NAME         : "<<name<<endl;
	cout<<"BED No       : "<<bno<<endl;
	cout<<"AGE          : "<<age<<endl;
	cout<<"SEX          : "<<sex<<endl;
	cout<<"AILMENT      : "<<ailm<<endl;
	cout<<"DEPARTMENT   : "<<dept<<endl;
	cout<<"DOCTOR       : Dr. "<<doc<<endl;
	cout<<"DATE OF REGISTRATION : "<<date<<endl;
	cout<<"ROOM         : "<<room<<endl;
	cout<<"FOOD         : "<<food<<endl;
}

void patient :: del()
{
	char namet[50];
	long bdt;
	int ch;
	int ii = 0;
	cout<<endl<<endl<<"Enter the choice number"<<endl;
	cout<<"1 : SEARCH BY NAME"<<endl;
	cout<<"2 : SEARCH BY BED NO."<<endl;
	cout<<"3 : EXIT"<<endl;
	cin>>ch;
	fstream fin, fout;
	fin.open("PATIENTS.txt", ios::in);
	if(!fin)
	{
		cout<<endl<<endl<<"No Records Saved";
		getch();
		return;
	}
	fin.seekg(0,ios::beg);
	fout.open("temp.txt", ios::out);
	fout.seekp(0,ios::beg);
	switch(ch)
	{
		case 1: cout<<"Enter Name : ";
			gets(namet);
			while(!fin.eof())
			{
				fin.read((char*)&obj1,sizeof(obj1));
				if(strcmp(namet,name) != 0 && !fin.eof())
					fout.write((char*)&obj1,sizeof(obj1));
				else
				{
					ii = 1;
					cout<<endl<<"RECORD DELETED";
				}

			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 2: cout<<"Enter BED No. : ";
			cin>>bdt;
			while(!fin.eof())
			{
				fin.read((char*)&obj1,sizeof(obj1));
				if(bdt != bno && !fin.eof())
					fout.write((char*)&obj1,sizeof(obj1));
				else
				{
					ii = 1;
					cout<<endl<<"RECORD DELETED";
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 3: break;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	fin.close();
	fout.close();
	remove("PATIENTS.txt");
	rename("temp.txt","PATIENTS.txt");
	return;
}

void patient :: modify()
{
	char namet[50];
	long bdt;
	int ch;
	int ii = 0;
	cout<<endl<<endl<<"Enter the choice number"<<endl;
	cout<<"1 : SEARCH BY NAME"<<endl;
	cout<<"2 : SEARCH BY BED NO."<<endl;
	cout<<"3 : EXIT"<<endl;
	cin>>ch;
	fstream fin, fout;
	fin.open("PATIENTS.txt", ios::in);
	if(!fin)
	{
		cout<<endl<<endl<<"No Records Saved";
		getch();
		return;
	}
	fin.seekg(0,ios::beg);
	fout.open("temp.txt", ios::out);
	fout.seekp(0,ios::beg);
	switch(ch)
	{
		case 1: cout<<"Enter Name : ";
			gets(namet);
			while(!fin.eof())
			{
				fin.read((char*)&obj1,sizeof(obj1));
				if(strcmp(namet,name) == 0 && !fin.eof())
				{
					ii = 1;
					init();
					cout<<endl<<"RECORD MODIFIED";
				}
				if(!fin.eof())
					fout.write((char*)&obj1,sizeof(obj1));
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 2: cout<<"Enter BED No. : ";
			cin>>bdt;
			cin.get();
			while(!fin.eof())
			{
				fin.read((char*)&obj1,sizeof(obj1));
				if(bdt == bno && !fin.eof())
				{
					ii = 1;
					init();
					cout<<endl<<"RECORD MODIFIED";
				}
				if(!fin.eof())
					fout.write((char*)&obj1,sizeof(obj1));
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 3: break;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	fin.close();
	fout.close();
	remove("PATIENTS.txt");
	rename("temp.txt","PATIENTS.txt");
	return;
}
void patient :: calcbill()
{
	char namet[50];
	long bdt;
	int ch;
	int ii = 0;
	cout<<endl<<endl<<"Enter the choice number"<<endl;
	cout<<"1 : SEARCH BY NAME"<<endl;
	cout<<"2 : SEARCH BY BED NO."<<endl;
	cout<<"3 : EXIT"<<endl;
	cin>>ch;
	fstream fin;
	fin.open("PATIENTS.txt",ios::in);
	if(!fin)
	{
		cout<<endl<<endl<<"No Records Saved";
		getch();
		return;
	}
	fin.seekg(0,ios::beg);
	switch(ch)
	{
		case 1: cout<<"Enter Name : ";
			gets(namet);
			while(!fin.eof())
			{
				fin.read((char*)&obj1,sizeof(obj1));
				if(strcmp(namet,name) == 0 && !fin.eof())
				{
					calc();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
		case 2: cout<<"Enter BED No. : ";
			cin>>bdt;
			while(!fin.eof())
			{
				fin.read((char*)&obj1,sizeof(obj1));
				if(bdt == bno && !fin.eof())
				{
					calc();
					ii = 1;
				}
			}
			if(ii == 0)
				cout<<endl<<"NOT FOUND";
			getch();
			break;
	      case 3: break;
		default: cout<<"INVALID CHOICE!!!!"<<endl<<"Press any key to continue";
			getch();
	}
	fin.close();
	return;
}
void patient :: calc()
{
	cout<<"\nEnter the number of days admitted : ";
	cin>>n;
	clrscr();
	cout<<"\n\t\t\tBILL\n";
	cout<<"\nDoctor's fee : "<<n*1000;
	bill+=n*1000;
	cout<<"\nService charges : "<<n*100;
	bill+=n*100;
	    if(strcmp("veg",food)==0)
		  {
			   cout<<"\nFood charges : "<<n*500;
			   bill+=n*500;
		  }
	else if(strcmp("nonveg",food)==0)
		  {
			   cout<<"\nFood charges : "<<n*700;
			   bill+=n*700;
		  }
	     if(strcmp("VIP",room)==0)
		  {
			   cout<<"\nRoom charges are : "<<n*3000;
			   bill+=n*3000;
		  }
	else
	     if(strcmp("ICU",room)==0)
		  {
			   cout<<"\nRoom charges are : "<<n*5000;
			   bill+=n*5000;
		  }
	else if(strcmp("General",room)==0)
		  {
			   cout<<"\nRoom charges are : "<<n*1000;
			   bill+=n*1000;
		  }
			   cout<<"\n\n\n\t\t\tTOTAL BILL  : "<<bill;
}
void main()
{       textcolor(RED);
	textbackground(LIGHTGRAY);
	clrscr();
	welcomescreen();
	int no;
	do
	{
		clrscr();
		gotoxy(28,2);
		cout<<"ENTER THE CHOICE NUMBER"<<endl;
		gotoxy(29,8);
		cout<<"1 : Paitent's Database"<<endl;
		gotoxy(29,10);
		cout<<"2 : Doctor's Database"<<endl;
		gotoxy(29,12);
		cout<<"3 : Staff's Database"<<endl;
		gotoxy(29,14);
		cout<<"4 : EXIT";
		gotoxy(29,16);
		cin>>no;
		switch(no)
		{
			case 1: obj1.menu();
				break;
			case 2: obj3.menu();
				break;
			case 3: obj2.menu();
				break;
			case 4: break;
			default: cout<<"INVALID CHOICE!!!!"<<endl;
		}
	}while(no!=4);
	getch();
}