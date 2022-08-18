#include "Shared.hpp"

#define MAXSIZE 1024

enum LayerType {
	Input,
	Hidden,
	Output,
};

class Node {
public:
	double bias;
	double heldValue;
	double incomingWeights[MAXSIZE];

	Node(LayerType myType) {
		bias = InitializeBias(myType);
		heldValue = bias;
	}

	double InitializeBias(LayerType myType) { //can't be zero
		return 0.5 * (!(myType == Input || myType == Output));
	}

	double ActivationFunction(double sum) {
		if (sum > 1)
			sum = 1;
		else if (sum < 0)
			sum = 0;
		return sum;
	}
};

class NodeLayer {
public:
	LayerType myType;
	Node internalNodes[];

	NodeLayer(int layerSize, LayerType lType) {
		myType = lType;
		for (int i = 0; i < layerSize; i++)
			internalNodes[i] = Node(myType);
	}
};