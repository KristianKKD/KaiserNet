#include "Shared.hpp"
#include <random>

class Node {
private:
	double lastWeight[2];
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

	void UpdateWeight(int weightIndex, double newWeight) {
		lastWeight[0] = weightIndex;
		lastWeight[1] = GetWeightTowards(weightIndex);
		
		if (newWeight > 1)
			newWeight = 1;
		else if (newWeight < -1)
			newWeight = -1;

		outgoingWeights[weightIndex] = newWeight;
	}

	void RevertWeight() {
		outgoingWeights[(int)lastWeight[0]] = lastWeight[1];
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
		else if (sum < -1)
			sum = -1;

		return sum;
	}
};

class NodeLayer {
public:
	vector<Node*> nodes;

	NodeLayer(vector<double> target) { //a node layer created with a target will always be an input layer
		nodes = vector<Node*>();
		for (int i = 0; i < target.size(); i++)
			nodes.push_back(new Node(target[i]));
	}

	NodeLayer(int layerSize, bool isOutput = false) {
		nodes = vector<Node*>();
		for (int i = 0; i < layerSize; i++)
			nodes.push_back((isOutput) ? new Node(0) : new Node());
	}

	~NodeLayer() {
		while (nodes.size() > 0) {
			nodes.back()->~Node();
			nodes.pop_back();
		}
	}

};