#include "Layer.hpp"

//HYPER PARAMETERS
#define LEARNINGRATE = 0.1;

//void read_mnist(string path);
void GenerateOutput(int stepCount);
void ReadInput();
void Learn();

vector<NodeLayer> layerList;
string input;

bool pause;
vector<double> target;

int main() {
	Log("KaiserNet version: 0.0.2");
	//read_mnist("C:\\Users\\KrabGor\\Downloads\\labels\\t10k-images.idx3-ubyte");

	int inputLayerSize = 2;
	int outputLayerSize = 2;

	int hiddenLayerCount = 1;

	target = { 0.2, 0.9 };
	NodeLayer inputLayer = NodeLayer(target); //input layer
	layerList.push_back(inputLayer);

	for (int i = 0; i < hiddenLayerCount; i++)
		layerList.push_back(NodeLayer(hiddenLayerCount, Hidden)); //generate the hidden layers

	NodeLayer outputLayer = NodeLayer(outputLayerSize, Output); //output layer
	layerList.push_back(outputLayer);

	thread inputThread = thread(ReadInput);

	for (int i = 0; input != "stop"; i++) {
		while (pause) {}
		GenerateOutput(i);
		Learn();
	}

	inputThread.join();
	inputThread.~thread();
}

void ReadInput() {
	while (input != "stop") {
		input = "";
		std::cin >> input;
		if (input == "pause")
			pause = !pause;
	}
}

void GenerateOutput(int stepCount) {
	for (int layerIndex = 1; layerIndex < layerList.size(); layerIndex++) { //go through all the layers, skipping input layer (as that will be accounted for)
		NodeLayer currentLayer = layerList[layerIndex];
		NodeLayer prevLayer = layerList[layerIndex - 1];

		for (int nodeIndex = 0; nodeIndex < currentLayer.nodes.size(); nodeIndex++) { //for each node in the current layer
			//for each node, sum up the previous layer's nodes' values
			double sum = 0;

			for (int prevNodeIndex = 0; prevNodeIndex < prevLayer.nodes.size(); prevNodeIndex++)
				sum += prevLayer.nodes[prevNodeIndex].heldValue +
				prevLayer.nodes[prevNodeIndex].GetWeightTowards(nodeIndex);

			currentLayer.nodes[nodeIndex].Activate(sum); //make the node's value non-linear + bias
		}

		if (layerIndex == layerList.size() - 1 && stepCount % 10000 == 0) {
			string outputString;
			for (int nodeIndex = 0; nodeIndex < currentLayer.nodes.size(); nodeIndex++) { //for each node in the output layer
				outputString += ((nodeIndex != 0) ? " ": "") + to_string(nodeIndex) + ": " + to_string(currentLayer.nodes[nodeIndex].heldValue);
			}

			Log(outputString);
		}
	}
}

void Learn() {
	for (int layerIndex = 1; layerIndex < layerList.size(); layerIndex++) { //go through all the layers, skipping input layer (as that will be accounted for)
		for (int nodeIndex = 0; nodeIndex < layerList[layerIndex].nodes.size(); nodeIndex++) { //for each node in the current layer
			//RandomLearn();
		}
	}
}
