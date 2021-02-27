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

#ifndef NETWORK_H
#define NETWORK_H
#include "device_list.h"
#include <chrono>

//forward definition cause I like my node definition below ADT
class student;

//BINARY TREE: NETWORK
class network
{
	public:
		network();
		//network(const network& src_bst);
		~network();

		//manage nodes in BST
		bool add_student();
		student*& retrieve_student(student*& root, const char* student_name);
		bool display_one();
		bool display_all();
		bool remove_all();
        bool authentication(char* src_username, char* src_password);

		//recursive helper functions
		bool add_student(student*& root, student*& new_node, int new_ID);
        bool display_one(student*& root, char* find);
        bool display_all(student*& root);
        bool remove_all(student*& root);
		
		//wrapper functions to interact w/Student's device(s)
        bool add_device();      //setup new device for student
		bool call_school_phone();	//dial by extension number
		bool emergency_alarm();		//trips alarm system using school phone
		bool call_personal_phone();	//call through phone service provider
		bool text_personal_phone();	//SMS through personal phone
		bool direct_message();		//text via APP
		bool voice_call();		//call via APP
		bool video_call();		//video call via APP, premium account only

        //operator overloading
        student*& operator [] (const char* student_name);

	private:
		char* username;		//faux authentication
		char* password;		//faux authentication
		student* root;	//root node of BST
};


//DERIVED CLASS: USER 
class user: public network
{
	public:
        user();
        //user(const user& src_user);   never use this, it is pointless
        ~user();

        //main functions
		int main_program();	                //full program kickstarter
		char user_menu();	                //user selects option via char
		bool execute(char user_input);		//execute user choice
		bool continue_menu();	            //ask to run program again
		bool authentication();	            //faux login authentication step

	private:
		char* program_info;	//details about the program
};


//BST NODE: STUDENT
class student
{
	public:
		student();
		student(char* new_name, int new_ID);
		student(const student& src_node);
		~student();

		//main functions
		bool set_new();
        bool display_student();
        bool display_full_info();
        bool compare_name(const char* to_compare);
        bool compare_ID(int to_compare);
        
		//user interaction functions
        bool add_device();
        bool run_again();
       	bool call_school_phone();	//dial by extension number
		bool emergency_alarm();		//trips alarm system using school phone
		bool call_personal_phone();	//call through phone service provider
		bool text_personal_phone();	//SMS through personal phone
		bool direct_message();		//text via APP
		bool voice_call();		//call via APP
		bool video_call();		//video call via APP, premium account only

		student*& getLeft();
		student*& getRight();
        device_list*& getList();

		//Binary greater/less than operator overloading organize BST
		bool operator < (const student&) const;
		bool operator < (const char*) const ;
		bool operator > (const student&) const;
		bool operator > (const char*) const;

	private:
		char* student_name;		//ASCII used to make BST key
		int student_ID;			//integer used to make the BST key	
		student* left;
		student* right;
		device_list* comm_list;	//LLL of student's device(s)
};
#endif
