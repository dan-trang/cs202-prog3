/***************************************************
 * Daniel Trang
 * CS202: Programming Systems
 * Program #3
 * Device List Implementation File
 *
 * This file contains the implementation of functions
 * that build the Linear Linked List. This file also
 * contains implemented functions for the Node. Important
 * functions include wrapper functions that make calls to
 * the data class hierarchy called 'Communication'.
 * *************************************************/

#include "device_list.h"
using namespace std;

//LINEAR LINKED LIST:: DEVICE LIST
device_list::device_list(): head(nullptr), device_count(0), account_ID(nullptr){}


//device_list::device_list(const device_list& linear_list){}


device_list::~device_list()
{
	if(head)
	{
		delete [] head;
		head = nullptr;
	}

    if(account_ID)
    {
        delete [] account_ID;
        account_ID = nullptr;
    }
}


bool device_list::add_device()
{
	if(device_count == 3)
	{
		cout<<"[Cannot add more devices. Maximum device limit reached.]"<<endl;	
		return false;
	}

	//Ask for User to determine type of Device to add
	char user_input;
    bool good_input = false;
	while(good_input == false)
	{
		cout<<"\n-----------------------------------------\n";
		cout<<" What kind of device do you want to add?\n";
		cout<<"-----------------------------------------\n";
		cout<<"1. School Phone\n";
		cout<<"2. Smartphone\n";
		cout<<"3. Computer\n";
		cout<<"Enter your option: ";
		cin>>user_input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		if(user_input == '1' || user_input == '2' || user_input == '3')
		{
			good_input = true;	//breaks while loop
		}
		else
		{
			cout<<"[Invalid input. Please try again.]"<<endl;
		}
	}

	//Here, Device Node is created and upcasted to correct derived type.
	//1. School Phone, 2. Smartphone, 3. Computer
	device_node* save = head;	//save pointer to head of pre-existing list if any
	switch(user_input)
	{
		case '1':
			head = new device_node;			//create new Node 
			head->getDevice() = new school_phone;	//upcast + create new derived object within Node
			head->getDevice()->set_new();		//call function through virtual keyword
			head->getNext() = save;			//new head node points to old head 'save'
			device_count += 1;			//increment counter, keep track of max devices
			break;

		case '2':
			head = new device_node;			//create new Node
			head->getDevice() = new smartphone;		//upcast + create new derived object within Node
			head->getDevice()->set_new();		//call function through virtual keyword
			head->getNext() = save;			//new head node points to old head 'save'
			device_count += 1;			//increment counter, keep track of max devices
			break;

		case '3':
			head = new device_node;			//create new Node
			head->getDevice() = new computer;		//upcast + create new derived object within Node
			head->getDevice()->set_new();		//call function through virtual keyword
			head->getNext() = save;			//new head node points to old head 'save'
			device_count += 1;			//increment counter, keep track of max devices
			break;
	}	
	return true;
}


//device_node& device_list::retrieve_list(device_node* head){}


bool device_list::display_all()
{
	if(head == nullptr)
	{
		cout<<"[There are no devices for this student. Please add a device first.]"<<endl;
		return false;
	}

	return display_all(head);	
}


bool device_list::display_all(device_node* head)
{
	if(head != nullptr)
	{
		cout << *(head->getDevice());
		return display_all(head->getNext());
	}
	return true;
}


bool device_list::remove_all()
{
	if(head == nullptr)
	{
		cout<<"[This student does not own any devices. Please add one first.]"<<endl;
		return false;
	}

	remove_all(head);
	head = nullptr;
	return true;
}


bool device_list::remove_all(device_node* head)
{
	if(head->getNext()->getNext() != nullptr)
	{
		return remove_all(head->getNext());
	}
	else
	{
		delete head->getNext();
		head->getNext() = nullptr;
	}
	return true;
}


bool device_list::call_school_phone()
{
    if(head == nullptr)
	{
		cout<<"[This student does not own any devices. Please add one first.]"<<endl;
		return false;
	}

    return call_school_phone(head);
}

bool device_list::call_school_phone(device_node* head)
{
    if(head != nullptr)
    {
        if(head->getDevice()->peek_type() == 1)
        {
            head->getDevice()->call();
            return true;
        }
        return call_school_phone(head->getNext());
    }
    //reached end of list
    cout<<"[This student does not own a school phone.]"<<endl;
    return false;
}


bool device_list::emergency_alarm()
{
    if(head == nullptr)
	{
		cout<<"[This student does not own any devices. Please add one first.]"<<endl;
		return false;
	}

    return emergency_alarm(head);;
}


bool device_list::emergency_alarm(device_node* head)
{
    if(head != nullptr)
    {
        if(head->getDevice()->peek_type() == 1)
        {
            //RTTI for funzies
            school_phone* ohno;
            ohno = dynamic_cast<school_phone*>(head->getDevice());
            ohno->alarm();
            return true;
        }
        return emergency_alarm(head->getNext());
    }
    cout<<"[This student does not own a school phone.]"<<endl;
    return false;
}


bool device_list::call_personal_phone()
{
    if(head == nullptr)
	{
		cout<<"[This student does not own any devices. Please add one first.]"<<endl;
		return false;
	}

    return call_personal_phone(head);
}


bool device_list::call_personal_phone(device_node* head)
{
    if(head != nullptr)
    {
        if(head->getDevice()->peek_type() == 2)
        {
            head->getDevice()->call();
            return true;
        }
        return call_personal_phone(head->getNext());
    }
    cout<<"[This student does not own a smartphone.]"<<endl;
    return false;
}


bool device_list::text_personal_phone()
{
    if(head == nullptr)
    {
        cout<<"[This student does not own any devices. Please add one first.]"<<endl;
        return false;
    }
    return text_personal_phone(head);
}


bool device_list::text_personal_phone(device_node* head)
{
    if(head != nullptr)
    {
        if(head->getDevice()->peek_type() == 2)
        {
            head->getDevice()->message();
            return true;
        }
        return text_personal_phone(head->getNext());
    }
    cout<<"[This student does not own a smartphone.]"<<endl;
    return false;
}


bool device_list::direct_message()
{
    if(head == nullptr)
    {
        cout<<"[This student does not own any devices. Please add one first.]"<<endl;
        return false;
    }
 
    return direct_message(head);
}


bool device_list::direct_message(device_node* head)
{
    if(head != nullptr)
    {
        //if device is smartphone or computer
        if(head->getDevice()->peek_type() == 2 || head->getDevice()->peek_type() == 3)
        {
            if(head->getDevice()->peek_account_status() == true)
            {
                head->getDevice()->message();
                return true;
            }
        }
        return direct_message(head->getNext());
    }
    cout<<"[This student has not setup a PSU App account yet.]"<<endl;
    return false;
}


bool device_list::voice_call()
{
    if(head == nullptr)
    {
        cout<<"[This student does not own any devices. Please add one first.]"<<endl;
        return false;
    }
 
    return voice_call(head);
}


bool device_list::voice_call(device_node* head)
{
    if(head != nullptr)
    {
        if(head->getDevice()->peek_type() == 2 || head->getDevice()->peek_type() == 3)
        {
            if(head->getDevice()->peek_account_status() == true)
            {
                head->getDevice()->voice_call();
                return true;
            }
        }
        return voice_call(head->getNext());
    }
    cout<<"[This student has not setup a PSU App account yet.]"<<endl;
    return false;
}    


bool device_list::video_call()
{
    if(head == nullptr)
    {
        cout<<"[This student does not own any devices. Please add one first.]"<<endl;
        return false;
    }
 
    return video_call(head);
}


bool device_list::video_call(device_node* head)
{
    if(head != nullptr)
    {
        if(head->getDevice()->peek_type() == 2 || head->getDevice()->peek_type() == 3)
        {
            if(head->getDevice()->peek_account_status() == true)
            {
                head->getDevice()->video_call();
                return true;
            }
        }
        return video_call(head->getNext());
    }
    cout<<"[This student has not setup a PSU App account yet.]"<<endl;
    return false;
}


//LLL NODE: DEVICE NODE
device_node::device_node(): next(nullptr), device(nullptr), total_fees(0.0){}


/*
device_node::device_node(const device_node& src_node)
{
	//deep copy node to node
}
*/


device_node::~device_node()
{
    if(next != nullptr)
    {
        delete next;
        next = nullptr;
    }

    if(device)
    {
        delete device;
        device = nullptr;
    }
}


device_node*& device_node::getNext()
{
	return next;
}


communication*& device_node::getDevice()
{
    return device;
}

/*
device_node& operator += (communication& to_add)
{
    (*this).total_fees = temp
}
*/

//continue impl operator overloading here...
