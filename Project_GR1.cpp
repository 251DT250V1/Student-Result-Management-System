#include<iostream>
#include<fstream>
#include<cstring>
#include<string>

using namespace std;

struct Subject
{
    char subjectCode[20];
    char subjectName[50];
    float marks;
    char grade;
};

struct Student
{
    int studentID;
    char name[50];
    char course[50];
    float cgpa;
};

struct Node
{
    Student student;
    Subject subject[10];

    int totalSubject;

    Node *next;
};

class ResultRecord;

void totalStudent(ResultRecord&);
void highestCGPA(ResultRecord&);
void lowestCGPA(ResultRecord&);
void averageCGPA(ResultRecord&);

class User
{
protected:

    char username[50];
    char password[50];

public:

    User()
    {
        strcpy(username, "");
        strcpy(password, "");
    }

    virtual bool login()=0;

    virtual void logout()
    {
        cout<<"Logout Successful"<<endl;
    }

    virtual ~User()
    {

    }
};

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

class StudentUser : public User
{
public:

    StudentUser()
    {
    strcpy(username, "");
    strcpy(password, "");
    }

    void registerAccount();

    bool login();

    void logout();

    ~StudentUser()
    {
     cout<<"Student Object Deleted"<<endl;
    }
};

class Admin : public User
{
public:

    Admin()
    {
    strcpy(username, "");
    strcpy(password, "");
    }

    void registerAccount();

    bool login();

    void logout();

    ~Admin()
    {
    cout<<"Admin Object Deleted"<<endl;
    }
};

class ResultRecord : public Record
{
private:

    Node *head;

public:

    ResultRecord()
    {
        head=NULL;
        loadFile();
    }

    void addRecord();

    void displayRecord();

    void searchRecord();

    void sortRecord();

    void editRecord();

    void deleteRecord();

    void sortCGPA();

    void addSubject();

    void displaySubject();

    void saveFile();

    void loadFile();

    void summaryReport();

    void saveSummary();

    void binarySearch();

    void generateReport();



    void displayRecord(int id);

    

    void searchRecord(int id);

    
    
    void sortRecord(float dummy);



    void loadSummary();

    void loadReport();

    void searchSubject();

    void sortSubject();

    friend void totalStudent(ResultRecord &r);
    friend void highestCGPA(ResultRecord &r);
    friend void lowestCGPA(ResultRecord &r);
    friend void averageCGPA(ResultRecord &r);

    ~ResultRecord()
{
    saveFile();

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

// friend functions
    //Friend function 1
   void totalStudent(ResultRecord &r)
{
    Node *current=r.head;

    int total=0;

    while(current!=NULL)
    {
        total++;

        current=current->next;
    }

    cout<<"Total Students : " <<total <<endl;
}

    //friend function 2
    void highestCGPA(ResultRecord &r)
{
    if(r.head==NULL)
    {
        return;
    }

    Node *current=r.head;

    float highest=current->student.cgpa;

    while(current!=NULL)
    {
        if(current->student.cgpa>highest)
        {
            highest=current->student.cgpa;
        }

        current=current->next;
    }

    cout<<"Highest CGPA : " <<highest <<endl;
}

    //friend function 3
    void lowestCGPA(ResultRecord &r)
{
    if(r.head==NULL)
    {
        return;
    }

    Node *current=r.head;

    float lowest=current->student.cgpa;

    while(current!=NULL)
    {
        if(current->student.cgpa<lowest)
        {
            lowest=current->student.cgpa;
        }

        current=current->next;
    }

    cout<<"Lowest CGPA : " <<lowest <<endl;
}

    //friend function 4
    void averageCGPA(ResultRecord &r)
{
    Node *current=r.head;

    float total=0;

    int count=0;

    while(current!=NULL)
    {
        total+=current->student.cgpa;

        count++;

        current=current->next;
    }

    if(count!=0)
    {
        cout<<"Average CGPA : " <<total/count <<endl;
    }
}

// Student Register
void StudentUser::registerAccount()
{
    ofstream fout;

    fout.open("student.txt",ios::app);

    cout<<"\n===== Student Register ====="<<endl;
    cin.ignore();

    cout<<"Username : ";
    cin.getline(username, 50);

    cout<<"Password : ";
    cin.getline(password, 50);

    fout<<username<<endl<<password<<endl;

    fout.close();

    cout<<"Register Successfully"<<endl;
}

// Student Login
bool StudentUser::login()
{
    ifstream fin;

    string u,p;

    bool found=false;

    fin.open("student.txt");

    cout<<"\n===== Student Login ====="<<endl;

    cin.ignore();
    cout<<"Username : ";
    cin.getline(username, 50);

    cout<<"Password : ";
    cin.getline(password, 50);

    while(getline(fin,u) && getline(fin,p))
    {
        if(username==u && password==p)
        {
            found=true;
        }
    }

    fin.close();

    if(found)
    {
        cout<<"Login Successful"<<endl;
        return true;
    }
    else
    {
        cout<<"Wrong Username or Password"<<endl;
        return false;
    }
}

// Student Logout
void StudentUser::logout()
{
    cout<<"Student Logout Successfully"<<endl;
}

// Admin Register
void Admin::registerAccount()
{
    ofstream fout;

    fout.open("admin.txt",ios::app);

    cout<<"\n===== Admin Register ====="<<endl;

    cin.ignore();
    cout<<"Username : ";
    cin.getline(username, 50);

    cout<<"Password : ";
    cin.getline(password, 50);

    fout<<username<<endl<<password<<endl;

    fout.close();

    cout<<"Register Successfully"<<endl;
}

// Admin Login

bool Admin::login()
{
    ifstream fin;

    string u,p;

    bool found=false;

    fin.open("admin.txt");

    cout<<"\n===== Admin Login ====="<<endl;
    cin.ignore();

    cout<<"Username : ";
    cin.getline(username, 50);

    cout<<"Password : ";
    cin.getline(password, 50);

    while(getline(fin,u) && getline(fin,p))
    {
        if(username==u && password==p)
            found=true;
    }

    fin.close();

    if(found)
    {
        cout<<"Login Successful"<<endl;
        return true;
    }
    else
    {
        cout<<"Wrong Username or Password"<<endl;
        return false;
    }
    
}

// Admin Logout
void Admin::logout()
{
    cout<<"Admin Logout Successfully"<<endl;
}

void ResultRecord::addRecord()
{
    try
    {
        Node *newNode=new Node;

        cout<<"\n===== Add Student ====="<<endl;

        cout<<"Student ID : ";
        cin>>newNode->student.studentID;

        if(cin.fail())
        {
            throw 1;
        }

        cin.ignore();

        cout<<"Student Name : ";
        cin.getline(newNode->student.name,50);

        cout<<"Course : ";
        cin.getline(newNode->student.course,50);

        cout<<"CGPA : ";
        cin>>newNode->student.cgpa;

        newNode->totalSubject=0;
        newNode->next=NULL;

        if(head==NULL)
        {
            head=newNode;
        }
        else
        {
            Node *current=head;

            while(current->next!=NULL)
            {
                current=current->next;
            }

            current->next=newNode;
        }

        cout<<"Student Added Successfully"<<endl;
    }
    catch(int)
    {
        cout<<"Invalid Input"<<endl;

        cin.clear();
        cin.ignore(1000,'\n');
    }
}

void ResultRecord::displayRecord()
{
    Node *current=head;

    if(head==NULL)
    {
        cout<<"No Record Found"<<endl;
        return;
    }

    cout<<"\n===== Student List ====="<<endl;

    while(current!=NULL)
    {
        cout<<"Student ID : "
            <<current->student.studentID
            <<endl;

        cout<<"Name : "
            <<current->student.name
            <<endl;

        cout<<"Course : "
            <<current->student.course
            <<endl;

        cout<<"CGPA : "
            <<current->student.cgpa
            <<endl;

        cout<<"---------------------"<<endl;

        current=current->next;
    }
}

void ResultRecord::displayRecord(int id)
{
    Node *current=head;

    while(current!=NULL)
    {
        if(current->student.studentID==id)
        {
            cout<<"Student ID : "
                <<current->student.studentID
                <<endl;

            cout<<"Name : "
                <<current->student.name
                <<endl;

            return;
        }

        current=current->next;
    }

    cout<<"Student Not Found"<<endl;
};

void ResultRecord::saveFile()
{
    ofstream fout;

    fout.open("result.txt");

    Node *current=head;

    while(current!=NULL)
    {
        fout<<current->student.studentID<<endl;
        fout<<current->student.name<<endl;
        fout<<current->student.course<<endl;
        fout<<current->student.cgpa<<endl;

        current=current->next;
    }

    fout.close();

    cout<<"Data Saved Successfully"<<endl;
}

void ResultRecord::loadFile()
{
    ifstream fin;

    fin.open("result.txt");

    if(fin.fail())
    {
        return;
    }

    while(!fin.eof())
    {
        Node *newNode=new Node;

        fin>>newNode->student.studentID;

        fin.ignore();

        fin.getline(newNode->student.name,50);

        fin.getline(newNode->student.course,50);

        fin>>newNode->student.cgpa;

        fin.ignore();

        newNode->totalSubject=0;
        newNode->next=NULL;

        if(fin.fail())
        {
            delete newNode;
            break;
        }

        if(head==NULL)
        {
            head=newNode;
        }
        else
        {
            Node *current=head;

            while(current->next!=NULL)
            {
                current=current->next;
            }

            current->next=newNode;
        }
    }

    fin.close();
}

// Edit student information
void ResultRecord::editRecord()
{
    int id;
    bool found=false;

    cout<<"\nEnter Student ID to edit : ";
    cin>>id;

    Node *current=head;

    while(current!=NULL)
    {
        if(current->student.studentID==id)
        {
            found=true;

            cin.ignore();

            cout<<"New Name : ";
            cin.getline(current->student.name,50);

            cout<<"New Course : ";
            cin.getline(current->student.course,50);

            cout<<"New CGPA : ";
            cin>>current->student.cgpa;

            cout<<"Record Updated Successfully"<<endl;

            break;
        }

        current=current->next;
    }

    if(found==false)
    {
        cout<<"Student Not Found"<<endl;
    }
}


void ResultRecord::searchRecord()
{
    try
    {
    int id;

    cout<<"\nEnter Student ID : ";
    cin>>id;

    if(cin.fail())
        {
            throw 1;
        }

    Node *current=head;

    while(current!=NULL)
    {
        if(current->student.studentID==id)
        {
            cout<<"\nStudent Found"<<endl;

            cout<<"ID : "
                <<current->student.studentID
                <<endl;

            cout<<"Name : "
                <<current->student.name
                <<endl;

            cout<<"Course : "
                <<current->student.course
                <<endl;

            cout<<"CGPA : "
                <<current->student.cgpa
                <<endl;

            return;
        }

        current=current->next;
    }

    cout<<"Student Not Found"<<endl;
}
catch(int)
    {
        cout<<"Invalid Input"<<endl;

        cin.clear();
        cin.ignore(1000,'\n');
    }
}

void ResultRecord::searchRecord(int id)
{
    Node *current=head;

    while(current!=NULL)
    {
        if(current->student.studentID==id)
        {
            cout<<"Record Found"<<endl;

            return;
        }

        current=current->next;
    }

    cout<<"Record Not Found"<<endl;
}

// Add subject result
void ResultRecord::addSubject()
{
    int id;

    cout<<"\nEnter Student ID : ";
    cin>>id;

    Node *current=head;

    while(current!=NULL)
    {

        if(current->student.studentID==id)
        {
            if(current->totalSubject>=10)
            {
                cout<<"The student has reached the maximum number of subjects and cannot add any more."<<endl;
                return;
            }
            
            int n=current->totalSubject;

            cout<<"Subject Code : ";
            cin>>current->subject[n].subjectCode;

            cin.ignore();

            cout<<"Subject Name : ";
            cin.getline(current->subject[n].subjectName,50);

            cout<<"Marks : ";
            cin>>current->subject[n].marks;

            // simple grading
            if(current->subject[n].marks>=80)
                current->subject[n].grade='A';
            else if(current->subject[n].marks>=70)
                current->subject[n].grade='B';
            else if(current->subject[n].marks>=60)
                current->subject[n].grade='C';
            else if(current->subject[n].marks>=50)
                current->subject[n].grade='D';
            else
                current->subject[n].grade='F';

            current->totalSubject++;

            cout<<"Subject Added Successfully"<<endl;

            return;
        }

        current=current->next;
    }

    cout<<"Student Not Found"<<endl;
}



void ResultRecord::displaySubject()
{
    int id;

    cout<<"\nEnter Student ID : ";
    cin>>id;

    Node *current=head;

    while(current!=NULL)
    {
        if(current->student.studentID==id)
        {
            cout<<"\nStudent Name : "
                <<current->student.name
                <<endl;

            cout<<"--------------------"<<endl;

            for(int i=0;i<current->totalSubject;i++)
            {
                cout<<"Subject Code : "
                    <<current->subject[i].subjectCode
                    <<endl;

                cout<<"Subject Name : "
                    <<current->subject[i].subjectName
                    <<endl;

                cout<<"Marks : "
                    <<current->subject[i].marks
                    <<endl;

                cout<<"Grade : "
                    <<current->subject[i].grade
                    <<endl;

                cout<<"--------------------"<<endl;
            }

            return;
        }

        current=current->next;
    }

    cout<<"Student Not Found"<<endl;
}

// Bubble Sort by Student ID

void ResultRecord::sortRecord(float dummy)
{
    sortCGPA();
}

void ResultRecord::sortRecord()
{
    if(head==NULL)
    {
        cout<<"No Record Found"<<endl;
        return;
    }

    Node *current;
    Node *nextNode;

    bool swap;

    do
    {
        swap=false;

        current=head;

        while(current->next!=NULL)
        {
            nextNode=current->next;

            if(current->student.studentID >
               nextNode->student.studentID)
            {
                Student temp;

                temp=current->student;

                current->student=nextNode->student;

                nextNode->student=temp;

                swap=true;
            }

            current=current->next;
        }

    }while(swap);

    cout<<"Records Sorted Successfully"<<endl;
}

// Bubble Sort by CGPA
void ResultRecord::sortCGPA()
{
    if(head==NULL)
    {
        cout<<"No Record Found"<<endl;
        return;
    }

    Node *current;
    Node *nextNode;

    bool swap;

    do
    {
        swap=false;

        current=head;

        while(current->next!=NULL)
        {
            nextNode=current->next;

            if(current->student.cgpa <
               nextNode->student.cgpa)
            {
                Student temp;

                temp=current->student;

                current->student=nextNode->student;

                nextNode->student=temp;

                swap=true;
            }

            current=current->next;
        }

    }while(swap);

    cout<<"Sorted by CGPA"<<endl;
}

// Show simple summary
void ResultRecord::summaryReport()
{
    Node *current=head;

    int total=0;

    while(current!=NULL)
    {
        total++;

        current=current->next;
    }

    cout<<endl;

    cout<<"===== Summary Report ====="<<endl;

    cout<<"Total Students : "
        <<total
        <<endl;
}

void ResultRecord::saveSummary()
{
    ofstream fout;

    fout.open("summary.txt");

    Node *current=head;

    int total=0;

    while(current!=NULL)
    {
        total++;

        current=current->next;
    }

    fout<<"===== Summary Report ====="<<endl;

    fout<<"Total Students : "
        <<total
        <<endl;

    fout.close();

    cout<<"Summary Saved Successfully"<<endl;
}

// Search student by ID using Binary Search
void ResultRecord::binarySearch()
{
    if(head == NULL) {
        cout << "No record found in memory." << endl;
        return;
    }

    sortRecord();

    Student arr[100];

    int count=0;

    Node *current=head;

    while(current!=NULL)
    {
        arr[count]=current->student;

        count++;

        current=current->next;
    }

    int id;

    cout<<"Enter Student ID : ";
    cin>>id;

    int low=0;
    int high=count-1;
    int mid;

    bool found=false;

    while(low<=high)
    {
        mid=(low+high)/2;

        if(arr[mid].studentID==id)
        {
            cout<<"\nStudent Found"<<endl;

            cout<<"ID : "
                <<arr[mid].studentID
                <<endl;

            cout<<"Name : "
                <<arr[mid].name
                <<endl;

            cout<<"Course : "
                <<arr[mid].course
                <<endl;

            cout<<"CGPA : "
                <<arr[mid].cgpa
                <<endl;

            found=true;

            break;
        }
        else if(id<arr[mid].studentID)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }

    if(found==false)
    {
        cout<<"Student Not Found"<<endl;
    }
}

// Save report into report.txt
void ResultRecord::generateReport()
{
    ofstream fout;

    fout.open("report.txt");

    Node *current=head;

    int total=0;

    float sum=0;

    while(current!=NULL)
    {
        total++;

        sum+=current->student.cgpa;

        current=current->next;
    }

    fout<<"===== Report ====="<<endl;

    fout<<"Total Students : "
        <<total
        <<endl;

    if(total!=0)
    {
        fout<<"Average CGPA : "
            <<sum/total
            <<endl;
    }

    fout.close();

    cout<<"Report Generated Successfully"<<endl;
}

// Read summary file
void ResultRecord::loadSummary()
{
    ifstream fin;

    string line;

    fin.open("summary.txt");

    if(fin.fail())
    {
        cout<<"Summary File Not Found"<<endl;
        return;
    }

    cout<<"\n===== Summary ====="<<endl;

    while(getline(fin,line))
    {
        cout<<line<<endl;
    }

    fin.close();
}

// Display report file
void ResultRecord::loadReport()
{
    ifstream fin;

    string line;

    fin.open("report.txt");

    if(fin.fail())
    {
        cout<<"Report File Not Found"<<endl;
        return;
    }

    cout<<"\n===== Report ====="<<endl;

    while(getline(fin,line))
    {
        cout<<line<<endl;
    }

    fin.close();
}

// Search subject by code
void ResultRecord::searchSubject()
{
    char code[20];

    cout<<"Enter Subject Code : ";
    cin>>code;

    Node *current=head;

    while(current!=NULL)
    {
        for(int i=0;i<current->totalSubject;i++)
        {
            if(strcmp(current->subject[i].subjectCode,code)==0)
            {
                cout<<"\nSubject Found"<<endl;

                cout<<"Student Name : "
                    <<current->student.name
                    <<endl;

                cout<<"Subject Name : "
                    <<current->subject[i].subjectName
                    <<endl;

                cout<<"Marks : "
                    <<current->subject[i].marks
                    <<endl;

                return;
            }
        }

        current=current->next;
    }

    cout<<"Subject Not Found"<<endl;
}

// Bubble sort subject marks
void ResultRecord::sortSubject()
{
    Node *current=head;

    while(current!=NULL)
    {
        for(int i=0;i<current->totalSubject-1;i++)
        {
            for(int j=0;j<current->totalSubject-1-i;j++)
            {
                if(current->subject[j].marks <
                   current->subject[j+1].marks)
                {
                    Subject temp;

                    temp=current->subject[j];

                    current->subject[j]=current->subject[j+1];

                    current->subject[j+1]=temp;
                }
            }
        }

        current=current->next;
    }

    cout<<"Subject Sorted Successfully"<<endl;
}

// Delete student record
void ResultRecord::deleteRecord()
{
    try
    {
        int id;

        cout<<"Enter Student ID : ";
        cin>>id;

        if(cin.fail())
        {
            throw 1;
        }

        Node *current=head;
        Node *previous=NULL;

        while(current!=NULL)
        {
            if(current->student.studentID==id)
            {
                if(current==head)
                {
                    head=head->next;
                }
                else
                {
                    previous->next=current->next;
                }

                delete current;

                cout<<"Record Deleted"<<endl;

                return;
            }

            previous=current;
            current=current->next;
        }

        cout<<"Student Not Found"<<endl;
    }

    catch(int)
    {
        cout<<"Invalid Input"<<endl;

        cin.clear();

        cin.ignore(1000,'\n');
    }
}

void adminMenu(ResultRecord &system)
{
    int choice;

    do
    {
        cout<<"\n========== Admin Menu =========="<<endl;

        cout<<"1. Add Student"<<endl;
        cout<<"2. Display Student"<<endl;
        cout<<"3. Edit Student"<<endl;
        cout<<"4. Delete Student"<<endl;
        cout<<"5. Search Student"<<endl;
        cout<<"6. Sort By Student ID"<<endl;
        cout<<"7. Sort By CGPA"<<endl;
        cout<<"8. Add Subject"<<endl;
        cout<<"9. Display Subject"<<endl;
        cout<<"10. Binary Search"<<endl;
        cout<<"11. Generate Report"<<endl;
        cout<<"12. Search Subject"<<endl;
        cout<<"13. Sort Subject"<<endl;
        cout<<"14. View Report"<<endl;
        cout<<"15. View Statistics"<<endl;
        cout<<"16. Exit"<<endl;

        cout<<"Enter Choice : ";
        cin>>choice;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0; 
        }

        switch(choice)
        {
        case 1:
            system.addRecord();
            break;

        case 2:
            system.displayRecord();
            break;

        case 3:
            system.editRecord();
            break;

        case 4:
            system.deleteRecord();
            break;

        case 5:
            system.searchRecord();
            break;

        case 6:
            system.sortRecord();
            break;

        case 7:
            system.sortCGPA();
            break;

        case 8:
            system.addSubject();
            break;

        case 9:
            system.displaySubject();
            break;

        case 10:
            system.binarySearch();
            break;

        case 11:
            system.generateReport();
            break;

        case 12:
            system.searchSubject();
            break;

        case 13:
            system.sortSubject();
            break;

        case 14:
            system.loadReport();
            break;

        case 15:
            totalStudent(system);
            highestCGPA(system);
            lowestCGPA(system);
            averageCGPA(system);
            break;

        case 16:
            cout<<"Back to Main Menu"<<endl;
            break;

        default:
            cout<<"Invalid Choice"<<endl;
        }

    }while(choice!=16);
}

void studentMenu(ResultRecord &system)
{
    int choice;

    do
    {
        cout<<"\n========== Student Menu =========="<<endl;

        cout<<"1. Display Result"<<endl;
        cout<<"2. Search Student"<<endl;
        cout<<"3. Summary Report"<<endl;
        cout<<"4. Save Summary"<<endl;
        cout<<"5. View Saved Summary"<<endl;
        cout<<"6. Exit"<<endl;

        cout<<"Enter Choice : ";
        cin>>choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0; 
        }

        switch(choice)
        {
        case 1:
            system.displayRecord();
            break;

        case 2:
            system.searchRecord();
            break;

        case 3:
            system.summaryReport();
            break;

        case 4:
            system.saveSummary();
            break;

        case 5:
            system.loadSummary();
            break;

        case 6:
            cout<<"Back to Main Menu"<<endl;
            break;

        default:
            cout<<"Invalid Choice"<<endl;
        }

    }while(choice!=6);
}

int main()
{
    StudentUser student;
    Admin admin;
    ResultRecord system;

    int choice;

    do
    {
        cout<<"\n=================================="<<endl;
        cout<<"Student Result Management System"<<endl;
        cout<<"=================================="<<endl;

        cout<<"1. Student Register"<<endl;
        cout<<"2. Student Login"<<endl;
        cout<<"3. Admin Register"<<endl;
        cout<<"4. Admin Login"<<endl;
        cout<<"5. Exit"<<endl;

        cout<<"Enter Choice : ";
        cin>>choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0; 
        }

        switch(choice)
        {
        case 1:
            student.registerAccount();
            break;

        case 2:
            if(student.login())
            {
                studentMenu(system);
                student.logout();
            }
            break;

        case 3:
            admin.registerAccount();
            break;

        case 4:
            if(admin.login())
            {
                adminMenu(system);
                admin.logout();
            }

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