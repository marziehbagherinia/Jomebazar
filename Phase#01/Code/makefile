COMPILER = g++
C_OPT = -c 
C_STD = --std=c++11

a.out : main.o Store.o UserRepository.o ProductRepository.o StreamingService.o User.o Manager.o Seller.o Buyer.o Product.o Car.o Mobile.o Tv.o Offer.o
	$(COMPILER) $(C_STD) main.o Store.o UserRepository.o ProductRepository.o StreamingService.o User.o Manager.o Seller.o Buyer.o Product.o Car.o Mobile.o Tv.o Offer.o

main.o : main.cpp
	$(COMPILER) $(C_STD) $(C_OPT) main.cpp

StreamingService.o : StreamingService.cpp
	$(COMPILER) $(C_STD) $(C_OPT) StreamingService.cpp

Store.o : Store.cpp
	$(COMPILER) $(C_STD) $(C_OPT) Store.cpp

User.o : User.cpp
	$(COMPILER) $(C_STD) $(C_OPT) User.cpp

Manager.o : Manager.cpp
	$(COMPILER) $(C_STD) $(C_OPT) Manager.cpp

Seller.o : Seller.cpp
	$(COMPILER) $(C_STD) $(C_OPT) Seller.cpp

Buyer.o : Buyer.cpp
	$(COMPILER) $(C_STD) $(C_OPT) Buyer.cpp

UserRepository.o : UserRepository.cpp
	$(COMPILER) $(C_STD) $(C_OPT) UserRepository.cpp

ProductRepository.o : ProductRepository.cpp
	$(COMPILER) $(C_STD) $(C_OPT) ProductRepository.cpp

Product.o : Product.cpp
	$(COMPILER) $(C_STD) $(C_OPT) Product.cpp

Car.o : Car.cpp
	$(COMPILER) $(C_STD) $(C_OPT) Car.cpp

Mobile.o : Mobile.cpp
	$(COMPILER) $(C_STD) $(C_OPT) Mobile.cpp

Tv.o : Tv.cpp
	$(COMPILER) $(C_STD) $(C_OPT) Tv.cpp

Offer.o : Offer.cpp
	$(COMPILER) $(C_STD) $(C_OPT) Offer.cpp

clean :
	rm -f *.o
