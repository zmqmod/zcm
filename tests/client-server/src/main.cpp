#include "actor.hpp"
#include <string>

int main() {
  printf("%s\n", "Made it to the main" );
  zcm::Actor client_server_actor;
  printf("%s\n", "Created client_server_actor" );
  /*
  void * handle = dlopen("test_message.pb.so", RTLD_NOW);
  if(handle == NULL)
    std::cerr << dlerror() << std::endl;
  else {
    printf("%s\n", "Have handle for dll" );
    dlsym(handle, "TestMessage");
  }
  */
  client_server_actor.configure("configuration.json");
  printf("%s\n", "Configured client_server_actor" );
  client_server_actor.run();

  return 0;
}
