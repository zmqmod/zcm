ZCM_HEADERS=/usr/local/include/zcm
ZCM_LIBRARY=/usr/local/lib

TEST_INCLUDE_DIR=include
TEST_SOURCE_DIR=src
TEST_BUILD_DIR=build
TEST_CONFIG_DIR=config


run: $(TEST_BUILD_DIR)/configuration.json $(TEST_BUILD_DIR)/actor
	cd $(TEST_BUILD_DIR) && export LD_LIBRARY_PATH=$(PWD):$(LD_LIBRARY_PATH) && ./actor

clean:
	rm -rf $(TEST_BUILD_DIR)

$(TEST_BUILD_DIR)/actor: $(TEST_SOURCE_DIR)/main.cpp component_libs
	g++ $(TEST_SOURCE_DIR)/main.cpp -o $(TEST_BUILD_DIR)/actor -I$(TEST_INCLUDE_DIR) -std=c++11 -ldl -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq

component_libs:  $(TEST_BUILD_DIR)/component_1.so $(TEST_BUILD_DIR)/component_2.so $(TEST_BUILD_DIR)/component_3.so

$(TEST_BUILD_DIR)/configuration.json: $(TEST_CONFIG_DIR)/configuration.json
	mkdir -p $(TEST_BUILD_DIR)
	cp -r $(TEST_CONFIG_DIR)/* $@

$(TEST_BUILD_DIR)/component_1.so: $(TEST_SOURCE_DIR)/component_1.cpp
	mkdir -p $(TEST_BUILD_DIR)
	g++ -fPIC -shared $(TEST_SOURCE_DIR)/component_1.cpp -o $@ -I$(TEST_INCLUDE_DIR) -std=c++11 -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lboost_filesystem

$(TEST_BUILD_DIR)/component_2.so: $(TEST_SOURCE_DIR)/component_2.cpp
	mkdir -p $(TEST_BUILD_DIR)
	g++ -fPIC -shared $(TEST_SOURCE_DIR)/component_2.cpp -o $@ -I$(TEST_INCLUDE_DIR) -std=c++11 -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lboost_filesystem

$(TEST_BUILD_DIR)/component_3.so: $(TEST_SOURCE_DIR)/component_3.cpp
	mkdir -p $(TEST_BUILD_DIR)
	g++ -fPIC -shared $(TEST_SOURCE_DIR)/component_3.cpp -o $@ -I$(TEST_INCLUDE_DIR) -std=c++11 -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lboost_filesystem
