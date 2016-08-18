/** @file    client_component.cpp
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions for the Client_Component class
 */

#include "client_component.hpp"
#include <exception>

namespace zcm {

  /**
   * @brief Function required to dynamically load client_component.so
   */
  extern "C" {
    Component* create_component() {
      return new Client_Component();
    }
  }

  /**
   * @brief Construct a client component
   * Register all operations exposed by this component
   */
  Client_Component::Client_Component() {
    printf("%s\n", "Created client component" );
    register_functionality("timer_function",
			   std::bind(&Client_Component::timer_function, this));
  }

  /**
   * @brief A timer operation
   * This operation can be triggered by a periodic timer
   * Bind this operation to a periodic timer in the JSON configuration
   */
  void Client_Component::timer_function() {
    // Create new message
    TestMessage new_message;
    printf("%s\n", "Created new client message" );
    new_message.set_message("client_timer_message");
    new_message.set_id(0);

    // Prepare request string
    std::string * request_string = new std::string;
    new_message.SerializeToString(request_string);
    std::cout << "/* client_comp request string */" << *request_string << std::endl;

    // Call server
    try
    {
      std::string response = client("client_port")->call(*request_string);
      std::cout << "Client.Received response: " << response << std::endl;
    }
    catch (const std::runtime_error& error)
    {
      std::cout << "Error: " << error.what()<< std::endl;
    }

  }

}
