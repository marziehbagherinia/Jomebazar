#include "UserRepository.h"

UserRepository* UserRepository::mainRepository;

UserRepository::UserRepository()
{
    boss = new Manager(1 , ADMINMAIL, ADMINUSERNAME, ADMINPASS);
    userId.push_back(1);
    users.push_back(boss);
    currentID = 2;
}

int UserRepository::getLastId() 
{
    return userId[userId.size() - 1];
}

UserRepository* UserRepository::getUserRep()
{
    if(!mainRepository)
    {
        mainRepository = new UserRepository();
    }

    return mainRepository;
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
                users.push_back(sp);
                userId.push_back(currentID);
                currentID++; 
                return sp;
                break;
            }

            case(buyer) : {
                Buyer* bp = new Buyer(currentID, informations[EMAIL], 
                                informations[USERNAME], informations[PASSWORD]);
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

        users.push_back(bp);
        userId.push_back(currentID);
        currentID++;
        return bp;
    }
}

User* UserRepository::loginCheck(std::map<std::string, std::string> informations)
{
    if (boss->findUser(informations) != false)
    {
        return boss;
    }

    for (int i = 0; i < users.size(); ++i)
    {
        if (users[i]->findUser(informations) != false)
            return users[i];
    }

    throw Server::Exception("There is no user with these informations");
}

void UserRepository::setOffer(Offer* offer, int userID)
{

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

int UserRepository::checkAccountCash(User* buyer)
{
    int userID = findUserIndex(buyer);

    double payableAmount = 0;

    if (userID != -1)
    {
        for (int i = 0; i < currentOrder[userID].size(); ++i)
            payableAmount += currentOrder[userID][i]->getPrice();
    
        int result = buyer->submitCart(payableAmount); 

        if (result == 0)
        {
            return 0;
        }

        else if (result == 1)
        {
            for (int i = 0; i < currentOrder[userID].size(); ++i)
            {
                currentOrder[userID][i]->submitShop();
            }

            doneOrder[userID].push_back(currentOrder[userID]);
            currentOrder[userID].clear();

            return 1;
        }
    }

}

void UserRepository::getMyOffer(User* seller)
{
    map <string, string> informations;
    int userID = findUserIndex(seller);

    if (userID != -1)
    {
        cout << "productId | offerId | offerUnitPrice | offerAmount" << endl;

        for (int i = 0; i < offerRecommender[userID].size(); ++i)
        {
            offerRecommender[userID][i]->getOffer();
        }
    }
}

vector <Offer*> UserRepository::getCart(User* buyer)
{
    int userID = findUserIndex(buyer);

    if (userID != -1)
    {
        return currentOrder[userID];
    }
    else
        throw Server::Exception("There is no user with these informations.");
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

bool UserRepository::isManager(int id) 
{
    if (users[id - 1]->whatIsMyType() == 1)
    {
        return 1;
    }

    return 0;
}

bool UserRepository::isSeller(int id) 
{
    if (users[id - 1]->whatIsMyType() == 2)
    {
        return 1;
    }

    return 0;
}

bool UserRepository::isBuyer(int id) 
{
    if (users[id - 1]->whatIsMyType() == 3)
    {
        return 1;
    }

    return 0;
}

User* UserRepository::getUser(int userID)
{
    if (users[userID - 1] != NULL)
    {
        return users[userID - 1];
    }
    throw Server::Exception("There is no user with this information");
}

vector <Offer*> UserRepository::getUserOffer(int userID)
{
   return offerRecommender[userID]; 
}

bool UserRepository::isDuplicateUsername(string newUsername)
{
    for (int i = 0; i < users.size(); ++i)
    {
        if (newUsername == users[i]->getUsername())
            return 1;
    }

    return 0;
}