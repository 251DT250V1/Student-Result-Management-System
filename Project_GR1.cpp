#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<cstdlib>

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
    char studentID[20];
    char name[50];
    char course[50];
    float cgpa;
    char enrolledCourseCode[20];
};

struct Node
{
    Student student;
    Subject subject[10];

    int totalSubject;

    Node *next;
};

// Course Management: a separate dynamic non-primitive (linked list)
// data structure storing the catalogue of courses students can enroll in.
struct Course
{
    char courseCode[20];
    char courseName[50];
    int creditHours;
    int maxCapacity;
    int enrolledCount;
};

struct CourseNode
{
    Course course;
    CourseNode *next;
};

class ResultRecord;

void totalStudent(ResultRecord&);
void highestCGPA(ResultRecord&);
void lowestCGPA(ResultRecord&);
void averageCGPA(ResultRecord&);

// ============================================================
// SCREEN UTILITIES FOR DEV C++ (WINDOWS)
// ============================================================
void clearScreen() {
    system("cls"); 
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    cin.get(); 
}

class User
{
protected:

    char username[50];
    char password[50];
    int failedAttempts;

public:

    User()
    {
        strcpy(username, "");
        strcpy(password, "");
        failedAttempts=0;
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
private:

    bool attemptLogin();
    char currentStudentID[20];
    

public:
    

    StudentUser()
    {
    strcpy(username, "");
    strcpy(password, "");
    strcpy(currentStudentID,"");
    }

    void registerAccount(ResultRecord &system);

    bool login();

    void logout();
    void profileMenu();
    void viewProfile();
    void changePassword();
    
    const char* getStudentID();

    ~StudentUser()
    {
     cout<<"Student Object Deleted."<<endl;
    }
};

class Admin : public User
{
private:

    bool attemptLogin();

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
    cout<<"Admin Object Deleted."<<endl;
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

    void addRecord(Student s);

    void displayRecord();

    void displayRecord(char id[]);

    void searchRecord();

    void searchRecord(char id[]);

    void sortRecord();

    void sortRecord(int mode);

    void editRecord();

    void deleteRecord();

    void sortCGPA();

    void addSubject();

    void displaySubject();

    void displaySubject(char id[]);

    void saveFile();

    void loadFile();

    void summaryReport();

    void saveSummary();

    void binarySearch();

    void generateReport();

    void loadSummary();

    void loadReport();

    void deleteSubject(char id[]);

    int validateCGPA(float c);

    int validateMarks(float m);

    bool updateEnrolledCourse(char id[],char code[]);

    void classificationReport();
    void saveClassificationReport();
    char classifyCGPA(float c);

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

// Forward declaration so ResultRecord can be referenced inside
// CourseManager's enrollCourse() (it needs to look up a student
// record to confirm the student exists before enrolling them).
class CourseManager : public Record
{
private:

    CourseNode *courseHead;

public:

    CourseManager()
    {
        courseHead=NULL;
        loadCourseFile();
    }

    void addRecord();

    void addRecord(Course c);

    void displayRecord();

    void displayRecord(char codeFilter[]);

    char* getFirstCourseCode()
    {
        if(courseHead != NULL) return courseHead->course.courseCode;
        return NULL;
    }

    void searchRecord();

    bool searchRecord(char code[]);

    void sortRecord();

    void editCourse();

    void deleteCourse();

    void loadCourseFile();

    void saveCourseFile();

    bool enrollStudent(ResultRecord &system, char studentID[], char code[]);

    void courseEnrollmentReport();

    ~CourseManager()
    {
        saveCourseFile();

        CourseNode *current=courseHead;

        while(current!=NULL)
        {
            CourseNode *temp=current;

            current=current->next;

            delete temp;
        }

        cout<<"Course Memory Released."<<endl;
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
void StudentUser::registerAccount(ResultRecord &system)
{
    try
    {
        ofstream fout;

        fout.open("student.txt",ios::app);

        cout<<"\n===== STUDENT REGISTER ====="<<endl;
        cin.ignore(1000,'\n');

        cout<<"Username : ";
        cin.getline(username, 50);

        cout<<"Password : ";
        cin.getline(password, 50);
        
        cout<<"Student ID : ";
        cin>>currentStudentID;

        if(strlen(username)==0 || strlen(password)==0)
        {
            fout.close();
            throw 1;
        }

        fout<<username<<endl;
        fout<<password<<endl;
        fout<<currentStudentID<<endl;

        fout.close();

        // A registered login account on its own has no academic record
        // yet (academic records live in ResultRecord, normally managed
        // by Admin). Create a basic placeholder record here, using the
        // ID just registered, so the student isn't stuck seeing "Not
        // Found" on Display/Search/Sort/Delete until an admin separately
        // adds a matching record. Admin can still edit name/course/CGPA
        // later through Edit Student.
        Student s;

        strcpy(s.studentID, currentStudentID);
        strcpy(s.name, username);
        strcpy(s.course, "Undeclared");
        s.cgpa = 0.0;
        strcpy(s.enrolledCourseCode, "NONE");

        system.addRecord(s);

        cout<<"Register Successfully!"<<endl;
    }
    catch(int)
    {
        cout<<"Registration Failed: Username and Password cannot be empty."<<endl;
    }
}

// Student Login
// Single login attempt: prompts once, checks credentials against
// student.txt, and reports success/failure. Returns true on success.
// Throws 2 if no student.txt exists yet, 1 if input was empty.
bool StudentUser::attemptLogin()
{
    try
    {
        ifstream fin;

        char u[50], p[50], sid[20];

        bool found=false;

        fin.open("student.txt");

        if(fin.fail())
        {
            throw 2;
        }

        cout<<"Username : ";
        cin.getline(username, 50);

        cout<<"Password : ";
        cin.getline(password, 50);

        if(strlen(username)==0 || strlen(password)==0)
        {
            fin.close();
            throw 1;
        }

        while(fin.getline(u,50) && fin.getline(p,50) && fin.getline(sid,20))
        {
            if(strcmp(username,u)==0 && strcmp(password,p)==0)
            {
                found=true;
                strcpy(currentStudentID,sid);
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
            cout<<"Invalid Username or Password."<<endl;
            return false;
        }
    }
    catch(int errorCode)
    {
        if(errorCode==2)
        {
            cout<<"No Registered Students Found. Please Register First."<<endl;
        }
        else
        {
            cout<<"Login Failed: Username and Password cannot be empty."<<endl;
        }

        return false;
    }
}

// Public login: gives the student up to 3 attempts before locking
// them out for this session.
bool StudentUser::login()
{
    cout<<"\n===== STUDENT LOGIN ====="<<endl;
    cin.ignore(1000,'\n');

    while(1)
    {
        if(attemptLogin())
        {
            return true;
        }
        cout << "Login failed. Please try again." << endl;
    }
}

// Student Logout
void StudentUser::logout()
{
    cout<<"Student Logout Successfully"<<endl;
}

void StudentUser::viewProfile()
{
    cout<<"\n===== MY PROFILE ====="<<endl;

    cout<<"Username : " <<username <<endl;
    cout<<"Student ID : "<<currentStudentID<<endl;
    cout<<"Role : Student"<<endl;
}

void StudentUser::changePassword()
{
    char newPassword[50];

    cin.ignore(1000,'\n');

    cout<<"Enter New Password : ";
    cin.getline(newPassword,50);

    if(strlen(newPassword)==0)
    {
        cout<<"Password Cannot Be Empty"<<endl;
        return;
    }

    ifstream fin("student.txt");
    ofstream fout("temp.txt");

    char u[50], p[50], sid[20];

    while(fin.getline(u,50) && fin.getline(p,50) && fin.getline(sid,20))
    {
        if(strcmp(u,username)==0)
        {
            fout<<u<<endl;
            fout<<newPassword<<endl;
            fout<<sid<<endl;

            strcpy(password,newPassword);
        }
        else
        {
            fout<<u<<endl;
            fout<<p<<endl;
            fout<<sid<<endl;
        }
    }

    fin.close();
    fout.close();

    remove("student.txt");
    rename("temp.txt","student.txt");

    cout<<"Password Changed Successfully"<<endl;
}

const char* StudentUser::getStudentID()
{
    return currentStudentID;
}

void StudentUser::profileMenu()
{
    int choice;

    do
    {
        clearScreen();

        cout<<"\n===== STUDENT PROFILE ====="<<endl;

        cout<<"1. View Profile"<<endl;
        cout<<"2. Change Password"<<endl;
        cout<<"3. Back"<<endl;

        cout<<"Enter Choice : ";

        cin>>choice;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');
            choice=0;
        }

        switch(choice)
        {
            case 1:

                viewProfile();
                pauseScreen();
                break;

            case 2:

                changePassword();
                pauseScreen();
                break;

            case 3:

                break;

            default:

                cout<<"Invalid Choice"<<endl;
                pauseScreen();
        }

    }while(choice!=3);
}

// Admin Register
void Admin::registerAccount()
{
    try
    {
        ofstream fout;

        fout.open("admin.txt",ios::app);

        cout<<"\n===== ADMIN REGISTER ====="<<endl;

        cin.ignore(1000,'\n');
        cout<<"Username : ";
        cin.getline(username, 50);

        cout<<"Password : ";
        cin.getline(password, 50);

        if(strlen(username)==0 || strlen(password)==0)
        {
            fout.close();
            throw 1;
        }

        fout<<username<<endl<<password<<endl;

        fout.close();

        cout<<"Register Successfully!"<<endl;
    }
    catch(int)
    {
        cout<<"Registration Failed: Username and Password cannot be empty."<<endl;
    }
}

// Admin Login
// Single login attempt for Admin, same pattern as StudentUser::attemptLogin.
bool Admin::attemptLogin()
{
    try
    {
        ifstream fin;

        char u[50], p[50];

        bool found=false;

        fin.open("admin.txt");

        if(fin.fail())
        {
            throw 2;
        }

        cout<<"Username : ";
        cin.getline(username, 50);

        cout<<"Password : ";
        cin.getline(password, 50);

        if(strlen(username)==0 || strlen(password)==0)
        {
            fin.close();
            throw 1;
        }

        while(fin.getline(u,50) && fin.getline(p,50))
        {
            if(strcmp(username,u)==0 && strcmp(password,p)==0)
                found=true;
        }

        fin.close();

        if(found)
        {
            cout<<"Login Successful!"<<endl;
            return true;
        }
        else
        {
            cout<<"Invalid Username or Password."<<endl;
            return false;
        }
    }
    catch(int errorCode)
    {
        if(errorCode==2)
        {
            cout<<"No Registered Admin Found. Please Register First."<<endl;
        }
        else
        {
            cout<<"Login Failed: Username and Password cannot be empty."<<endl;
        }

        return false;
    }
}


bool Admin::login()
{
    cout<<"\n===== ADMIN LOGIN ====="<<endl;
    cin.ignore(1000,'\n');

    while(1)
    {
        if(attemptLogin())
        {
            return true;
        }
        cout << "Login failed. Please try again." << endl;
    }
}

// Admin Logout
void Admin::logout()
{
    cout<<"Admin Logout Successfully!"<<endl;
}

void ResultRecord::addRecord()
{
    try
    {
        Node *newNode=new Node;

        cout<<"\n===== ADD STUDENT ====="<<endl;

        cout<<"Student ID : ";
        cin>>newNode->student.studentID;

        if(cin.fail())
        {
            delete newNode;
            throw 1;
        }
        
        Node *check=head;

        while(check!=NULL)
        {
            if(strcmp(check->student.studentID, newNode->student.studentID)==0)
            {
                delete newNode;
        
                cout<<"Student ID Already Exists!"<<endl;
        
                return;
            }
        
            check=check->next;
        }

        cin.ignore(1000,'\n');

        cout<<"Student Name : ";
        cin.getline(newNode->student.name,50);
        if(strlen(newNode->student.name)==0)
        {
            delete newNode;
        
            cout<<"Student Name Cannot Be Empty"<<endl;
        
            return;
        }

        cout<<"Course : ";
        cin.getline(newNode->student.course,50);

        cout<<"CGPA : ";
        cin>>newNode->student.cgpa;

        if(cin.fail())
        {
            delete newNode;
            throw 1;
        }

        if(validateCGPA(newNode->student.cgpa)==0)
        {
            delete newNode;
            throw 2;
        }

        newNode->totalSubject=0;
        newNode->next=NULL;
        strcpy(newNode->student.enrolledCourseCode,"NONE");

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

        cout<<"Student Added Successfully!"<<endl;
    }
    catch(int errorCode)
    {
        if(errorCode==2)
        {
            cout<<"Invalid CGPA. Must be between 0.0 and 4.0"<<endl;
        }
        else
        {
            cout<<"Invalid Input"<<endl;
        }

        cin.clear();
        cin.ignore(1000,'\n');
    }
}

// Overloaded addRecord: accepts a ready-made Student struct directly
// instead of asking for keyboard input. Used internally by loadSampleData()
// and by any future feature that needs to insert a record programmatically.
void ResultRecord::addRecord(Student s)
{
    Node *check=head;

    while(check!=NULL)
    {
        if(strcmp(check->student.studentID, s.studentID)==0)
        {
            // Already exists (e.g. admin already added this student) -
            // don't create a duplicate record.
            return;
        }

        check=check->next;
    }

    Node *newNode=new Node;

    newNode->student=s;
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
}

void ResultRecord::displayRecord()
{
    Node *current=head;

    if(head==NULL)
    {
        cout<<"No Record Found!"<<endl;
        return;
    }

    cout<<"\n================ STUDENT LIST ================\n";
    cout<<left<<setw(15)<<"ID"<<setw(25)<<"Name"<<setw(35)<<"Course"<<setw(10)<<"CGPA"<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl;

    while(current!=NULL)
    {
        cout<<left<<setw(12)<<current->student.studentID<<setw(25)<<current->student.name<<setw(35)<<current->student.course<<setw(10)<<fixed<<setprecision(2)<<current->student.cgpa<<endl;

        current=current->next;
    }
}

void ResultRecord::displayRecord(char id[])
{
    Node *current=head;

    while(current!=NULL)
    {
        if(strcmp(current->student.studentID,id)==0)
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

    cout<<"Student Not Found!"<<endl;
}

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
        fout<<current->student.enrolledCourseCode<<endl;
        fout<<current->totalSubject<<endl;

        for(int i=0;i<current->totalSubject;i++)
        {
            fout<<current->subject[i].subjectCode<<endl;
            fout<<current->subject[i].subjectName<<endl;
            fout<<current->subject[i].marks<<endl;
            fout<<current->subject[i].grade<<endl;
        }

        current=current->next;
    }

    fout.close();

    cout<<"Data Saved Successfully!"<<endl;
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

        if(fin.fail())
        {
            delete newNode;
            break;
        }

        fin.ignore();

        fin.getline(newNode->student.name,50);

        fin.getline(newNode->student.course,50);

        fin>>newNode->student.cgpa;

        fin.ignore();

        fin.getline(newNode->student.enrolledCourseCode,20);
        fin>>newNode->totalSubject;
        fin.ignore();
        
        for(int i=0;i<newNode->totalSubject;i++)
        {
            fin.getline(newNode->subject[i].subjectCode,20);
        
            fin.getline(newNode->subject[i].subjectName,50);
        
            fin>>newNode->subject[i].marks;
        
            fin>>newNode->subject[i].grade;
        
            fin.ignore();
        }

        if(fin.fail() || strlen(newNode->student.enrolledCourseCode)==0)
        {
            // Older result.txt files (saved before the Course module
            // existed) won't have this line, or end-of-file was reached
            // right after CGPA. Default to "NONE" instead of discarding
            // the whole record.
            strcpy(newNode->student.enrolledCourseCode,"NONE");
            fin.clear();
        }

        
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
    }

    fin.close();
}

// Edit student information
void ResultRecord::editRecord()
{
    char id[20];
    bool found=false;

    cout<<"\nEnter Student ID to edit : ";
    cin>>id;

    Node *current=head;

    while(current!=NULL)
    {
        if(strcmp(current->student.studentID,id)==0)
        {
            found=true;

            cin.ignore(1000,'\n');

            char tempName[50];

            cout<<"New Name : ";
            cin.getline(tempName,50);
            
            if(strlen(tempName)==0)
            {
                cout<<"Name Cannot Be Empty!"<<endl;
                return;
            }
            
            strcpy(current->student.name,tempName);

            cout<<"New Course : ";
            cin.getline(current->student.course,50);

            cout<<"New CGPA : ";
            cin>>current->student.cgpa;
            
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000,'\n');
            
                cout<<"Invalid Input"<<endl;
                return;
            }
            
            if(validateCGPA(current->student.cgpa)==0)
            {
                cout<<"Invalid CGPA!"<<endl;
                return;
            }
            
            cout<<"Record Updated Successfully!"<<endl;

            break;
        }

        current=current->next;
    }

    if(found==false)
    {
        cout<<"Student Not Found!"<<endl;
    }
}

void ResultRecord::searchRecord()
{
    try
    {
        char id[20];

        cout<<"\nEnter Student ID : ";
        cin>>id;

        if(cin.fail())
        {
            throw 1;
        }

        Node *current=head;

        while(current!=NULL)
        {
            if(strcmp(current->student.studentID,id)==0)
            {
                cout<<"\n========================================"<<endl;
                cout<<"            STUDENT FOUND"<<endl;
                cout<<"========================================"<<endl;

                cout<<left<<setw(15)<<"Student ID"<<": "<<current->student.studentID<<endl;
                cout<<left<<setw(15)<<"Name"<<": "<<current->student.name<<endl;
                cout<<left<<setw(15)<<"Course"<<": "<<current->student.course<<endl;
                cout<<left<<setw(15)<<"CGPA"<<": "<<fixed<<setprecision(2)<<current->student.cgpa<<endl;
                cout<<"========================================"<<endl;
                return;
            }
            current=current->next;
        }
        cout<<"Student Not Found!"<<endl;
    }
    catch(int)
    {
        cout<<"Invalid Input!"<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
    }
}

void ResultRecord::searchRecord(char id[])
{
    Node *current=head;

    while(current!=NULL)
    {
        if(strcmp(current->student.studentID,id)==0)
        {
            cout<<"Record Found!"<<endl;

            return;
        }

        current=current->next;
    }

    cout<<"Record Not Found!"<<endl;
}

// Add subject result
void ResultRecord::addSubject()
{
    try
    {
        char id[20];

        cout<<"\nEnter Student ID : ";
        cin>>id;

        if(cin.fail())
        {
            throw 1;
        }

        Node *current=head;

        while(current!=NULL)
        {
            if(strcmp(current->student.studentID,id)==0)
            {
                if(current->totalSubject>=10)
                {
                    cout<<"Subject List Full For This Student (Max 10)"<<endl;
                    return;
                }

                int n=current->totalSubject;

                cout<<"Subject Code : ";
                cin>>current->subject[n].subjectCode;

                cin.ignore(1000,'\n');

                cout<<"Subject Name : ";
                cin.getline(current->subject[n].subjectName,50);

                cout<<"Marks : ";
                cin>>current->subject[n].marks;

                if(cin.fail() || validateMarks(current->subject[n].marks)==0)
                {
                    cout<<"Invalid Marks. Must be between 0 and 100"<<endl;

                    cin.clear();
                    cin.ignore(1000,'\n');

                    return;
                }

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

        cout<<"Student Not Found!"<<endl;
    }
    catch(int)
    {
        cout<<"Invalid Input"<<endl;

        cin.clear();
        cin.ignore(1000,'\n');
    }
}

void ResultRecord::displaySubject()
{
    char id[20];

    cout<<"\nEnter Student ID : ";
    cin>>id;

    displaySubject(id);
}

void ResultRecord::displaySubject(char id[])
{
    Node *current=head;

    while(current!=NULL)
    {
        if(strcmp(current->student.studentID,id)==0)
        {
            cout<<"\n============================================================"<<endl;
            cout<<"                 STUDENT SUBJECT RECORD"<<endl;
            cout<<"============================================================"<<endl;
            cout<<"Student ID : "<<current->student.studentID<<endl;
            cout<<"Name       : "<<current->student.name<<endl;
            cout<<"\n------------------------------------------------------------"<<endl;
            if(current->totalSubject==0)
            {
                cout<<"No Subject Records Found!"<<endl;
                return;
            }

            cout<<left<<setw(15)<<"Code"<<setw(30)<<"Subject"<<setw(10)<<"Marks"<<setw(10)<<"Grade"<<endl;
            cout<<"------------------------------------------------------------"<<endl;

            for(int i=0;i<current->totalSubject;i++)
            {
                cout<<left<<setw(15)<<current->subject[i].subjectCode<<setw(30)<<current->subject[i].subjectName<<setw(10)<<current->subject[i].marks<<setw(10)<<current->subject[i].grade<<endl;
            }
            cout<<"------------------------------------------------------------"<<endl;
            return;
        }
        current=current->next;
    }
    cout<<"Student Not Found!"<<endl;
}

// Overloaded sortRecord: mode 1 = sort by ID, mode 2 = sort by CGPA
void ResultRecord::sortRecord(int mode)
{
    if(mode==1)
    {
        sortRecord();
    }
    else if(mode==2)
    {
        sortCGPA();
    }
    else
    {
        cout<<"Invalid Sort Mode!"<<endl;
    }
}

// Bubble Sort by Student ID
void ResultRecord::sortRecord()
{
    if(head==NULL)
    {
        cout<<"No Record Found!"<<endl;
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

            if(strcmp(current->student.studentID, nextNode->student.studentID)>0)
            {
                Student tempStudent;

                tempStudent=current->student;
                current->student=nextNode->student;
                nextNode->student=tempStudent;

                Subject tempSubject[10];

                for(int i=0;i<10;i++)
                {
                    tempSubject[i]=current->subject[i];
                    current->subject[i]=nextNode->subject[i];
                    nextNode->subject[i]=tempSubject[i];
                }

                int tempTotal;

                tempTotal=current->totalSubject;
                current->totalSubject=nextNode->totalSubject;
                nextNode->totalSubject=tempTotal;

                swap=true;
            }
            current=current->next;
        }
    }while(swap);

    cout<<"Records Sorted Successfully!"<<endl;
}

// Bubble Sort by CGPA
void ResultRecord::sortCGPA()
{
    if(head==NULL)
    {
        cout<<"No Record Found!"<<endl;
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

            if(current->student.cgpa < nextNode->student.cgpa)
            {
                Student tempStudent;

                tempStudent=current->student;
                current->student=nextNode->student;
                nextNode->student=tempStudent;

                Subject tempSubject[10];

                for(int i=0;i<10;i++)
                {
                    tempSubject[i]=current->subject[i];
                    current->subject[i]=nextNode->subject[i];
                    nextNode->subject[i]=tempSubject[i];
                }

                int tempTotal;

                tempTotal=current->totalSubject;
                current->totalSubject=nextNode->totalSubject;
                nextNode->totalSubject=tempTotal;

                swap=true;
            }

            current=current->next;
        }

    }while(swap);

    cout<<"Sorted by CGPA."<<endl;
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
    cout<<"\n===================================="<<endl;
    cout<<"         SUMMARY REPORT"<<endl;
    cout<<"===================================="<<endl;
    cout<<left<<setw(25)<<"Total Students"<<total<<endl;
    cout<<"===================================="<<endl;
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

    cout<<"Summary Saved Successfully!"<<endl;
}

// Search student by ID using Binary Search
void ResultRecord::binarySearch()
{
    sortRecord();
    Student arr[500];

    int count = 0;
    Node *current = head;
    while(current != NULL)
    {
        arr[count] = current->student;
        count++;
        current = current->next;
    }

    char target[20];

    cout<<"Enter Student ID : ";
    cin>>target;

    int left = 0;
    int right = count - 1;

    while(left <= right)
    {
        int mid = (left + right) / 2;

        if(strcmp(arr[mid].studentID,target)==0)
        {
            cout<<"\nStudent Found"<<endl;

            cout<<"Student ID : "
                <<arr[mid].studentID
                <<endl;

            cout<<"Name : "
                <<arr[mid].name
                <<endl;
            return;
        }
        else if(strcmp(arr[mid].studentID,target)<0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    cout<<"Student Not Found"<<endl;
}

// Save report into report.txt
void ResultRecord::generateReport()
{
    ofstream fout;

    fout.open("report.txt");

    Node *current=head;

    int total=0;

    float sum=0;

    int gradeA=0, gradeB=0, gradeC=0, gradeD=0, gradeF=0;

    while(current!=NULL)
    {
        total++;

        sum+=current->student.cgpa;

        for(int i=0;i<current->totalSubject;i++)
        {
            switch(current->subject[i].grade)
            {
            case 'A':
                gradeA++;
                break;
            case 'B':
                gradeB++;
                break;
            case 'C':
                gradeC++;
                break;
            case 'D':
                gradeD++;
                break;
            case 'F':
                gradeF++;
                break;
            }
        }

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

    fout<<endl<<"--- Grade Distribution (All Subjects) ---"<<endl;

    fout<<"Grade A : "<<gradeA<<endl;
    fout<<"Grade B : "<<gradeB<<endl;
    fout<<"Grade C : "<<gradeC<<endl;
    fout<<"Grade D : "<<gradeD<<endl;
    fout<<"Grade F : "<<gradeF<<endl;

    fout.close();

    cout<<"Report Generated Successfully!"<<endl;
}

// Read summary file
void ResultRecord::loadSummary()
{
    ifstream fin;

    char line[200];

    fin.open("summary.txt");

    if(fin.fail())
    {
        cout<<"Summary File Not Found!"<<endl;
        return;
    }

    cout<<"\n===== SUMMARY ====="<<endl;

    while(fin.getline(line,200))
    {
        cout<<line<<endl;
    }

    fin.close();
}

// Display report file
void ResultRecord::loadReport()
{
    ifstream fin;

    char line[200];

    fin.open("report.txt");

    if(fin.fail())
    {
        cout<<"Report File Not Found!"<<endl;
        return;
    }

    cout<<"\n===== REPORT ====="<<endl;

    while(fin.getline(line,200))
    {
        cout<<line<<endl;
    }

    fin.close();
}

void ResultRecord::deleteSubject(char id[])
{
    Node *current=head;

    while(current!=NULL)
    {
        if(strcmp(current->student.studentID,id)==0)
        {
            if(current->totalSubject==0)
            {
                cout<<"No Subject Record Found For This Student!"<<endl;
                return;
            }

            char code[20];

            cout<<"Enter Subject Code To Delete : ";
            cin>>code;

            int index=-1;

            for(int i=0;i<current->totalSubject;i++)
            {
                if(strcmp(current->subject[i].subjectCode,code)==0)
                {
                    index=i;
                    break;
                }
            }

            if(index==-1)
            {
                cout<<"Subject Not Found!"<<endl;
                return;
            }

            char confirm;

            cout<<"Delete This Subject Record? (Y/N) : ";
            cin>>confirm;

            if(confirm!='Y' && confirm!='y')
            {
                cout<<"Delete Cancelled"<<endl;
                return;
            }

            for(int i=index;i<current->totalSubject-1;i++)
            {
                current->subject[i]=current->subject[i+1];
            }

            current->totalSubject--;

            cout<<"Subject Record Deleted Successfully!"<<endl;

            return;
        }

        current=current->next;
    }

    cout<<"Student Not Found!"<<endl;
}

int ResultRecord::validateCGPA(float c)
{
    if(c<0.0 || c>4.0)
    {
        return 0;
    }

    return 1;
}

int ResultRecord::validateMarks(float m)
{
    if(m<0 || m>100)
    {
        return 0;
    }

    return 1;
}

bool ResultRecord::updateEnrolledCourse(char id[],char code[])
{
    Node *current=head;
    while(current!=NULL)
    {
        if(strcmp(current->student.studentID,id)==0)
        {
            if(strcmp(current->student.enrolledCourseCode,"NONE")!=0)
            {
                return false;
            }
            strcpy(current->student.enrolledCourseCode,code);
            
           return true;
        }
        current=current->next;
    }
    return false;
}

char ResultRecord::classifyCGPA(float c)
{
    if(c >= 3.67) return 'F';
    else if(c >= 3.00) return 'U';
    else if(c >= 2.00) return 'L';
    else if(c >= 1.00) return 'T';
    else return 'X';
}

void ResultRecord::classificationReport()
{
    if(head == NULL)
    {
        cout << "No Record Found!" << endl;
        return;
    }

    int countFirst = 0, countUpper = 0, countLower = 0, countThird = 0, countFail = 0;

    cout << "\n===== CGPA CLASSIFICATION REPORT =====" << endl;

    Node *current = head;
    while(current != NULL)
    {
        char band = classifyCGPA(current->student.cgpa);

        cout << current->student.studentID << " - "
             << current->student.name << " - CGPA "
             << current->student.cgpa << " - ";

        switch(band)
        {
        case 'F':
            cout << "First Class" << endl;
            countFirst++;
            break;
        case 'U':
            cout << "Second Class (Upper)" << endl;
            countUpper++;
            break;
        case 'L':
            cout << "Second Class (Lower)" << endl;
            countLower++;
            break;
        case 'T':
            cout << "Third Class" << endl;
            countThird++;
            break;
        default:
            cout << "Fail" << endl;
            countFail++;
        }

        current = current->next;
    }

    cout << "\n--- SUMMARY ---" << endl;
    cout << "First Class : " << countFirst << endl;
    cout << "Second Class (Upper) : " << countUpper << endl;
    cout << "Second Class (Lower) : " << countLower << endl;
    cout << "Third Class : " << countThird << endl;
    cout << "Fail : " << countFail << endl;
}

void ResultRecord::saveClassificationReport()
{
    if(head == NULL)
    {
        cout << "No Record Found!" << endl;
        return;
    }

    ofstream fout;
    fout.open("classification_report.txt");

    int countFirst = 0, countUpper = 0, countLower = 0, countThird = 0, countFail = 0;

    fout << "===== CGPA CLASSIFICATION REPORT =====" << endl;

    Node *current = head;
    while(current != NULL)
    {
        char band = classifyCGPA(current->student.cgpa);

        fout << current->student.studentID << " - "
             << current->student.name << " - CGPA "
             << current->student.cgpa << " - ";

        switch(band)
        {
        case 'F':
            fout << "First Class" << endl;
            countFirst++;
            break;
        case 'U':
            fout << "Second Class (Upper)" << endl;
            countUpper++;
            break;
        case 'L':
            fout << "Second Class (Lower)" << endl;
            countLower++;
            break;
        case 'T':
            fout << "Third Class" << endl;
            countThird++;
            break;
        default:
            fout << "Fail" << endl;
            countFail++;
        }

        current = current->next;
    }

    fout << "\n--- SUMMARY ---" << endl;
    fout << "First Class : " << countFirst << endl;
    fout << "Second Class (Upper) : " << countUpper << endl;
    fout << "Second Class (Lower) : " << countLower << endl;
    fout << "Third Class : " << countThird << endl;
    fout << "Fail : " << countFail << endl;

    fout.close();
    cout << "Classification report saved successfully to classification_report.txt." << endl;
}

void ResultRecord::deleteRecord()
{
    try
    {
        char id[20];

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
            if(strcmp(current->student.studentID,id)==0)
        {
            char confirm;
        
            cout<<"Delete This Student? (Y/N) : ";
            cin>>confirm;
        
            if(confirm!='Y' && confirm!='y')
            {
                cout<<"Delete Cancelled"<<endl;
                return;
            }
        
            if(current==head)
            {
                head=head->next;
            }
            else
            {
                previous->next=current->next;
            }
        
            delete current;
        
            cout<<"Record Deleted!"<<endl;
        
            return;
        }
            previous=current;
            current=current->next;
        }

        cout<<"Student not found!"<<endl;
    }

    catch(int)
    {
        cout<<"Invalid input!"<<endl;

        cin.clear();

        cin.ignore(1000,'\n');
    }
}

// ============================================================
// CourseManager Implementation
// ============================================================

void CourseManager::addRecord()
{
    try
    {
        CourseNode *newNode=new CourseNode;

        cout<<"\n===== ADD COURSE ====="<<endl;

        cout<<"Course Code : ";
        cin>>newNode->course.courseCode;

        if(searchRecord(newNode->course.courseCode)==true)
        {
            delete newNode;
            throw 3;
        }

        cin.ignore(1000,'\n');

        cout<<"Course Name : ";
        cin.getline(newNode->course.courseName,50);

        cout<<"Credit Hours : ";
        cin>>newNode->course.creditHours;

        if(cin.fail())
        {
            delete newNode;
            throw 1;
        }

        cout<<"Max Capacity : ";
        cin>>newNode->course.maxCapacity;

        if(cin.fail() || newNode->course.maxCapacity<=0)
        {
            delete newNode;
            throw 2;
        }

        newNode->course.enrolledCount=0;
        newNode->next=NULL;

        if(courseHead==NULL)
        {
            courseHead=newNode;
        }
        else
        {
            CourseNode *current=courseHead;

            while(current->next!=NULL)
            {
                current=current->next;
            }

            current->next=newNode;
        }

        cout<<"Course Added Successfully!"<<endl;
    }
    catch(int errorCode)
    {
        cin.clear();
        cin.ignore(1000,'\n');

        if(errorCode==2)
        {
            cout<<"Invalid Capacity! Must be a positive number."<<endl;
        }
        else if(errorCode==3)
        {
            cout<<"Course Code Already Exists!"<<endl;
        }
        else
        {
            cout<<"Invalid Input!"<<endl;
        }
    }
}

void CourseManager::addRecord(Course c)
{
    if(searchRecord(c.courseCode)==true)
    {
        return;
    }

    CourseNode *newNode=new CourseNode;

    newNode->course=c;
    newNode->next=NULL;

    if(courseHead==NULL)
    {
        courseHead=newNode;
    }
    else
    {
        CourseNode *current=courseHead;

        while(current->next!=NULL)
        {
            current=current->next;
        }

        current->next=newNode;
    }
}

void CourseManager::displayRecord()
{
    if(courseHead==NULL)
    {
        cout<<"No Course Found!"<<endl;
        return;
    }

    cout<<"\n==================== COURSE LIST ====================\n";

    cout<<left <<setw(15)<<"Code" <<setw(30)<<"Course Name" <<setw(15)<<"Credit" <<setw(15)<<"Enrolled" <<endl;
    cout<<"--------------------------------------------------------------"<<endl;
    CourseNode *current=courseHead;

    while(current!=NULL)
    {
        cout<<left<<setw(15)<<current->course.courseCode<<setw(30)<<current->course.courseName<<setw(15)<<current->course.creditHours;

        cout<<current->course.enrolledCount<<"/"<<current->course.maxCapacity<<endl;
            
        current=current->next;
    }
    cout<<"--------------------------------------------------------------"<<endl;
}

void CourseManager::displayRecord(char codeFilter[])
{
    if(courseHead==NULL)
    {
        cout<<"No Course Found!"<<endl;
        return;
    }

    bool any=false;

    CourseNode *current=courseHead;

    cout<<"\n===== FILTERED COURSE LIST ====="<<endl;

    while(current!=NULL)
    {
        if(strstr(current->course.courseCode,codeFilter)!=NULL)
        {
            cout<<"Course Code : "<<current->course.courseCode<<endl;
            cout<<"Course Name : "<<current->course.courseName<<endl;
            cout<<"Credit Hours : "<<current->course.creditHours<<endl;
            cout<<"Enrolled : "<<current->course.enrolledCount
                <<" / "<<current->course.maxCapacity<<endl;
            cout<<"---------------------"<<endl;

            any=true;
        }

        current=current->next;
    }

    if(any==false)
    {
        cout<<"No Matching Course Found!"<<endl;
    }
}

void CourseManager::searchRecord()
{
    char code[20];

    cout<<"Enter Course Code : ";
    cin>>code;

    if(searchRecord(code)==true)
    {
        CourseNode *current=courseHead;

        while(current!=NULL)
        {
            if(strcmp(current->course.courseCode,code)==0)
            {
                cout<<"\nCourse Found!"<<endl;
                cout<<"Course Name : "<<current->course.courseName<<endl;
                cout<<"Credit Hours : "<<current->course.creditHours<<endl;
                cout<<"Enrolled : "<<current->course.enrolledCount
                    <<" / "<<current->course.maxCapacity<<endl;
                return;
            }

            current=current->next;
        }
    }
    else
    {
        cout<<"Course not found!"<<endl;
    }
}

bool CourseManager::searchRecord(char code[])
{
    CourseNode *current=courseHead;

    while(current!=NULL)
    {
        if(strcmp(current->course.courseCode,code)==0)
        {
            return true;
        }

        current=current->next;
    }

    return false;
}

void CourseManager::sortRecord()
{
    if(courseHead==NULL || courseHead->next==NULL)
    {
        cout<<"Not Enough Courses To Sort"<<endl;
        return;
    }

    CourseNode *sorted=NULL;
    CourseNode *current=courseHead;

    while(current!=NULL)
    {
        CourseNode *next=current->next;

        if(sorted==NULL || sorted->course.creditHours>=current->course.creditHours)
        {
            current->next=sorted;
            sorted=current;
        }
        else
        {
            CourseNode *search=sorted;

            while(search->next!=NULL &&
                  search->next->course.creditHours<current->course.creditHours)
            {
                search=search->next;
            }

            current->next=search->next;
            search->next=current;
        }

        current=next;
    }

    courseHead=sorted;

    cout<<"Courses Sorted By Credit Hours Successfully!"<<endl;
}

void CourseManager::editCourse()
{
    char code[20];
    bool found=false;

    cout<<"Enter Course Code to edit : ";
    cin>>code;

    CourseNode *current=courseHead;

    while(current!=NULL)
    {
        if(strcmp(current->course.courseCode,code)==0)
        {
            found=true;

            cin.ignore(1000,'\n');

            cout<<"New Course Name : ";
            cin.getline(current->course.courseName,50);

            cout<<"New Credit Hours : ";
            cin>>current->course.creditHours;
            
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000,'\n');
            
                cout<<"Invalid Credit Hours"<<endl;
                return;
            }

            cout<<"New Max Capacity : ";
            cin>>current->course.maxCapacity;
            if(cin.fail() ||
               current->course.maxCapacity<=0)
            {
                cin.clear();
                cin.ignore(1000,'\n');
            
                cout<<"Invalid Capacity"<<endl;
                return;
            }

            cout<<"Course Updated Successfully!"<<endl;

            break;
        }

        current=current->next;
    }

    if(found==false)
    {
        cout<<"Course Not Found!"<<endl;
    }
}

void CourseManager::deleteCourse()
{
    char code[20];
    char confirm;

    cout<<"Enter Course Code to delete : ";
    cin>>code;

    cout<<"Delete This Course? (Y/N) : ";
    cin>>confirm;

    if(confirm!='Y' && confirm!='y')
    {
        cout<<"Delete Cancelled"<<endl;
        return;
    }

    CourseNode *current=courseHead;
    CourseNode *previous=NULL;

    while(current!=NULL)
    {
        if(strcmp(current->course.courseCode,code)==0)
        {
            if(current==courseHead)
            {
                courseHead=courseHead->next;
            }
            else
            {
                previous->next=current->next;
            }

            delete current;

            cout<<"Course Deleted Successfully!"<<endl;
            return;
        }

        previous=current;
        current=current->next;
    }

    cout<<"Course not found!"<<endl;
}

void CourseManager::saveCourseFile()
{
    ofstream fout;

    fout.open("courses.txt");

    CourseNode *current=courseHead;

    while(current!=NULL)
    {
        fout<<current->course.courseCode<<endl;
        fout<<current->course.courseName<<endl;
        fout<<current->course.creditHours<<endl;
        fout<<current->course.maxCapacity<<endl;
        fout<<current->course.enrolledCount<<endl;

        current=current->next;
    }

    fout.close();

    cout<<"Course data saved successfully!"<<endl;
}

void CourseManager::loadCourseFile()
{
    ifstream fin;

    fin.open("courses.txt");

    if(fin.fail())
    {
        return;
    }

    while(!fin.eof())
    {
        CourseNode *newNode=new CourseNode;

        fin>>newNode->course.courseCode;

        if(fin.fail())
        {
            delete newNode;
            break;
        }

        fin.ignore();

        fin.getline(newNode->course.courseName,50);

        fin>>newNode->course.creditHours;
        fin>>newNode->course.maxCapacity;
        fin>>newNode->course.enrolledCount;

        newNode->next=NULL;

        if(courseHead==NULL)
        {
            courseHead=newNode;
        }
        else
        {
            CourseNode *current=courseHead;

            while(current->next!=NULL)
            {
                current=current->next;
            }

            current->next=newNode;
        }
    }

    fin.close();
}

bool CourseManager::enrollStudent(ResultRecord &system, char studentID[], char code[])
{
    if(searchRecord(code)==false)
    {
        cout<<"Course Not Found!"<<endl;
        return false;
    }

    CourseNode *current=courseHead;

    while(current!=NULL)
    {
        if(strcmp(current->course.courseCode,code)==0)
        {
            if(current->course.enrolledCount>=current->course.maxCapacity)
            {
                cout<<"Course Is Full!"<<endl;
                return false;
            }

            if(system.updateEnrolledCourse(studentID,code)==false)
        {
            cout<<"Student Not Found OR Already Enrolled!"<<endl;
        
            return false;
        }

            current->course.enrolledCount++;

            cout<<"Enrolled Successfully Into "<<current->course.courseName<<endl;

            return true;
        }

        current=current->next;
    }

    return false;
}

void CourseManager::courseEnrollmentReport()
{
    if(courseHead==NULL)
    {
        cout<<"No Course Found!"<<endl;
        return;
    }

    sortRecord();

    ofstream fout;

    fout.open("course_report.txt");

    cout<<"\n===== COURSE ENROLLMENT REPORT ====="<<endl;
    fout<<"===== COURSE ENROLLMENT REPORT ====="<<endl;

    CourseNode *current=courseHead;

    while(current!=NULL)
    {
        cout<<current->course.courseCode<<" ("<<current->course.courseName
            <<") : "<<current->course.enrolledCount<<" / "
            <<current->course.maxCapacity<<endl;

        fout<<current->course.courseCode<<" ("<<current->course.courseName
            <<") : "<<current->course.enrolledCount<<" / "
            <<current->course.maxCapacity<<endl;

        current=current->next;
    }

    fout.close();
}

void welcomeScreen()
{
    clearScreen();

    cout << "\n";
    cout << "==================================================================" << endl;
    cout << " * " << endl;
    cout << " * * WELCOME TO STUDENT RESULT MANAGEMENT SYSTEM               " << endl;
    cout << " * * * " << endl;
    cout << " * * * * " << endl;
    cout << "==================================================================" << endl;
    cout << "\n"; 
    cout << "                    [ Press ENTER to Launch ]                     " << endl;
    cout << "\n";
    cout << "==================================================================" << endl;


    cin.get();
}

int roleMenu()
{
    int choice;

    clearScreen();

    cout<<"\n========== SELECT ROLE =========="<<endl;

    cout<<"1. Student"<<endl;
    cout<<"2. Admin"<<endl;
    cout<<"3. Exit"<<endl;

    cout<<"Enter Choice : ";
    cin>>choice;
    
    if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0; 
        }

    return choice;
}

int studentAccessMenu()
{
    int choice;

    clearScreen();

    cout<<"\n========== STUDENT =========="<<endl;

    cout<<"1. Login"<<endl;
    cout<<"2. Register"<<endl;
    cout<<"3. Back"<<endl;

    cout<<"Enter Choice : ";
    cin>>choice;
    
    if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0; 
        }

    return choice;
}

int adminAccessMenu()
{
    int choice;

    clearScreen();

    cout<<"\n========== ADMIN =========="<<endl;

    cout<<"1. Login"<<endl;
    cout<<"2. Register"<<endl;
    cout<<"3. Back"<<endl;

    cout<<"Enter Choice : ";
    cin>>choice;
    
    if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0; 
        }

    return choice;
}

// ============================================================
// MENUS WITH SCREEN CLEARING AND PAUSING INTEGRATION
// ============================================================
void adminMenu(ResultRecord &system, CourseManager &courses)
{
    int choice;

    do
    {
        clearScreen(); 

        cout<<"\n========== ADMIN MENU =========="<<endl;

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
        cout<<"12. View Report"<<endl;
        cout<<"13. View Statistics"<<endl;
        cout<<"14. Course Management"<<endl;
        cout<<"15. CGPA Classification Report"<<endl;
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
            pauseScreen(); 
            break;

        case 2:
            system.displayRecord();
            pauseScreen();
            break;

        case 3:
            system.editRecord();
            pauseScreen();
            break;

        case 4:
            system.deleteRecord();
            pauseScreen();
            break;

        case 5:
            system.searchRecord();
            pauseScreen();
            break;

        case 6:
            system.sortRecord(1);
            pauseScreen();
            break;

        case 7:
            system.sortRecord(2);
            pauseScreen();
            break;

        case 8:
            system.addSubject();
            pauseScreen();
            break;

        case 9:
            system.displaySubject();
            pauseScreen();
            break;

        case 10:
            system.binarySearch();
            pauseScreen();
            break;

        case 11:
            system.generateReport();
            pauseScreen();
            break;

        case 12:
            system.loadReport();
            pauseScreen();
            break;

        case 13:
            totalStudent(system);
            highestCGPA(system);
            lowestCGPA(system);
            averageCGPA(system);
            pauseScreen();
            break;

        case 14:
        {
            int courseChoice;

            do
            {
                clearScreen(); 

                cout<<"\n----- COURSE MANAGEMENT -----"<<endl;
                cout<<"1. Add Course"<<endl;
                cout<<"2. Display All Courses"<<endl;
                cout<<"3. Search Course"<<endl;
                cout<<"4. Edit Course"<<endl;
                cout<<"5. Delete Course"<<endl;
                cout<<"6. Sort Courses By Credit Hours"<<endl;
                cout<<"7. Course Enrollment Report"<<endl;
                cout<<"8. Back to Admin Menu"<<endl;

                cout<<"Enter Choice : ";
                cin>>courseChoice;
                
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    choice = 0; 
                }

                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000,'\n');
                    courseChoice=0;
                    
                    cout<<"\nInvalid Choice!"<<endl;
                    pauseScreen();
                    continue;
                }

                switch(courseChoice)
                {
                case 1:
                    courses.addRecord();
                    pauseScreen();
                    break;

                case 2:
                    courses.displayRecord();
                    pauseScreen();
                    break;

                case 3:
                    courses.searchRecord();
                    pauseScreen();
                    break;

                case 4:
                    courses.editCourse();
                    pauseScreen();
                    break;

                case 5:
                    courses.deleteCourse();
                    pauseScreen();
                    break;

                case 6:
                    courses.sortRecord();
                    pauseScreen();
                    break;

                case 7:
                    courses.courseEnrollmentReport();
                    pauseScreen();
                    break;

                case 8:
                    cout<<"Back to Admin Menu"<<endl;
                    break;

                default:
                    cout<<"Invalid Choice!"<<endl;
                    pauseScreen();
                }

            }while(courseChoice!=8);

            break;
        }

        case 15:
        {
            int subChoice;
            cout<<"\n----- CGPA CLASSIFICATION -----"<<endl;
            cout<<"1. View On Screen"<<endl;
            cout<<"2. Save To File"<<endl;
            cout<<"Enter Choice : ";
            cin>>subChoice;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                subChoice = 0; 
            }

            if(subChoice==2)
            {
                system.saveClassificationReport();
            }
            else
            {
                system.classificationReport();
            }
            pauseScreen();
            break;
        }

        case 16:
            {
                char confirm;
            
                cout<<"Are you sure you want to exit? (Y/N) : ";
                cin>>confirm;
            
                if(confirm=='Y' || confirm=='y')
                {
                    choice=16;
                }
                else
                {
                    choice=0;
                }
            
                break;
            }

        default:
            cout<<"Invalid Choice!"<<endl;
            pauseScreen();
        }

    }while(choice!=16);
}

void studentMenu(StudentUser &student, ResultRecord &system, CourseManager &courses)
{
    int choice;

    do
    {
        clearScreen(); 

        cout<<"\n========== STUDENT MENU =========="<<endl;

        cout<<"1. My Profile"<<endl;
        cout<<"2. Display Result"<<endl;
        cout<<"3. Search Student"<<endl;
        cout<<"4. Summary Report"<<endl;
        cout<<"5. Save Summary"<<endl;
        cout<<"6. View Saved Summary"<<endl;
        cout<<"7. Browse Available Courses"<<endl;
        cout<<"8. Enroll In A Course"<<endl;
        cout<<"9. Sort Result By Student ID"<<endl;
        cout<<"10. Sort Result By CGPA"<<endl;
        cout<<"11. Delete My Subject Record"<<endl;
        cout<<"12. Exit"<<endl;

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
            student.profileMenu();
            break;

        case 2:
            system.displayRecord();
            pauseScreen();
            break;

        case 3:
            system.searchRecord();
            pauseScreen();
            break;

        case 4:
            system.summaryReport();
            pauseScreen();
            break;

        case 5:
            system.saveSummary();
            pauseScreen();
            break;

        case 6:
            system.loadSummary();
            pauseScreen();
            break;

        case 7:
            courses.displayRecord();
            pauseScreen();
            break;

        case 8:
        {
            char courseCode[20];
            cout<<"Enter Course Code : ";
            cin>>courseCode;
            courses.enrollStudent(
                system,
                (char*)student.getStudentID(),
                courseCode
            );
            pauseScreen();
            break;
        }

        case 9:
            system.sortRecord(1);
            pauseScreen();
            break;

        case 10:
            system.sortRecord(2);
            pauseScreen();
            break;

        case 11:
            system.deleteSubject((char*)student.getStudentID());
            pauseScreen();
            break;

        case 12:
            {
                char confirm;
            
                cout<<"Are you sure you want to exit? (Y/N) : ";
                cin>>confirm;
            
                if(confirm=='Y' || confirm=='y')
                {
                    choice=12;
                }
                else
                {
                    choice=0;
                }
            
                break;
            }

        default:
            cout<<"Invalid Choice!"<<endl;
            pauseScreen();
        }

    }while(choice!=12);
}


int main()
{
    StudentUser student;
    Admin admin;
    ResultRecord system;
    CourseManager courses;

        welcomeScreen();

    int roleChoice;

    do
    {
        roleChoice = roleMenu();

        switch(roleChoice)
        {
            case 1:
            {
                int studentChoice;

                do
                {
                    studentChoice = studentAccessMenu();

                    switch(studentChoice)
                    {
                        case 1:

                            if(student.login())
                            {
                                studentMenu(student,system,courses);
                                student.logout();
                            }

                            pauseScreen();
                            break;

                        case 2:

                            student.registerAccount(system);
                            pauseScreen();
                            break;

                        case 3:

                            break;

                        default:

                            cout<<"\nInvalid Choice!"<<endl;
                            pauseScreen();
                    }

                }while(studentChoice!=3);

                break;
            }

            case 2:
            {
                int adminChoice;

                do
                {
                    adminChoice = adminAccessMenu();

                    switch(adminChoice)
                    {
                        case 1:

                            if(admin.login())
                            {
                                adminMenu(system,courses);
                                admin.logout();
                            }

                            pauseScreen();
                            break;

                        case 2:

                            admin.registerAccount();
                            pauseScreen();
                            break;

                        case 3:

                            break;

                        default:

                            cout<<"\nInvalid Choice!"<<endl;
                            pauseScreen();
                    }

                }while(adminChoice!=3);

                break;
            }

            case 3:

                cout<<"Thank You"<<endl;
                break;

            default:

                cout<<"Invalid Choice!"<<endl;
                pauseScreen();
        }

    }while(roleChoice!=3);

    return 0;
}