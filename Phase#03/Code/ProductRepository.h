#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map> 
#include <bits/stdc++.h> 

#include "Exceptions.h"
#include "Product.h"
#include "Car.h"
#include "Mobile.h"
#include "Tv.h"
#include "Buyer.h"
#include "Offer.h"

#define OK "OK"
#define TYPE "type"
#define FILEPATH "filePath"
#define CAR "car"
#define MOBILE "mobile"
#define TV "tv"

#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define PRODUCTID "productId"
#define UNITPRICE "offerUnitPrice"
#define AMOUNT "offerAmount"
#define OFFERID "offerId"
#define OFFERPRICE "offerPrice"
#define DISCOUNTPERCENT "discountPercent"
#define DISCOUNTNUMBER "discountNumber"

using namespace std;

enum productType { car, mobile, tv};

class ProductRepository
{
public:
	ProductRepository();

	Offer* addOffer(map <string, string> informations, User* recommender);

	Offer* getOrderedOffer(int offerId, int amount,
	                       int discountCode);

	vector <Offer*> sortOnOfferPrice();

	int isMyUnitPrice(double unitPrice);
	int findProductId(int productId, int userID);
	int whereIsMyProduct(int productId);

	void addProducts(map <string, string> informations);
	void isMyProduct(int productId);
	void isDuplicateOffer(int productId, int userID);
	void addToUsers(int userID);
	void changeProductOffer(int offerId, map <string, string> informations);
	void isOfferIdExist(int offerId);
	void generateDiscount(int offerId, map <string, string> informations);
	void getAllOffers(string order, string field);
	void getPro();
	void getOfferOnPro(int productId);
	map<string, string> getProDetail(int productId);
	void postComment(int productId, User* commenter, string comment);
	void getComments(int productId, User* user);
	void discoverProduct(int productId);
	void doCompare(int productId1, int productId2);
 	int whatIsMyType(int productId);
 	vector <Offer*> getOfferOn(int productId);

	vector <Car*> getCars();
	vector <Mobile*> getMobiles();
	vector <Tv*> getTvs();

	static ProductRepository* getProductRep();



private:
	int id;
	int newOfferID;
	static ProductRepository* mainRepository;
	
	vector <int> usersID;
	vector <int> productIds;
	vector <int> offerIds;

	vector <Product*> products;
	vector <Car*> cars;
	vector <Mobile*> mobiles;
	vector <Tv*> tvs;
	vector <Offer*> offers;

	map <int, int> offerProductId;	
	map <int, User*> commenterUser;
	map <int, vector <int> > offerRecommender;
	
};

#endif