#include "Layer.hpp"
#include <tuple>

double CalculateError(vector<NodeLayer> input);
vector<NodeLayer> UpdateEdges(vector<NodeLayer> input);
void Print(vector<NodeLayer> input);

extern int stepCount;

vector<NodeLayer> Learn(vector<NodeLayer> input) {
	/*vector<NodeLayer> oldLayers = input;

	double oldDifference = CalculateError(oldLayers);*/

	UpdateEdges(input);
	double newDifference = CalculateError(input);

	/*if (newDifference < 0.0001) {
		Error("Got the result we were looking for!", 0, true);
	} else if (newDifference > oldDifference) {
		input = oldLayers;
	}*/

	stepCount++;
	return input;
}

vector<NodeLayer> UpdateEdges(vector<NodeLayer> input) {
	int randomChanges = std::rand() % 10;
	//save which edges got changed

	for (int layerIndex = 1; layerIndex < input.size() - 1; layerIndex++) { //layers
		for (int nodeIndex = 0; nodeIndex < input[layerIndex].nodes.size(); nodeIndex++) { //nodes
			Node* current = input[layerIndex].nodes[nodeIndex];

			for (int edge = 0; edge < input[layerIndex + 1].nodes.size() && randomChanges < 10; edge++) { //weighted edges

				double randomChange = (double(std::rand() % 10) + 1) * //random value between 0.1-1
					(1 - (2 * (std::rand() % 2 == 1))) * //negative or positive
					LEARNINGRATE; //learning rate multiplier to make the random change smaller/bigger

				current->UpdateWeight(edge, randomChange);
				//save which edges got changed
				randomChanges--;
			}
		}
	}

	//compare the changes
	//if it the error is worse, revert it

	return input;
}

void UpdateHeldValues(vector<NodeLayer> input) {
	for (int layerIndex = 1; layerIndex < input.size(); layerIndex++) { //go through all the layers, skipping input layer (as that will be accounted for)
		NodeLayer currentLayer = input[layerIndex];
		NodeLayer prevLayer = input[layerIndex - 1];

		for (int nodeIndex = 0; nodeIndex < currentLayer.nodes.size(); nodeIndex++) { //for each node in the current layer
			//for each node, sum up the previous layer's nodes' values + weighted edges
			double sum = 0;

			for (int prevNodeIndex = 0; prevNodeIndex < prevLayer.nodes.size(); prevNodeIndex++)
				sum += prevLayer.nodes[prevNodeIndex]->heldValue *
				prevLayer.nodes[prevNodeIndex]->GetWeightTowards(nodeIndex); //add all the weights from the previous nodes into a sum

			currentLayer.nodes[nodeIndex]->Activate(sum); //make the node's value non-linear + bias
		}
	}
}

double CalculateError(vector<NodeLayer> input) {
	string outputString = "";
	double errorMargin = 0;
	for (int lastNodes = 0; lastNodes < input[input.size() - 1].nodes.size(); lastNodes++) { //for each node in the output layer
		double nodeValue = input[input.size() - 1].nodes[lastNodes]->heldValue;
		outputString += ((lastNodes != 0) ? " " : "") +
			to_string(lastNodes) + ": " + to_string(nodeValue);

		double difference = input[0].nodes[lastNodes]->heldValue - nodeValue;
		if (difference < 0)
			difference *= -1;
		errorMargin += difference; //return the difference in values
	}

	if (stepCount % 10000 == 0 || errorMargin < LEARNINGRATE) //every few steps print the current position
		Log(outputString + "     ERRORMARGIN IS:" + to_string(errorMargin));

	return errorMargin;
}
