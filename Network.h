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


#ifndef NETWORK_H
#define NETWORK_H
#include <vector>

#include "Node.cpp"

using namespace std;

class Network {
	public:
		Network(vector <int> topology);
		void feedForward(const vector <double> inputVals);
		void backPropogate(vector<double> targetVals);
		void getResults(vector <double> resultVals);
		double getAverageError();
		
	private:
		vector< vector<Node> > layers;	//2-D array of [layer][node]
		double error;
		double averageError;
		double averageSmoothingFactor;
};

#endif