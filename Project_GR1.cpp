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

    void login()
    {
        cout<<"Student Login"<<endl;
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

    void login()
    {
        cout<<"Admin Login"<<endl;
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
    ResultRecord system;

    cout<<"===================================="<<endl;
    cout<<" STUDENT RESULT MANAGEMENT SYSTEM"<<endl;
    cout<<"===================================="<<endl;

    return 0;
}