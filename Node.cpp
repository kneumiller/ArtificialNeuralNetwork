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


#include <cstdlib>
#include <cmath>

#include "Node.h"

//Want to have a higher learning rate because there is less data available to train on
// The higher the rate, the faster (sometimes more reckless) it learns
double Node::learningRate = 0.5; 	//Learning rate between [0.0 - 1.0]
double Node::alpha = 0.5;					//Momentum between [0.0 - n]


Node::Node(int numOutputs, int myIndex) {
	for (int i = 0; i < numOutputs; i++) {
		outputWeight.push_back(randomWeight());
	}
	
	nodeIndex = myIndex;
}

double Node::randomWeight() {
	//Returns a value between 0 and 1
	return rand() / double(RAND_MAX);
}

void Node::nodeFeedForward(vector<Node> previousLayer) {
	double sum = 0;
	for (int i = 0; i < previousLayer.size(); i++) {
		sum += previousLayer[i].getOutputVal() * 
						previousLayer[i].outputWeight[nodeIndex];
	}
	
	outputVal = transferFunction(sum);
}

double Node::transferFunction(double x) {
	//Use the tangeant function: range [-1.0 - 1.0]
	return tanh(x);
}

double Node::transferFunctionDerivative(double x) {
	//Tangeant function derivative (1 - tan^2(x))
	return 1.0 - x * x;
}

void Node::setOutputVal(double value) {
	outputVal = value;
}

double Node::getOutputVal() {
	return outputVal;
}

void Node::outputGradient(double value) {
	//Find the difference between the target val and the actual val it has
	double difference = value - outputVal;
	gradient = difference * transferFunctionDerivative(outputVal);
}

void Node::hiddenGradient(vector <Node> nextLayer) {
	//Derivative of weights
	double derivative = 0;
	
	//Sum the contributions of the errors that we make to the 
	// nodes that we feed in the next layer
	for (int i = 0; i < nextLayer.size() - 1; i++) {
		derivative += outputWeight[i] * nextLayer[i].gradient;
	}
	
	gradient = derivative * transferFunctionDerivative(outputVal);
}

void Node::updateInputWeights(vector<Node> previousLayer) {
	for (int i = 0; i < previousLayer.size(); i++) {
		//The other node in the previous layer being updated
		Node otherNode = previousLayer[i];
		
		//The other node's connection weight between itself and the current node
		double oldWeightDifference = otherNode.changeInWeight[nodeIndex];
		
		//To find the new delta weight: 
		//	take the individual input, magnify it by the gradient and training weight,
		//	and add momentum (a fraction of the previous delta weight)
		double newWeightDifference = 
					(learningRate * otherNode.getOutputVal() * gradient) + (alpha * oldWeightDifference); 
		otherNode.changeInWeight[nodeIndex] = newWeightDifference;
		otherNode.outputWeight[nodeIndex] += newWeightDifference;
	}
}