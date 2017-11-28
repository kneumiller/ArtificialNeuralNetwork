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


#ifndef NODE_H
#define NODE_H
#include <vector>

using namespace std;

class Node {
	public:
		Node(int numOutputs, int myIndex);
		double randomWeight();
		void updateInputWeights(vector<Node> previousLayer);
		void setOutputVal(double value);
		double getOutputVal();
		void outputGradient(double value);
		void hiddenGradient(vector <Node> nextLayer);
		void nodeFeedForward(vector<Node> previousLayer);
		
	private:
		double transferFunction(double x);
		double transferFunctionDerivative(double x);
		double outputVal;
		double gradient;
		static double learningRate;
		static double alpha;
		int nodeIndex;
		vector<double> outputWeight;
		vector<double> changeInWeight;
};

#endif