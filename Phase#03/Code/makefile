CC=g++
STD=-std=c++11
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) a.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/Store.o: Store.cpp Store.h UserRepository.h ProductRepository.h Exceptions.h Model.h handlers.h my_server.hpp server/server.hpp
	$(CC) $(CF) -c Store.cpp -o $(BUILD_DIR)/Store.o

$(BUILD_DIR)/UserRepository.o: UserRepository.cpp UserRepository.h User.h Manager.h Seller.h Buyer.h Offer.h server/server.hpp
	$(CC) $(CF) -c UserRepository.cpp -o $(BUILD_DIR)/UserRepository.o

$(BUILD_DIR)/ProductRepository.o: ProductRepository.cpp ProductRepository.h Product.h Car.h Mobile.h Tv.h Buyer.h Offer.h Exceptions.h server/server.hpp
	$(CC) $(CF) -c ProductRepository.cpp -o $(BUILD_DIR)/ProductRepository.o

$(BUILD_DIR)/Model.o: Model.cpp Model.h
	$(CC) $(CF) -c Model.cpp -o $(BUILD_DIR)/Model.o

$(BUILD_DIR)/Product.o: Product.cpp Product.h Offer.h User.h Buyer.h Seller.h Manager.h server/server.hpp
	$(CC) $(CF) -c Product.cpp -o $(BUILD_DIR)/Product.o

$(BUILD_DIR)/Car.o: Car.cpp Car.h Product.h
	$(CC) $(CF) -c Car.cpp -o $(BUILD_DIR)/Car.o

$(BUILD_DIR)/Mobile.o: Mobile.cpp Mobile.h Product.h
	$(CC) $(CF) -c Mobile.cpp -o $(BUILD_DIR)/Mobile.o

$(BUILD_DIR)/Tv.o: Tv.cpp Tv.h Product.h
	$(CC) $(CF) -c Tv.cpp -o $(BUILD_DIR)/Tv.o

$(BUILD_DIR)/User.o: User.cpp User.h Offer.h Exceptions.h server/server.hpp
	$(CC) $(CF) -c User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Manager.o: Manager.cpp Manager.h User.h
	$(CC) $(CF) -c Manager.cpp -o $(BUILD_DIR)/Manager.o

$(BUILD_DIR)/Seller.o: Seller.cpp Seller.h User.h
	$(CC) $(CF) -c Seller.cpp -o $(BUILD_DIR)/Seller.o

$(BUILD_DIR)/Buyer.o: Buyer.cpp Buyer.h User.h
	$(CC) $(CF) -c Buyer.cpp -o $(BUILD_DIR)/Buyer.o

$(BUILD_DIR)/Offer.o: Offer.cpp Offer.h
	$(CC) $(CF) -c Offer.cpp -o $(BUILD_DIR)/Offer.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/handlers.o: handlers.cpp handlers.h UserRepository.h server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/main.o: main.cpp Store.h
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

a.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/Store.o $(BUILD_DIR)/UserRepository.o $(BUILD_DIR)/ProductRepository.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/Model.o $(BUILD_DIR)/Product.o $(BUILD_DIR)/Car.o $(BUILD_DIR)/Mobile.o $(BUILD_DIR)/Tv.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Manager.o $(BUILD_DIR)/Seller.o $(BUILD_DIR)/Buyer.o $(BUILD_DIR)/Offer.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/Store.o $(BUILD_DIR)/UserRepository.o $(BUILD_DIR)/ProductRepository.o $(BUILD_DIR)/Model.o $(BUILD_DIR)/Product.o $(BUILD_DIR)/Car.o $(BUILD_DIR)/Mobile.o $(BUILD_DIR)/Tv.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Manager.o $(BUILD_DIR)/Seller.o $(BUILD_DIR)/Buyer.o $(BUILD_DIR)/Offer.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o a.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
