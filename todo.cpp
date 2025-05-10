//to do list
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
using namespace std;

int ID;

struct Tasks{
	int id;
	string task;
};

void title(){
	cout<<"\t\t\t---TO DO LIST---"<<endl;
}
void addTask();
void displayTasks();
void removeTask();
void clearTask();

int main(){

    title();
    displayTasks();
	int choice=0;
	while(choice!=5){
		cout<<"1. Add task"<<endl<<"2. Display tasks"<<endl<<"3. Remove task"<<endl<<"4. To clear all task"<<endl<<"5. End the program"<<endl;
		cout<<"Enter your choice: "<<endl;
		cin>>choice;

		while(cin.fail()){
		  cin.clear();
		  cin.ignore(100,'\n');
		}

		switch(choice){
			case 1:
				addTask();
				break;
			case 2:
				displayTasks();
				cout<<"Current tasks are displayed"<<endl<<endl;
				break;
			case 3:
			    removeTask();
			    break;
			case 4:
				clearTask();
				break;
			case 5:
				cout<<endl<<"-----Program ended successfully-----"<<endl<<"-----Thank you-----";
				break;
			default:
				system("cls");
				title();
				displayTasks();
				cout<<"Invalid input"<<endl<<endl;
		}
	}

	return 0;
}

void addTask(){
	system("cls");
	title();

	ifstream iFileId;
    iFileId.open("idfile.txt");  // store the last id in this file
    int line;
    if(iFileId>>line){
	     ID=line;
    }
    else{
    	ID=0;
	}
    iFileId.close();


	Tasks tasks;
	cout<<"Enter task"<<endl;
	cin.ignore();
	getline(cin,tasks.task);
	ID++;
	ofstream ofile;
	ofile.open("todo.txt",ios::app); // append mode to retain previosly added tasks
	ofile<<ID<<"\n";
	ofile<<tasks.task<<"\n";
	ofile.close();

	ofstream fileId;
	fileId.open("idfile.txt",ios::trunc); // trunc mode to previous id
	fileId<<ID<<"\n";
	fileId.close();

	cout<<"Added successfully\n"<<endl;
	displayTasks();
	cout<<"Enter 1 to add another task.\nEnter 0 if you are done adding."<<endl;
	int add;
	cin>>add;
	if(add==1){
		addTask();
	}
	else{
		system("cls");
		title();
		displayTasks();
	}

}

void displayTasks(){
	system("cls");
	title();
	cout<<"\t\tTASKS:"<<endl;

	ifstream iFileId;
    iFileId.open("idfile.txt");
    int line;
    if(iFileId>>line){
	     ID=line;
    }
    else{
    	ID=0;
	}
    iFileId.close();

    if(ID==0){
		cout<<"No tasks to display."<<endl;
	}


	Tasks tasks;
	ifstream ifile;
	ifile.open("todo.txt");
	while(ifile>>tasks.id){
		ifile.ignore();
		getline(ifile,tasks.task);
		if(tasks.task!=""){
		  cout<<tasks.id<<". "<<tasks.task<<endl;
     	}
	}

	ifile.close();
	cout<<"____"<<endl<<endl;
}

void removeTask(){
	system("cls");
	title();
	displayTasks();
	cout<<"Enter id of task to remove"<<endl;
	int del;
	cin>>del;
	Tasks tasks;

	ifstream ifile;
	ifile.open("todo.txt");

	ofstream newfile;
	newfile.open("newFile.txt",ios::trunc);

	int index=0;
	bool found=0;

	while(ifile>>tasks.id){
		ifile.ignore();
		getline(ifile,tasks.task);
		if(tasks.task!="" && tasks.id!=del){
			index++;
			newfile<<index<<"\n";
			newfile<<tasks.task<<"\n";
     	}
     	if(tasks.id==del){
            found=1;
     	}
	}
	if(found){
	  ifile.close();
	  newfile.close();
	  remove("todo.txt");

	  ofstream idFile;
	  idFile.open("idfile.txt",ios::trunc);
	  idFile<<index;
	  idFile.close();

	  rename("newFile.txt","todo.txt");
	  displayTasks();
	  cout<<"Task removed successfully."<<endl<<"___"<<endl;
	}
	else{
		title();
		displayTasks();
        cout<<"Id not found"<<endl<<endl;
        remove("newFile.txt");
	}
}

void clearTask(){
	system("cls");
	ofstream ifile;
	ifile.open("todo.txt",ios::trunc);
	ifile.close();

	ofstream idFile;
	idFile.open("idfile.txt",ios::trunc);
	idFile.close();

	title();
	displayTasks();
	cout<<"All tasks cleared successfully"<<endl<<endl;
}