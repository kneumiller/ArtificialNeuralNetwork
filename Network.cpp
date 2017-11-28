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
#include <cassert>

#include "Network.h"

Network::Network (vector<int> topology) {
	int numLayers = topology.size();
	cout << "topology size: " << topology.size() << endl;
	
	/*Create new layers and populate them with nodes*/
	for (int i = 0; i < numLayers; i++) {
		int numOutputs;
		layers.push_back(vector<Node>());
		
		//If this is the output layer (the last layer) then there will be no outputs given
		//Otherwise, the number of outputs is equal to the number of nodes in the next layer over
		if (i == numLayers - 1)
			numOutputs = 0;
		else
			numOutputs = topology[i + 1];
			
		for (int j = 0; j <= topology[i]; j++) {
			//Appends the Node onto the previous vector (i is used as the node index)
			layers.back().push_back(Node(numOutputs, i));
			cout << "New node - number of outputs: " << numOutputs << endl;
		}
	}
}

void Network::backPropogate(vector<double> targetVals) {
	//Determine if the neural network training is working
	vector<Node> outputLayer = layers.back();
	error = 0.0;
	double delta = 0;
	
	//Find the difference between teh expected value and the actual value
	cout << "output layer size: " << outputLayer.size() << endl;
	for (int i = 0; i <= outputLayer.size() - 1; i++) {
		cout << "loop" << endl;
		delta = targetVals[i] - outputLayer[i].getOutputVal();
		error += delta * delta;
		cout << "loop 2" << endl;
	}
		cout << "I finished" << endl;

	
	error /= outputLayer.size() - 1;	//Find the average of the error^2 
	error = sqrt(error);							//RMS (Root-Mean-Squared)
	
	//Calculate the average Error Rate for each run
	averageError = (averageError * averageSmoothingFactor + error
										/ (averageSmoothingFactor + 1));
	
	//Find the gradient for the output layers (don't include the bias node)
	for (int i = 0; i < outputLayer.size() - 1; i++) {
		outputLayer[i].outputGradient(targetVals[i]);
	}
	
	//Find the gradient for all of the hidden layers (starting w/ the right most hidden layer)
	for (int i = layers.size() - 2; i > 0; i--) {
		//Create vectors for display purposes
		vector<Node> hiddenLayer = layers[i]; //Current layer
		vector<Node> nextLayer = layers[i+1];
		
		for (int j = 0; j < hiddenLayer.size(); j++) {
			hiddenLayer[j].hiddenGradient(nextLayer);
		}
	}
	
	//Update the weights of each connection by looping through ALL the layers
	for (int i = layers.size() - 1; i > 0; i--) {
		vector <Node> currentLayer = layers[i];
		vector <Node> previousLayer = layers[i - 1];
		
		for (int j = 0; j < currentLayer.size(); j++) {
				currentLayer[j].updateInputWeights(previousLayer);
		}
	}
}

void Network::feedForward(const vector<double> inputVals) {
	//Make sure that the number of given neurons is the same as the number of neurons in the vector array
	cout << "Input Vals size: " << inputVals.size() << endl;
	cout << "Number of neurons: " << layers[0].size() << endl;
	assert(inputVals.size() == layers[0].size());
	
	//Give the input nodes the input values
	for (int i = 0; i < inputVals.size(); i++) {
		layers[0][i].setOutputVal(inputVals[i]);
	}
		
	//Forward propagate - move through each layer then through each node and feed forward
	for (int i = 1; i < layers.size(); i++) {
		vector<Node> previousLayer = layers[i-1];
		for (int j = 0; j < layers[i].size(); j++) {
			layers[i][j].nodeFeedForward(previousLayer);
		}
	}
}

void Network::getResults(vector <double> results) {
	results.clear();
	
	for (int i = 0; i < layers.back().size() - 1; i++) {
		results.push_back(layers.back()[i].getOutputVal());
	}
}

double Network::getAverageError() {
	return averageError;
}