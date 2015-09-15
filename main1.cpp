//Larry Martinez 0946364
//Cosc 4330 OS Summer 2015 

#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


int main()
{	
	int numOfNodesLvlOne;
	int numOfNodesLvlTwo=0; //creating variables to keep count of how many nodes are in each level

	if(!(cin>>numOfNodesLvlOne))
	{
		cout<<"Tree cannot be built, please use a valid text file."<<endl; //error checking for valid input
		_exit(0);
	}
	
	//cout<<numOfNodesLvlOne<<endl;

	int childTrackerLvlOne[numOfNodesLvlOne]; //creating an array that is of size numOfNodesLvlOne
	int zeroChecker=0; //variable used for checking that each node in the 3rd level does not have any children
	
	for(int i=0; i<numOfNodesLvlOne; i++)
	{
		if(cin>>childTrackerLvlOne[i])
		{
			numOfNodesLvlTwo += childTrackerLvlOne[i]; //filling array of values for lvl1 & then adding them together to get num of nodes for lvl2
		}
		else
		{
			cout<<"Tree cannot be built, please use a valid text file."<<endl; //error checking for valid input
			_exit(0);
		}
		//cout<<childTrackerLvlOne[i]<<endl;			
	}

	//cout<<"Number of Nodes at Level 2: "<<numOfNodesLvlTwo<<endl;
		
	for(int j=0; j<numOfNodesLvlTwo; j++)
	{
		if(cin>>zeroChecker)
			zeroChecker +=zeroChecker; // adding the values for lvl 2 into zeroChecker		
		else
		{
			cout<<"Tree cannot be built, please use a valid text file."<<endl; //error checking for valid input
			_exit(0);
		}

		//cout<<zeroChecker<<endl;		

		if(zeroChecker !=0)
		{
			cout<<"Tree has more than 3 levels"<<endl;
			_exit(0);	//if zeroChecker does not equal zero break because tree is more than 3 levels
		}
	}

	int i;
	int pid;
	int ppid;
	int processID;
	int rootProcessID;
	vector <int> level1PID;
	vector <int> level2PID;

	rootProcessID = getpid();	
	for(i=0; i<numOfNodesLvlOne; i++)
	{
		pid=fork();
		if(pid!=0)
		{
			level1PID.push_back(pid);
			//cout<<"level 1 pids: "<<pid<<endl;
		}
			if(pid==0)
			{
				//cout<<"1st lvl node below: "<<endl;
				//processID = getpid();
				//cout<<"PID: "<<processID;
				//parentProcessID = getppid();
				//cout<<" PPID: "<<parentProcessID<<endl<<endl;
				break;
			}
	}

	/*
	if(pid!=0)
	{
		for(int k=0; k<level1PID.size(); k++)
			cout<<"level 1 pid: "<<level1PID[k]<< " " <<getpid()<<endl;
	}
	*/

	if (pid==0 && childTrackerLvlOne[i]!=0)
	{
		//cout<<childTrackerLvlOne[i]<<endl;
		for(int l=0; l<childTrackerLvlOne[i]; l++)
		{
			pid=fork();
			//cout<<"pid test: "<<pid<<endl;
			if(pid!=0) // && childTrackerLvlOne[i]!=0)
			{
				level2PID.push_back(pid);
			}

						
			if(pid==0)
			{
				//cout<<"2nd lvl node below: "<<endl;
				//processID = getpid();
				//cout<<"PID: "<<processID;
				//parentProcessID=getppid();
				//cout<<" PPID: "<<parentProcessID<<endl<<endl;
				cout<<"I'm a leaf of the tree"<<endl;
				sleep(2);
				_exit(0);
			}
		}
	}

	ifstream input;
	ofstream output;
	stringstream fileNameStream;
	string convertedString;

	if(pid!=0 && rootProcessID != getpid())
	{
		while(wait(0)!=-1);
		//for(int m=0; m<level1PID.size(); m++)
		//	processID =(int)getpid();
		//	cout<<"level 2 pid: "<<level2PID[m]<<" "<<getpid()<<endl;
		
		processID = (int)getpid();
		//cout<<processID<<endl;
				
		fileNameStream<<"File"<<processID<<".txt";
		convertedString = fileNameStream.str();
		output.open (convertedString.c_str());

		if(output.fail())
		{
			cerr<<"Text file could not be created."<<endl;
			_exit(0);
		}
		else
		{		
			for(int m=0; m<level2PID.size(); m++)
				output<<level2PID[m]<<endl;
		}
		
		output.close();
		_exit(0);	
	}
	
	string lvl2;
	
	if(rootProcessID==getpid())
	{
		while(wait(0)!=-1);
		
		for(int g=0; g<level1PID.size(); g++)
		{	
			if(childTrackerLvlOne[g]>0)
			{
				stringstream fileNameToOpen;
				fileNameToOpen<<"File"<<level1PID[g]<<".txt";
				string convertedFileNameString;
				convertedFileNameString = fileNameToOpen.str();	 
				input.open(convertedFileNameString.c_str());
				cout<<convertedFileNameString<<endl;
				if(input.fail())
				{
					cerr<<"Text file could not be opened."<<endl;
					_exit(0);
				}
	
				while(getline(input, lvl2))
				{
					cout<<lvl2<<endl;
					
				}
				input.close();
			}
		}
	}
	return 0;
}
