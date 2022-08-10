#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map> 
#include <bits/stdc++.h> 

#include "./server/server.hpp"
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
	static UserRepository* getUserRep();

	User* addUser(map <string, string> informations);
	User* loginCheck(map <string, string> informations);
	User* getUser(int userID);

	int findUserIndex(User* user);
	int getLastId();

	void setOffer(Offer* offer, int userID);
	void addToCart(User* buyer, Offer* order);
	int checkAccountCash(User* buyer);
	void getMyOffer(User* seller);
	vector <Offer*> getCart(User* buyer);
	void getOrder(User* buyer, int count);
	void emptyCart(User* buyer);

	vector <Offer*> getUserOffer(int userID);

	bool isManager(int id);
	bool isSeller(int id);
	bool isBuyer(int id);

	bool isDuplicateUsername(string newUsername);

private:
	static UserRepository* mainRepository;

	int currentID;
	
	Manager* boss;
	
	vector <int> userId;
	vector <User*> users;

	map <int, vector <Offer*> > offerRecommender;
	map <int, vector <Offer*> > currentOrder;
	map <int, vector <vector <Offer*>> > doneOrder;

};

#endif