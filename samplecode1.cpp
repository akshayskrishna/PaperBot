#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<ctime>
using namespace std;
class account
{
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
        ofstream writeAccount(path.c_str(),ios::app);
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
            iss>>date>>cause>>debit>>credit;
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
};

int main()
{
    account a("test");
    a.newuser();
    a.addcredit(25);
    a.addcredit(100);
    a.subdebit(25);
    a.addcredit(70);
    a.subdebit(10);
    account a2("test2");
    a2.newuser();
    a2.addcredit(25);
    a2.addcredit(100);
    a2.subdebit(25);
    a2.addcredit(70);
    a2.subdebit(10);

}

