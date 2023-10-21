// lab 07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Node
{
public:
	int Priority;
	int Time_to_complete;
	bool Is_waiting;
	bool is_completed;
	char Process_name;
	int Memory;
	Node* nextProcess;

	Node(int Priority, int time, bool is_waiting, char name, int memory,int complete)
	{
		this->Priority = Priority;
		this->Time_to_complete = time;
		this->Is_waiting = is_waiting;
		this->Process_name = name;
		this->Memory = memory;
		this->is_completed = complete;
		nextProcess = NULL;
	}

};

class CPU_Processor
{
public:
	static int Max_Ram;
	static int Used_Ram;
	int priority_level;//1-20
	int ram_level;//1-500
	int time_level;//1-10
	char name;//A-Z
	Node* head = NULL;
	Node* tail = NULL;
	void set_attributes_of_process()
	{

		priority_level = (rand() % 20) + 1;//1-20
		ram_level = (rand() % 500) + 1;//1-500
		time_level = (rand() % 10) + 1;//1-10
		int ascii = (rand() % 26) + 1;
		ascii += 65;
		name = char(ascii);
	}
	void Task_add()
	{



		set_attributes_of_process();
		Used_Ram += ram_level;
		Node* newprocess = new Node(priority_level, time_level, false, name, ram_level,false);
		if (!head)
		{
			head = newprocess;
			tail = newprocess;

		}
		else
		{
			tail->nextProcess = newprocess;
			tail = newprocess;

		}

	}
	//this function will be call according to 15% cndition: 
	void Spawing(int s)
	{
		for (int i = 0; i < s; i++)
		{
			int chance_to_add = (rand() % 100);//0-99
			//STEP 01: if chance occures and ram exists then simply create it:
			if (chance_to_add < 15 && Used_Ram < Max_Ram)
			{
				Task_add();
			}

			//STEP 02: cheak priority if lower one running then stop that and run currrent one  
			else if (chance_to_add<15 && Used_Ram>Max_Ram)
			{
				//if(priority_level)
				Node* lower = Is_higher_priority(priority_level);
				//cheak if there is non task exist which have lower priority then current one
				if (lower == NULL)
				{
					cout << "Task is un important" << endl;
					continue;
				}
				//free ram of lower one
				Used_Ram -= lower->Memory;
				//put on waiting state
				lower->Is_waiting = true;

			
			}
			//STEP 03: Update Time for all Tasks: 1 loop iteration=1sec
			Update_Time();
			//STEP 04: Task end if there is no time left
			End_tasks();
			//STEP 05: Printing after every seconds:
			Display_all_Process();


			}

	}
	//this function will compare current task's priority with all running task if ram is full
	Node* Is_higher_priority(int priority)
	{
		Node* temp = head;

		//gettting most lower priority level
		int lower = temp->Priority;
		Node* lowerone = NULL;
		while (temp)
		{
			if (lower > temp->Priority)
			{
				lower = temp->Priority;
				//storing node
				lowerone = temp;
			}
			temp = temp->nextProcess;

		}
		return lowerone;
		
	}

	void Update_Time()
	{
		Node* temp = head;
		while (temp)
		{
			if(!temp->is_completed&&!temp->Is_waiting)
			{
			temp->Time_to_complete -= 1;
			if (temp->Time_to_complete <= 0)
			{
				temp->is_completed = true;
				
			}
			}
			temp = temp->nextProcess;
		}
	}


	void End_tasks()
	{
		Node* temp=head;
		if (temp == NULL) {
			return;
		}
		while (temp->nextProcess)
		{
			if (temp->Time_to_complete <= 0||temp->is_completed)
														
		{
				temp->is_completed = true;
				temp->Is_waiting = false;
				
		}
			temp = temp->nextProcess;
		}
	}

	void Display_all_Process()
	{
		Node* traverse = head;
		//Printing task which are neither completed  nor running state 
		while (traverse)
		{
			//
			if (!traverse->is_completed && !traverse->Is_waiting)
			{

			cout << "Process Name :" << traverse->Process_name << endl;
			cout << "Process Memeory : " << traverse->Memory << endl;
			cout << "Process Priority : " << traverse->Priority << endl;
			cout << "Process Time : " << traverse->Time_to_complete << endl;
			cout << "Process state : " << "Waiting" << endl;
			cout << "Status : " << "Not complete" << endl;
			cout << "Total RAM : " << Max_Ram << endl;
			cout << "Used RAM : " << Used_Ram << endl;

			cout << "-----------------1------------------------\n";
			}
			traverse = traverse->nextProcess;
		}


		 traverse = head;
		//Printing task which are  completed but on waiting state 
		while (traverse)
		{
			//
			if (traverse->is_completed && traverse->Is_waiting)
			{

			cout << "Process Name :" << traverse->Process_name << endl;
			cout << "Process Memeory : " << traverse->Memory << endl;
			cout << "Process Priority : " << traverse->Priority << endl;
			cout << "Status : " << "completed" << endl;
			cout << "Total RAM : " << Max_Ram << endl;
			cout << "Used RAM : " << Used_Ram << endl;

			cout << "---------------------2--------------------\n";
			}
			traverse = traverse->nextProcess;
		}

		traverse = head;
		//Printing task which are  not completed and on running state 
		while (traverse)
		{
			//
			if (traverse->is_completed && !traverse->Is_waiting) 
			{

			cout << "Process Name :" << traverse->Process_name << endl;
			cout << "Process Memeory : " << traverse->Memory << endl;
			cout << "Process Priority : " << traverse->Priority << endl;
			cout << "Process Time : " << traverse->Time_to_complete << endl;
			
			cout << "Status : " << " completed" << endl;
			cout << "Total RAM : " << Max_Ram << endl;
			cout << "Used RAM : " << Used_Ram << endl;

			cout << "--------------------3---------------------\n";
			}
			traverse = traverse->nextProcess;
		}
	}

};
int CPU_Processor::Max_Ram = 2048;
int CPU_Processor::Used_Ram = 0;
int main()
{
	srand(time(NULL));
	CPU_Processor P1;
	//Running 50 differnt Process 
	P1.Spawing(50);
	return 0;

}


