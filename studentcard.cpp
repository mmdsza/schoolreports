#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ncurses.h>
using namespace std;
class student{
    int rollno;
    char name[50];
    int notaport, notaing, notamat;
    float media;
    char grade;
    int std;
    void calcular(){
        media = (notaport+notaing+notamat)/3.0;
        if(media >=60)
            grade = 'A';
        else if(media >=50 && media<60)
            grade = 'B';
        else if(media >=33 && media <50)
            grade = 'C';
        else
            grade ='F';
    }
public:
    void getdata(){
        cout << "\n Enter the roll number of the student: " << endl;
        cin >> rollno;
        cout << "\n Enter the name of the student: " << endl;
        cin >> name;
        cout << "\n Nota de PT" << endl;
        cin >>notaport;
        cout << "\n Nota Ing" << endl;
        cin >> notaing;
        cout << "\n nota mat" << endl;
        cin >> notamat;
        calcular();
    }   
    void showdata()
    {
        cout << "Student roll" << rollno << endl;
        cout << "student name: " << name << endl;
        cout << "nota pt: " << notaport << endl;
        cout << "nota ing: " <<notaing << endl;
        cout << "nota mat: " << notamat << endl;
        cout << "Media: "  << media << endl;
        cout << "Grade: " <<grade <<endl;

    } 
    void show_tabular(){
        cout<<rollno<<setw(12)<<name<<setw(10)<<notaport<<setw(3)<<notamat<<setw(3)<<notaing<<setw(3)<<media<<"   "<<grade<<endl;
    }
    int retrollno(){
        return rollno;
    }    
};


// declaring global objects // 
fstream fp;
student st;

//writing a file 

void write_student(){
    fp.open("student.dat", ios::out|ios::app);
    st.getdata();
    fp.write((char*)&st, sizeof(student));
    fp.close();
    cout << "\n Student record has been created";
    getch();
    }
// Displaying all data
void display_all(){
    system("clear");
    cout << "\n Display all records " << endl;
    fp.open("student.dat", ios::in);
    while(fp.read((char*)&st, sizeof(student))){
        st.showdata();
        cout<<"\n\n=============\n";
        system("clear");
    }
    fp.close();
    getch();
}

// read specific from file

void display_specific(int n){
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st, sizeof(student))){
        if(st.retrollno()==n){
            system("clear");
            st.showdata();
            flag=1;
        }
    }
    fp.close();
    if(flag==0){
        cout << "\n Record doesn't exist" << endl;
    getch();
    }
}

// modify record

void modify_student(){
    int no, found=0;
    system("clear");
    cout << "\n To modify " << endl;
    cout << "\n Please enter the student roll number" << endl;
    cin >> no;
    fp.open("student.dat", ios::in|ios::out);
    while(fp.read((char*)&st, sizeof(student))&& found ==0){
        if(st.retrollno()==no){
            st.showdata();
            cout << "\n Please enter the new details of the student" <<endl;
            st.getdata();
            unsigned int multi = abs(-1);
            int pos =multi*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout << "\n Records updated" << endl;
            found=1;
        }
    }
    fp.close();
    if(found==0){
        cout<< "\n Record not found"<< endl;
    }
    getch();
}


// delete record

void delete_student(){
    int no;
    system("clear");
    cout << "\n Delete Records" << endl;
    cout << "\n Enter the student's roll number" << endl;
    cin >> no;
    fp.open("student.dat", ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st, sizeof(student))){
        if(st.retrollno()!=no){
            fp2.write((char*)&st, sizeof(student));
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat","student.dat");
    cout << "Record deleted" <<endl;
    getch();
}

// Displaying stuff

void class_result(){
    system("clear");
    fp.open("student.dat",ios::in);
    if(!fp){
        cout << "File missing"<<endl;
        getch();
        exit(0);
        }
    cout << "\n All student records" << endl;
    cout << "Roll Number,  Name,      Port, Ing, Mat, Grade" << endl;
    while(fp.read((char*)&st,sizeof(student))){
        st.show_tabular();
    }
    fp.close();
    getch();
}

//menu

void result(){
    int ans, rollno;
    char ch;
    system("clear");
    cout << "\n Result Menu" << endl;
    cout << "1. Class Result \n 2. Student Report Card \n 3. Main Menu" <<endl;
    cin >> ans;
    switch(ans){
        case 1:
            class_result();
            break;
        case 2:
            do {
                system("clear");
                char ans;
                cout <<"\n Enter student's roll number" << endl;
                cin >> rollno;
                display_specific(rollno);
                cout << "\n more results?(y/n)?" << endl;
                cin >> ans;
            }
            while(ans=='y'||ans=='Y');
            break;
        case 3:
            break;
        default:
            cout << "\a";
    }   

}

void entry_menu()
{
    system("clear");
    char ch2;
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
    ch2=getch();
    cout << "\n You chose: " << ch2 << endl;
    switch(ch2)
    {
    case '1':
        system("clear");
        write_student();
        break;
    case '2':
        display_all();
        break;
    case '3':
        int num;
        system("clear");
        cout<<"\n\n\tPlease Enter The roll number ";
        cin>>num;
        display_specific(num);
        break;
    case '4':
        modify_student();
        break;
    case '5':
        delete_student();
        break;
    case '6':
        break;
    default:
        cout<<"\a";
        entry_menu();
    }
}


void intro(){
    system("clear");
    cout << "STUDENT REPORT CARD PROJECT" << endl;
    cout << "MADE BY: MAURICIO" <<endl;
    getch();
}

int main()
{
    char ch;
    intro();
    do
    {
        system("clear");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. RESULT MENU";
        cout<<"\n\n\t02. ENTRY/EDIT MENU";
        cout<<"\n\n\t03. EXIT";
        cout<<"\n\n\tPlease Select Your Option (1-3) ";
        ch=getch();
        cout << "You chose: " << ch << endl;
        switch(ch)
        {
        case '1':
            system("clear");
            result();
            break;
        case '2':
            entry_menu();
            break;
        case '3':
            exit(0);
        default :
            cout<<"\a";
        }
    }
    while(ch!='3');
    return 0;
}