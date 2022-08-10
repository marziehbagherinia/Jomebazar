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

void Store::run() 
{ 

	try {
		MyServer server(5000);
		server.setNotFoundErrPage("static/404.html");
		server.get("/profile.png", new ShowImage("profile.png"));
		server.get("/images.jpeg", new ShowImage("images.jpeg"));
		server.get("/final.jpg", new ShowImage("final.jpg"));
		server.get("/back.jpeg", new ShowImage("back.jpeg"));
		server.get("/", new ShowLogin());
		server.get("/login", new ShowLogin());
		server.post("/login", new LoginHandler());
		server.get("/signup", new ShowSignup());
		server.post("/signup", new SignupHandler());		
		server.get("/manager_home", new ShowManagerHome());
		server.post("/up", new UploadHandler());
		server.get("/products", new showProducts());
		server.post("/products", new showProducts());		
		server.get("/seller_home", new ShowSellerHome());
		server.get("/post_offer", new showPostOffer());		
		server.post("/post_offer", new postOfferHandler());
		server.get("/buyer_home", new ShowBuyerHome());
		server.get("/bank", new ShowBuyerBank());
		server.post("/charge_wallet", new chargeWalletHandler());
		server.post("/product_detail", new productDetailHandler());
		server.post("/add_to_cart", new addToCartlHandler());
		server.get("/shop", new showShopPage());
		server.post("/submit_cart", new submitCartlHandler());
		server.get("/logout", new LogoutHandler());
		server.post("/logout", new LogoutHandler());		
		server.run();
  } catch (Server::Exception e) {
    std::cerr << e.getMessage() << std::endl;
  } 
}
