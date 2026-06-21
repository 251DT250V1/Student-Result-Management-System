#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
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
    int studentID;
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

    // Shared utility (not virtual -- both StudentUser and Admin call this
    // exact same logic) that appends a line to the security log file.
    // role identifies which module triggered the event (e.g. "STUDENT",
    // "ADMIN") so the single log file can be read back and understood
    // for both modules without needing two separate files.
    void logSecurityEvent(const char role[], const char user[], const char outcome[])
    {
        ofstream fout;

        fout.open("security_log.txt",ios::app);

        fout<<"["<<role<<"] User: "<<user<<" - "<<outcome<<endl;

        fout.close();
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

public:

    StudentUser()
    {
    strcpy(username, "");
    strcpy(password, "");
    }

    void registerAccount();

    bool login();

    void logout();
    void profileMenu();
	void viewProfile();
	void changePassword();

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

    void displayRecord(int id);

    void searchRecord();

    void searchRecord(int id);

    void sortRecord();

    void sortRecord(int mode);

    void editRecord();

    void deleteRecord();

    void sortCGPA();

    void addSubject();

    void displaySubject();

    void displaySubject(int id);

    void saveFile();

    void loadFile();

    void summaryReport();

    void saveSummary();

    void binarySearch();

    void generateReport();

    void generateReport(int id);

    void loadSummary();

    void loadReport();

    void searchSubject();

    void sortSubject();

    void topScorer();

    int validateCGPA(float c);

    int validateMarks(float m);

    bool updateEnrolledCourse(int id, char code[]);

    void getEnrolledCourse(int id, char result[]);

    char classifyCGPA(float c);

    void classificationReport();

    void saveClassificationReport();

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

    void searchRecord();

    bool searchRecord(char code[]);

    void sortRecord();

    void editCourse();

    void deleteCourse();

    void loadCourseFile();

    void saveCourseFile();

    bool enrollStudent(ResultRecord &system, int studentID, char code[]);

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
void StudentUser::registerAccount()
{
    try
    {
        ofstream fout;

        fout.open("student.txt",ios::app);

        cout<<"\n===== STUDENT REGISTER ====="<<endl;
        cin.ignore();

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

// Student Login
// Single login attempt: prompts once, checks credentials against
// student.txt, and reports success/failure. Returns true on success.
// Throws 2 if no student.txt exists yet, 1 if input was empty.
bool StudentUser::attemptLogin()
{
    try
    {
        ifstream fin;

        string u,p;

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
// them out for this session. Every attempt (success or failure) is
// recorded through the shared logSecurityEvent() helper inherited
// from User, so admin.txt/student.txt credentials being guessed
// repeatedly leaves a trail in security_log.txt.
bool StudentUser::login()
{
    failedAttempts=0;

    cout<<"\n===== STUDENT LOGIN ====="<<endl;
    cin.ignore();

    while(failedAttempts<3)
    {
        if(attemptLogin())
        {
            logSecurityEvent("STUDENT",username,"LOGIN SUCCESS");
            return true;
        }

        failedAttempts++;

        logSecurityEvent("STUDENT",username,"LOGIN FAILED");

        if(failedAttempts<3)
        {
            cout<<"Attempt "<<failedAttempts<<" of 3 failed. Try again."<<endl;
        }
    }

    cout<<"Too Many Failed Attempts. Account Locked For This Session."<<endl;

    logSecurityEvent("STUDENT",username,"ACCOUNT LOCKED");

    return false;
}

// Student Logout
void StudentUser::logout()
{
    cout<<"Student Logout Successfully"<<endl;
}

void StudentUser::viewProfile()
{
    cout<<"\n===== MY PROFILE ====="<<endl;

    cout<<"Username : "
        <<username
        <<endl;

    cout<<"Role : Student"<<endl;
}

void StudentUser::changePassword()
{
    char newPassword[50];

    cin.ignore();

    cout<<"Enter New Password : ";
    cin.getline(newPassword,50);

    if(strlen(newPassword)==0)
    {
        cout<<"Password Cannot Be Empty"<<endl;
        return;
    }

    ifstream fin("student.txt");
    ofstream fout("temp.txt");

    string u,p;

    while(getline(fin,u) && getline(fin,p))
    {
        if(u==username)
        {
            fout<<u<<endl;
            fout<<newPassword<<endl;

            strcpy(password,newPassword);
        }
        else
        {
            fout<<u<<endl;
            fout<<p<<endl;
        }
    }

    fin.close();
    fout.close();

    remove("student.txt");
    rename("temp.txt","student.txt");

    cout<<"Password Changed Successfully"<<endl;
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

        cin.ignore();
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

        string u,p;

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

        while(getline(fin,u) && getline(fin,p))
        {
            if(username==u && password==p)
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

// Public login: same 3-attempt lockout policy as StudentUser::login,
// logged with role "ADMIN" so both modules share one readable log file.
bool Admin::login()
{
    failedAttempts=0;

    cout<<"\n===== ADMIN LOGIN ====="<<endl;
    cin.ignore();

    while(failedAttempts<3)
    {
        if(attemptLogin())
        {
            logSecurityEvent("ADMIN",username,"LOGIN SUCCESS");
            return true;
        }

        failedAttempts++;

        logSecurityEvent("ADMIN",username,"LOGIN FAILED");

        if(failedAttempts<3)
        {
            cout<<"Attempt "<<failedAttempts<<" of 3 failed. Try again."<<endl;
        }
    }

    cout<<"Too Many Failed Attempts. Account Locked For This Session."<<endl;

    logSecurityEvent("ADMIN",username,"ACCOUNT LOCKED");

    return false;
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
		    if(check->student.studentID==
		       newNode->student.studentID)
		    {
		        delete newNode;
		
		        cout<<"Student ID Already Exists!"<<endl;
		
		        return;
		    }
		
		    check=check->next;
		}

        cin.ignore();

        cout<<"Student Name : ";
        cin.getline(newNode->student.name,50);

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

    cout<<"\n===== STUDENT LIST  ====="<<endl;

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

    cout<<"Student Not Found!"<<endl;
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

        fin.ignore();

        fin.getline(newNode->student.name,50);

        fin.getline(newNode->student.course,50);

        fin>>newNode->student.cgpa;

        if(fin.fail())
        {
            delete newNode;
            break;
        }

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

    cout<<"Student Not Found!"<<endl;
}
catch(int)
    {
        cout<<"Invalid Input!"<<endl;

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
                if(current->totalSubject>=10)
                {
                    cout<<"Subject List Full For This Student (Max 10)"<<endl;
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
    int id;

    cout<<"\nEnter Student ID : ";
    cin>>id;

    displaySubject(id);
}

// Overloaded displaySubject: takes the ID directly, no prompt.
// Reused internally (e.g. by topScorer()) and could be called by any
// future feature that already knows which student it wants to show.
void ResultRecord::displaySubject(int id)
{
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

    cout<<"Student Not Found!"<<endl;
}

// Overloaded sortRecord: mode 1 = sort by ID, mode 2 = sort by CGPA
// This lets the menu call one function instead of two separate ones.
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

    cout<<"Summary Saved Successfully!"<<endl;
}

// Search student by ID using Binary Search
void ResultRecord::binarySearch()
{
    if(head == NULL) {
        cout << "No record found in memory." << endl;
        return;
    }

    sortRecord();

    Student arr[500];

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
        cout<<"Student Not Found!"<<endl;
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

// Overloaded generateReport: produces a focused report for a single
// student instead of the whole system. Saved to the same report.txt
// so the existing loadReport() viewer/file requirement still applies.
void ResultRecord::generateReport(int id)
{
    Node *current=head;

    while(current!=NULL)
    {
        if(current->student.studentID==id)
        {
            ofstream fout;

            fout.open("report.txt");

            fout<<"===== Individual Student Report ====="<<endl;

            fout<<"Student ID : "<<current->student.studentID<<endl;
            fout<<"Name : "<<current->student.name<<endl;
            fout<<"Course : "<<current->student.course<<endl;
            fout<<"CGPA : "<<current->student.cgpa<<endl;

            fout<<endl<<"--- Subjects ---"<<endl;

            for(int i=0;i<current->totalSubject;i++)
            {
                fout<<current->subject[i].subjectCode<<" - "
                    <<current->subject[i].subjectName<<" : "
                    <<current->subject[i].marks<<" ("
                    <<current->subject[i].grade<<")"<<endl;
            }

            fout.close();

            cout<<"Individual Report Generated Successfully!"<<endl;

            return;
        }

        current=current->next;
    }

    cout<<"Student Not Found!"<<endl;
}

// Read summary file
void ResultRecord::loadSummary()
{
    ifstream fin;

    string line;

    fin.open("summary.txt");

    if(fin.fail())
    {
        cout<<"Summary File Not Found!"<<endl;
        return;
    }

    cout<<"\n===== SUMMARY ====="<<endl;

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
        cout<<"Report File Not Found!"<<endl;
        return;
    }

    cout<<"\n===== REPORT ====="<<endl;

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
                cout<<"\nSubject Found!"<<endl;

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

    cout<<"Subject Not Found!"<<endl;
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

    cout<<"Subject Sorted Successfully!"<<endl;
}

// Validates that a CGPA value falls within the accepted range (0.0 - 4.0).
// Returns 1 if valid, 0 if invalid. Used to keep bad manual input from
// silently corrupting a student's record.
int ResultRecord::validateCGPA(float c)
{
    if(c<0.0 || c>4.0)
    {
        return 0;
    }

    return 1;
}

// Validates that a subject mark falls within the accepted range (0 - 100).
// Returns 1 if valid, 0 if invalid.
int ResultRecord::validateMarks(float m)
{
    if(m<0 || m>100)
    {
        return 0;
    }

    return 1;
}

// Finds and displays the student with the highest CGPA, then shows
// their subject breakdown using the overloaded displaySubject(int).
// Demonstrates re-use of an existing overload rather than duplicating logic.
void ResultRecord::topScorer()
{
    if(head==NULL)
    {
        cout<<"No Record Found!"<<endl;
        return;
    }

    Node *current=head;
    Node *best=head;

    while(current!=NULL)
    {
        if(current->student.cgpa>best->student.cgpa)
        {
            best=current;
        }

        current=current->next;
    }

    cout<<"\n===== TOP SCORER ====="<<endl;

    cout<<"Student ID : "<<best->student.studentID<<endl;
    cout<<"Name : "<<best->student.name<<endl;
    cout<<"Course : "<<best->student.course<<endl;
    cout<<"CGPA : "<<best->student.cgpa<<endl;

    displaySubject(best->student.studentID);
}

// Used by CourseManager::enrollStudent() to write the enrolled course
// code onto the matching student's record. Returns false if the
// student ID doesn't exist, so the caller can report that cleanly.
bool ResultRecord::updateEnrolledCourse(int id, char code[])
{
    Node *current=head;
    while(current!=NULL)
    {
        if(current->student.studentID==id)
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

// Used by the Student menu to show which course a student is
// currently enrolled in, by writing the code into the caller's buffer.
void ResultRecord::getEnrolledCourse(int id, char result[])
{
    Node *current=head;

    while(current!=NULL)
    {
        if(current->student.studentID==id)
        {
            strcpy(result,current->student.enrolledCourseCode);
            return;
        }

        current=current->next;
    }

    strcpy(result,"UNKNOWN");
}

// Classifies a single CGPA value into a degree classification band
// following the standard Malaysian university scale. Returns a single
// character code so classificationReport() can both print the full
// label and tally counts using a compact switch.
// 'F' = First Class, 'U' = Second Upper, 'L' = Second Lower,
// 'T' = Third Class, 'X' = Fail
char ResultRecord::classifyCGPA(float c)
{
    if(c>=3.67)
    {
        return 'F';
    }
    else if(c>=3.00)
    {
        return 'U';
    }
    else if(c>=2.00)
    {
        return 'L';
    }
    else if(c>=1.00)
    {
        return 'T';
    }
    else
    {
        return 'X';
    }
}

// Displays every student grouped by classification band, then a
// tally of how many students fall into each band. Pure console
// version; saveClassificationReport() is the file-writing counterpart.
void ResultRecord::classificationReport()
{
    if(head==NULL)
    {
        cout<<"No Record Found!"<<endl;
        return;
    }

    int countFirst=0, countUpper=0, countLower=0, countThird=0, countFail=0;

    cout<<"\n===== CGPA CLASSIFICATION REPORT ====="<<endl;

    Node *current=head;

    while(current!=NULL)
    {
        char band=classifyCGPA(current->student.cgpa);

        cout<<current->student.studentID<<" - "
            <<current->student.name<<" - CGPA "
            <<current->student.cgpa<<" - ";

        switch(band)
        {
        case 'F':
            cout<<"First Class"<<endl;
            countFirst++;
            break;

        case 'U':
            cout<<"Second Class (Upper)"<<endl;
            countUpper++;
            break;

        case 'L':
            cout<<"Second Class (Lower)"<<endl;
            countLower++;
            break;

        case 'T':
            cout<<"Third Class"<<endl;
            countThird++;
            break;

        default:
            cout<<"Fail"<<endl;
            countFail++;
        }

        current=current->next;
    }

    cout<<"\n--- SUMMARY ---"<<endl;
    cout<<"First Class : "<<countFirst<<endl;
    cout<<"Second Class (Upper) : "<<countUpper<<endl;
    cout<<"Second Class (Lower) : "<<countLower<<endl;
    cout<<"Third Class : "<<countThird<<endl;
    cout<<"Fail : "<<countFail<<endl;
}

// Same classification logic as classificationReport(), but writes
// the breakdown to classification_report.txt instead of (or as well
// as) printing it, satisfying the "save to txt / retrieve from txt"
// pattern already used elsewhere in the system.
void ResultRecord::saveClassificationReport()
{
    if(head==NULL)
    {
        cout<<"No Record Found!"<<endl;
        return;
    }

    ofstream fout;

    fout.open("classification_report.txt");

    int countFirst=0, countUpper=0, countLower=0, countThird=0, countFail=0;

    fout<<"===== CGPA CLASSIFICATION REPORT ====="<<endl;

    Node *current=head;

    while(current!=NULL)
    {
        char band=classifyCGPA(current->student.cgpa);

        fout<<current->student.studentID<<" - "
            <<current->student.name<<" - CGPA "
            <<current->student.cgpa<<" - ";

        switch(band)
        {
        case 'F':
            fout<<"First Class"<<endl;
            countFirst++;
            break;

        case 'U':
            fout<<"Second Class (Upper)"<<endl;
            countUpper++;
            break;

        case 'L':
            fout<<"Second Class (Lower)"<<endl;
            countLower++;
            break;

        case 'T':
            fout<<"Third Class"<<endl;
            countThird++;
            break;

        default:
            fout<<"Fail"<<endl;
            countFail++;
        }

        current=current->next;
    }

    fout<<"\n--- SUMMARY ---"<<endl;
    fout<<"First Class : "<<countFirst<<endl;
    fout<<"Second Class (Upper) : "<<countUpper<<endl;
    fout<<"Second Class (Lower) : "<<countLower<<endl;
    fout<<"Third Class : "<<countThird<<endl;
    fout<<"Fail : "<<countFail<<endl;

    fout.close();

    cout<<"Classification report saved successfully."<<endl;
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

        cin.ignore();

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

    cout<<"\n===== COURSE LIST ====="<<endl;

    CourseNode *current=courseHead;

    while(current!=NULL)
    {
        cout<<"Course Code : "<<current->course.courseCode<<endl;
        cout<<"Course Name : "<<current->course.courseName<<endl;
        cout<<"Credit Hours : "<<current->course.creditHours<<endl;
        cout<<"Enrolled : "<<current->course.enrolledCount
            <<" / "<<current->course.maxCapacity<<endl;
        cout<<"---------------------"<<endl;

        current=current->next;
    }
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

            cin.ignore();

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

bool CourseManager::enrollStudent(ResultRecord &system, int studentID, char code[])
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
    cout << " *								                                   " << endl;
    cout << " * *	WELCOME TO STUDENT RESULT MANAGEMENT SYSTEM   	           " << endl;
    cout << " * * *                          				                   " << endl;
    cout << " * * * *                                        		           " << endl;
    cout << "==================================================================" << endl;
    cout << "\n"; 
    cout << "                    [ Press ENTER to Launch ]                    " << endl;
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
        cout<<"11. Generate Report (All Students)"<<endl;
        cout<<"12. Search Subject"<<endl;
        cout<<"13. Sort Subject"<<endl;
        cout<<"14. View Report"<<endl;
        cout<<"15. View Statistics"<<endl;
        cout<<"16. Top Scorer"<<endl;
        cout<<"17. Generate Report (Single Student)"<<endl;
        cout<<"18. Course Management"<<endl;
        cout<<"19. CGPA Classification Report"<<endl;
        cout<<"20. Exit"<<endl;

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
            system.searchSubject();
            pauseScreen();
            break;

        case 13:
            system.sortSubject();
            pauseScreen();
            break;

        case 14:
            system.loadReport();
            pauseScreen();
            break;

        case 15:
            totalStudent(system);
            highestCGPA(system);
            lowestCGPA(system);
            averageCGPA(system);
            pauseScreen();
            break;

        case 16:
            system.topScorer();
            pauseScreen();
            break;

        case 17:
        {
            int reportID;

            cout<<"Enter Student ID : ";
            cin>>reportID;

            system.generateReport(reportID);
            pauseScreen();
            break;
        }

        case 18:
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

        case 19:
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
            choice = 0; 
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

        case 20:
            {
			    char confirm;
			
			    cout<<"Are you sure you want to exit? (Y/N) : ";
			    cin>>confirm;
			
			    if(confirm=='Y' || confirm=='y')
			    {
			        choice=20;
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

    }while(choice!=20);
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
		cout<<"8. Search Course"<<endl;
		cout<<"9. Enroll In A Course"<<endl;
		cout<<"10. View My Enrolled Course"<<endl;
		cout<<"11. Exit"<<endl;

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
            courses.searchRecord();
            pauseScreen();
            break;

        case 9:
        {
            int studentID;
            char courseCode[20];

            cout<<"Enter Your Student ID : ";
            cin>>studentID;

            cout<<"Enter Course Code : ";
            cin>>courseCode;

            courses.enrollStudent(system,studentID,courseCode);
            pauseScreen();
            break;
        }

        case 10:
        {
            int studentID;
            char result[20];

            cout<<"Enter Your Student ID : ";
            cin>>studentID;

            system.getEnrolledCourse(studentID,result);

            cout<<"Enrolled Course Code : "<<result<<endl;
            pauseScreen();
            break;
        }

        case 11:
            {
			    char confirm;
			
			    cout<<"Are you sure you want to exit? (Y/N) : ";
			    cin>>confirm;
			
			    if(confirm=='Y' || confirm=='y')
			    {
			        choice=11;
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

    }while(choice!=11);
}


int main()
{
    StudentUser student;
    Admin admin;
    ResultRecord system;
    CourseManager courses;

    int choice;

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

                            student.registerAccount();
                            pauseScreen();
                            break;
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
    