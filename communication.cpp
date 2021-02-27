/*********************************************
 * Daniel Trang
 * CS202: Programming Systems
 * Program #3
 * Communication Implementation File
 *
 * Here contains implementation of all the functions
 * defined in the commmunication header file. It's
 * important to note that the operator overloading has
 * unique interactions within each derived class.
 *
 * The virtual base functions are phony functions that
 * do not perform anything impactful. These shouldn't ever
 * be called in any way unless accidental.
 * *********************************************/

#include "communication.h"
using namespace std;

//BASE CLASS: COMMUNICATION
communication::communication(): device_type(0), device_name(nullptr), total_fee(0.0){}


communication::communication(const communication & src_communication)
{
	if(src_communication.device_name != nullptr)
	{
		this->device_name = new char[strlen(src_communication.device_name)+1];
		strcpy(this->device_name, src_communication.device_name);
	}

	device_type = src_communication.device_type;
    total_fee = src_communication.total_fee;
}


communication::~communication()
{
	if(device_name)
	{
		delete [] device_name;
		device_name = nullptr;
	}
}


int communication::peek_type()
{
	return device_type;
}


bool communication::update_type(int type)
{
	device_type = type;
	return true;
}


bool communication::set_name(char* new_name)
{
	if(device_name)
	{
		delete [] device_name;
		device_name = nullptr;
	}
	device_name = new char[strlen(new_name)+1];
	strcpy(device_name, new_name);
	return true;
}


bool communication::set_new()
{
	//default call
	return false;
}


bool communication::set_existing(char* src_ID)
{
    //default call
    return false;
}


bool communication::call()
{
	//default call
	return false;
}


bool communication::message()
{
	//default call
	return false;
}


bool communication::voice_call()
{
    //default call
    return false;
}


bool communication::video_call()
{
	//default call
	return false;
}


bool communication::peek_account_status()
{
    //default call
    return false;
}


float communication::sum_fee() const
{
    //shouldn't ever call here
	return 0.0;
}


bool communication::compare_number(int phone_number)
{
	return false;
}


bool communication::display()
{
    cout << "Device Name: " << device_name << endl;
    return true;
}


communication & communication::operator = (const communication & src_communication)
{
	if(*this == src_communication)
	{
		return *this;
	}

	if(this->device_name)
	{
		delete [] this->device_name;
		this->device_name = nullptr;
	}
	
	this->device_name = new char[strlen(src_communication.device_name)+1];
	strcpy(this->device_name, src_communication.device_name);

	this->device_type = src_communication.device_type;

    this->total_fee = src_communication.total_fee;
	return *this;
}


communication communication::operator + (const communication& to_add) const
{
    communication total(*this);
    total.total_fee = this->total_fee + to_add.sum_fee();
    return total;
}


bool communication::operator == (const communication & to_compare) const
{
    if(this->device_name == nullptr)
    {
        return false;
    }

	if(strcmp(this->device_name, to_compare.device_name)==0)
	{
        if(this->device_type == to_compare.device_type)
        {
            return true;
        }
	}
	return false;
}


bool communication::operator == (int phone_number)
{
	return compare_number(phone_number);
}


bool communication::operator != (const communication & to_compare) const
{
	if(strcmp(this->device_name, to_compare.device_name)==0)
	{
        if(this->device_type == to_compare.device_type)
        {
            return false;
        }
    }
	return true;
}


ostream & operator << (ostream & out, communication & to_display)
{
	to_display.display();
	return out;
}



//DERIVED CLASS: SCHOOL PHONE
school_phone::school_phone(): phone_extension(0), school_phone_fee(49.99), location(nullptr)
{
	char standard[17];
	strcpy(standard, "PSU-issued Phone");

	communication::update_type(1);
	communication::set_name(standard);
}


school_phone::school_phone(const school_phone & src_phone): communication(src_phone)
{
	phone_extension = src_phone.phone_extension;
	school_phone_fee = src_phone.school_phone_fee;

	if(src_phone.location != nullptr)
	{
		location = new char[strlen(src_phone.location)+1];
		strcpy(location, src_phone.location);
	}		
}


school_phone::~school_phone()
{
    if(location)
    {
        delete [] location;
        location = nullptr;
    }
}


bool school_phone::set_new()
{
	char input_location[150];

	cout<<"Enter a unique 3-digit extension number (ex. 579): ";
	cin>>phone_extension;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
	cout<<"Enter a random address to simulate live location: ";
	cin.get(input_location, 150);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

    location = new char[strlen(input_location)+1];
    strcpy(location, input_location);

	cout<<"New PSU school phone issued to student."<<endl;
    return true;
}


bool school_phone::call()
{
	//phone extension comparison should be handled by operator overloading '=='
	cout<<"[call via school phone successful... phone call has ended]"<<endl;
	return true;
}


float school_phone::sum_fee() const
{
	return school_phone_fee;	
}


bool school_phone::compare_number(int phone_number)
{
	if(this->phone_extension == phone_number)
	{
		return true;
	}
	return false;
}


bool school_phone::display()
{
	cout << *this << endl;
    return true;
}


bool school_phone::alarm()
{
	if(location != nullptr)
	{
		cout<<"Last pinged location: ["<<location<<"]"<<endl;
		return true;
	}
	cout<<"Last pinged location: [UNKNOWN]"<<endl;
	return false;
}


school_phone & school_phone::operator = (const school_phone & src_school_phone)
{
	if(*this == src_school_phone)
	{
		return *this;
	}

	this->phone_extension = src_school_phone.phone_extension;
	this->school_phone_fee = src_school_phone.school_phone_fee;

	if(this->location)
	{
		delete [] this->location;
		this->location = nullptr;
	}

	this->location = new char[strlen(src_school_phone.location)+1];
	strcpy(this->location, src_school_phone.location);

    this->communication::operator=(src_school_phone);
    return *this;
}


/*
school_phone school_phone::operator + (computer & to_add) const
{
    school_phone total(*this);
    total.school_phone_fee = this->school_phone_fee + to_add.get_fee();
    return total;
}


school_phone school_phone::operator + (smartphone & to_add) const
{
	school_phone total = *this;
	total.school_phone_fee = this->school_phone_fee + to_add.add_fees();
	return total;
}
*/


bool school_phone::operator == (const school_phone& to_compare) const
{
    if(this->phone_extension == to_compare.phone_extension)
    {
        if(strcmp(this->location, to_compare.location)==0)
        {
            if(this->school_phone_fee == to_compare.school_phone_fee)
            {
                return true;
            }
        }
    }
    return false;
}


bool school_phone::operator == (const int to_dial) const
{
	if(this->phone_extension == to_dial)
	{
		return true;
	}
	return false;
}


bool school_phone::operator != (const int to_dial) const
{
	if(this->phone_extension == to_dial)
	{
		return false;
	}
	return true;
}


ostream & operator << (ostream & out, school_phone & to_display)
{
    out <<"\n     School Phone     \n";
    out <<"-----------------------\n";
    to_display.communication::display();
	out << "Phone Extension: " << to_display.phone_extension;
    out << "\nEmergency Location: "<< to_display.location;
	out << "\nSchool Phone Fee: $" << to_display.school_phone_fee << endl;
	return out;
}



//DERIVED CLASS: SMARTPHONE
smartphone::smartphone(): phone_number(0), phone_OS(nullptr), phone_plan(nullptr), smartphone_fee(0.0), account_status(false), account_ID(nullptr), app_fee(0.0)
{
    communication::update_type(2);  //2. smartphone
}

smartphone::smartphone(const smartphone & src_smartphone)
{
	phone_number = src_smartphone.phone_number;
	smartphone_fee = src_smartphone.smartphone_fee;
	account_status = src_smartphone.account_status;
    app_fee = src_smartphone.app_fee;

	if(phone_OS)
	{
		delete [] phone_OS;
		phone_OS = nullptr;
	}
	phone_OS = new char[strlen(src_smartphone.phone_OS)+1];
	strcpy(phone_OS, src_smartphone.phone_OS);

    if(phone_plan)
    {
        delete [] phone_plan;
        phone_plan = nullptr;
    }
    phone_plan = new char[strlen(src_smartphone.phone_plan)+1];
    strcpy(phone_plan, src_smartphone.phone_plan);

	if(account_ID)
	{
		delete [] account_ID;
		account_ID = nullptr;
	}
	account_ID = new char[strlen(src_smartphone.account_ID)+1];
	strcpy(account_ID, src_smartphone.account_ID);
}


smartphone::~smartphone()
{
    if(phone_OS)
	{
		delete [] phone_OS;
		phone_OS = nullptr;
	}

    if(phone_plan)
    {
        delete [] phone_plan;
        phone_plan = nullptr;
    }

	if(account_ID)
	{
		delete [] account_ID;
		account_ID = nullptr;
	}
}


bool smartphone::set_new()
{
    bool make_account = false;
    bool good_input = false;

    while(good_input == false)
    {
        char user_select;
        char new_phone[100], new_OS[100];
        user_select = setup_phone(); 
        switch(user_select)
        {
            case '1':
                strcpy(new_phone, "iPhone 13 Pro Max");
                communication::set_name(new_phone);

                strcpy(new_OS, "iOS 14.4 (18D52)");
                phone_OS = new char[strlen(new_OS)+1];
                strcpy(phone_OS, new_OS);
                cout<<"Enter your phone number: ";
                cin>>phone_number;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                good_input = true;
                break;
 
            case '2':
                strcpy(new_phone, "Samsung Galaxy S21");
                communication::set_name(new_phone);

                strcpy(new_OS, "One UI 3.1, Android 11");
                phone_OS = new char[strlen(new_OS)+1];
                strcpy(phone_OS, new_OS);
                cout<<"Enter your phone number: ";
                cin>>phone_number;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                good_input = true;
                break;

            default:
                cout<<"Invalid input. Please try again.\n"<<endl;
        }
    }

    good_input = false;     //reset variable to false
    while(good_input == false)
    {
        char user_select;
        char new_plan[100];
        user_select = setup_phone_plan();
        switch(user_select)
        {
            case '1':
                strcpy(new_plan, "4G LTE Lite");
                phone_plan = new char[strlen(new_plan)+1];
                strcpy(phone_plan, new_plan);
                smartphone_fee = 24.99;
                good_input = true;
                break;
            
            case '2':
                strcpy(new_plan, "5G Unlimited Data");
                phone_plan = new char[strlen(new_plan)+1];
                strcpy(phone_plan, new_plan);
                smartphone_fee = 74.99;
                good_input = true;
                break;

            default:
                cout<<"Invalid input. Please try again.\n"<<endl;
        }
    }
    
    make_account = opt_in();    //call to action prompt for opt in
    good_input = false;     //reset variable to false
    while(make_account == true && good_input == false)
    {
        char user_select;
        char new_user_ID[200];
        user_select = setup_account();
        switch(user_select)
        {
            case '1':
                account_status = true;
                account_type = 1;

                cout<<"Make a unique username (ex.CuriousGeorge): ";
                cin.get(new_user_ID, 100);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                account_ID = new char[strlen(new_user_ID)+1];
                strcpy(account_ID, new_user_ID);
                good_input = true;
                break;

            case '2':
                account_status = true;
                account_type = 2;
                app_fee = 4.99;

                cout<<"Make a unique username (ex.BananaJoe): ";
                cin.get(new_user_ID, 100);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                account_ID = new char[strlen(new_user_ID)+1];
                strcpy(account_ID, new_user_ID);
                good_input = true;
                break;
                       
            default:
                cout<<"Invalid input. Please try again.\n"<<endl;
        }
    }
    return true;
}

char smartphone::setup_phone()
{
    char user_choice;
    cout<<"\n----------------------------\n";
    cout<<"   Choose your Smartphone   \n";
    cout<<"----------------------------\n";
    cout<<"1. iPhone 13 Pro Max\n";
    cout<<"2. Samsung Galaxy S21"<<endl;
    cout<<"\nEnter your option: ";
    cin>>user_choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return user_choice; 
}

char smartphone::setup_phone_plan()
{
    char user_choice;
    cout<<"\n----------------------------\n";
    cout<<"     Phone Service Plans    \n";
    cout<<"----------------------------\n";
    cout<<"1. 4G LTE Lite Plan // $24.99 per month\n";
    cout<<"2. 5G Unlimited Data Plan // $74.99 per month"<<endl;
    cout<<"\nEnter your option: ";
    cin>>user_choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return user_choice;
}


bool smartphone::opt_in()
{
    char user_choice;
    cout<<"\n*****Would you like to download PSU's Communication App?*****\n";
    cout<<"This app will connect you with fellow classmates, tutors,\n";
    cout<<"and professors giving you the best university experience.\n";
    cout<<"\n1. Yes, sign me up!\n";
    cout<<"2. No, thanks. I'd rather not take advantage of this amazing opportunity."<<endl;
    cout<<"\nEnter your option: ";
    cin>>user_choice;
    
    if(user_choice == '1')
    {
        return true;
    }
    return false; 
}


char smartphone::setup_account()
{
    char user_choice;
    cout<<"\n----------------------------\n";
    cout<<"      PSU App Membership    \n";
    cout<<"----------------------------\n";
    cout<<"1. Free Standard Account (perks: message board + voice call)\n";
    cout<<"2. Premium Account (perks: standard plus video calling 1080p + access to homework solutions)"<<endl;
    cout<<"\nEnter your option: ";
    cin>>user_choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return user_choice; 
}


bool smartphone::set_existing(char* src_ID, int src_account_type)
{
    account_status = true;
    account_type = src_account_type;
    account_ID = new char[strlen(src_ID)+1];
    strcpy(account_ID, src_ID);
    if(account_type == 2)
    {
        app_fee = 4.99;
    }

    char user_select;
    bool good_input = false;

    while(good_input == false)
    {
        char new_phone[100], new_OS[100];
        user_select = setup_phone(); 
        switch(user_select)
        {
            case '1':
                strcpy(new_phone, "iPhone 13 Pro Max");
                communication::set_name(new_phone);

                strcpy(new_OS, "iOS 14.4 (18D52)");
                phone_OS = new char[strlen(new_OS)+1];
                strcpy(phone_OS, new_OS);
                good_input = true;
                break;
 
            case '2':
                strcpy(new_phone, "Samsung Galaxy S21");
                communication::set_name(new_phone);

                strcpy(new_OS, "One UI 3.1, Android 11");
                phone_OS = new char[strlen(new_OS)+1];
                strcpy(phone_OS, new_OS);
                good_input = true;
                break;

            default:
                cout<<"Invalid input. Please try again.\n"<<endl;
        }
    }

    good_input = false;     //reset variable to false
    while(good_input == false)
    {
        char new_plan[100];
        user_select = setup_phone_plan();
        switch(user_select)
        {
            case '1':
                strcpy(new_plan, "4G LTE Lite");
                phone_plan = new char[strlen(new_plan)+1];
                strcpy(phone_plan, new_plan);
                smartphone_fee = 24.99;
                good_input = true;
                break;
            
            case '2':
                strcpy(new_plan, "5G Unlimited Data");
                phone_plan = new char[strlen(new_plan)+1];
                strcpy(phone_plan, new_plan);
                smartphone_fee = 74.99;
                good_input = true;
                break;

            default:
                cout<<"Invalid input. Please try again.\n"<<endl;
        }
    }
    
    cout<<"Enter your phone number: ";
    cin>>phone_number;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}


bool smartphone::peek_account_status()
{
    return account_status;
}


bool smartphone::call()
{
	cout<<"[call via personal phone successful... phone call has ended]"<<endl;
    return true;
}


bool smartphone::message()
{
    //no app setup, use SMS
    if(account_status == false)
    {
        cout<<"[successfully texted student through phone provider SMS]"<<endl;
        return true;
    }

    //generate random number 1-10 
    srand((unsigned) time(0));
    int random_num = (rand() % 10) + 1;

    switch(random_num)
    {
        case 1:
            cout<<"omg whats up? long time no see!"<<endl;
            break;

        case 2:
            cout<<"sry i missed your msg earlier... could i buy you lunch some time? :)"<<endl;
            break;

        case 3:
            cout<<"... sorry busy atm. gtg."<<endl; 
            break;

        case 4:
            cout<<"heyo what's up. did you know we have club meeting tonight at 7pm?"<<endl;
            break;

        case 5:
            cout<<"dude I was just about to msg you, I got into Google!"<<endl;
            break;

        case 6:
            cout<<"dude I was just about to msg you... I got rejected from Google :("<<endl;
            break;

        case 7:
            cout<<"stop msging me... i'm busy trying to finish my Labs -_-"<<endl;
            break;

        case 8:
            cout<<"I don't recognize your username...Do I know you?"<<endl;
            break;
            
        case 9:
            cout<<"You changed your username? 'CodingMonkey1337' lul hilarious"<<endl;
            break;
            
        case 10:
            cout<<"hey! I was just about to msg you, I think the due date was pushed back till next week"<<endl;
            break;
    }
    return true;
}


bool smartphone::voice_call()
{
    cout<<"[call via PSU Mobile App successful... call has ended]"<<endl;
    return true;
}


bool smartphone::video_call()
{
    cout<<"[video call via PSU Mobile app successful... call has ended]"<<endl;
    return true;
}


float smartphone::sum_fee() const
{
	return (smartphone_fee + app_fee); 
}


bool smartphone::compare_number(int phone_number)
{
	if(this->phone_number == phone_number)
	{
		return true;
	}
	return false;
}


bool smartphone::display()
{
	cout << *this << endl;	
    return true;
}


smartphone& smartphone::operator = (const smartphone& to_assign)
{  
    if(*this == to_assign)
        return *this; 

    //static variable assignment
    phone_number = to_assign.phone_number;
    smartphone_fee = to_assign.smartphone_fee;
    account_status = to_assign.account_status;
    account_type = to_assign.account_type;
    app_fee = to_assign.app_fee;

    //dynamic variables
    phone_OS = new char[strlen(to_assign.phone_OS)+1];
    strcpy(phone_OS, to_assign.phone_OS);
    
    phone_plan = new char[strlen(to_assign.phone_plan)+1];
    strcpy(phone_plan, to_assign.phone_plan);

    account_ID = new char[strlen(to_assign.account_ID)+1];
    strcpy(account_ID, to_assign.account_ID);

    //Assigning Parent private members
    communication::operator = (to_assign);
    return *this;
}


/*
smartphone smartphone::operator + (school_phone& to_add) const
{  
    smartphone total(*this);
	total.smartphone_fee = this->smartphone_fee + this->app_fee + to_add.get_fee();
	return total;
}


smartphone smartphone::operator + (const computer& to_add) const
{
    smartphone total(*this);
    total.smartphone_fee = this->smartphone_fee + this->app_fee + to_add.app_fee
    return total;
}
*/


bool smartphone::operator == (const smartphone& to_compare) const
{
    if(this->phone_number == to_compare.phone_number)
    {
        if(strcmp(this->account_ID, to_compare.account_ID)==0)
        {
            if(this->smartphone_fee == to_compare.smartphone_fee)
            {
                return true;
            }
        }
    }
    return false;
}



bool smartphone::operator == (const int to_dial) const
{ 
    if(this->phone_number == to_dial)
    {
        return true;
    }
    return false;
}


bool smartphone::operator == (const char* to_compare) const
{
    if(this->account_ID == nullptr)
    {
        return false;
    }

    if(strcmp(this->account_ID, to_compare) == 0)
    {
        return true;
    }
    return false;
}


bool smartphone::operator != (const int to_dial) const
{
    if(this->phone_number == to_dial)
    {
        return false;
    }
    return true;
}


bool smartphone::operator != (const char* to_compare) const
{
    if(strcmp(this->account_ID, to_compare) == 0)
    {
        return false;
    }
    return true;
}


ostream& operator << (ostream& out, smartphone& to_display)
{
    out <<"\n       Smartphone      \n";
    out <<"-----------------------\n";
    to_display.communication::display();
    out << "Phone Number: " << to_display.phone_number;
    out << "\nPhone OS: " << to_display.phone_OS;
    out << "\nPhone Plan: " << to_display.phone_plan;
    out << "\nMonthly Fee: " << to_display.smartphone_fee;
    out << "\nApp Account: ";
    if(to_display.account_type == 1)
    {
        out << "ENABLED | Standard\n";
        out << "Username: " << to_display.account_ID;
    }
    else if(to_display.account_type == 2)
    {
        out << "ENABLED | Premium\n";
        out << "Username: " << to_display.account_ID;
    }
    else
    {
        out << "DISABLED";
    }
    out << "\nApp Fee: $" << to_display.app_fee << endl;
    return out;
}



//DERIVED CLASS: COMPUTER
computer::computer(): account_status(false), account_type(0), computer_OS(nullptr), account_ID(nullptr), app_fee(0.0)
{
    communication::update_type(3);
}


computer::computer(const computer& src_computer)
{
    account_status = src_computer.account_status; 
    account_type = src_computer.account_type;
    app_fee = src_computer.app_fee;

    computer_OS = new char[strlen(src_computer.computer_OS)+1];
    strcpy(computer_OS, src_computer.computer_OS);

    account_ID = new char[strlen(src_computer.account_ID)+1];
    strcpy(account_ID, src_computer.account_ID);
}


computer::~computer()
{
    if(computer_OS)
    {
        delete [] computer_OS;      
        computer_OS = nullptr;
    }

    if(account_ID)
    {
        delete [] account_ID;
        account_ID = nullptr;
    }
}


bool computer::set_new()
{
    bool make_account = false;
    bool good_input = false;
   
    //Setting up new computer info
    while(good_input == false)
    {
        char user_select;
        char new_computer[100], new_OS[100];
        user_select = setup_computer(); 
        switch(user_select)
        {
            case '1':
                strcpy(new_computer, "ASUS RoG Zephyrus G14");
                communication::set_name(new_computer);

                strcpy(new_OS, "Windows 10 Pro");
                computer_OS = new char[strlen(new_OS)+1];
                strcpy(computer_OS, new_OS);

                good_input = true;
                break;
 
            case '2':
                strcpy(new_computer, "Macbook Pro 13");
                communication::set_name(new_computer);

                strcpy(new_OS, "macOS Big Sur 11.2.1 (20D74)");
                computer_OS = new char[strlen(new_OS)+1];
                strcpy(computer_OS, new_OS);

                good_input = true;
                break;

            default:
                cout<<"Invalid input. Please try again.\n"<<endl;
        }
    }

    make_account = opt_in();
    good_input = false;
    while(make_account == true && good_input == false)
    {
        char user_select;
        char new_user_ID[200];
        user_select = setup_account();
        switch(user_select)
        {
            case '1':
                account_status = true;
                account_type = 1;

                cout<<"Make a unique username (ex.LazyPanda): ";
                cin.get(new_user_ID, 100);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                account_ID = new char[strlen(new_user_ID)+1];
                strcpy(account_ID, new_user_ID);
                good_input = true;
                break;

            case '2':
                account_status = true;
                account_type = 2;
                app_fee = 4.99;

                cout<<"Make a unique username (ex.DerpyGazelle): ";
                cin.get(new_user_ID, 100);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                account_ID = new char[strlen(new_user_ID)+1];
                strcpy(account_ID, new_user_ID);
                good_input = true;
                break;
                       
            default:
                cout<<"Invalid input. Please try again.\n"<<endl;
        }
    }      
    return true;
}


bool computer::set_existing(char* src_ID, int src_account_type)
{
    account_status = true;
    account_type = src_account_type;
    account_ID = new char[strlen(src_ID)+1];
    strcpy(account_ID, src_ID);
    if(account_type == 2)
    {
        app_fee = 4.99;
    }

    bool good_input = false;
    while(good_input == false)
    {
        char user_select;
        char new_computer[100], new_OS[100];
        user_select = setup_computer(); 
        switch(user_select)
        {
            case '1':
                strcpy(new_computer, "ASUS RoG Zephyrus G14");
                communication::set_name(new_computer);

                strcpy(new_OS, "Windows 10 Pro");
                computer_OS = new char[strlen(new_OS)+1];
                strcpy(computer_OS, new_OS);

                good_input = true;
                break;
 
            case '2':
                strcpy(new_computer, "Macbook Pro 13");
                communication::set_name(new_computer);

                strcpy(new_OS, "macOS Big Sur 11.2.1 (20D74)");
                computer_OS = new char[strlen(new_OS)+1];
                strcpy(computer_OS, new_OS);

                good_input = true;
                break;

            default:
                cout<<"Invalid input. Please try again.\n"<<endl;
        }
    }
    return true;
}


bool computer::peek_account_status()
{
    return account_status;
}


bool computer::message()
{
    //generate random number 1-10 
    srand((unsigned) time(0));
    int random_num = (rand() % 10) + 1;

    switch(random_num)
    {
        case 1:
            cout<<"omg whats up? long time no see!"<<endl;
            break;

        case 2:
            cout<<"sry i missed your msg earlier... could i buy you lunch some time? :)"<<endl;
            break;

        case 3:
            cout<<"... sorry busy atm. gtg."<<endl; 
            break;

        case 4:
            cout<<"heyo what's up. did you know we have club meeting tonight at 7pm?"<<endl;
            break;

        case 5:
            cout<<"dude I was just about to msg you, I got into Google!"<<endl;
            break;

        case 6:
            cout<<"dude I was just about to msg you... I got rejected from Google :("<<endl;
            break;

        case 7:
            cout<<"stop msging me... i'm busy trying to finish my Labs -_-"<<endl;
            break;

        case 8:
            cout<<"I don't recognize your username...Do I know you?"<<endl;
            break;
            
        case 9:
            cout<<"You changed your username? 'CodingMonkey1337' lul hilarious"<<endl;
            break;
            
        case 10:
            cout<<"hey! I was just about to msg you, I think the due date was pushed back till next week"<<endl;
            break;
    }
    return true;
}


bool computer::voice_call()
{
    cout<<"[Voice call via PSU Desktop App successful... call has ended]"<<endl;
    return true;
}


bool computer::video_call()
{
    cout<<"[Video call via PSU Desktop App successful... call has ended]"<<endl;
    return true;
}


float computer::sum_fee() const
{
	return app_fee;
}


bool computer::display()
{
	cout << *this << endl;
    return true;
}


char computer::setup_computer()
{
    char user_choice;
    cout<<"\n----------------------------\n";
    cout<<"     Choose your Computer     \n";
    cout<<"----------------------------\n";
    cout<<"1. ASUS RoG Zephyrus G14\n";
    cout<<"2. Macbook Pro 13"<<endl;
    cout<<"\nEnter your option: ";
    cin>>user_choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return user_choice; 
}


bool computer::opt_in()
{
    char user_choice;
    cout<<"\n*****Would you like to download PSU's Communication App?*****\n";
    cout<<"This app will connect you with fellow classmates, tutors,\n";
    cout<<"and professors giving you the best university experience.\n";
    cout<<"!!! YOU MUST DOWNLOAD APP ON COMPUTER TO UTILIZE COMMUNICATION FUNCTIONALITY !!!\n"<<endl;
    cout<<"\n1. Yes, sign me up!\n";
    cout<<"2. No, thanks. I'd rather not take advantage of this amazing opportunity."<<endl;
    cout<<"\nEnter your option: ";
    cin>>user_choice;
    
    if(user_choice == '1')
    {
        return true;
    }
    return false; 
}


char computer::setup_account()
{
    char user_choice;
    cout<<"\n----------------------------\n";
    cout<<"      PSU App Membership    \n";
    cout<<"----------------------------\n";
    cout<<"1. Free Standard Account (perks: message board + voice call)\n";
    cout<<"2. Premium Account (perks: standard plus video calling 1080p + access to homework solutions)"<<endl;
    cout<<"\nEnter your option: ";
    cin>>user_choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return user_choice; 
}


computer& computer::operator = (const computer& to_assign)
{
    if(*this == to_assign)
        return *this;

    //base class variables
    communication::operator = (to_assign);

    //static variables
    account_status = to_assign.account_status; 
    account_type = to_assign.account_type;
    app_fee = to_assign.app_fee;
    
    //dynamic memory
    computer_OS = new char[strlen(to_assign.computer_OS)+1];
    strcpy(computer_OS, to_assign.computer_OS);

    account_ID = new char[strlen(to_assign.account_ID)+1];
    strcpy(account_ID, to_assign.account_ID);
    return *this;
}


/*
computer computer::operator + (school_phone& to_add) const
{
    computer total(*this);
    total.app_fee = this->app_fee + to_add.get_fee();
    return total;
}


computer computer::operator + (smartphone& to_add) const
{
    computer total(*this);
    total.app_fee = this->app_fee + to_add.add_fees();
    return total;
}
*/


bool computer::operator == (const computer& to_compare) const
{
    if(strcmp(this->account_ID, to_compare.account_ID)==0)
    {
        if(strcmp(this->computer_OS, to_compare.computer_OS)==0)
        {
            return true;
        }
    }
    return false;
}


bool computer::operator == (const char* src_ID) const
{
    if(this->account_ID == nullptr)
    {
        return false;
    }

    if(strcmp(this->account_ID, src_ID) == 0)
    {
        return true;
    }
    return false;
}


bool computer::operator != (const computer& to_compare) const
{
    if(strcmp(this->account_ID, to_compare.account_ID)==0)
    {
        if(strcmp(this->computer_OS, to_compare.computer_OS)==0)
        {
            return false;
        }
    }
    return true;
}


bool computer::operator != (const char* src_ID) const
{
    if(this->account_ID == nullptr)
    {
        return true;
    }

    if(strcmp(this->account_ID, src_ID)==0)
    {
        return false;
    }
    return true;
}


ostream& operator << (ostream& out, computer& to_display)
{
    out <<"\n      Computer       \n";
    out <<"-----------------------\n";
    to_display.communication::display();
    out << "Computer OS: " <<to_display.computer_OS;
    out << "\nApp Account: ";
    if(to_display.account_type == 1)
    {
        out << "ENABLED | Standard\n";
        out << "Username: " << to_display.account_ID;
    }
    else if(to_display.account_type == 2)
    {
        out << "ENABLED | Premium\n";
        out << "Username: " << to_display.account_ID;
    }
    else
    {
        out << "DISABLED";
    }
    out << "\nApp Fee: $" << to_display.app_fee << endl;
    return out;
}
