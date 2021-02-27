/**********************************************
 * Daniel Trang
 * CS202: Programming Systems
 * Program #3
 * Communication Header File
 *
 * This file contains the base class communication
 * as well as it's three derived classes school phone,
 * smartphone, and computer. There are common function
 * prototypes which are called through virtual keyword,
 * and there are class-specific functions that will
 * require RTTI implementation later.
 *
 * Ultimately, these classes contain all the information
 * about any type of device as well as functions to
 * manage these class data and how it displays to the outside.
 * *********************************************/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <ctime>


//BASE CLASS: COMMUNICATION
class communication
{
	public:
		communication();
		communication(const communication& src_communication);
		virtual ~communication();

		int peek_type();		//returns int corresponding to device type
		bool update_type(int type);	//updates integer based on device type
		bool set_name(char* new_name);	//updates device name
		
		//virtual functions
		virtual bool set_new(); 			//set private members
		virtual bool set_existing(char* src_ID);	//if app account has been setup/paid before
		virtual bool call();				//call via Phone# or extension
		virtual bool message();				//message via App
       	virtual bool voice_call();          //voice call vis App
		virtual bool video_call();			//video call via App if premium account
        virtual bool peek_account_status();        //returns bool depending if account is active

		//virtual op overloading helpers
		virtual float sum_fee() const;
		virtual bool compare_number(int phone_number);
		virtual bool display();
        
		//operator overloading
		communication& operator = (const communication&);	//assignment
        communication operator + (const communication&) const;   //add opeator
		bool operator == (const communication&) const;	//comparison
		bool operator == (int);
		bool operator != (const communication&) const;	//comparison opposite
		friend std::ostream& operator << (std::ostream&, communication&);	//out stream
			
	private:
		int device_type;	//1. school phone 2. smartphone 3. computer
		char* device_name;  
        float total_fee;
};


//DERIVED CLASS: SCHOOL PHONE
class school_phone: public communication
{
	public:
		school_phone();
		school_phone(const school_phone& src_school_phone);
		~school_phone();

		//main functions
		bool set_new();
		bool call();

		float sum_fee() const;
		bool compare_number(int phone_number);
		bool display();

		//class-specific function -- needs RTTI to invoke 
		bool alarm();	 //*PSU ALERT: [name] requested emergency response ASAP* Last pinged location: [location]

		//operator overloading
		school_phone& operator = (const school_phone&);	//assignment
        bool operator == (const school_phone&) const;   //compare two phone objects
	  	bool operator == (const int) const;			//comparison extension number
		bool operator != (const int) const;			//comparison extension number
		friend std::ostream& operator << (std::ostream&, school_phone&);	//out stream	

		/*
		school_phone operator + (computer&) const;	//add fees (school phone + computer)
		school_phone operator + (smartphone&) const;	//add fees (school phone + smartphone)
		*/

	private:
		int phone_extension;	//unique 3-digit phone extension
        float school_phone_fee;
		char* location;		//unique "live" location of student
};



//DERIVED CLASS: SMARTPHONE
class smartphone: public communication
{
	public:
		smartphone();
		smartphone(const smartphone& src_smartphone);
		~smartphone();

		//main functions
		bool set_new();
		bool set_existing(char* src_ID, int src_account_type);    //if student has existing PSU app account, ignore app variables
		bool call();		//calls via phone service provider
		bool message();		//App functionality
		bool voice_call();	//calls via App
		bool video_call();	//App functionality

		float sum_fee() const;
		bool compare_number(int phone_number);
		bool display();
        bool peek_account_status();

		//operator overloading
		smartphone& operator = (const smartphone&);		//assignment
        bool operator == (const smartphone&) const;     //compare two smartphone objects
		bool operator == (const int) const;			        //compares phone number
		bool operator == (const char*) const;		    //compares student's app username+tag#
		bool operator != (const int) const;			        //compares phone number (opposite)
		bool operator != (const char*) const;		    //compares student's app username+tag# (opposite)
		friend std::ostream& operator << (std::ostream&, smartphone&);	//out stream

		/*	removed add_fees();
		smartphone operator + (school_phone&) const;	//add fees (smartphone + school phone) 
		smartphone operator + (computer&) const;		//add fees (smartphone + computer)
		*/
	
	protected:
		char setup_phone();         //Android vs. iPhone 
		char setup_phone_plan();    //1. 4G LTE Lite Plan or 2. 5G Unlimited Plan
		char setup_account();       //if student opts-in to PSU app
		bool opt_in();              //prompts user to agree to download app

	private:
		int phone_number;	        //unique phone number
		char* phone_OS;	            //iOS 14.4 (18D52)
		char* phone_plan;		    //1. 4G LTE Lite Plan 2. 5G Unlimited Plan
		float smartphone_fee;	    //cost based on plan selection

		bool account_status;	    //true: ENABLED or false: DISABLED
		int account_type;           //1. Standard or 2. Premium
		char* account_ID;	        //this is the student's personalized username+tag#
		float app_fee;		        //monthly account fee for PSU's app
};



//DERIVED CLASS: COMPUTER
class computer: public communication
{
	public:
		computer();
		computer(const computer& src_computer);
		~computer();

		//main functions
		bool set_new();
		bool set_existing(char* src_ID, int src_account_type);
		bool message();
		bool voice_call();
		bool video_call();

		float sum_fee() const;
		bool display();
        bool peek_account_status();

		//operator overloading
		computer& operator = (const computer&);		//assignment
		bool operator == (const computer&) const;   //compares two computer objects
		bool operator != (const computer&) const;   //compare two computer objects (opposite)
		bool operator == (const char*) const;		//compares student's app username+tag#
		bool operator != (const char*) const;		//compares student's app username+tag# (opposite)
		friend std::ostream& operator << (std::ostream&, computer&); 	//out stream

		/*
		computer operator + (school_phone&) const;	//add fees (computer + school phone)
		computer operator + (smartphone&) const; 		//add fees (computer + smartphone)
		*/

	protected:
		char setup_computer();
		bool opt_in();
		char setup_account();

	private:
		bool account_status;	//true: ENABLED or false: DISABLED
		int account_type;   	//1. Standard or 2. Premium
		char* computer_OS;	//macOS Big Sur 11.2.1 (20D74)
		char* account_ID;	//this is the student's personalized username+tag#
		float app_fee;		//monthly account fee for PSU's app
};
#endif
