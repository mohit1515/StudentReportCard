#include <iostream>
#include <iomanip>
#include <cstdio>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#define clrscr() system("cls");
using namespace std;

//--------------------------------
//here we create a student class
//--------------------------------
class student
{
    unsigned int rollno;
    char name[30];
    int physics,chemistry,maths,english,computer_science;
    float per;
    char grade;
    //int std;

    void calculate()
    {
        per=(physics+chemistry+maths+english+computer_science)/5.0;
        if(per>=60)
            grade='A';
        else if(per>=50 && per<60)
            grade='B';
        else if(per>=33 && per<50)
            grade='C';
        else
            grade='F';
    }
public:
    void getstudentdata()
    {
        cout<<"\nEnter The roll number of student ";
        cin>>rollno;
        cout<<"\n\nEnter The Name of student ";
        cin>>name;// this method is used to get string value
        cout<<"\nEnter The marks in physics out of 100 : ";
        cin>>physics;
        cout<<"\nEnter The marks in chemistry out of 100 : ";
        cin>>chemistry;
        cout<<"\nEnter The marks in maths out of 100 : ";
        cin>>maths;
        cout<<"\nEnter The marks in English out of 100 : ";
        cin>>english;
        cout<<"\nEnter The marks in computer science out of 100 : ";
        cin>>computer_science;

        calculate();
    }

    void showstudentdata()
    {
        cout<<"\nRoll number of student : "<<rollno;
        cout<<"\nName of student : "<<name;
        cout<<"\nMarks in Physics : "<<physics;
        cout<<"\nMarks in Chemistry : "<<chemistry;
        cout<<"\nMarks in Maths : "<<maths;
        cout<<"\nMarks in English : "<<english;
        cout<<"\nMarks in Computer Science :"<<computer_science;
        cout<<"\nPercentage of student is  :"<<setprecision(2)<<per;
        cout<<"\nGrade of student is :"<<grade;
    }

    void show_tabular()
    {
        cout<<rollno<<setw(12)<<name<<setw(10)<<physics<<setw(3)<<chemistry<<setw(3)<<maths<<setw(3)<<english<<setw(3)<<computer_science<<setw(6)<<setprecision(3)<<per<<"   "<<grade<<endl;
    }

    int  getrollno()
    {
        return rollno;
    }
};


student stu; // creating object of student class
fstream fp;  // for writing data into the file

//this is a function to write data into file
void write_student()
{
    fp.open("student.dat",ios::out|ios::app); //open a file for writing and changes are implemented at end
    stu.getstudentdata();
    fp.write((char*)&stu,sizeof(student)); //writing object into file
    fp.close();
    cout<<"\n\nstudent record Has Been Created ";
    getch();
}

//this is a function to read complete data from file
void display_all()
{
    clrscr();
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("student.dat",ios::in); //open a file in read mode only, a user is not able to modify data

    while(fp.read((char*)&stu,sizeof(student))) //reading object from file
    {
        stu.showstudentdata();
        cout<<"\n\n====================================\n";
        getch();
    }
    fp.close();
    getch();
}


void display_sp(int n)  //here n is the entered roll number and check weather a record exist or not
{
    int flag=0;
    fp.open("student.dat",ios::in); //open a file in read mode

    while(fp.read((char*)&stu,sizeof(student))) //reading object from the file
    {
        if(stu.getrollno()==n)
        {
            clrscr();
            stu.showstudentdata();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
        cout<<"\n\nrecord not exist";
    getch();
}

//function to modify record of a student
void modify_student()
{
    int no,found=0;
    clrscr();
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The roll number of student";
    cin>>no;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&stu,sizeof(student)) && found==0)
    {
        if(stu.getrollno()==no)
        {
            stu.showstudentdata(); //shows the result if roll number of student exist
            cout<<"\nPlease Enter The New Details of student"<<endl;
            stu.getstudentdata();  // this module is used to get data from the user
            int pos=-1*sizeof(stu);
            fp.seekp(pos,ios::cur); //Sets the position where the next character is to be inserted into the output stream.
                                    //cur means from current position in the stream
            fp.write((char*)&stu,sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}



//function to delete a record of particular student from a file
void delete_student()
{
    int no;
    clrscr();
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The roll number of student You Want To Delete";
    cin>>no;
    fp.open("student.dat",ios::in|ios::out);//opens file in read and write mode
    fstream fp2;                    //to create new file
    fp2.open("Temp.dat",ios::out); //open file in only write mode
    fp.seekg(0,ios::beg);           //SEEKG Sets the position of the next character to be extracted from the input stream.
                                    //beg means beginning of the stream
                                    //extraction is from first word
    while(fp.read((char*)&stu,sizeof(student)))
    {
        if(stu.getrollno()!=no)
        {
            fp2.write((char*)&stu,sizeof(student)); //write object one by one in new file except the one whose roll number is given
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
}

// method used to display result of class in tabular form get data from method of student class
void class_result()
{
    clrscr();
    fp.open("student.dat",ios::in); //open student file in read mode no changes allowed
    if(!fp)  //if file not present
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
        cout<<"\n\n\n Program is closing ....";
        getch();
        exit(0);
    }

    cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
    cout<<"====================================================\n";
    cout<<"Roll No. Name          P  C  M  E  CS  %age Grade\n";
    cout<<"====================================================\n";

    while(fp.read((char*)&stu,sizeof(student)))
    {
        stu.show_tabular();  //Stu is the globally declared object of student class
                             //set_tabular is public method of student class
    }
    fp.close();
    getch();
}


//function to display result menu
void result()
{
    int ans,rno;
    char ch;
    clrscr();
    cout<<"\n\n\nRESULT MENU";
    cout<<"\n\n\n1. Class Result\n\n2. Student Report Card\n\n3.Back to Main Menu";
    cout<<"\n\n\nEnter Choice (1/2)? ";
    cin>>ans;
    switch(ans)
    {
    case 1 :
        class_result();//display result of whole class in tabular form
        break;
    case 2 :
    {
        do
        {
            clrscr();
            char ans;
            cout<<"\n\nEnter Roll Number Of Student : ";
            cin>>rno;
            display_sp(rno); //display the result of particular student
            cout<<"\n\nDo you want to See More Result (y/n)?";
            cin>>ans;
        }
        while(ans=='y'||ans=='Y');

        break;
    }
    case 3:
        break;
    default:
        cout<<"\a"; //'\a' is the escape character for a beep ( a = alert )
    }
}

//entry and exit menu of project
void entry_menu()
{
    clrscr();
    char ch2;
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
    ch2=getche();   //getche() function echoes the character to the screen
    switch(ch2)
    {
    case '1':
        clrscr();
        write_student();
        break;
    case '2':
        display_all();
        break;
    case '3':
        int num;
        clrscr();
        cout<<"\n\n\tPlease Enter The roll number ";
        cin>>num;
        display_sp(num);
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



int main()
{
    char ch;
    //intro();
    do
    {
        clrscr();
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. RESULT MENU";
        cout<<"\n\n\t02. ENTRY/EDIT MENU";
        cout<<"\n\n\t03. EXIT";
        cout<<"\n\n\tPlease Select Your Option (1-3) ";
        ch=getche();
        switch(ch)
        {
        case '1':
            clrscr();
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
}










