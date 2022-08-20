#include "Layer.hpp"
#include <random>

//void read_mnist(string path);
vector<NodeLayer> GenerateOutput(vector<NodeLayer> input);
void ReadInput();
void Learn(vector<NodeLayer> input);
void Print(vector<NodeLayer> input);
double CalculateError(vector<NodeLayer> input);
vector<NodeLayer> UpdateEdges(vector<NodeLayer> input);

string command;

bool pause = true;

int inputLayerSize = 2;
int outputLayerSize = 2;

int hiddenLayerCount = 2;
int hiddenLayerSize = 2;

int stepCount = 0;

vector<NodeLayer> currentLayers;

int main() {
	Log("KaiserNet version: 0.0.3");
	//read_mnist("C:\\Users\\KrabGor\\Downloads\\labels\\t10k-images.idx3-ubyte");
	vector<double> target = { 0.2, 0.9 };

	vector<NodeLayer> layerList;

	NodeLayer inputLayer = NodeLayer(target); //input layer
	layerList.push_back(inputLayer);

	for (int i = 0; i < hiddenLayerCount; i++)
		layerList.push_back(NodeLayer(hiddenLayerSize)); //generate the hidden layers

	NodeLayer outputLayer = NodeLayer(outputLayerSize, true); //output layer
	layerList.push_back(outputLayer);

	currentLayers = layerList;

	thread inputThread = thread(ReadInput);

	for (; command != "stop";) {
		while (pause) {}
		Learn(layerList);
	}

	inputThread.join();
	inputThread.~thread();
}

void ReadInput() {
	while (command != "stop") {
		command = "";
		std::cin >> command;
		if (command == "pause")
			pause = true;
		if (command == "unpause")
			pause = false;
		if (command == "step") {
			int lastStepCount = stepCount;
			pause = false;
			while (lastStepCount == stepCount) {}
			pause = true;
			Print(currentLayers);
		} if (command == "print") {
			pause = true;
			Print(currentLayers);
		}
	}
}

void Print(vector<NodeLayer> input) {
	string outputString = "Targets: ";
	for (int i = 0; i < input[0].nodes.size(); i++)
		outputString += to_string(input[0].nodes[i].heldValue) + " ";
	Log(outputString);

	for (int layerIndex = 0; layerIndex < input.size(); layerIndex++) { //layers
		NodeLayer l = input[layerIndex];
		Log("LAYER[" + to_string(layerIndex) + "]");

		for (int nodeIndex = 0; nodeIndex < l.nodes.size(); nodeIndex++) { //nodes
			Node n = l.nodes[nodeIndex];
			Log("	NODE[" + to_string(nodeIndex) + "] VALUE: " +
				to_string(n.heldValue) + "	BIAS: " + to_string(n.bias));

			if (layerIndex != input.size() - 1)
				for (int nodeWeights = 0; nodeWeights < input[layerIndex + 1].nodes.size(); nodeWeights++) { //weighted edges
					double edge = n.outgoingWeights[nodeWeights];
					Log("		EDGE[" + to_string(nodeWeights) + "]: " + to_string(edge));
				}
		}
	}
}

vector<NodeLayer> GenerateOutput(vector<NodeLayer> input) {
	for (int layerIndex = 1; layerIndex < input.size(); layerIndex++) { //go through all the layers, skipping input layer (as that will be accounted for)
		NodeLayer currentLayer = input[layerIndex];
		NodeLayer prevLayer = input[layerIndex - 1];

		for (int nodeIndex = 0; nodeIndex < currentLayer.nodes.size(); nodeIndex++) { //for each node in the current layer
			//for each node, sum up the previous layer's nodes' values + weighted edges
			double sum = 0;

			for (int prevNodeIndex = 0; prevNodeIndex < prevLayer.nodes.size(); prevNodeIndex++)
				sum += prevLayer.nodes[prevNodeIndex].heldValue +
					prevLayer.nodes[prevNodeIndex].GetWeightTowards(nodeIndex); //add all the weights from the previous nodes into a sum

			currentLayer.nodes[nodeIndex].Activate(sum); //make the node's value non-linear + bias
			Log(currentLayer.nodes[nodeIndex].heldValue);
		}
	}

	return input;
}

void Learn(vector<NodeLayer> input) {
	//vector<NodeLayer> oldLayers = input;

	//double oldDifference = CalculateError(input);
	//
	input = UpdateEdges(input);
	CalculateError(input);

	//input = GenerateOutput(input);
	//double newDifference = CalculateError(input);

	//if (newDifference < 0.0001) {
	//	command = "stop";
	//	Log("Got the result we were looking for!");
	//} else if (newDifference > oldDifference) {
	//	//input = oldLayers;
	//}
	
	currentLayers = input;
}

vector<NodeLayer> UpdateEdges(vector<NodeLayer> input) {
	for (int layerIndex = 1; layerIndex < input.size() - 1; layerIndex++) { //layers
		for (int nodeIndex = 0; nodeIndex < input[layerIndex].nodes.size(); nodeIndex++) { //nodes
			Node current = input[layerIndex].nodes[nodeIndex];

			for (int edge = 0; edge < input[layerIndex + 1].nodes.size(); edge++) { //weighted edges

				double randomChange = (double(std::rand() % 9999) + 1) / 10000.0 * //random value between 0.1-1
					1 - (2 * (std::rand() % 1)) * //negative or positive
					LEARNINGRATE; //learning rate multiplier to make the random change smaller/bigger

				current.outgoingWeights[edge] += randomChange;
			}
		}
	}

	stepCount++;
	return input;
}

double CalculateError(vector<NodeLayer> input) {
	string outputString = "";
	double errorMargin = 0;
	for (int lastNodes = 0; lastNodes < input[input.size() - 1].nodes.size(); lastNodes++) { //for each node in the output layer
		double nodeValue = input[input.size() - 1].nodes[lastNodes].heldValue;
		outputString += ((lastNodes != 0) ? " " : "") +
			to_string(lastNodes) + ": " + to_string(nodeValue);

		double difference = input[0].nodes[lastNodes].heldValue - nodeValue;
		if (difference < 0)
			difference *= -1;
		errorMargin += difference; //return the difference in values
	}

	if (stepCount % 10000 == 0 || errorMargin < LEARNINGRATE) //every few steps print the current position
		Log(outputString + "     ERRORMARGIN IS:" + to_string(errorMargin));

	return errorMargin;
}
