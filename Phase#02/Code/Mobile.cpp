#include "Mobile.h"



Mobile::Mobile(int _id, string _name, int _weight, double _CPUFrequency, int _inMemory, int _RAM, double _displaySize, int _cameraRes, string _OS)
: Product(_id, _name),
  weight(_weight),
  CPUFrequency(_CPUFrequency),
  inMemory(_inMemory),
  RaM(_RAM),
  displaySize(_displaySize),
  cameraRes(_cameraRes),
  Os(_OS)
{

}


void Mobile::getProductDetail()
{
  string space = "\n";
  string cpu = convertingToString(to_string(CPUFrequency));
  string disp = convertingToString(to_string(displaySize));

  string output = name + space + 
                  WEIGHT + to_string(weight) + space +
                  CPUF + cpu + space +
                  BUILTMEM + to_string(inMemory) + space +
                  RAM + to_string(RaM) + space +
                  DISPLAYSIZE + disp + space +
                  CAMERARES + to_string(cameraRes) + space +
                  OS + Os;

  cout << output << endl;
}

void Mobile::compare(Product* product)
{
  product->compareWith(this);
}


void Mobile::compareWith(Product* product)
{
  throw BadRequest();
}

void Mobile::compareWith(Mobile* mobile)
{

  cout << mobile->name << " | " << this->name   << endl;

  cout << WEIGHT      << mobile->weight       << " | " << this->weight       << endl;
  cout << CPUF        << mobile->CPUFrequency << " | " << this->CPUFrequency << endl;
  cout << BUILTMEM    << mobile->inMemory     << " | " << this->inMemory     << endl;
  cout << RAM         << mobile->RaM          << " | " << this->RaM          << endl;
  cout << DISPLAYSIZE << mobile->displaySize  << " | " << this->displaySize  << endl;
  cout << CAMERARES   << mobile->cameraRes    << " | " << this->cameraRes    << endl;
  cout << OS          << mobile->Os           << " | " << this->Os           << endl;
}