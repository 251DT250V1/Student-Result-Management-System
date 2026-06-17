#include<iostream>
#include<fstream>
#include<cstring>
#include<string>

using namespace std;

//====================
// STRUCT 1
//====================
struct Subject
{
    char subjectCode[20];
    char subjectName[50];
    float marks;
    char grade;
};

//====================
// STRUCT 2
//====================
struct Student
{
    int studentID;
    char name[50];
    char course[50];
    float cgpa;
};

//====================
// LINKED LIST NODE
//====================
struct Node
{
    Student student;
    Subject subject[10];
    int totalSubject;

    Node* next;
};

//====================
// FORWARD DECLARATION
//====================
class ResultRecord;

void totalStudent(ResultRecord&);
void highestCGPA(ResultRecord&);
void lowestCGPA(ResultRecord&);
void averageCGPA(ResultRecord&);

//====================
// BASE CLASS 1
//====================
class User
{
protected:
    string username;
    string password;

public:

    User()
    {
        username="";
        password="";
    }

    virtual void login()=0;

    virtual void logout()
    {
        cout<<"Logout Successful"<<endl;
    }

    virtual ~User()
    {
    }
};

//====================
// BASE CLASS 2
//====================
class Record
{
public:

    Record()
    {
    }

    virtual void addRecord()=0;

    virtual void displayRecord()=0;

    virtual void searchRecord()=0;

    virtual void sortRecord()=0;

    virtual ~Record()
    {
    }
};

//====================
// DERIVED CLASS 1
//====================
class StudentUser : public User
{
public:

    StudentUser()
    {
    }

    void registerAccount()
    {
        ofstream fout;

        fout.open("student.txt",ios::app);

        cout<<"===== Student Registration ====="<<endl;

        cout<<"Username : ";
        cin>>username;

        cout<<"Password : ";
        cin>>password;

        fout<<username<<" "<<password<<endl;

        fout.close();

        cout<<"Registration Successful"<<endl;
    }

    void login()
    {
        ifstream fin;

        string u,p;

        bool found=false;

        fin.open("student.txt");

        cout<<"===== Student Login ====="<<endl;

        cout<<"Username : ";
        cin>>username;

        cout<<"Password : ";
        cin>>password;

        while(fin>>u>>p)
        {
            if(username==u && password==p)
            {
                found=true;
                break;
            }
        }

        fin.close();

        if(found)
        {
            cout<<"Login Successful"<<endl;
        }
        else
        {
            cout<<"Invalid Username or Password"<<endl;
        }
    }

    void logout()
    {
        cout<<"Student Logout Successful"<<endl;
    }

    ~StudentUser()
    {
        cout<<"Student Destructor Called"<<endl;
    }
};

//====================
// DERIVED CLASS 2
//====================
class Admin : public User
{
public:

    Admin()
    {
    }

    void registerAccount()
    {
        ofstream fout;

        fout.open("admin.txt",ios::app);

        cout<<"===== Admin Registration ====="<<endl;

        cout<<"Username : ";
        cin>>username;

        cout<<"Password : ";
        cin>>password;

        fout<<username<<" "<<password<<endl;

        fout.close();

        cout<<"Registration Successful"<<endl;
    }

    void login()
    {
        ifstream fin;

        string u,p;

        bool found=false;

        fin.open("admin.txt");

        cout<<"===== Admin Login ====="<<endl;

        cout<<"Username : ";
        cin>>username;

        cout<<"Password : ";
        cin>>password;

        while(fin>>u>>p)
        {
            if(username==u && password==p)
            {
                found=true;
                break;
            }
        }

        fin.close();

        if(found)
        {
            cout<<"Login Successful"<<endl;
        }
        else
        {
            cout<<"Invalid Username or Password"<<endl;
        }
    }

    void logout()
    {
        cout<<"Admin Logout Successful"<<endl;
    }

    ~Admin()
    {
        cout<<"Admin Destructor Called"<<endl;
    }
};

//====================
// DERIVED CLASS 3
//====================
class ResultRecord : public Record
{
private:

    Node* head;

public:

    ResultRecord()
    {
        head=NULL;
    }

    //Friend Functions
    friend void totalStudent(ResultRecord&);
    friend void highestCGPA(ResultRecord&);
    friend void lowestCGPA(ResultRecord&);
    friend void averageCGPA(ResultRecord&);

    //Pure Virtual Functions
    void addRecord()
    {

    }

    void displayRecord()
    {

    }

    void searchRecord()
    {

    }

    void sortRecord()
    {

    }

    ~ResultRecord()
    {
        Node *current=head;

        while(current!=NULL)
        {
            Node *temp=current;
            current=current->next;
            delete temp;
        }

        cout<<"Memory Released"<<endl;
    }
};

//====================
// FRIEND FUNCTION 1
//====================
void totalStudent(ResultRecord &r)
{
    Node *current=r.head;

    int count=0;

    while(current!=NULL)
    {
        count++;
        current=current->next;
    }

    cout<<"Total Student = "<<count<<endl;
}

//====================
// FRIEND FUNCTION 2
//====================
void highestCGPA(ResultRecord &r)
{

}

//====================
// FRIEND FUNCTION 3
//====================
void lowestCGPA(ResultRecord &r)
{

}

//====================
// FRIEND FUNCTION 4
//====================
void averageCGPA(ResultRecord &r)
{

}

//====================
// MAIN FUNCTION
//====================
int main()
{
    StudentUser student;
    Admin admin;

    int choice;

    do
    {
        cout<<endl;
        cout<<"===================================="<<endl;
        cout<<" STUDENT RESULT MANAGEMENT SYSTEM"<<endl;
        cout<<"===================================="<<endl;

        cout<<"1. Student Register"<<endl;
        cout<<"2. Student Login"<<endl;
        cout<<"3. Admin Register"<<endl;
        cout<<"4. Admin Login"<<endl;
        cout<<"5. Exit"<<endl;

        cout<<"Enter Choice : ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            student.registerAccount();
            break;

        case 2:
            student.login();
            break;

        case 3:
            admin.registerAccount();
            break;

        case 4:
            admin.login();
            break;

        case 5:
            cout<<"Thank You"<<endl;
            break;

        default:
            cout<<"Invalid Choice"<<endl;
        }

    }while(choice!=5);

    return 0;
}