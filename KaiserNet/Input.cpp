#include "Layer.hpp"

void Print(vector<NodeLayer> input);

bool pause = true;
string command;
int stepCount = 0;
extern vector<NodeLayer> layerList;

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
			Print(layerList);
		} if (command == "print") {
			pause = true;
			Print(layerList);
		}
	}
	Error("Exited input thread!", 0, true);
}

void Print(vector<NodeLayer> input) {
	string outputString = "Targets: ";
	for (int i = 0; i < input[0].nodes.size(); i++)
		outputString += to_string(input[0].nodes[i]->heldValue) + " ";
	Log(outputString);

	for (int layerIndex = 0; layerIndex < input.size(); layerIndex++) { //layers
		NodeLayer l = input[layerIndex];
		Log("LAYER[" + to_string(layerIndex) + "]");

		for (int nodeIndex = 0; nodeIndex < l.nodes.size(); nodeIndex++) { //nodes
			Node* n = l.nodes[nodeIndex];
			Log("	NODE[" + to_string(nodeIndex) + "] VALUE: " +
				to_string(n->heldValue) + "	BIAS: " + to_string(n->bias));

			if (layerIndex != input.size() - 1)
				for (int nodeWeights = 0; nodeWeights < input[layerIndex + 1].nodes.size(); nodeWeights++) { //weighted edges
					double edge = n->outgoingWeights[nodeWeights];
					Log("		EDGE[" + to_string(nodeWeights) + "]: " + to_string(edge));
				}
		}
	}
}
