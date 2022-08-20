#include "Shared.hpp"
#include <random>

class Node {
public:
	double bias;
	double heldValue;
	double outgoingWeights[MAXSIZE];

	Node() {
		bias = GetRandomValue();
		heldValue = GetRandomValue();
		for (int i = 0; i < MAXSIZE; i++)
			outgoingWeights[i] = GetRandomValue();
	}

	Node(double target) {
		heldValue = target;
		bias = 0;
		for (int i = 0; i < MAXSIZE; i++)
			outgoingWeights[i] = GetRandomValue();
	}


	~Node() {}

	static double GetRandomValue() { //can't be zero
		return double(std::rand() % 10) / 1000.0;
	}

	double GetWeightTowards(int nodeIndex) {
		return outgoingWeights[nodeIndex];
	}

	void Activate(double sum) {
		heldValue = ActivationFunction(sum + bias);
	}

	static double ActivationFunction(double sum) {
		if (sum > 1)
			sum = 1;
		else if (sum < 0)
			sum *= LEARNINGRATE;
		
		return sum;
	}
};

class NodeLayer {
public:
	vector<Node> nodes;

	NodeLayer(vector<double> target) { //a node layer created with a target will always be an input layer
		vector<Node> newNodes;
		for (int i = 0; i < target.size(); i++)
			newNodes.push_back(Node(target[i]));

		nodes = newNodes;
	}

	NodeLayer(int layerSize, bool isOutput = false) {
		vector<Node> newNodes;
		for (int i = 0; i < layerSize; i++)
			newNodes.push_back((isOutput) ? Node(0) : Node());

		nodes = newNodes;
	}


	~NodeLayer() {}
};