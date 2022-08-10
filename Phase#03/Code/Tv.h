#ifndef TV_H
#define TV_H

#include <iostream>

#include "Product.h"

#define SCREENSIZE "ScreenSize: "
#define SCREENTYPE  "ScreenType: "
#define RESOLUTION "Resolution: "
#define THREED "3D: "
#define HDR "HDR: "

using namespace std;

class Tv : public Product
{
public:
	Tv(int _id, string _name, int _screenSize, string _screenType, string _resolution, bool _3D, bool _HDR);
	
	map<string, string> getProductDetail();
	void compare(Product* product);
  	void compareWith(Product* product);
  	void compareWith(Tv* tv);
  	int getType() {return 3;}

private:
	int screenSize;

	bool threeD;
	bool HDr;
	
	string screenType;
	string resolution;
	
};

#endif
