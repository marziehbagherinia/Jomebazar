#include "Tv.h"

Tv::Tv(int _id, string _name, int _screenSize, string _screenType, string _resolution, bool _3D, bool _HDR)
: Product(_id, _name),
  screenSize(_screenSize),
  screenType(_screenType),
  resolution(_resolution),
  threeD(_3D),
  HDr(_HDR)
{
  
}

map<string, string> Tv::getProductDetail()
{
	map<string, string> informations;

	informations["name"] = name;
  informations[SCREENSIZE] = to_string(screenSize);
  informations[SCREENTYPE] = screenType;
  informations[RESOLUTION] = resolution;
  informations[THREED] = to_string(threeD);
  informations[HDR] = to_string(HDr);

  return informations;

  string space = "\n";
	
	string output = name + space + 
	                SCREENSIZE + to_string(screenSize) + space +
	                SCREENTYPE + screenType + space +
	                RESOLUTION + resolution + space +
	                THREED + to_string(threeD) + space +
	                HDR + to_string(HDr);

  	cout << output << endl;

}

void Tv::compare(Product* product)
{
  product->compareWith(this);
}


void Tv::compareWith(Product* product)
{
  throw BadRequest();
}

void Tv::compareWith(Tv* tv)
{

  cout << tv->name << " | " << this->name   << endl;

  cout << SCREENSIZE << tv->screenSize << " | " << this->screenSize << endl;
  cout << SCREENTYPE << tv->screenType << " | " << this->screenType << endl;
  cout << RESOLUTION << tv->resolution << " | " << this->resolution << endl;
  cout << THREED     << tv->threeD     << " | " << this->threeD     << endl;
  cout << HDR 		 << tv->HDr        << " | " << this->HDr        << endl;
}