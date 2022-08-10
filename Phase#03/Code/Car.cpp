#include "Car.h"

Car::Car(int _id, string _name, int _weight, int _numSeats, int _numCylinders, int _engineCapacity, bool _parkingSensor)
: Product(_id, _name),
  weight(_weight),
  numSeats(_numSeats),
  numCylinders(_numCylinders),
  engineCapacity(_engineCapacity),
  parkingSensor(_parkingSensor)
{

}

map<string, string> Car::getProductDetail()
{
  map<string, string> informations;

  informations["name"] = name;
  informations[WEIGHT] = to_string(weight);
  informations[NUMSEATS] = to_string(numSeats);
  informations[NUMCYLINDER] = to_string(numCylinders);
  informations[ENGINEC] = to_string(engineCapacity);
  informations[PARKINGSENSOR] = to_string(parkingSensor);

  return informations;
	
	string space = "\n";

	string output = name + space + 
	                WEIGHT + to_string(weight) + space +
	                NUMSEATS + to_string(numSeats) + space +
	                NUMCYLINDER + to_string(numCylinders) + space +
	                ENGINEC + to_string(engineCapacity) + space +
	                PARKINGSENSOR + to_string(parkingSensor);

  cout << output << endl;

}

void Car::compare(Product* product)
{
	product->compareWith(this);
}


void Car::compareWith(Product* product)
{
	throw BadRequest();
}

void Car::compareWith(Car* car)
{

	cout << car->name << " | " << this->name << endl;

	cout << WEIGHT        << car->weight         << " | " << this->weight         << endl;
	cout << NUMSEATS      << car->numSeats       << " | " << this->numSeats       << endl;
	cout << NUMCYLINDER   << car->numCylinders 	 << " | " << this->numCylinders   << endl;
	cout << ENGINEC       << car->engineCapacity << " | " << this->engineCapacity << endl;
	cout << PARKINGSENSOR << car->parkingSensor  << " | " << this->parkingSensor  << endl;
}