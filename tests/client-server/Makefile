ZCM_HEADERS=/usr/local/include/zcm
ZCM_LIBRARY=/usr/local/lib

TEST_PROTO_DIR=proto
TEST_INCLUDE_DIR=include
TEST_SOURCE_DIR=src
TEST_BUILD_DIR=build
TEST_CONFIG_DIR=config

all: $(TEST_BUILD_DIR)/actor

run: $(TEST_BUILD_DIR)/configuration.json $(TEST_BUILD_DIR)/actor
	 export LD_LIBRARY_PATH=./$(TEST_BUILD_DIR):$(LD_LIBRARY_PATH) && ./$(TEST_BUILD_DIR)/actor

actor: $(TEST_BUILD_DIR)/actor

proto: $(TEST_PROTO_DIR)/test_message.pb.cc $(TEST_PROTO_DIR)/test_message.pb.h

clean:
	rm -rf $(TEST_BUILD_DIR)
	rm $(TEST_PROTO_DIR)/test_message.pb.*

$(TEST_PROTO_DIR)/test_message.pb.cc $(TEST_PROTO_DIR)/test_message.pb.h: $(TEST_PROTO_DIR)/test_message.proto
	protoc --cpp_out=. $(TEST_PROTO_DIR)/test_message.proto

$(TEST_BUILD_DIR)/actor: $(TEST_SOURCE_DIR)/main.cpp $(TEST_BUILD_DIR)/server_component.so $(TEST_BUILD_DIR)/client_component.so $(TEST_PROTO_DIR)/test_message.pb.cc
	g++ $(TEST_SOURCE_DIR)/main.cpp \
	 $(TEST_PROTO_DIR)/test_message.pb.cc \
	 -o $@  \
	 -I$(TEST_INCLUDE_DIR) -I. -I$(ZCM_HEADERS) \
	 -std=c++11 -ldl -lboost_system -lboost_filesystem -pthread \
	 -L$(ZCM_LIBRARY) -lzcm -lzmq -lprotobuf -rdynamic 

$(TEST_BUILD_DIR)/configuration.json: $(TEST_CONFIG_DIR)/configuration.json
	mkdir -p $(TEST_BUILD_DIR)
	cp -r $(TEST_CONFIG_DIR)/* $@

#Make implicit rule for recompiling client and server
$(TEST_BUILD_DIR)/server_component.so: $(TEST_SOURCE_DIR)/server_component.cpp $(TEST_INCLUDE_DIR)/server_component.hpp $(TEST_PROTO_DIR)/test_message.pb.h
	mkdir -p $(TEST_BUILD_DIR)
	g++ -fPIC -shared $(TEST_SOURCE_DIR)/server_component.cpp -o $@ \
	 -I$(TEST_INCLUDE_DIR) -std=c++11 -pthread -I$(TEST_PROTO_DIR) \
	 -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lprotobuf

$(TEST_BUILD_DIR)/client_component.so: $(TEST_SOURCE_DIR)/client_component.cpp $(TEST_PROTO_DIR)/test_message.pb.h
	mkdir -p $(TEST_BUILD_DIR)
	g++ -fPIC -shared $(TEST_SOURCE_DIR)/client_component.cpp -o $@ \
	 -I$(TEST_INCLUDE_DIR) -std=c++11 -pthread -I$(TEST_PROTO_DIR) \
	 -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lprotobuf
