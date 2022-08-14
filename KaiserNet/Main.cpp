#include "Shared.hpp"

void read_mnist(string path);

int main() {
	Log("KaiserNet version: 0.0.0");
	read_mnist("C:\\Users\\KrabGor\\Downloads\\labels\\t10k-images.idx3-ubyte");
}