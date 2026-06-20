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

    ~StudentUser()
    {
     cout<<"Student Object Deleted"<<endl;
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

        cout<<"Course Memory Released"<<endl;
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

        cout<<"\n===== Student Register ====="<<endl;
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

        cout<<"Register Successfully"<<endl;
    }
    catch(int)
    {
        cout<<"Registration Failed: Username and Password cannot be empty"<<endl;
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
            cout<<"Wrong Username or Password"<<endl;
            return false;
        }
    }
    catch(int errorCode)
    {
        if(errorCode==2)
        {
            cout<<"No Registered Students Found. Please Register First"<<endl;
        }
        else
        {
            cout<<"Login Failed: Username and Password cannot be empty"<<endl;
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

    cout<<"\n===== Student Login ====="<<endl;
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

// Admin Register
void Admin::registerAccount()
{
    try
    {
        ofstream fout;

        fout.open("admin.txt",ios::app);

        cout<<"\n===== Admin Register ====="<<endl;

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

        cout<<"Register Successfully"<<endl;
    }
    catch(int)
    {
        cout<<"Registration Failed: Username and Password cannot be empty"<<endl;
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
            cout<<"Login Successful"<<endl;
            return true;
        }
        else
        {
            cout<<"Wrong Username or Password"<<endl;
            return false;
        }
    }
    catch(int errorCode)
    {
        if(errorCode==2)
        {
            cout<<"No Registered Admin Found. Please Register First"<<endl;
        }
        else
        {
            cout<<"Login Failed: Username and Password cannot be empty"<<endl;
        }

        return false;
    }
}

// Public login: same 3-attempt lockout policy as StudentUser::login,
// logged with role "ADMIN" so both modules share one readable log file.
bool Admin::login()
{
    failedAttempts=0;

    cout<<"\n===== Admin Login ====="<<endl;
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
            delete newNode;
            throw 1;
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

        cout<<"Student Added Successfully"<<endl;
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
        fout<<current->student.enrolledCourseCode<<endl;

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

        if(fin.fail())
        {
            delete newNode;
            break;
        }

        fin.ignore();

        fin.getline(newNode->student.enrolledCourseCode,20);

        if(fin.fail() || strlen(newNode->student.enrolledCourseCode)==0)
        {
            // Older result.txt files (saved before the Course module
            // existed) won't have this line, or end-of-file was reached
            // right after CGPA. Default to "NONE" instead of discarding
            // the whole record.
            strcpy(newNode->student.enrolledCourseCode,"NONE");
            fin.clear();
        }

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

        cout<<"Student Not Found"<<endl;
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

    cout<<"Student Not Found"<<endl;
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
        cout<<"Invalid Sort Mode"<<endl;
    }
}

// Bubble Sort by Student ID

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

    cout<<"Report Generated Successfully"<<endl;
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

            cout<<"Individual Report Generated Successfully"<<endl;

            return;
        }

        current=current->next;
    }

    cout<<"Student Not Found"<<endl;
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
        cout<<"No Record Found"<<endl;
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

    cout<<"\n===== Top Scorer ====="<<endl;

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
        cout<<"No Record Found"<<endl;
        return;
    }

    int countFirst=0, countUpper=0, countLower=0, countThird=0, countFail=0;

    cout<<"\n===== CGPA Classification Report ====="<<endl;

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

    cout<<"\n--- Summary ---"<<endl;
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
        cout<<"No Record Found"<<endl;
        return;
    }

    ofstream fout;

    fout.open("classification_report.txt");

    int countFirst=0, countUpper=0, countLower=0, countThird=0, countFail=0;

    fout<<"===== CGPA Classification Report ====="<<endl;

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

    fout<<"\n--- Summary ---"<<endl;
    fout<<"First Class : "<<countFirst<<endl;
    fout<<"Second Class (Upper) : "<<countUpper<<endl;
    fout<<"Second Class (Lower) : "<<countLower<<endl;
    fout<<"Third Class : "<<countThird<<endl;
    fout<<"Fail : "<<countFail<<endl;

    fout.close();

    cout<<"Classification Report Saved Successfully"<<endl;
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

// ============================================================
// CourseManager Implementation
// A second dynamic non-primitive data structure (linked list of
// CourseNode) tracking the course catalogue. Demonstrates the same
// Record interface used by ResultRecord but applied to a different
// entity, and adds a second manually-implemented sorting algorithm
// (insertion sort) distinct from the bubble sort used for students.
// ============================================================

// Add a course interactively (Admin only).
void CourseManager::addRecord()
{
    try
    {
        CourseNode *newNode=new CourseNode;

        cout<<"\n===== Add Course ====="<<endl;

        cout<<"Course Code : ";
        cin>>newNode->course.courseCode;

        // Reject duplicate course codes so the catalogue stays consistent.
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

        cout<<"Course Added Successfully"<<endl;
    }
    catch(int errorCode)
    {
        cin.clear();
        cin.ignore(1000,'\n');

        if(errorCode==2)
        {
            cout<<"Invalid Capacity. Must be a positive number"<<endl;
        }
        else if(errorCode==3)
        {
            cout<<"Course Code Already Exists"<<endl;
        }
        else
        {
            cout<<"Invalid Input"<<endl;
        }
    }
}

// Overloaded addRecord: accepts a ready-made Course struct directly,
// the same pattern used by ResultRecord::addRecord(Student s).
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
        cout<<"No Course Found"<<endl;
        return;
    }

    cout<<"\n===== Course List ====="<<endl;

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

// Overloaded displayRecord: filters the course list so only courses
// whose code contains the given substring are shown. Lets the Customer
// module browse a narrower list instead of the entire catalogue.
void CourseManager::displayRecord(char codeFilter[])
{
    if(courseHead==NULL)
    {
        cout<<"No Course Found"<<endl;
        return;
    }

    bool any=false;

    CourseNode *current=courseHead;

    cout<<"\n===== Filtered Course List ====="<<endl;

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
        cout<<"No Matching Course Found"<<endl;
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
                cout<<"\nCourse Found"<<endl;
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
        cout<<"Course Not Found"<<endl;
    }
}

// Overloaded searchRecord: returns a bool instead of printing, so it
// can be reused internally (duplicate-check in addRecord, validity
// check in enrollStudent) without producing console output.
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

// Insertion Sort by Credit Hours (ascending) — a second manually
// implemented sorting algorithm distinct from the bubble sort used
// for student records, applied here to the course linked list.
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

    cout<<"Courses Sorted By Credit Hours Successfully"<<endl;
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

            cout<<"New Max Capacity : ";
            cin>>current->course.maxCapacity;

            cout<<"Course Updated Successfully"<<endl;

            break;
        }

        current=current->next;
    }

    if(found==false)
    {
        cout<<"Course Not Found"<<endl;
    }
}

void CourseManager::deleteCourse()
{
    char code[20];

    cout<<"Enter Course Code to delete : ";
    cin>>code;

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

            cout<<"Course Deleted Successfully"<<endl;

            return;
        }

        previous=current;
        current=current->next;
    }

    cout<<"Course Not Found"<<endl;
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

    cout<<"Course Data Saved Successfully"<<endl;
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

// Enrolls a student into a course: validates the student exists (via
// ResultRecord), the course exists and has capacity, then updates
// both the course's enrolledCount and the student's enrolledCourseCode.
// This is the link that keeps the Customer and Staff modules consistent
// with each other -- an enrollment made by a student is immediately
// visible to Admin through the same shared ResultRecord and courses.txt.
bool CourseManager::enrollStudent(ResultRecord &system, int studentID, char code[])
{
    if(searchRecord(code)==false)
    {
        cout<<"Course Not Found"<<endl;
        return false;
    }

    CourseNode *current=courseHead;

    while(current!=NULL)
    {
        if(strcmp(current->course.courseCode,code)==0)
        {
            if(current->course.enrolledCount>=current->course.maxCapacity)
            {
                cout<<"Course Is Full"<<endl;
                return false;
            }

            if(system.updateEnrolledCourse(studentID,code)==false)
            {
                cout<<"Student Not Found"<<endl;
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

// Shows how many students are enrolled in each course, sorted by
// enrollment count (reuses the insertion sort above before printing,
// so the busiest course appears first).
void CourseManager::courseEnrollmentReport()
{
    if(courseHead==NULL)
    {
        cout<<"No Course Found"<<endl;
        return;
    }

    sortRecord();

    ofstream fout;

    fout.open("course_report.txt");

    cout<<"\n===== Course Enrollment Report ====="<<endl;
    fout<<"===== Course Enrollment Report ====="<<endl;

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

void adminMenu(ResultRecord &system, CourseManager &courses)
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
            system.sortRecord(1);
            break;

        case 7:
            system.sortRecord(2);
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
            system.topScorer();
            break;

        case 17:
        {
            int reportID;

            cout<<"Enter Student ID : ";
            cin>>reportID;

            system.generateReport(reportID);

            break;
        }

        case 18:
        {
            int courseChoice;

            do
            {
                cout<<"\n----- Course Management -----"<<endl;
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
                    break;

                case 2:
                    courses.displayRecord();
                    break;

                case 3:
                    courses.searchRecord();
                    break;

                case 4:
                    courses.editCourse();
                    break;

                case 5:
                    courses.deleteCourse();
                    break;

                case 6:
                    courses.sortRecord();
                    break;

                case 7:
                    courses.courseEnrollmentReport();
                    break;

                case 8:
                    cout<<"Back to Admin Menu"<<endl;
                    break;

                default:
                    cout<<"Invalid Choice"<<endl;
                }

            }while(courseChoice!=8);

            break;
        }

        case 19:
        {
            int subChoice;

            cout<<"\n----- CGPA Classification -----"<<endl;
            cout<<"1. View On Screen"<<endl;
            cout<<"2. Save To File"<<endl;

            cout<<"Enter Choice : ";
            cin>>subChoice;

            if(subChoice==2)
            {
                system.saveClassificationReport();
            }
            else
            {
                system.classificationReport();
            }

            break;
        }

        case 20:
            cout<<"Back to Main Menu"<<endl;
            break;

        default:
            cout<<"Invalid Choice"<<endl;
        }

    }while(choice!=20);
}

void studentMenu(ResultRecord &system, CourseManager &courses)
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
        cout<<"6. Browse Available Courses"<<endl;
        cout<<"7. Search Course"<<endl;
        cout<<"8. Enroll In A Course"<<endl;
        cout<<"9. View My Enrolled Course"<<endl;
        cout<<"10. Exit"<<endl;

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
            courses.displayRecord();
            break;

        case 7:
            courses.searchRecord();
            break;

        case 8:
        {
            int studentID;
            char courseCode[20];

            cout<<"Enter Your Student ID : ";
            cin>>studentID;

            cout<<"Enter Course Code : ";
            cin>>courseCode;

            courses.enrollStudent(system,studentID,courseCode);

            break;
        }

        case 9:
        {
            int studentID;
            char result[20];

            cout<<"Enter Your Student ID : ";
            cin>>studentID;

            system.getEnrolledCourse(studentID,result);

            cout<<"Enrolled Course Code : "<<result<<endl;

            break;
        }

        case 10:
            cout<<"Back to Main Menu"<<endl;
            break;

        default:
            cout<<"Invalid Choice"<<endl;
        }

    }while(choice!=10);
}

int main()
{
    StudentUser student;
    Admin admin;
    ResultRecord system;
    CourseManager courses;

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
                studentMenu(system,courses);
                student.logout();
            }
            break;

        case 3:
            admin.registerAccount();
            break;

        case 4:
            if(admin.login())
            {
                adminMenu(system,courses);
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