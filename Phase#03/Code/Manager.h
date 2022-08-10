#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>

#include "User.h"

#define ASCEND "ASCEND"
#define DESCEND "DESCEND"
#define OFFERPRICE "offerPrice"
#define FIELD "field"
#define OFFERID "offerId"

using namespace std;

class Manager : public User
{
public:
	Manager(int _id, string _email, string _username, string _password);
	void ableToSeller();
	void ableToManager();
	void ableToBuyer();
	void chargeWallet(double amount);
	void getWallet(int count);
	double getCash();
	int whatIsMyType();
	
};

#endif