#include "Shared.hpp"

#define MAXSIZE 128

enum LayerType {
	Input,
	Output,
	Hidden,
};

class Node {
public:
	double bias;
	double heldValue;
	double outgoingWeights[MAXSIZE];

	Node(LayerType myType) {
		bias = InitializeBias(myType);
		heldValue = bias;
		for (int i = 0; i < MAXSIZE; i++)
			outgoingWeights[i] = bias;
	}

	~Node() {}

	double InitializeBias(LayerType myType) { //can't be zero
		return 0.01;
	}

	void Pulse(double incomingValue) {

	}

	double GetWeightTowards(int nodeIndex) {
		return outgoingWeights[nodeIndex];
	}

	void Activate(double sum) {
		sum += bias;
		if (sum > 1)
			sum = 1;
		else if (sum < 0)
			sum = 0;
		
		heldValue = sum;
	}
};

class NodeLayer {
public:
	LayerType myType;
	vector<Node> nodes;

	NodeLayer(vector<double> target) { //a node layer created with a target will always be an input layer
		vector<Node> newNodes;
		for (int i = 0; i < target.size(); i++)
			newNodes.push_back(Node(Input));

		nodes = newNodes;
		myType = Input;
	}

	NodeLayer(int layerSize, LayerType lType) {
		vector<Node> newNodes;
		for (int i = 0; i < layerSize; i++)
			newNodes.push_back(Node(lType));

		nodes = newNodes;
		myType = lType;
	}

	~NodeLayer() {}
};