#include "actor.hpp"
#include <string>
#include <vector>
#include <unistd.h>
#include <boost/filesystem.hpp>

std::vector<std::string> arguments(const int argc, const char* argv[]){
	std::vector<std::string> result;
	for (int i = 0; i< argc; ++i)
		result.push_back(argv[i]);
	return result;
	}

void usage(){
	std::cout << "Explain how this are supposed to work" << std::endl;
}

int main(const int argc, const char* argv[]) {
  std::cout << "Made it to the main" << std::endl;

  namespace fs = boost::filesystem;
  fs::path pwd (fs::current_path());
  std::cout << "current directory: " << pwd << std::endl;

  char* LD_LIBRARY_PATH = getenv("LD_LIBRARY_PATH");
  std::cout << "print LD_LIBRARY_PATH "  << LD_LIBRARY_PATH <<std::endl;

  std::vector<std::string> cmdargs = arguments(argc, argv);

  std::cout << "print cmdargs.size(): " << cmdargs.size() << std::endl;
  std::cout << "print cmdargs[0]" << cmdargs[0] << std::endl;
  std::cout << "print cmdargs[1]" << cmdargs[1].c_str() << std::endl;

  if (cmdargs.size() < 1){
	  std::cout << "No config file" << std::endl;
	  usage();
	  return -1;
  }
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
  std::cout << "main call configure actor" << std::endl;

  client_server_actor.configure(cmdargs[1]);
  printf("%s\n", "Configured client_server_actor" );
  client_server_actor.run();

  return 0;
}
