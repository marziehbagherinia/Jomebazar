#ifndef BUYER_H
#define BUYER_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

#include "User.h"

using namespace std;

class Buyer : public User
{
public:
	Buyer(int _id, string _email, string _username, string _password);
	void ableToSeller();
	void ableToBuyer();
	void ableToManager();
	void chargeWallet(double amount);
	void getWallet(int count);
	void checkAmountValidation(double amount);
	double getCash();
	int submitCart(double payableAmount);
	int whatIsMyType();
};

#endif