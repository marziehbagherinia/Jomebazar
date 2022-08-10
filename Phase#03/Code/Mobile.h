#ifndef MOBILE_H
#define MOBILE_H

#include <iostream>

#include "Product.h"

#define WEIGHT "Weight: "
#define CPUF  "CPUFrequency: "
#define BUILTMEM "Built-inMemory: "
#define RAM "RAM: "
#define DISPLAYSIZE "DisplaySize: "
#define CAMERARES "CameraResolution: "
#define OS "OperatingSystem: "
using namespace std;

class Mobile : public Product
{
public:
	Mobile(int _id, string _name, int _weight, double _CPUFrequency, 
		   int _inMemory, int _RAM, double _displaySize, int _cameraRes, string _OS);
	
	map<string, string> getProductDetail();
	void compare(Product* product);
  	void compareWith(Product* product);
  	void compareWith(Mobile* mobile);
  	int getType() {return 2;}
	
private:
	int weight;
	double CPUFrequency;
	int inMemory;
	int RaM;
	double displaySize;
	int cameraRes;
	string Os;
};

#endif