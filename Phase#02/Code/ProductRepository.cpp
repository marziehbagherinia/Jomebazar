#include "ProductRepository.h"

#define TYPE "type"
#define FILEPATH "filePath"
#define CAR "car"
#define MOBILE "mobile"
#define TV "tv"


ProductRepository::ProductRepository()
{
    id = 0;
}

productType getProductType(string type)
{
    if (type == CAR)
    {
        return car;
    }
    else if (type == MOBILE)
    {
        return mobile;
    }
    else if (type == TV)
    {
        return tv;
    }
}

 vector< vector< string >> readData(string filename)
 {
 	string name = "./Data/" + filename; 

	string line, field, firstLine;
    vector< vector< string >> helperV;  
    vector< string > gettingLine;

	ifstream myfile(name.c_str());
    if(myfile.is_open())
    {
        getline(myfile, firstLine);
        while (getline(myfile,line))
        {
            gettingLine.clear();
            stringstream ss(line);
            while(getline(ss,field,','))
            {
                gettingLine.push_back(field);
            }
            helperV.push_back(gettingLine); 
        }
    }
    else
    {
        throw NotFound();
    }
    return helperV;
 }

void ProductRepository::addProducts(map <string, string> informations)
{
	productType type = getProductType(informations[TYPE]);
    vector< vector< string >> data;  
    int index = 0;
	    
    switch(type) {
        case(car) : {
            data = readData(informations[FILEPATH]);
            while(index != data.size())
            {
                id++;
            	Car* cp = new Car(id, data[index][0], stoi(data[index][1]), 
                          stoi(data[index][2]), stoi(data[index][3]), 
                          stoi(data[index][4]), stoi(data[index][5]));
                
                products.push_back(cp);
                productIds.push_back(id);
            	index++;
            }
            index = 0;
            cout << OK << endl;
            break;
        }

        case(mobile) : {
            data = readData(informations[FILEPATH]);
            while(index != data.size())
            {
                id++;
            	Mobile* mp = new Mobile(id, data[index][0], stoi(data[index][1]), 
                             stod(data[index][2]), stoi(data[index][3]),
                             stoi(data[index][4]), stod(data[index][5]), 
                             stoi(data[index][6]), data[index][7]);
                
                products.push_back(mp);
                productIds.push_back(id);
            	index++;
            }
            index = 0;
            cout << OK << endl;
            break;
        }

        case(tv) : {
            data = readData(informations[FILEPATH]);
            while(index != data.size())
            {
                id++;
            	Tv* tp = new Tv(id, data[index][0], stoi(data[index][1]), 
                             data[index][2], data[index][3], 
                             stoi(data[index][4]), stoi(data[index][5]));

                products.push_back(tp);
                productIds.push_back(id);
            	delete tp;
                index++;
            }
            index = 0;
            cout << OK << endl;
            break;
        }
    }
}

int ProductRepository::whereIsMyProduct(int productId)
{
    int index = distance(productIds.begin(), 
                find(productIds.begin(), productIds.end(), productId));
    
    if (index != productIds.size()) 
    {
        return index;
    }
    
    else 
    {
        return -1;
    }
}

void ProductRepository::isMyProduct(int productId)
{
    if (find(productIds.begin(), productIds.end(), 
        productId) == productIds.end())
        throw PermissionDenied();
}

void ProductRepository::discoverProduct(int productId)
{
    if (find(productIds.begin(), productIds.end(), 
        productId) == productIds.end())
        throw NotFound();
}

int ProductRepository::findProductId(int productId, int userID)
{
    return distance(offerRecommender[userID].begin(), 
           find(offerRecommender[userID].begin(), 
            offerRecommender[userID].end(), productId));
}

void ProductRepository::isDuplicateOffer(int productId, int userID)
{
    if (find(offerRecommender[userID].begin(), 
        offerRecommender[userID].end(), productId)
        != offerRecommender[userID].end())
    {
        throw BadRequest();
    }
}

void ProductRepository::addToUsers(int userID)
{
    if (find(usersID.begin(), usersID.end(), 
        userID) == usersID.end())
        usersID.push_back(userID);
}

Offer* ProductRepository::addOffer(map <string, string> informations, User* recommender, int offerID)
{
    int productId = stoi(informations[PRODUCTID]);
    int userID = recommender->getID();

    isMyProduct(productId);
    isDuplicateOffer(productId, userID);
    addToUsers(userID);
    
    offerRecommender[userID].push_back(productId);
    offerProductId[offerID] = productId;
    offerIds.push_back(offerID);

    string productName = products[productId - 1]->getName();

    Offer* op = new Offer(offerID, productId, productName,
                          stod(informations[UNITPRICE]),
                          stoi(informations[AMOUNT]), 
                          recommender);

    products[productId - 1]->addToOffers(op);
    offers.push_back(op);

    return op;
}

void ProductRepository::changeProductOffer(int offerId, map <string, string> informations)
{
    isOfferIdExist(offerId);
    double newUnitPrice = stod(informations[UNITPRICE]);
    int newAmount = stoi(informations[AMOUNT]);

    int productId = offerProductId[offerId];
    
    products[productId - 1]->editOffer(offerId, newUnitPrice, newAmount);
}

void ProductRepository::isOfferIdExist(int offerId)
{
    if (!offerProductId[offerId])
        throw BadRequest();
}

int ProductRepository::isMyUnitPrice(double unitPrice)
{
    for (int i = 0; i < offers.size(); ++i)
    {
        if (offers[i]->getUnitPrice() == unitPrice)
        {
            return i;
        }
    }
    return -1;
}

void ProductRepository::generateDiscount(int offerId, map <string, string> informations)
{
    isOfferIdExist(offerId);
    double disPercent = stod(informations[DISCOUNTPERCENT]);
    int disNumber = stoi(informations[DISCOUNTNUMBER]);

    int productId = offerProductId[offerId];

    products[productId - 1]->generateDisC(offerId, disPercent, disNumber);
}

Offer* ProductRepository::getOrderedOffer(int offerId, int amount, int discountCode)
{
    int productId = offerProductId[offerId];

    Offer* order = products[productId - 1]->setNewOrder(offerId, amount, discountCode);

    return order;
}

void ProductRepository::postComment(int productId, User* commenter, string comment)
{
    discoverProduct(productId);

    int index = whereIsMyProduct(productId);

    if (index != -1)
       products[index]->addToComments(comment, commenter);
}

void ProductRepository::getAllOffers(string order, string field)
{
    cout << "productId | offerId | offerUnitPrice | offerAmount" << endl;

    if (field == OFFERID)
    {
        if (order == ASCEND)
        {
            for (int i = 0; i < offers.size(); ++i)
                offers[i]->getOffer();
        }
        else if (order == DESCEND)
        {
            for (int i = offers.size() - 1; i > -1; i--)
                offers[i]->getOffer();
        }
        
    }
    else if (field == OFFERPRICE)
    {
        vector <Offer*> sortedOffers = sortOnOfferPrice();
        
        if (order == ASCEND)
        {
            for (int i = 0; i < sortedOffers.size(); ++i)
                sortedOffers[i]->getOffer();
        }
        else if (order == DESCEND)
        {
            for (int i = sortedOffers.size() - 1; i > -1; i--)
                sortedOffers[i]->getOffer();
        }

    }
}

vector <Offer*> ProductRepository::sortOnOfferPrice()
{
    vector <Offer*> sortedOffers;
    vector <double> newOfferPrice;

    for (int i = 0; i < offers.size(); ++i)
    {
        newOfferPrice.push_back(offers[i]->getUnitPrice());
    }

    sort(newOfferPrice.begin(), newOfferPrice.end());

    int index;

    for (int i = 0; i < newOfferPrice.size(); ++i)
    {
        index = isMyUnitPrice(newOfferPrice[i]);

        if (index != -1)
            sortedOffers.push_back(offers[index]);  
    }

    return sortedOffers;
}

void ProductRepository::getPro()
{
    cout << "productId | productName" << endl;
    for (int i = 0; i < products.size(); ++i)
    {
        products[i]->getProducts();
    }
}

void ProductRepository::getOfferOnPro(int productId)
{
    products[productId - 1]->getOfferOnProduct();
}

void ProductRepository::getProDetail(int productId)
{
    products[productId - 1]->getProductDetail();
}

void ProductRepository::doCompare(int productId1, int productId2)
{
    discoverProduct(productId1);
    discoverProduct(productId2);
    products[productId1 - 1]->compare(products[productId2 - 1]);
}

void ProductRepository::getComments(int productId, User* user)
{
    products[productId - 1]->printComments(user);
}