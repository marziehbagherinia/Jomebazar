#ifndef _HANDLERS_H_
#define _HANDLERS_H_


#include <iostream>
#include <fstream>  
#include <map>
#include <string>
#include <vector>
#include <cstdlib> 
#include <bits/stdc++.h>

#include "./server/server.hpp"
#include "UserRepository.h"
#include "ProductRepository.h"

using namespace std; 


#define WEIGHT "Weight: "
#define NUMSEATS  "Num.OfSeats: "
#define NUMCYLINDER "Num.OfCylinders: "
#define ENGINEC "EngineCapacity: "
#define PARKINGSENSOR "ReverseParkingSensors: "

#define CPUF  "CPUFrequency: "
#define BUILTMEM "Built-inMemory: "
#define RAM "RAM: "
#define DISPLAYSIZE "DisplaySize: "
#define CAMERARES "CameraResolution: "
#define OS "OperatingSystem: "

#define SCREENSIZE "ScreenSize: "
#define SCREENTYPE  "ScreenType: "
#define RESOLUTION "Resolution: "
#define THREED "3D: "
#define HDR "HDR: "


class ShowLogin : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowSignup : public RequestHandler {
public:
  Response *callback(Request *);
};

class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class LogoutHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowManagerHome : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowSellerHome : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowBuyerHome : public RequestHandler {
public:
  Response *callback(Request *);
};

class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class showProducts : public RequestHandler {
public:
  Response *callback(Request *);
};

class showPostOffer : public RequestHandler {
public:
  Response *callback(Request *);
};

class postOfferHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowBuyerBank : public RequestHandler {
public:
  Response *callback(Request *);
};

class chargeWalletHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class productDetailHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class addToCartlHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class showShopPage : public RequestHandler {
public:
  Response *callback(Request *);
};

class submitCartlHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

#endif