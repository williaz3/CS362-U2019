/*Zack Williams
 * CS325 HW4 Last to start implementation
 * */

//Include necessary libraries for file access, cin/cout, vector functionality, and sort
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
//open our text file
freopen("act.txt", "r", stdin);

//initali function declaration
int readData =1;//used to read all our data into the vector
int act, start, end;// variables that will have data read in to them for the activity #, start time, and end time values
int setNum =1;// displays the set of activities associated with the test results

//read data from text file and increment readData so how much data is read in is known for later looping
while (cin >> readData){

//declare our vector that is structured like so < activity < startTime, endTime> > to better organize the data
vector< pair<int, pair<int, int> > > list; 

	//while the total data read in has not been reached
	for (int i = 0; i < readData; ++i){
	//write input in a known pattern of end time paired with the pair of start time and activity # and use make_pair to create pair objects whitin our vector
	cin >> act >> start >> end; 
	list.push_back(make_pair(end, make_pair(start, act)));
	}//end for

//use the sort command to sort from low to high values in our vector named list
sort(list.begin(), list.end());
int last = 0; 

vector <int> chosen;//stores the list of activities that will be used by the greedy algorithm

//store the first element from our list vectot ,which will have the lowest finish time and store in the chosen data vector for comparison
chosen.push_back(list[0].second.second);

	for(int j = 1; j < readData; ++j){
	//if our lists start time (second pair, first item) is greater than or equal to our previous vector's elements end time then add the current list item to the list of the chosen activities
		if (list[j].second.first >= list[last].first){
			chosen.push_back(list[j].second.second);
			last = j;
			}//end if
	}//end for

//print results
cout << "Set " << setNum << " Number of activities selected = " << chosen.size() << "\n";
cout << "Activities: ";
int k = 0;
	while ( k < chosen.size() ){
		cout << chosen.at(k) << " ";
		k++;
		}//end printing for 
	cout << "\n";
	setNum++;
	}//end while
}//end main


// make_pair refernece http://www.cplusplus.com/reference/utility/make_pair/
