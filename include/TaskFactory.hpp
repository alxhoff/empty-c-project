#ifndef __TASKFACTORY_HPP__
#define __TASKFACTORY_HPP__

#include "Tasks.hpp"
#include "Scheduler.hpp"

#include <any>
#include <functional>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <utility>

class TaskFactory {
 private:
  int next_pid;
  TaskFactory();

  // This doesnt work as std::function cannot have function signatures that
  // accept multiple arguemnts
  // std::unordered_map<eTaskTypes, std::function<std::unique_ptr<Task>(...)>>
  //     creators;

  // Change the map to store callable objects that store args in a tuple that
  // is implemented using std::any to accomodate different tuple configurations
  // between object types
  std::unordered_map<eTaskTypes, std::function<std::unique_ptr<Task>(std::any)>>
      creators;

  int getPID();

 public:
  static TaskFactory& getInstance();

  // Register lambda creation function with creators map
  // T is type of task, Args are constructor arg types
  template <typename T, typename... Args>
  void registerCreator(eTaskTypes type) {
    // args are prepended with int getPID in create thus they will have type
    // int, Args...
    creators[type] = [this](std::any args) -> std::unique_ptr<Task>{
      //unpack args tuple from std::any
      //prepend an int that will store the PID so that the arg type is correct
      //for when create passes in getPID as the first argument
      auto argsTuple = std::any_cast<std::tuple<Args...>>(args);
      //apply passes a tuple containing args to a callable, in this case
      //a lambda. The creator passes in a int PID and the user's args
      return std::apply(
          [this](auto&&... unpackedArgs) {
            return std::make_unique<T>(
                getPID(), std::forward<decltype(unpackedArgs)>(unpackedArgs)...);
          },
          argsTuple);
    };
  }

  // Create a class object providing variadic arguments
  template <typename... Args>
  void create(eTaskTypes type, Args&&... args) {
    auto it = creators.find(type);
    if (it != creators.end()) {

      //Adding a PID that is not provided by the user
      //This needs to be also accepted by the function registered as creator
      std::tuple<Args...> arguments{ std::forward<Args>(args)...};
      std::unique_ptr<Task> t = it->second(arguments);
      Scheduler::getInstance().addTask(std::move(t));
      return;
    }
    throw std::runtime_error("Task type not supported");
  }
};

#endif  //__TASKFACTORY_HPP__
