#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map> 
#include <bits/stdc++.h> 

#include "Exceptions.h"
#include "Offer.h"

#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define PRODUCTID "productId"
#define UNITPRICE "offerUnitPrice"
#define AMOUNT "offerAmount"
#define OFFERID "offerId"
#define DISCOUNTPERCENT "discountPercent"
#define DISCOUNTNUMBER "discountNumber"

using namespace std;

class User
{
public:
	User(int _id, string _email, string _username, string _password);

	string getUsername();

	bool findUser(map <string, string> informations);

	int getID();

	virtual void ableToSeller() = 0;
	virtual void ableToBuyer() = 0;
	virtual void ableToManager() = 0;
	virtual void chargeWallet(double amount) = 0;
	virtual void getWallet(int count) = 0;
	virtual double getCash() = 0;
	virtual void submitCart(double payableAmount);

protected:	
	int id;
	string email;
	string username;
	string password;
	vector <double> wallet;
};

#endif