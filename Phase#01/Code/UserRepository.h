#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map> 
#include <bits/stdc++.h> 

#include "User.h"
#include "Manager.h"
#include "Seller.h"
#include "Buyer.h"
#include "Offer.h"

#define OK "OK"
#define ADMINMAIL "admin@gmail.com"
#define ADMINUSERNAME "admin"
#define ADMINPASS  "admin"

#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define TYPE "type"
#define MANAGER "manager"
#define SELLER "seller"
#define BUYER "buyer"
#define PRODUCTID "productId"
#define UNITPRICE "offerUnitPrice"
#define AMOUNT "offerAmount"

using namespace std;

enum userType { manager, seller, buyer};

class UserRepository
{
public:
	UserRepository();

	User* addUser(map <string, string> informations);
	User* loginCheck(map <string, string> informations);

	int findUserIndex(User* user);

	void setOffer(Offer* offer, User* recommender);
	void addToCart(User* buyer, Offer* order);
	void checkAccountCash(User* buyer);
	void getMyOffer(User* seller);
	void getCart(User* buyer);
	void getOrder(User* buyer, int count);
	void emptyCart(User* buyer);

private:
	int currentID;
	
	Manager* boss;
	
	vector <int> userId;
	vector <User*> users;

	map <int, vector <Offer*> > offerRecommender;
	map <int, vector <Offer*> > currentOrder;
	map <int, vector <vector <Offer*>> > doneOrder;

};

#endif