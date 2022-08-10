#ifndef SELLER_H
#define SELLER_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

#include "User.h"

using namespace std;

class Seller : public User
{
public:
	Seller(int _id, string _email, string _username, string _password);
	
	bool isOfferExist(Offer* offer);
	void ableToSeller();
	void ableToBuyer();
	void ableToManager();
	void chargeWallet(double amount);
	void getWallet(int count);
	double getCash();

private:
	vector <Offer*> myOffers;
};

#endif