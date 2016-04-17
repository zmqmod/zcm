#include <iostream>
#include "pub_sub_component.hpp"

int main() {
  Pub_Sub_Component * new_instance = new Pub_Sub_Component("publish_subscribe_component");
  new_instance->init();

  Pub_Sub_Component * new_instance_2 = new Pub_Sub_Component("publish_subscribe_component");
  new_instance_2->init();

  std::thread * instance_1_thread = new_instance->spawn();
  instance_1_thread->join();
  return 0;
}
