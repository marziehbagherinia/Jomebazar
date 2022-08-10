#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map> 
#include <bits/stdc++.h> 

#include "Offer.h"
#include "User.h"
#include "Buyer.h"
#include "Seller.h"
#include "Manager.h"

#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"

using namespace std;

string convertingToString(string input);

class Mobile;
class Tv;
class Car;

class Product
{
public:
	Product(int _id, string _name);

	int getID();
	int findOffer(int offerId);

	string getName();

	Offer* setNewOrder(int offerId, int amount, int discountCode);

	void addToOffers(Offer* offer);
	void editOffer(int offerId, double newUnitPrice, int newAmount);
	void generateDisC(int offerId, double disPercent, int disNumber);
	void getProducts();
	void getOfferOnProduct();
	void addToComments(string comment, User* commenter);
	void printComments(User* user);

	virtual void getProductDetail() {};
	virtual void compare(Product* product) = 0;
  	virtual void compareWith(Product* product) {}
  	virtual void compareWith(Tv* tv) {}
  	virtual void compareWith(Mobile* mobile) {}
  	virtual void compareWith(Car* car) {}

protected:
	int id;
	string name;
	vector <Offer*> offers;

	vector < string > comments;
	
	map <int, User*> commenterUser;
	map <string, vector<string>> userComment;
	
};

#endif