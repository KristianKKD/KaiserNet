#include "Layer.hpp"

//HYPER PARAMETERS
#define LEARNINGRATE = 0.1;

void InitNetwork() { //create the neural network in here
	int inputLayersCount = 2;
	int hiddenLayerCount = 1;
	int outputLayersCount = 2;
	

	NodeLayer inputLayer = NodeLayer(inputLayersCount, Input);
	NodeLayer hiddenLayer = NodeLayer(hiddenLayerCount, Hidden);
	NodeLayer outputLayer = NodeLayer(outputLayersCount, Output);

}