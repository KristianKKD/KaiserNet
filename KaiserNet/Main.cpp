#include "Layer.hpp"
#include <random>

//void read_mnist(string path);
void ReadInput();
vector<NodeLayer> Learn(vector<NodeLayer> input);

extern bool pause, shuttingDown;
extern int stepCount;

int inputLayerSize = 2;
int outputLayerSize = 2;

int hiddenLayerCount = 2;
int hiddenLayerSize = 2;

vector<NodeLayer> layerList;

int main() {
	Log("KaiserNet version: 0.0.4a");
	//read_mnist("C:\\Users\\KrabGor\\Downloads\\labels\\t10k-images.idx3-ubyte");
	vector<double> target = { 0.2, 0.9 };

	NodeLayer inputLayer = NodeLayer(target); //input layer
	layerList.push_back(inputLayer);

	for (int i = 0; i < hiddenLayerCount; i++)
		layerList.push_back(NodeLayer(hiddenLayerSize)); //generate the hidden layers

	NodeLayer outputLayer = NodeLayer(outputLayerSize, true); //output layer
	layerList.push_back(outputLayer);

	thread inputThread = thread(ReadInput);

	for (; !shuttingDown;) {
		while (pause) {}
		layerList = Learn(layerList);
	}

	inputThread.join();
	inputThread.~thread();
}
