#ifndef OFFER_H
#define OFFER_H

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

#include "User.h"
#include "Exceptions.h"

using namespace std;

class User;

class Offer
{
public:
	Offer(int _id, int _productId, string _productName, double _unitPrice, int _amount, User* _recommender);
	
	int getID();
	double getPrice();
	double getUnitPrice();

	string getOfferProperty();

	void setNewFeatures(double newUnitPrice, int newAmount);
	void generateDisCode(double _disPercent, int disNumber);
	void setOrder(int _amount, int _discountCode);
	void checkDisCodeValidation(int _discountCode);
	void checkAmountValidation(int _amount);
	void submitShop();
	void getOffer();
	void getAll();
	void removeDisCode(int discountCode);
	
private:
	int id;
	int productId;
	int amount;
	int waitingAmount;

	double unitPrice;
	double disPercent;
	double waitingPrice;
	
	string productName;
	
	User* recommender;

	vector <int> dicountCode;
	
};

#endif