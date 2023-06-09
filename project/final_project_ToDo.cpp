#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <stdlib.h>


using namespace std;

class ToDo{
	
	public:
	
	//add task
	int add(string s){
    int pending,done;
    string temp;
    vector<string> v;

    ifstream read;
    read.open("todo.txt",ios::app);

    while(getline(read,temp))
    {
        v.push_back(temp);
    }
    read.close();

    bool check=false; //task not present

    for(int i=0;i<v.size();i++)
    {
        if(s==v[i])
        check=true; // task is already added earlier, but needed to refresh it.
    }

    if(check==false)
    {
        fstream write;
        write.open("todo.txt",ios::app);
        write<<s<<endl;
        cout<<"Added todo : "<<"\""<<s<<"\""<<endl;
        write.close();
    }
    else
    {
        ofstream write;
        write.open("todo.txt");
        
        for(int i=0;i<v.size();i++)
        {
            if(v[i]!=s)
            {
                write<<v[i]<<endl;
            }
        }

        write<<s<<endl;
        cout<<"Added todo : "<<"\""<<s<<"\""<<endl;
        write.close();
    }
    
    return 0;
}


//delete the task
void del(int k) 
{
    string s;
    vector<string> v;

    ifstream read;
    read.open("todo.txt");
    while(getline(read,s))
    {
        v.push_back(s);
    }
    read.close();

    if(k>v.size() ||k<1)
    {
        // if the task number entered is greater thsn the number of task, then it cannot be deleted or it does not exist.
        cout<<"ERROR...! task #"<<k<<" does not exist! No task is deletd!"<<endl;
    }
    else
    {
        ofstream write;
        write.open("todo.txt");
        for(int i=0;i<v.size();i++)
        {
            if(i!=k-1)
            write<<v[i]<<endl;				//rewrite the code except the specified index
        }
        cout<<"Deleted todo #"<<k<<endl;
    }
    
}


//complete the task
void done(int k)
{

    int year,month,date,z;
    vector<string> v;
    string s,x;

    time_t ttime= time(0);				//for the current date
    tm *local_time=localtime(&ttime);
    year=local_time->tm_year + 1900;
    month=local_time->tm_mon + 1;
    date=local_time->tm_mday;

    ifstream read;
    read.open("todo.txt");

    while(getline(read,s))
    {
        v.push_back(s);
    }
    read.close();

    // if k > number of tasks in queue then ERROR,

    if(k>v.size() || k<1)
    {
        cout<<"ERROR...! task #"<<k<<" doesn't exist!"<<endl;
    } 
    else
    {
        ofstream write1,write2;
        write1.open("todo.txt");
        write2.open("done.txt",ios::app);
        for(int i=0;i<v.size();i++)
        {
            if(i==k-1)
            {
                x=v[i];
                cout<<"Marked todo #"<<k<<" as done."<<endl;
            }
            else
            {
                write1<<v[i]<<endl;
            }
        }
        write1.close();
        write2<<"x "<<year<<"-"<<month<<"-"<<date<<" "<<x<<endl;
        write2.close();
    }
}


//list the pending tasks
void ls() 
{
    string s;
    vector<string> v;

    ifstream read;
    read.open("todo.txt");
    while(getline(read,s))
    {
        v.push_back(s);
    }
    read.close();

    if(v.size()==0)
    {
        cout<<"There are no pending todos."<<endl;
    }
    else
    {
        for(int i=v.size()-1;i>=0;i--)
        {
            s=v.back();
            v.pop_back();
            cout<<"["<<(i+1)<<"]"<<" "<<s<<endl;
        }
    }
}
void report() //status
{
    int pending =0,done=0;
    string s;
    int year,month,date;

    ifstream read;
    read.open("todo.txt");  // todo.txt contains the pending tasks;
    if(read!=NULL)
    {
        while(getline(read,s))
        {
            pending++;
        }
    }
    read.close();

    read.open("done.txt"); // done.txt contains the completed tasks
    if(read!=NULL)
    {
        while(getline(read,s))
        {
            done++;
        }
    }
    read.close();


	//for displaying along with time
    time_t ttime= time(0);
    tm *local_time=localtime(&ttime);
    year=local_time->tm_year + 1900;
    month=local_time->tm_mon + 1;
    date=local_time->tm_mday;

    cout<<year<<"-"<<month<<"-"<<date<<" "<<"Pending Tasks : "<<pending<<" Completed Tasks : "<<done<<endl;
    
}

void comp_det(){
	string s;
    vector<string> v;

    ifstream read;
    read.open("done.txt");
    while(getline(read,s))
    {
        v.push_back(s);
    }
    read.close();

    if(v.size()==0)
    {
        cout<<"There are no completed todos."<<endl;
    }
    else
    {
        for(int i=v.size()-1;i>=0;i--)
        {
            s=v.back();
            v.pop_back();
            cout<<"["<<(i+1)<<"]"<<" "<<s<<endl;
        }
    }
}


void menu() 
{
	cout<<"---------------MENU------------------"<<endl;
	cout<<"1. add new task "<<endl;
	cout<<"2. delete the task "<<endl;
	cout<<"3. mark the task as done "<<endl;
	cout<<"4. list the pending tasks "<<endl;
	cout<<"5. report about ToDo"<<endl;	
	cout<<"6. display the details of completed task"<<endl;
	cout<<"7. quit ToDo"<<endl;

}
};
int main(){
	ToDo todo;
	string desc;
	int index;
	int input_option;
	while (1){
		todo.menu();
		cout<<"Enter your choice"<<endl;
		cin>>input_option;
		system("CLS");
		cin.ignore();
		
		switch (input_option){
		
			case 1:
				cout<<"Enter the description of the task"<<endl;
				getline(cin,desc);
				
				todo.add(desc);
				break;
				
			case 2:
				cout<<"Enter the index of the task"<<endl;
				cin>>index;
				todo.del(index);
				break;
			
			case 3:
				cout<<"Enter the index of the task"<<endl;
				cin>>index;
				todo.done(index);
				break;
				
			case 4:
				todo.ls();
				break;
			
			case 5:
				todo.report();
				break;
			
			case 6:
				todo.comp_det();
				break;
				
			case 7:
				cout<<"Have a great day!!"<<endl;
				exit(0);
				
			default:
				cout<<"Please enter the valid choice"<<endl;
				break;
			
	}
		
	}
	return 0;
}
