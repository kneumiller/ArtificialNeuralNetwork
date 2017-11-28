/********************************************************************
* Kodi Neumiller																										*
* kneumiller																												*
* CSCI 446																													*
* Assignment 5: Machine Learning																		*
*																																		*
* An A.I. based off of a neural network pattern. 										*
*		The program will take in a file of with each row having some		*
*		amount of input and one output.																	*
*																																		*	
*	To compile: g++ -o MachineLearning MachineLearning.cpp						*
*	To run:	./MachineLearning																					*
********************************************************************/


#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Network.cpp"
#include "WeatherInput.cpp"
#include "ClassInput.cpp"

using namespace std;

int main () {
	vector <string> fileData; 

	string inputFile;
	cout << "Please enter file name" << endl;
	cin >> inputFile;
	
	double normalizedData [20][5];
	double normalizedDeerData [6000][21];
	if (inputFile == "weather.csv") {
		readWeatherData(normalizedData);
		cout << "\n\n----Using weather.csv-----\n\n";
	}
	else if (inputFile == "class.csv") {
		readClassData(normalizedData);
		cout << "\n\n----Using class.csv-----\n\n";
	}
	else if (inputFile == "DeerHunter.csv") {
		//readDeerData(normalizedData);
		cout << "\n\n----Using DeerHunter.csv-----\n\n";
	}
	else
		cout << "\nFilename not valid" << endl;

	vector <int> topology;
	//Create a topology that has number of inputs, 3 hidden layers, and 1 output layer
	topology.push_back(4);
	topology.push_back(5);
	topology.push_back(4);
	topology.push_back(3);
	topology.push_back(1);
	
	Network myNet (topology);
	
	vector<double> inputVals, targetVals, outputVals;
	int currentRow = 0;
	double errorRate;
	
	
	for (int i = 0; i < 18; i++) {
		inputVals.clear();
		targetVals.clear();
		
		//Loop that adds the input values row by row starting at the third row (to ignore the column headers and the 0s)
		// If the current i position modulus number of inputs equals 0 then that means it is at the end of the row and
		// the final value will be the expected output
		for (int j = 0; j < 5; j++) {
			if (j % 5 == 0 && j != 0)
				targetVals.push_back(normalizedData[i][j]);
			else
				inputVals.push_back(normalizedData[i][j]);
		}
		myNet.feedForward(inputVals);
		
		myNet.getResults(outputVals);
		
		myNet.backPropogate(targetVals);
		
		errorRate = myNet.getAverageError();
		cout << "Error rate: " << errorRate << endl;
		currentRow++;
	}
	
}