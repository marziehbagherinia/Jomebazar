#include "UserRepository.h"



UserRepository::UserRepository()
{
    boss = new Manager(1 , ADMINMAIL, ADMINUSERNAME, ADMINPASS);
    userId.push_back(1);
    currentID = 2;
}

userType getUserType(string type)
{
    if (type == MANAGER)
    {
        return manager;
    }
    else if (type == SELLER)
    {
        return seller;
    }
    else if (type == BUYER)
    {
        return buyer;
    }
}


User* UserRepository::addUser(map <string, string> informations)
{
    if (informations.size() == 4)
    {
        userType type = getUserType(informations[TYPE]);
        switch(type) {
            case(manager) : {
                return boss;
                break;
            }

            case(seller) : {
                Seller* sp = new Seller(currentID, informations[EMAIL],
                                 informations[USERNAME], informations[PASSWORD]);
                cout << OK << endl;
                users.push_back(sp);
                userId.push_back(currentID);
                currentID++; 
                return sp;
                break;
            }

            case(buyer) : {
                Buyer* bp = new Buyer(currentID, informations[EMAIL], 
                                informations[USERNAME], informations[PASSWORD]);
                cout << OK << endl;
                users.push_back(bp);
                userId.push_back(currentID);
                currentID++;
                return bp;
                break;
            }
        }
    }

    else if (informations.size() == 3)
    {
        Buyer* bp = new Buyer(currentID, informations[EMAIL], 
                        informations[USERNAME], informations[PASSWORD]);
        cout << OK << endl;
        users.push_back(bp);
        userId.push_back(currentID);
        currentID++;
        return bp;
    }
}

User* UserRepository::loginCheck(std::map<std::string, std::string> informations)
{
    if (boss->findUser(informations) != false){
        return boss;
    }

    for (int i = 0; i < users.size(); ++i)
    {
        if (users[i]->findUser(informations) != false)
        {
            return users[i];
        }
        throw BadRequest();
    }
}

void UserRepository::setOffer(Offer* offer, User* recommender)
{
    int userID = findUserIndex(recommender);

    if (userID != -1)
    {
        offerRecommender[userID].push_back(offer);
    }
}

int UserRepository::findUserIndex(User* user)
{
    for (int i = 0; i < users.size(); ++i)
    {
        if (users[i]->getID() == user->getID())
        {
            return users[i]->getID();
        }
    }
    return -1;
}

void UserRepository::addToCart(User* buyer, Offer* order)
{
    int userID = findUserIndex(buyer);

    if (userID != -1)
    {
        currentOrder[userID].push_back(order);
    }
}

void UserRepository::checkAccountCash(User* buyer)
{
    int userID = findUserIndex(buyer);

    double payableAmount = 0;

    if (userID != -1)
    {
        for (int i = 0; i < currentOrder[userID].size(); ++i)
            payableAmount += currentOrder[userID][i]->getPrice();
    
        buyer->submitCart(payableAmount);

        for (int i = 0; i < currentOrder[userID].size(); ++i)
        {
            currentOrder[userID][i]->submitShop();
        }

        doneOrder[userID].push_back(currentOrder[userID]);
        currentOrder[userID].clear();
    }

}

void UserRepository::getMyOffer(User* seller)
{
    int userID = findUserIndex(seller);

    if (userID != -1)
    {
        cout << "productId | offerId | offerUnitPrice | offerAmount" << endl;
        
        for (int i = 0; i < offerRecommender[userID].size(); ++i)
            offerRecommender[userID][i]->getOffer();
    }
}

void UserRepository::getCart(User* buyer)
{
    int userID = findUserIndex(buyer);

    if (userID != -1)
    {
        if (currentOrder[userID].size() == 0)
        {
            cout << "EMPTY" << endl;
        }
        else
        {
            cout << "productId | productName | offerId | sellerId | totalPriceConsideringDiscount | amount" << endl;
            for (int i = 0; i < currentOrder[userID].size(); ++i)
                currentOrder[userID][i]->getAll();
        }
    }
}

void UserRepository::getOrder(User* buyer, int count)
{
    int userID = findUserIndex(buyer);
    int temp = count;
    int counter = doneOrder[userID].size() - 1;

    if (userID != -1)
    {
        if (doneOrder[userID].size() == 0)
        {
            cout << "EMPTY" << endl;
        }
        
        else
        {
            cout << "productId | productName | offerId | sellerId | soldPrice | amount" << endl;
            
            if (count > doneOrder[userID].size())
            {
                for (int i = 0; i < doneOrder[userID].size(); ++i) 
                {    
                    for (int j = 0; j < doneOrder[userID][i].size(); ++j)
                        doneOrder[userID][i][j]->getAll();
    
                    if (i != doneOrder[userID].size() - 1)
                        cout << "****" << endl;
                }
            }

            else
            {
                while(temp != 0)
                {
                    for (int i = 0; i < doneOrder[userID][counter].size(); ++i)
                        doneOrder[userID][counter][i]->getAll();

                    if (temp != 1)
                        cout << "****" << endl;

                    temp--;
                    counter--;
                }
            }
            
        }
    }

    
    
}

void UserRepository::emptyCart(User* buyer)
{
   int userID = findUserIndex(buyer); 
   if (userID != -1)
    {
        currentOrder[userID].clear();
    }
   
}