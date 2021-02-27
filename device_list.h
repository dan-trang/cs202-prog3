/***************************************************
 * Daniel Trang
 * CS202: Programming Systems
 * Program #3
 * Device List Header File
 *
 * This file contains the abstract data type class
 * for a Linear Linked List. This LLL contains nodes
 * of type 'device_node' which hold pointers to the
 * actual data class.
 *
 * Each of the device_nodes will have private members
 * that keep track of total fees of device(s) as well
 * as if the student has an active account/username.
 * *************************************************/

#ifndef DEVICE_LIST_H
#define DEVICE_LIST_H
#include "communication.h"

//forward declaration
class device_node;

//LINEAR LINKED LIST: DEVICE LIST 
class device_list
{
	public:
		device_list();
		//device_list(const device_list& linear_list);
		~device_list();

		//manage nodes in LLL
		bool add_device();				//new node
		device_node& retrieve_list(device_node* head);	//deep copy of LLL
		bool display_all();				//display full device info
		bool remove_all();				//deallocate all nodes

		//device wrapper functions
		bool call_school_phone();	//dial by extension number
		bool emergency_alarm();		//trips alarm system using school phone
		bool call_personal_phone();	//call through phone provider
		bool text_personal_phone();	//SMS through personal phone
		bool direct_message();		//text via APP
		bool voice_call();		//call via APP
		bool video_call();		//video call via APP, premium account only
	
        //recursive calls
		device_node& deep_copy(device_node* head);	//using old LLL's head ptr, create deep copy
		bool display_all(device_node* head);
		bool remove_all(device_node* head);
		bool call_school_phone(device_node* head);	//dial by extension number
		bool emergency_alarm(device_node* head);		//trips alarm system using school phone
		bool call_personal_phone(device_node* head);	//call through phone provider
		bool text_personal_phone(device_node* head);	//SMS through personal phone
		bool direct_message(device_node* head);		//text via APP
		bool voice_call(device_node* head);		//call via APP
		bool video_call(device_node* head);		//video call via APP, premium account only

	private:
		device_node* head;	//pointer to head of LLL
		int device_count;	//this can be no more than 3
		char* account_ID;	//existing account ID if app is downloaded on one device
};


//LLL NODE: DEVICE NODE
class device_node 
{
	public:
		device_node();
		//device_node(const device_node& src_node);
		~device_node();
		
		//main node functions
		device_node*& getNext();
        communication*& getDevice();
		//device_node& operator += (communication& to_add);	//total sum of fees????

	private:
		device_node* next;	//pointer to next node in list
		communication* device;	//pointer to data class
		float total_fees;	//a sum of fees of all devices in the list
};
#endif
