#ifndef CAR_H
#define CAR_H

#include <iostream>

#include "Product.h"

#define WEIGHT "Weight: "
#define NUMSEATS  "Num.OfSeats: "
#define NUMCYLINDER "Num.OfCylinders: "
#define ENGINEC "EngineCapacity: "
#define PARKINGSENSOR "ReverseParkingSensors: "

using namespace std;

class Car : public Product
{
public:
	Car(int _id, string _name, int _weight, int _numSeats, int _numCylinders, int _engineCapacity, bool _parkingSensor);

	map<string, string> getProductDetail();
	void compare(Product* product);
  	void compareWith(Product* product);
  	void compareWith(Car* car);
  	int getType() {return 1;}

private:
	int weight;
	int numSeats;
	int numCylinders;
	int engineCapacity;
	
	bool parkingSensor;
};

#endif