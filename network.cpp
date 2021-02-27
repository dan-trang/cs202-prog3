/*******************************************************
 * Daniel Trang
 * CS202: Programming Systems
 * Program #3
 * Network Header File
 *
 * This file contains the class Network which is an
 * abstract data type class Binary Search Tree. This class
 * will manage the nodes of the tree which are of class Student.
 * Each student node represents a person in the network -- each
 * with their own unique student ID, name, and list of devices
 * they use on a daily basis.
 *
 * The User class is derived from the BST network class and just
 * adds another layer of abstraction. From the user class, we can
 * create an object of type user to shield private data of Network.
 * I've added a faux authentication for the user to simulate logging
 * into the network.
 * ******************************************************/

#include "network.h"
using namespace std;


//BINARY TREE: NETWORK
network::network(): root(nullptr)
{
    username = new char[9];
    password = new char[9];
    strcpy(username, "password");
    strcpy(password, "username");
}


/*
network::network(const network& src_bst)
{
	//copy bst	
}
*/

network::~network()
{
	if(username)
	{
		delete [] username;
		username = nullptr;
	}

	if(password)
	{
		delete [] password;
		password = nullptr;
	}

    if(root)
    {
        delete root;
        root = nullptr;
    }
}


bool network::add_student()
{
	//if no root node, make one
	if(root == nullptr)
	{
		root = new student;	
		root->set_new();
		return true;
	}

	//Ask for new student info
	int new_ID = 0;
	char new_name[100];
	cout<<"Enter new student's name: ";
	cin.get(new_name, 100);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<"Enter new student's ID (6-digits): ";
	cin>>new_ID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//create new student node with user given info	
	student* new_node = new student(new_name, new_ID);

	//Now find a position in the Tree to place that new node
	//if ID greater or less than node: go left, go right
	return add_student(root, new_node, new_ID);
}


bool network::add_student(student*& root, student*& new_node, int new_ID)
{
    //check for duplicate student ID#
    if(root->compare_ID(new_ID)==true)
    {
        cout<<"[Cannot add new student. That student ID already exists.]"<<endl;
        return false;
    }
	//if new node is greater than root go right
	if(*new_node > *root)
	{
		//if right is null, make right = new node
		if(root->getRight() == nullptr)
		{
			root->getRight() = new_node;
			return true;
		}
		//else traverse to the right
		return add_student(root->getRight(), new_node, new_ID);
	}

	//if new node is less than root go left
	if(*new_node < *root)
	{
		//if left is null, make left = new node
		if(root->getLeft() == nullptr)
		{
			root->getLeft() = new_node;
			return true;
		}
		//else traverse to the left
		return add_student(root->getLeft(), new_node, new_ID);
	}
	
	//if new node is not greater or less than root, it must be equal
	cout<<"[Cannot add new student. That student name already exists.]"<<endl;
	return false;
}


student*& network::retrieve_student(student*& root, const char* student_name)
{
    if(root != nullptr)
    {
        if(*root > student_name)
            return retrieve_student(root->getLeft(), student_name);
        if(root->compare_name(student_name)==true)
        {
            return root;
        }
        if(*root < student_name)
            return retrieve_student(root->getRight(), student_name); 
    }
    return root;
}


bool network::display_one()
{
    if(root == nullptr)
    {
        cout<<"[There are no existing entries in the student network. Please add one first.]"<<endl;
        return false;
    }
    char find[100];
    cout<<"Which student do you want to query?: ";
    cin.get(find, 100);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return display_one(root, find);
}

bool network::display_one(student*& root, char* find)
{
    if(root->getLeft() != nullptr)
        display_one(root->getLeft(), find);
    if(root->compare_name(find)==true)
    {
        if(root->getList() == nullptr)
        {
            cout<<"[This student does not have any devices.]"<<endl;
            return false;
        }
        root->display_full_info();
        return true;
    }
    if(root->getRight() != nullptr)
        display_one(root->getRight(), find);
    
    //couldn't find user in network
    cout<<"[Could not find that name in the system.]"<<endl;
    return true;
}


bool network::display_all()
{
    if(root == nullptr)
    {
        cout<<"[There are no existing entries in the student network. Please add one first.]"<<endl;
        return false;
    }

    cout<<"\n=========================\n";
    cout<<"  CS202 STUDENT NETWORK  ";
    cout<<"\n=========================";
    display_all(root);
    cout<<endl;
    return true;
}


bool network::display_all(student*& root)
{
    if(root->getLeft() != nullptr)
        display_all(root->getLeft());
    root->display_student();
    if(root->getRight() != nullptr)
        display_all(root->getRight());
    return true;
}


bool network::remove_all()
{
    if(root == nullptr)
    {
        cout<<"[The network is empty. There is nothing to remove...]"<<endl;
        return false;
    }

    remove_all(root);
    delete root;
    root = nullptr;
    cout<<"[Student Network has been fully purged...]"<<endl;
    return true;
}


bool network::remove_all(student*& root)
{
    if(root->getLeft() != nullptr)
        remove_all(root->getLeft());
    if(root->getRight() != nullptr)
        remove_all(root->getRight());
    delete root->getLeft();
    delete root->getRight();
    root->getLeft() = nullptr;
    root->getRight() = nullptr;
    return true;
}


bool network::authentication(char* src_username, char* src_password)
{
    if(strcmp(username, src_username)==0 && strcmp(password, src_password)==0)
    {
        return true;
    }
    return false;
}


bool network::add_device()
{
    char find[100];
    cout<<"Add new device to which student?: ";
    cin.get(find, 100);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if((*this)[find] != nullptr)
    {
        (*this)[find]->add_device();
        return true;
    }
    cout<<"[Could not find that name in the system.]"<<endl;
    return false;
}


bool network::call_school_phone()
{
    char find[100];
    cout<<"Who do you want to call?: ";
    cin.get(find, 100);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if((*this)[find] != nullptr)
    {
        (*this)[find]->call_school_phone();
        return true;
    }
    cout<<"[Could not find that name in the system.]"<<endl;
    return false;
}


bool network::emergency_alarm()
{
    char find[100];
    cout<<"Who set off their alarm system?: ";
    cin.get(find, 100);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if((*this)[find] != nullptr)
    {
        (*this)[find]->emergency_alarm();
        return true;
    }
    cout<<"[Could not find that name in the system.]"<<endl;
    return false;
}


bool network::call_personal_phone()
{
    char find[100];
    cout<<"Who do you want to call?: ";
    cin.get(find, 100);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if((*this)[find] != nullptr)
    {
        (*this)[find]->call_personal_phone();
        return true;
    }
    cout<<"[Could not find that name in the system.]"<<endl;
    return false;
}


bool network::text_personal_phone()
{
    char find[100];
    cout<<"Who do you want to text?: ";
    cin.get(find, 100);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if((*this)[find] != nullptr)
    {
        (*this)[find]->text_personal_phone();
        return true;
    }
    cout<<"[Could not find that name in the system.]"<<endl;
    return false;
}


bool network::direct_message()
{
    char find[100];
    cout<<"Who do you want to text?: ";
    cin.get(find, 100);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if((*this)[find] != nullptr)
    {
        (*this)[find]->direct_message();
        return true;
    }
    cout<<"[Could not find that name in the system.]"<<endl;
    return false;
}


bool network::voice_call()
{
    char find[100];
    cout<<"Who do you want to voice call?: ";
    cin.get(find, 100);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if((*this)[find] != nullptr)
    {
        (*this)[find]->voice_call();
        return true;
    }
    cout<<"[Could not find that name in the system.]"<<endl;
    return false;
}


bool network::video_call()
{
    char find[100];
    cout<<"Who do you want to video call?: ";
    cin.get(find, 100);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if((*this)[find] != nullptr)
    {
        (*this)[find]->video_call();
        return true;
    }
    cout<<"[Could not find that name in the system.]"<<endl;
    return false;
}


student*& network::operator [] (const char* student_name)
{
    if(root == nullptr)
    {
        cout<<"[This student network is empty.]"<<endl;
        return root;
    }

    return retrieve_student(root, student_name);
}



//DERIVED CLASS: USER
user::user()
{
    program_info = new char[250];
    strcpy(program_info, "======= Portland State University =======\nStudent Network v1.0 GuppyFish\nDaniel Trang\nCS202: Programming Systems\nProgram 3: Operator Overloading\n=========================================\n");
}


user::~user()
{
    delete [] program_info;
    program_info = nullptr;
}


int user::main_program()
{
    bool check = false;
    char user_input;

    cout<<program_info<<endl;
    while(check == false)
    {
        check = authentication();   //if check = true, break loop
    }

    user_input = user_menu();
    while(user_input != 'x' && check == true)
    {
        execute(user_input);
        check = continue_menu();    //if check = false, break loop
        if(check == true)
        {
            user_input = user_menu();
        }
    }
    cout<<"*** PROGRAM EXIT ***"<<endl;
    return 0;
}


char user::user_menu()
{
    char user_input;
    auto current = chrono::system_clock::now();
    time_t curr_time = chrono::system_clock::to_time_t(current);

    cout<<"\n"<<endl;
    cout<<"----------------- CS202 STUDENT NETWORK -----------------"<<endl;
    cout<<" Welcome, [User]. It is currently "<<ctime(&curr_time);
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"Manage the Student Network"<<endl;
    cout<<"1. Add a new student to the network"<<endl;                                  //add_student()
    cout<<"2. Add new student device(s)"<<endl;                                         //add_device()
    cout<<"3. Display a single student's full information"<<endl;                       //display_one()
    cout<<"4. Display all students in the network"<<endl;                               //display_all()
    cout<<"5. Remove all students from the network"<<endl;                              //remove_all()
    cout<<"\nTest Student's Communication Device(s)"<<endl;     
    cout<<"a. Call by school landline phone"<<endl;                                     //call_school_phone()
    cout<<"b. Dispatch emergency reponder to student's distress location"<<endl;       //emergency_alarm()
    cout<<"c. Call by student's personal cell phone"<<endl;                             //call_personal_phone()
    cout<<"d. Text student's personal cell phone"<<endl;                                //text_personal_phone()
    cout<<"e. Direct message through PSU app"<<endl;                                    //direct_message()
    cout<<"f. Voice call through PSU app"<<endl;                                        //voice_call()
    cout<<"g. Video call through PSU app"<<endl;                                        //video_call()
    cout<<"\nx. Exit Program\n"<<endl;

    cout<<"Please enter your selection: ";
    cin>>user_input;
    cin.ignore(1000, '\n');
    return user_input;
}


bool user::execute(char user_input)
{
   switch(user_input)
   {
       //Add a new student
       case '1':
           this->add_student();
           break;
           
       //Add new student device
       case '2':  
           this->add_device();
           break;

       //Display one student's full info
       case '3':
           this->display_one();
           break;

       //Display all students in network
       case '4':
           this->display_all();
           break;

       //Remove all students in network
       case '5':
           this->remove_all();
           break;

       //Call school phone
       case 'a':
           this->call_school_phone();
           break;

       //Trip the alarm system
       case 'b':
           this->emergency_alarm();
           break;

       //Call by personal phone
       case 'c':
           this->call_personal_phone();
           break;

       //Text personal phone
       case 'd':
           this->text_personal_phone();
           break;

       //DM through App
       case 'e':
           this->direct_message();
           break;

       //Voice call through App
       case 'f':
           this->voice_call();
           break;

       //Video call through App
       case 'g':
           this->video_call();
           break;

       //Exit Program
       case 'x':
           cout<<"exiting program..."<<endl;
           break;

       default:
           cout<<"[Invalid Input]"<<endl;
           break;
   }
   return true;
}


bool user::continue_menu()
{
    char yes_no;
    cout<<"Return to the Main Menu? (y/n): ";
    cin>>yes_no;

    if(yes_no == 'y' || yes_no == 'Y')
        return true;
    else
        return false;
}


bool user::authentication()
{
    bool check = false;
    while(check == false)
    {
        char some_user[100], some_password[100];
        cout<<"user: ";
        cin.get(some_user, 100);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"password: ";
        cin.get(some_password, 100);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        check = network::authentication(some_user, some_password);
        if(check == false)
        {
            cout<<"Failed authentication.\n"<<endl;
        }
    }
    return true;
}



//BST NODE: STUDENT
student::student(): student_name(nullptr), student_ID(0), left(nullptr), right(nullptr), comm_list(nullptr){}


student::student(char* new_name, int new_ID): comm_list(nullptr)
{
	student_name = new char[strlen(new_name)+1];
	strcpy(student_name, new_name);

	student_ID = new_ID;
}


/*
student::student(const student& src_node)
{
    //unused copy constr.
}
*/

student::~student()
{
	if(student_name)
	{
		delete [] student_name;
		student_name = nullptr;
	}

    if(comm_list)
    {
        comm_list->remove_all();
        delete comm_list;
        comm_list = nullptr;
    }

	if(left)
	{
		delete left;
		left = nullptr;
	}

	if(right)
	{
		delete right;
		right = nullptr;
	}
}


bool student::set_new()
{
	//Ask for new student info
	char new_name[100];
	cout<<"Enter new student's name: ";
	cin.get(new_name, 100);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<"Enter new student's ID (6-digits): ";
	cin>>student_ID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

	student_name = new char[strlen(new_name)+1];
	strcpy(student_name, new_name);

	return true;
}


bool student::display_student()
{
    cout<<"\n-------------------------"<<endl;
    cout<<"Student Name: "<<student_name<<endl;
    cout<<"Student ID: U-"<<student_ID<<endl;
    cout<<"-------------------------";
    return true;
}


bool student::display_full_info()
{
    display_student();
    cout<<endl;
    if(comm_list == nullptr)
    {
        cout<<"["<<student_name<<" has no devices.]"<<endl;
        return false;
    }
    comm_list->display_all();
    return true;
}


bool student::compare_name(const char* to_compare)
{
    if(strcmp(student_name, to_compare)==0)
        return true;
    return false;
}


bool student::compare_ID(int to_compare)
{
    if(student_ID == to_compare)
        return true;
    return false;
}


bool student::add_device()
{
    if(comm_list == nullptr)
    {
        comm_list = new device_list;
    }

    bool check = true;
    while(check == true)
    {
        comm_list->add_device();
        check = run_again();
    }
    return true;
}


bool student::run_again()
{
    char choice;
    cout<<"Do you want to add another device for "<<student_name<<"? (y/n):"<<endl;
    cin>>choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(choice == 'y' || choice == 'Y')
        return true;
    return false;
}


bool student::call_school_phone()
{
    if(comm_list == nullptr)
    {
        cout<<"["<<student_name<<" does not have any devices.]"<<endl;
        return false;
    }
    comm_list->call_school_phone();
    return true;
}


bool student::emergency_alarm()
{
    if(comm_list == nullptr)
    {
        cout<<"["<<student_name<<" does not have any devices.]"<<endl;
        return false;
    }
    cout<<"["<<student_name<<" requested immediate emergency support. "; 
    comm_list->emergency_alarm();
    return true;
}


bool student::call_personal_phone()
{
    if(comm_list == nullptr)
    {
        cout<<"["<<student_name<<" does not have any devices.]"<<endl;
        return false;
    }
    comm_list->call_personal_phone();
    return true;
}


bool student::text_personal_phone()
{
     if(comm_list == nullptr)
    {
        cout<<"["<<student_name<<" does not have any devices.]"<<endl;
        return false;
    }
    comm_list->text_personal_phone();
    return true;
}


bool student::direct_message()
{
    if(comm_list == nullptr)
    {
        cout<<"["<<student_name<<" does not have any devices.]"<<endl;
        return false;
    }
    comm_list->direct_message();
    return true;
}


bool student::voice_call()
{
    if(comm_list == nullptr)
    {
        cout<<"["<<student_name<<" does not have any devices.]"<<endl;
        return false;
    }
    comm_list->voice_call();
    return true;
}


bool student::video_call()
{
    if(comm_list == nullptr)
    {
        cout<<"["<<student_name<<" does not have any devices.]"<<endl;
        return false;
    }
    comm_list->video_call();
    return true;
}


student*& student::getLeft()
{
	return left;
}


student*& student::getRight()
{
	return right;
}


device_list*& student::getList()
{
    return comm_list;
}


//operator overloading impl...
bool student::operator < (const student& src_node) const
{
	//if((*this).student_ID < src_node.student_ID)
    if(strcmp(this->student_name, src_node.student_name)<0)
	{
		return true;
	}	
	return false;
}

bool student::operator < (const char* src_name) const
{
	//if((*this).student_ID < src_ID)
    if(strcmp(this->student_name, src_name)<0)
	{
		return true;
	}
	return false;
}

bool student::operator > (const student& src_node) const
{
	//if((*this).student_ID > src_node.student_ID)
    if(strcmp(this->student_name, src_node.student_name)>0)
	{
		return true;
	}
	return false;
}

bool student::operator > (const char* src_name) const
{
	//if((*this).student_ID > src_ID)
    if(strcmp(this->student_name, src_name)>0)
	{
		return true;
	}
	return false;
}
