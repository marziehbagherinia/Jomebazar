#include "Store.h"



Store::Store()
{
	map <string, string> informations;
	informations[EMAIL] = ADMINMAIL;
	informations[USERNAME] = ADMINUSERNAME;
	informations[PASSWORD] = ADMINPASS;
	informations[TYPE] = "manager"; 
	currentUser = userRepository.addUser(informations);

	offerID = 1;
}

void checkInputValidation(vector <string> input, int select)
{
	if (select == 0)
	{
		if (input.size() < 5 )
			throw BadRequest();
			
	}

	else if (select == 1)
	{
		if (input.size() < 2)
			throw BadRequest();
	}
}

void Store::checkCurrentUser()
{
	if (currentUser == NULL)
	{
		throw PermissionDenied();
	}
}

void Store::actOn(vector <string> input)
{
	map <string, string> informations;

	if (input[FIRST] == POST)
	{
		if (input[SECOND] == SIGNUP)
		{
			try {
				checkInput(input, 2);
				checkInputValidation(input, 0);
				for(int i = 4; i < input.size(); i += 2)
					informations[input[i - 1]] = input[i];

				currentUser = userRepository.addUser(informations);

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    }
		}

		else if (input[SECOND] == LOGIN)
		{
			User* loggingIn;

			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];

			try {
				checkInput(input, 3);
				if (currentUser != NULL)
					throw BadRequest();
				
				loggingIn = userRepository.loginCheck(informations);
			
				if(loggingIn != NULL)
				{
					currentUser = loggingIn;
					cout << OK << endl;
				}

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    }
		}

		else if (input[SECOND] == LOGOUT)
		{
			if(currentUser != NULL)
			{
				userRepository.emptyCart(currentUser);
				currentUser = NULL;
				cout << OK << endl;
			}
			else
				cout << PERMISSION_DENIED << endl;
		}

		else if (input[SECOND] == IMPORTP)
		{
			try {

				checkCurrentUser();
				checkInput(input, 4);
				for(int i = 4; i < input.size(); i += 2) 
					informations[input[i - 1]] = input[i];

				productRepository.addProducts(informations);

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    } catch(NotFound& e) {

		      cout << e.what() << endl;
		    
		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    }
		}
		
		else if (input[SECOND] == OFFER)
		{
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];

			try {	

				checkInput(input, 5);
				checkCurrentUser();
				currentUser->ableToSeller();
				Offer* op = productRepository.addOffer(informations, currentUser, offerID);
				userRepository.setOffer(op, currentUser);

				offerID++;
				cout << OK << endl;

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		    	cout << e.what() << endl;
		    }
		}
		
		else if (input[SECOND] == CHANGEOFFER)
		{
		
			try {
				checkInput(input, 6);
				checkCurrentUser();
				
				for(int i = 4; i < input.size(); i += 2)
					informations[input[i - 1]] = input[i];

				int offerId = stoi(informations[OFFERID]);

				currentUser->ableToSeller();
				productRepository.changeProductOffer(offerId, informations);

				cout << OK << endl;

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		    	cout << e.what() << endl;
		    }
		}
	
		else if (input[SECOND] == GENERATEDC)
		{

			try {

				checkInput(input, 7);
				checkCurrentUser();

				for(int i = 4; i < input.size(); i += 2)
					informations[input[i - 1]] = input[i];

				currentUser->ableToSeller();
				productRepository.generateDiscount(stoi(informations[OFFERID]), informations);

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    } 
		}
	
		else if (input[SECOND] == ADDTOCART)
		{

			try {

				checkInput(input, 8);
				checkCurrentUser();

				for(int i = 4; i < input.size(); i += 2)
						informations[input[i - 1]] = input[i];

				int offerId = stoi(informations[OFFERID]);
				int amount = stoi(informations[ORDERAMOUNT]);
				int discountCode = 0;

				if (informations.size() >= 3)
					discountCode = stoi(informations[DISCOUNTCODE]);

				currentUser->ableToBuyer();
				Offer* order = productRepository.getOrderedOffer(offerId, amount, discountCode);
				userRepository.addToCart(currentUser, order);

				cout << OK << endl;

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		    	cout << e.what() << endl;
		    }
		}

		else if (input[SECOND] == SUBMITCART)
		{
			try {

				checkCurrentUser();
				currentUser->ableToBuyer();
				userRepository.checkAccountCash(currentUser);

				cout << OK << endl;

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		    	cout << e.what() << endl;
		    }
		}

		else if (input[SECOND] == CHARGEWALLET)
		{
			try {

				checkInput(input, 9);
				checkCurrentUser();
				
				for(int i = 4; i < input.size(); i += 2)
					informations[input[i - 1]] = input[i];

				double amount = stod(informations[CHARGEAMOUNT]);

				currentUser->chargeWallet(amount);
				cout << OK << endl;

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    }
		}

		else if (input[SECOND] == COMMENT)
		{
			
			try {

				checkInput(input, 10);
				currentUser->ableToBuyer();
				checkCurrentUser();
				
				int productId = stoi(input[4]);
			
				string comment = "";
				
				for (int i = 6; i < input.size(); ++i)
					comment = comment + input[i] + " ";

				comment.erase(comment.end() -1);

				 map <string, int> alaki;
				 alaki[comment] = 1;
    			 map<string, int> res =  computeProb(alaki);

    			 if (res[comment] == 0)
    			 {
    			 	productRepository.postComment(productId, currentUser, comment);
    			 }

				cout << OK << endl;

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(NotFound& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    }
		}

		else if (input[SECOND] == EVALUATEMODEL)
		{
			
			vector <vector <string>> tests = readDatas("test.csv");
		 	map <string, int> testRealScore = saveData(tests);
		 	map <string, int> testResult = computeProb(testRealScore);
		 	getReasult(testRealScore, testResult);
		}

		else
		{
			try {

				throw NotFound();
				
			} catch(NotFound& e) {

				cout << e.what() << endl;
			}
		}
	}

	else if (input[FIRST] == GET)
	{
		if (input[SECOND] == OFFERS)
		{

			try {

				checkInput(input, 11);				
				checkCurrentUser();

				for(int i = 4; i < input.size(); i += 2)
					informations[input[i - 1]] = input[i];

				string order = informations[ORDER];
				string field = informations[FIELD];

				currentUser->ableToManager();
				productRepository.getAllOffers(order, field);

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    }
		}
	
		else if (input[SECOND] == GETP)
		{
			try {

				checkCurrentUser();
				productRepository.getPro();

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    }
		}

		else if (input[SECOND] == MYOFFERS)
		{
			try {

				checkCurrentUser();
				currentUser->ableToSeller();
				userRepository.getMyOffer(currentUser);

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    }
		}
	
		else if (input[SECOND] == WALLET)
		{

			try {
				checkCurrentUser();
	
				int count = stoi(input[4]);

				currentUser->getWallet(count);

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    }
		}
	
		else if (input[SECOND] == OFFERSONP)
		{
		
			try {

				checkInput(input, 13);
				checkCurrentUser();

				for(int i = 4; i < input.size(); i += 2)
					informations[input[i - 1]] = input[i];

				int productId = stoi(informations[PRODUCTID]);

				currentUser->ableToBuyer();
				productRepository.getOfferOnPro(productId);

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    }
		}
	
		else if (input[SECOND] == PRODUCTDETAIL)
		{
			try {

				checkInput(input, 13);
				checkCurrentUser();

				for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];

				int productId = stoi(informations[PRODUCTID]);

				currentUser->ableToBuyer();
				productRepository.getProDetail(productId);

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    }
		
		}

		else if (input[SECOND] == COMMENTS)
		{
			try {
				checkInput(input, 13);
				checkCurrentUser();
		
				for(int i = 4; i < input.size(); i += 2)
					informations[input[i - 1]] = input[i];

				int productId = stoi(informations[PRODUCTID]);

				currentUser->ableToBuyer();
				productRepository.getComments(productId, currentUser);

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    }

		}

		else if (input[SECOND] == CART)
		{
			try {

				checkCurrentUser();
				currentUser->ableToBuyer();
				userRepository.getCart(currentUser);

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    }
		}

		else if (input[SECOND] == ORDERS)
		{
			try {
				checkInput(input, 12);
				checkCurrentUser();
				
				for(int i = 4; i < input.size(); i += 2)
					informations[input[i - 1]] = input[i];

				int count = stoi(informations[COUNT]);

				currentUser->ableToBuyer();
				userRepository.getOrder(currentUser, count);

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    }
		}
	
		else if (input[SECOND] == COMPARE)
		{
			

			try {

				checkInput(input, 14);
				checkCurrentUser();

				for(int i = 4; i < input.size(); i += 2)
					informations[input[i - 1]] = input[i];

				int productId1 = stoi(informations[PRODUCTID1]);
				int productId2 = stoi(informations[PRODUCTID2]);

				currentUser->ableToBuyer();
				productRepository.doCompare(productId1, productId2);

		    } catch(PermissionDenied& e) {

		      cout << e.what() << endl;

		    } catch(NotFound& e) {

		      cout << e.what() << endl;
		    
		    } catch(BadRequest& e) {

		      cout << e.what() << endl;
		    
		    }
		}

		else
		{
			try {

				throw NotFound();

			} catch(NotFound& e) {

				cout << e.what() << endl;
			}
		}
	}

	else
	{
		try {

			 throw BadRequest();

		} catch(BadRequest& e) {

		   cout << e.what() << endl;

		}
	}
}

void Store::checkInput(vector<string> input, int select)
{

	if (select == 2)
	{
		if( input[3] != EMAIL || input[5] != USERNAME
			|| input[7] != PASSWORD)
			throw BadRequest();
	}

	else if (select == 3)
	{
		if( input[3] != EMAIL || input[5] != PASSWORD)
			throw BadRequest();
	}

	else if (select == 4)
	{
		if( input[3] != TYPE || input[5] != FILEPATH)
			throw BadRequest();
	}

	else if (select == 5)
	{
		if (input[3] != PRODUCTID || input[5] != UNITPRICE 
			|| input[7] != AMOUNT)
		{
			throw BadRequest();
		}
	}

	else if (select == 6)
	{
		if (input[3] != OFFERID || input[5] != UNITPRICE 
			|| input[7] != AMOUNT)
		{
			throw BadRequest();
		}
	}

	else if (select == 7)
	{
		if (input[3] != OFFERID || input[5] != DISCOUNTPERCENT 
			|| input[7] != DISCOUNTNUMBER)
		{
			throw BadRequest();
		}
	}

	else if (select == 8) 
	{
		if (input[3] != OFFERID || input[5] != ORDERAMOUNT)
		{
			throw BadRequest();
		}
	}

	else if (select == 9)
	{
		if (input[3] !=CHARGEAMOUNT)
		{
			throw BadRequest();
		}
	}

	else if (select == 10)
	{
		if (input[3] != PRODUCTID || input[5] != COMMENT)
		{
			throw BadRequest();
		}
	}

	else if (select == 11)
	{
		if (input[3] != ORDER || input[5] != FIELD )
		{
			throw BadRequest();
		}
	}

	else if (select == 12)
	{
		if (input[3] != COUNT) 
		{
			throw BadRequest();
		}
	}

	else if (select == 13)
	{
		if (input[3] != PRODUCTID)
		{
			throw BadRequest();
		}
	}

	else if (select == 14)
	{
		if (input[3] != PRODUCTID || input[5] != PRODUCTID2)
		{
			throw BadRequest();
		}
	}
}