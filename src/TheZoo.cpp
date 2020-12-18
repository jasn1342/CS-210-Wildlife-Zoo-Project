#include <iostream>
#include <jni.h>
#include <vector>
#include <fstream>
#include <string>
#include<bits/stdc++.h>
using namespace std;

int i = 0;
vector<string> fileString;
string track, name, type, subType, eggs, nurse, data;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}
void AddAnimal()
{
        //Get and edit the track number from user
        cout << "Track Number: ";
        cin >> track;
        track.insert(track.begin(),7-track.length(),'0');

        //Get and edit animal name from user
        cout << "Animal Name: ";
        cin >> name;
        name.append(16 - name.length(), ' '); //character length limiter

        //Get and edit animal type from user
        cout << "Animal Type: ";
        cin >> type;
        type.append(16 - type.length(), ' ');

        //Get and edit animal sub-type from user
        cout << "Animal Sub-Type: ";
        cin >> subType;
        subType.append(16 - subType.length(), ' ');

        //Get number of  eggs from user
        cout << endl << "Number of Eggs: ";
        cin >> eggs;

        //get nursing info from user
        cout << endl << "Nursing? (0 for no 1 for yes): ";
        cin >> nurse;
        cout << endl;

        //Data summary for file
        data = track + name + type + subType + eggs + nurse;
        fileString.push_back(data);
}


void RemoveAnimal()
{
        string item = "";
        cout << "Enter Track Number: ";
        cin >> track;

        std::vector<string>::iterator it; //stores position of searched variable
        it = std::find(fileString.begin(), fileString.end(), item);
        if(it != fileString.end()){
                fileString.erase(it);
        }
        else{
                cout <<"Track Number not found. Please enter a valid Track Number." << endl;
                RemoveAnimal();
        }
}

void LoadDataFromFile()
{
        string file = "zoodata.txt"; //links to zoodata text document
        std::ifstream in(file.c_str());
        if(!in){
                std::cerr << "Load failed!" << file << std::endl;
        }
        std::string str;
        while(getline(in,str)){
                if(str.size() > 0){
                        fileString.push_back(str);
                }
        }
        cout << "Load complete!"<<endl;
        in.close();
}

void SaveDataToFile()
{
        fstream file;
        string file_name = "zoodata.txt";
        file.open(file_name);
        if(file.fail()){
                cout << "File not found! ";
        }
        else {
                int i = 0;
                int as = fileString.size();
                while(as <= i)
                {
                        file << fileString[as];
                        as--;
                }
        }
}

void DisplayData()
{
        for(int i=0; i<fileString.size(); i++){
                cout << fileString.at(i) << endl;
        }
}

void DisplayMenu()
{
        int option = 0;
        menu:
        cout << "---------------Menu--------------" << endl;
        cout << "(1)Load Animal" << endl;
        cout <<	"(2)Generate Date" << endl;
        cout << "(3)Display Animal Data" << endl;
        cout <<	"(4)Add Record" << endl;
        cout <<	"(5)Delete Record" << endl;
        cout << "(6)Save Animal Data" << endl;
        cout << "---------------------------------" << endl;
        cin>> option;

        switch(option)
        {
        case 1:
                LoadDataFromFile();
                goto menu; //returns to main menu after function process is finished
        case 2:
                GenerateData();
                goto menu;
        case 3:
                DisplayData();
                goto menu;
        case 4:
                AddAnimal();
                goto menu;
        case 5:
                RemoveAnimal();
                goto menu;
        case 6:
                SaveDataToFile();
                goto menu;
        case 7:
                cout<<"Quitting";
                return;
        default:
                cout << "Invalid Option!" << endl;
                cout <<"Select option 1-6 or press 7 to quit" << endl;
                goto menu;
        }
}

int main()
{
        DisplayMenu();//Removed GenerateData () so that menu loads for user. User has option to Generate Data.
        return 1;
}
