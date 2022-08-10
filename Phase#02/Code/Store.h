#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map> 
#include <bits/stdc++.h> 

#include "Exceptions.h"
#include "UserRepository.h"
#include "ProductRepository.h"
#include "Model.h"

#define ADMINMAIL "admin@gmail.com"
#define ADMINUSERNAME "admin"
#define ADMINPASS  "admin"

#define FIRST 0
#define SECOND 1
#define OK "OK"
#define POST "POST"
#define GET  "GET"
#define SIGNUP "signup"
#define LOGOUT "logout"
#define LOGIN "login"
#define IMPORTP "importProducts"
#define OFFERS "offers"
#define OFFER "offer"
#define GETP "getProducts"
#define MYOFFERS "myOffers"
#define CHANGEOFFER "changeOffer"
#define WALLET "wallet"
#define GENERATEDC "generateDiscountCode"
#define OFFERSONP "offersOnProduct"
#define PRODUCTDETAIL "productDetail"
#define COMMENTS "comments"
#define ADDTOCART "addToCart"
#define CART "cart"
#define SUBMITCART "submitCart"
#define ORDERS "orders"
#define CHARGEWALLET "chargeWallet"
#define COMMENT "comment"
#define COMPARE "compare"
#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define PRODUCTID "productId"
#define PRODUCTID1 "productId1"
#define PRODUCTID2 "productId2"
#define UNITPRICE "offerUnitPrice"
#define AMOUNT "offerAmount"
#define OFFERID "offerId"
#define ORDER "order"
#define ASCEND "ASCEND"
#define DESCEND "DESCEND"
#define FIELD "field"
#define OFFERPRICE "offerPrice"
#define ORDERAMOUNT "amount"
#define CHARGEAMOUNT "amount"
#define COUNT "count"
#define  DISCOUNTCODE "discountCode"
#define DISCOUNTPERCENT "discountPercent"
#define DISCOUNTNUMBER "discountNumber"
#define EVALUATEMODEL "evaluateModel"


using namespace std;

class UserRepository;

class Store
{
public:
	Store();
	void actOn(vector <string> input);
	void checkCurrentUser();
	void checkInput(vector<string> input, int select);

private:
	
	UserRepository userRepository;
	ProductRepository productRepository;
	User* currentUser;
	
	int offerID;
	
};

#endif