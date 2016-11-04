/** @file    server.cpp
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions for the Server class
 */

#include "server.hpp"

namespace zcm {

  Server::Server(std::string name,
            		 unsigned int priority,
            		 zmq::context_t * actor_context,
            		 std::vector<std::string> endpoints,
            		 std::function<void()> operation_function,
            		 Operation_Queue * operation_queue_ptr,
            		 int timeout = 500) :
    name(name),
    priority(priority),
    endpoints(endpoints),
    operation_function(operation_function),
    operation_queue_ptr(operation_queue_ptr),
    server_socket_timeout(timeout)
    {
      context = actor_context;
      server_socket = new zmq::socket_t(*context, ZMQ_REP);
      server_socket->setsockopt(ZMQ_RCVTIMEO, server_socket_timeout); // milliseconds
      response = new std::string("");
      for (auto endpoint : endpoints)
        server_socket->bind(endpoint);
      ready = true;
    }

  Server::~Server() {
    server_socket->close();
    delete context;
    delete server_socket;
  }

  void Server::bind(std::vector<std::string> new_endpoints) {
    endpoints = new_endpoints;
    server_socket = new zmq::socket_t(*context, ZMQ_REP);
    server_socket->setsockopt(ZMQ_RCVTIMEO, server_socket_timeout); // milliseconds
    response = new std::string("");
    for (auto endpoint : endpoints)
      server_socket->bind(endpoint);
    ready = true;
  }

  std::string Server::get_name() {
    return name;
  }

  unsigned int Server::get_priority() {
    return priority;
  }

  void Server::add_connection(std::string new_connection) {
    server_socket->bind(new_connection);
  }

  void Server::recv() {
    while(true) {
      //std::cout << "/* ready state*/" << ready << std::endl;
      while(!ready) {}
      zmq::message_t received_request;
      server_socket->recv(&received_request);
      //std::cout << "/* request received by 0MQ */" << std::endl;
      std::string request = std::string(static_cast<char*>(received_request.data()),
					received_request.size());
      //std::cout << "/* server request string */" << request << std::endl;
      //std::cout << "/* server request length: */" << request.length() << std::endl;
      if (request.length() > 0) {
        ready = false;
        //std::cout << "/* Q operation */" << std::endl;
        func_mutex.lock();
        buffer.push(request);
        // Create a new operation & bind the request as the first argument
        Server_Operation * new_operation
          = new Server_Operation(name, priority, operation_function, server_socket, &ready, response);
          operation_queue_ptr->enqueue(new_operation);
          func_mutex.unlock();
          //std::cout << "/* operation Q'd */" << std::endl;
      }
    }
  }

  void Server::rebind_operation_function(std::function<void()> new_operation_function) {
    func_mutex.lock();
    operation_function = new_operation_function;
    func_mutex.unlock();
  }

  std::thread Server::spawn() {
    return std::thread(&Server::recv, this);//call recv in this thread?
  }

  void Server::start() {
    std::thread server_thread = spawn();
    server_thread.detach();
  }

  bool Server::is_buffer_empty() {
    if (buffer.empty())
      return true;
    else
      return false;
  }

  std::string Server::message() {
    std::string first_message = "";
    if (!is_buffer_empty()) {
      first_message = buffer.front();
      buffer.pop();
    }
    return first_message;
  }

  void Server::set_response(std::string new_response) {
    *response = new_response;
  }

  std::vector<std::string> Server::getEndpoints(){
    return endpoints;
  }

}
