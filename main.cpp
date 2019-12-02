
#include<iostream>
#include<fstream>
#include<sstream>
#include<conio.h>
#include<string>
#include<algorithm>
#include<ctime>
#include<string.h>
using namespace std;
class account
{
protected:

    int total,debit,credit;
    time_t t;
    struct tm*now;
    int year,month,day,hour,minutes,second;
    string id,path,date,cause,delimiter;
public:
    account(string inid)
    {
        id=inid;
        t=time(0);
        now=localtime(&t);
        year=(now->tm_year+1900);
        day=(now->tm_mday);
        month=(now->tm_mon+1);
        hour=(now->tm_hour);
        minutes=(now->tm_min);
        second=(now->tm_sec);
        path="db\\account\\"+id+".txt";
        delimiter=" ";
    }
    void newuser()
    {
        ofstream writeAccount(path.c_str());
        if(writeAccount)
        {
            debit=0;
            credit=0;
            total=0;
            writeAccount<<day<<"/"<<month<<"/"<<year<<"--"<<hour<<":"<<minutes<<":"<<second<<" "<<"B/F    "<<debit<<"\t"<<credit<<"\t"<<total<<"\n";
        }
    }
    void getlastline()
    {
        ifstream readAccount(path.c_str());
        while(getline(readAccount,delimiter))
        {
            stringstream iss(delimiter);
            iss>>date>>cause>>debit>>credit>>total;
        }
    }
    void addcredit(int c)
    {
        getlastline();
        debit=0;
        credit=c;
        total+=c;
        ofstream writeAccount(path.c_str(),ios::app);
        if(writeAccount)
            writeAccount<<day<<"/"<<month<<"/"<<year<<"--"<<hour<<":"<<minutes<<":"<<second<<" "<<"Credit "<<debit<<"\t"<<credit<<"\t"<<total<<"\n";
    }
    void subdebit(int d)
    {
        getlastline();
        credit=0;
        debit=d;
        total-=d;
        ofstream writeAccount(path.c_str(),ios::app);
        if(writeAccount)
            writeAccount<<day<<"/"<<month<<"/"<<year<<"--"<<hour<<":"<<minutes<<":"<<second<<" "<<"Debit "<<debit<<"\t"<<credit<<"\t"<<total<<"\n";
    }
    int getbalance()
    {
        getlastline();
        return total;

    }
    void getStatment()
    {
        ifstream readFile (path.c_str());
        char line[225];
        if (readFile)
            while(readFile)
            {
                readFile.getline(line,225);
                cout<<line<<endl;
            }
    }
};
class user
{
protected:
    string delimiter;
    string inputpass;
    string dbpass;
    bool found,flag;
    char c;
public:
    string usertype,dbid,inputid;
    user()
    {
        delimiter=" ";
        found=false;
    }
    bool login()
    {
        cout<<"User id:";
        cin>>inputid;
        cout<<"Password:";
        while((c=getch())!='\r')
        {
            cout<<"*";                                  //this is to print * and hide the password
            inputpass+=c;                               //adds the entered char to pass string
        }
        ifstream readFile("uidandpass.txt");            //reads from the file with password and user name
        if(readFile)                                    //file reading function
        {
            while(getline(readFile,delimiter))
            {
                stringstream iss(delimiter);            //string stream for taking data from the file
                iss>>dbid>>dbpass>>usertype;
                if(inputid==dbid&&inputpass==dbpass)    //checks the user data with the file data
                {
                    cout<<"\nLog in successful\n";
                    return true;                         //this is a flag that says a user is found or not
                    break;                              //exits the loop when the user is found
                }
            }
            if(found==false)                            //if no user or wrong password, the found flag is set to false
            {
                cout<<"\nUser id or password incorrect\n";
                return false;
            }
            else
            {
                cout<<"Welcome\n";
                readFile.close();
            }
        }
        else
        {
            cout<<"File not found\n";
        }
    }
    void signup()
    {
        string conf;
        flag=false;
        cout<<"Enter User name:";
        cin>>inputid;
        ifstream readFile("uidandpass.txt");
        if(readFile)
        {
            while(getline(readFile,delimiter))
            {
                stringstream iss(delimiter);
                iss>>dbid>>dbpass;
                if(inputid==dbid)
                {
                    cout<<"\nUser name exists. Please try a new user name\n";
                    flag=true;
                    break;
                }
            }
            if(!flag)
            {

                cout<<"Enter the password:";
                while((c  =getch())!='\r')
                {
                    cout<<"*";                              //this is to print * and hide the password
                    inputpass+=c;                           //adds the entered char to pass string
                }
                cout<<"\nRe-enter the password:";
                while((c=getch())!='\r')
                {
                    cout<<"*";                              //this is to print * and hide the password
                    conf+=c;                                //adds the entered char to pass string
                }
                if(inputpass==conf)
                {
                    usertype="student";
                    ofstream writeFile("uidandpass.txt",ios::app);
                    if(writeFile)
                    {
                        writeFile<<"\n"<<inputid<<" "<<inputpass<<" "<<"student";
                    }
                    else
                        cout<<"Failed to open file\n";
                    writeFile.close();
                }
                else
                    cout<<"\nThe passwords don't match. Please re-enter\n";
            }
        }


    }
    friend void selectuser(user );
};
class student : public account
{
    string name,usn,dep,sem,id,delimiter;
    string sub[25];
    int cost[25];
public:
    student(string dbid) :account(dbid)
    {
        id=dbid;
        delimiter =" ";
    }
    void setdetails()
    {
        account a(id);
        a.newuser();
        cout<<"\n\t\t Please enter the following details\n";
        cout<<"Enter your name:(Blank Spaces are not allowed,use a underscore symbol to separate components) ";
        cin>>name;
        cout<<"Enter USN: ";
        cin>>usn;
        cout<<"Enter department:(cs/is/civ/mech/eee/ec) in the specified format:\t ";
        cin>>dep;
        cout<<"Enter the sem(1/2/3/4/5/6/7/8): ";
        cin>>sem;
        ofstream writeFile("db\\student.txt",ios::app);
        if(writeFile)
        {
            writeFile<<"\n"<<id<<" "<<name<<" "<<usn<<" "<<dep<<" "<<sem<<" ";
        }
        writeFile.close();

    }
    void getdata()
    {
        ifstream readFile("db\\student.txt");
        string uid;
        if(readFile)
        {
            while(getline(readFile,delimiter))
            {
                stringstream iss(delimiter);
                iss>>uid>>name>>usn>>dep>>sem;
                if(uid==id)
                    break;
            }
            string path="db\\"+dep+"\\"+"sem"+sem+"\\content.txt";
            ifstream read;
            read.open(path.c_str());
            if(read)
            {
                char line[255];
                cout<<"\n\n\n\n\n";
                cout<<"\t\t Available notes are\n";
                int i=0;
                while(read)
                {
                    read.getline(line,255);
                    if(read)
                    {
                        cout<<line<<endl;
                        sub[i]=line;
                        i++;
                    }
                }
            }
            read.close();
            string path2="db\\"+dep+"\\"+"sem"+sem+"\\cost.txt";
            read.open(path2.c_str());
            if(read)
            {
                int i=0;
                while(getline(read,delimiter))
                {
                    stringstream iss(delimiter);
                    iss>>cost[i];
                    cout<<"Cost of item:\t"<<i+1<<"="<<cost[i]<<endl;
                    i++;

                }
            }
            cout<<endl;
            cout<<"Choose a subject you want to order:";
            int isub;
            cin>>isub;
            cout<<"Choice is:"<<isub<<endl;
            cout<<"Balance:"<<getbalance()<<endl;
            cout<<"Cost:"<<cost[isub-1]<<endl;
            if(getbalance()<cost[isub-1])
            {
                cout<<"\nPlease contact the admin to increase credit\n";
            }
            else
            {
                char cyear[10];
                char cmonth[10];
                char cday[10];
                char ct[10];
                strftime(cyear, sizeof(cyear), "%Y", now);
                strftime(cmonth, sizeof(cmonth), "%m", now);
                strftime(cday, sizeof(cday), "%d", now);
                strftime(ct,sizeof(ct),"%X",now);
                char order[200];
                strcpy(order,"db\\orders\\");
                strcat(order,cyear);
                strcat(order,cmonth);
                strcat(order,cday);
                strcat(order,".txt");
                ofstream orderFile(order,ios::app);
                if(!orderFile)
                {
                    orderFile.close();
                    ofstream orderFile(order);
                    orderFile<<id<<" "<<sub[isub-1]<<" "<<ct<<endl;
                }
                else
                {
                    orderFile<<id<<" "<<sub[isub-1]<<" "<<ct<<endl;
                }
                cout<<"Your order id is: "<<ct;
                subdebit(cost[isub-1]);
                cout<<"Balance is: "<<getbalance();
            }

        }

    }

};
class admin : public account
{
public:
    admin(string id):account(id)
    {

    }

    void getorders()
    {
        char cyear[10];
        char cmonth[10];
        char cday[10];
        char ct[10];
        strftime(cyear, sizeof(cyear), "%Y", now);
        strftime(cmonth, sizeof(cmonth), "%m", now);
        strftime(cday, sizeof(cday), "%d", now);
        strftime(ct,sizeof(ct),"%X",now);
        char order[200];
        strcpy(order,"db\\orders\\");
        strcat(order,cyear);
        strcat(order,cmonth);
        strcat(order,cday);
        strcat(order,".txt");
        ifstream readorder(order);
        if(readorder)
        {
            char line[255];
            cout<<"Today's orders are: "<<endl;
            while(readorder)
            {
                readorder.getline(line,255);
                if(readorder)
                    cout<<line<<endl;
            }
        }
        else
            cout<<"No orders found!\n\n\n";
    }
};



void selectuser(user u,int choice)
{
    string utype= u.usertype;
    transform(utype.begin(), utype.end(), utype.begin(), ::tolower);
    if(utype=="student")
    {
        student s(u.inputid);
        if(choice==1)
        {
            cout<<"1. Get statement\n2. Get notes\n";
            cout<<"Enter your choice: ";
            int ch;
            cin>>ch;
            switch(ch)
            {
            case 1:
                cout<<"The account activity is as follows:\n";
                cout<<"Date      Time   Cause Debit Credit  Balance\n\n";
                s.getStatment();
                break;
            case 2:
                s.getdata();
                break;
            default:
                cout<<"Sorry. Please enter a valid choice\n";
            }
        }
        else if(choice==2)
            s.setdetails();
    }
    else if(u.usertype=="admin")
    {
        int choice;
        cout<<"1.Get todays orders\n2.Add credits\n";
        cin>>choice;
        admin adm(u.dbid);
        switch(choice)
        {
        case 1:
            adm.getorders();
            break;
        case 2:
        {
            int in;
            string stuid;
            cout<<"Enter the students id:";
            cin>>stuid;
            cout<<"Enter the amount to be added:";
            cin>>in;
            account acc(stuid);
            acc.addcredit(in);
        }
            break;
        }
    }
}

int main()
{
    user u;
    int attempt=0;
    int choice;
    bool flag=false;
    int ch=1;
    cout<<"...................PAPERBOT................\n";
    cout<<"...................Welcome to Paper Bot................\n\n";

       for(;;)
       {
           cout<<"Enter:\n1 to login\n2 to sign up\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
           {
            case 1:
                {
                    while(attempt<2)
                        {
                           user u1;
                           flag=u1.login();
                           if(flag==false)
                            attempt++;
                            else
                             {
                             u=u1;
                             break;
                             }
                        }
                }
            if(flag)
            do{
            selectuser(u,choice);
            cout<<"\nPress 1 to continue or any other key to exit\n";
            cin>>ch;
            }while(ch==1);
            break;
            case 2:
            u.signup();
            selectuser(u,choice);
            break;

            }
       }


}
