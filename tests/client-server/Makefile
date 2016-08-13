ZCM_HEADERS=/usr/local/include/zcm
ZCM_LIBRARY=/usr/local/lib

TEST_PROTO_DIR=proto
TEST_INCLUDE_DIR=include
TEST_SOURCE_DIR=src
TEST_BUILD_DIR=build
TEST_CONFIG_DIR=config

run: $(TEST_BUILD_DIR)/configuration.json $(TEST_BUILD_DIR)/actor
	cd $(TEST_BUILD_DIR) && export LD_LIBRARY_PATH=$(PWD):$(LD_LIBRARY_PATH) && ./actor

clean:
	rm -rf $(TEST_BUILD_DIR)

test_message.pb: $(TEST_PROTO_DIR)/test_message.proto
	protoc --cpp_out=$(TEST_PROTO_DIR) $(TEST_PROTO_DIR)/test_message.proto

$(TEST_BUILD_DIR)/actor: $(TEST_SOURCE_DIR)/main.cpp component_libs test_message.pb
	g++ $(TEST_SOURCE_DIR)/main.cpp \
	 $(TEST_PROTO_DIR)/test_message.pb.cc \
	 -o $@  \
	 -I$(TEST_INCLUDE_DIR) -I$(TEST_PROTO_DIR) -I$(ZCM_HEADERS) \
	 -std=c++11 -ldl -pthread \
	 -L$(ZCM_LIBRARY) -lzcm -lzmq -lprotobuf -rdynamic

component_libs: $(TEST_BUILD_DIR)/server_component.so $(TEST_BUILD_DIR)/client_component.so

$(TEST_BUILD_DIR)/configuration.json: $(TEST_CONFIG_DIR)/configuration.json
	mkdir -p $(TEST_BUILD_DIR)
	cp -r $(TEST_CONFIG_DIR)/* $@

#Make implicit rule for recompiling client and server
$(TEST_BUILD_DIR)/server_component.so: $(TEST_SOURCE_DIR)/server_component.cpp $(TEST_INCLUDE_DIR)/server_component.hpp test_message.pb
	mkdir -p $(TEST_BUILD_DIR)
	g++ -fPIC -shared $(TEST_SOURCE_DIR)/server_component.cpp -o $@ \
	 -I$(TEST_INCLUDE_DIR) -std=c++11 -pthread -I$(TEST_PROTO_DIR) \
	 -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lprotobuf

$(TEST_BUILD_DIR)/client_component.so: $(TEST_SOURCE_DIR)/client_component.cpp test_message.pb
	mkdir -p $(TEST_BUILD_DIR)
	g++ -fPIC -shared $(TEST_SOURCE_DIR)/client_component.cpp -o $@ \
	 -I$(TEST_INCLUDE_DIR) -std=c++11 -pthread -I$(TEST_PROTO_DIR) \
	 -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lprotobuf
