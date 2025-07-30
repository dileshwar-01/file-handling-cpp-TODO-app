#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct todoList{
    int id;
    string task;
};

int ID=0;

void banner(){
    cout<<"_____________________________________"<<endl;
    cout<<"\t      MY TODO"<<endl;
    cout<<"_____________________________________"<<endl;

}

void addTask(){
    system("cls");
    banner();
    todoList todo;
    cout<<"Enter new task: "<<endl;
    cin.get();
    getline(cin,todo.task);
    char save;
    cout<<"Save (y/n): ";
    cin>>save;
    if(save=='y'){
        ID++;
        ofstream fout("todo.txt",ios::app); //opening file in write mode using ofstream
        fout<<"\n"<<ID;
        fout<<"\n" <<todo.task;
        fout.close();

        char more;
        cout<<"Add more task? (y/n): ";
        cin>>more;
        if(more=='y'){
            addTask();
        }else{
            system("cls");
            cout<<"Added Successfully!"<<endl;
            return;
        }

    }
    system("cls");

    
}
void loadLastID() {
    ifstream fin("todo.txt");
    todoList todo;
    int lastID = 0;
    while (fin >> todo.id) {
        fin.ignore();
        getline(fin, todo.task);
        lastID = todo.id; // Only update when read is successful
    }
    ID = lastID;
    fin.close();
}

void showTask(){
    system("cls");
    banner();
    todoList todo;
    ifstream fin("todo.txt");
    cout<<  "Tasks: "<<endl;
    while(!fin.eof()){
        fin>>todo.id;
        fin.ignore();
        getline(fin,todo.task);
        if(todo.task != ""){
            cout<<"\t"<<todo.id<<":"<<todo.task<<endl;
        }
        else{
            cout<<"\tEmpty!"<<endl;;
        }

    }
    fin.close();
    char exit;
    cout<<"Exit? (y/n): ";
    cin>>exit;
    if(exit!='y'){
        showTask();
    }
    system("cls");
}

int searchTask(){
    system("cls");
    banner();
    int id;
    cout<<"Enter the task id: "<<endl;
    cin>>id;
    ifstream fin("todo.txt");
    while(!fin.eof()){
        todoList todo;
        fin>>todo.id;
        fin.ignore();
        getline(fin,todo.task);
        if(todo.id == id){
            cout<<"\t"<<todo.id<<":"<<todo.task<<endl;
            return id;
        }
    }
    system("cls");
    cout<<"Not found!"<<endl;
    return 0;
}

void deleteTask(){
    system("cls");
    int id= searchTask();
    if(id!=0){
        char del;
        cout<<"\n\tDelete? (y/n): ";
        cin>>del;
        if(del == 'y'){
            todoList todo;
            ofstream tempFile("temp.txt"); 
            ifstream fin("todo.txt");      
            int index=1;
            while(!fin.eof()){
                fin>>todo.id;
                fin.ignore();
                getline(fin,todo.task);
                if(todo.id != id){
                    tempFile<<"\n"<<index;
                    tempFile<<"\n"<<todo.task;
                    index++;
                    ID--;

                }
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt","todo.txt");
            system("cls");
            cout<<"\n\tDeleted Successfully!"<<endl;
        }else{
            system("cls");
            cout<<"\n\tNot Deleted!"<<endl;
        }
    }
}

void updateTask(){
    system("cls");
    int id= searchTask();
    if(id!=0){
        char upd;
        cout<<"\n\tUpdate? (y/n): ";
        cin>>upd;
        if(upd == 'y'){
            string updatedTask;
            cout<<"Enter updated task: "<<endl;
            cin.get();
            getline(cin,updatedTask);
            todoList todo;
            ofstream tempFile("temp.txt"); 
            ifstream fin("todo.txt");     
            int index=1;
            while(!fin.eof()){
                fin>>todo.id;
                fin.ignore();
                getline(fin,todo.task);
                if(todo.id != id){
                    tempFile<<"\n"<<index;
                    tempFile<<"\n"<<todo.task;
                    index++;
                    

                }else{
                    tempFile<<"\n"<<index;
                    tempFile<<"\n"<<updatedTask;
                }
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt","todo.txt");
            system("cls");
            cout<<"\n\tUpdated Successfully!"<<endl;
        }else{
            system("cls");
            cout<<"\n\tNot Updated!"<<endl;
        }
    }
}


int main(){
    system("cls");
    loadLastID(); 
    while(true){
        banner();
        cout<<"\n\t1. Add Task";
        cout<<"\n\t2. Show Task";
        cout<<"\n\t3. Search Task";
        cout<<"\n\t4. Delete Task";
        cout<<"\n\t5. Update Task";
        cout<<"\n\t6. Exit";

        int choice;
        cout<<"\n\tEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1: 
                addTask();
                break;
            case 2:
                showTask();
                break;
            case 3:
                searchTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                updateTask();
                break;
            case 6:
                exit(0);
            default:
                break;
        }
    }
}