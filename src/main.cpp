#include "TaskFactory.hpp"

#include <iostream>

extern "C" {
#include "main.h"
}

int main() {

  TaskFactory& tf = TaskFactory::getInstance();

  tf.create(eTaskTypes::NetworkTask, std::string("Network Task"),
            std::string("192.168.1.1"), true, 4);
  tf.create(eTaskTypes::FileIOTask, std::string("File IO Task"),
            std::string("example.txt"), 0, true, 3);
  tf.create(eTaskTypes::ComputationTask, std::string("Comp task 1"), 200, true,
            2);
  tf.create(eTaskTypes::ComputationTask, std::string("Comp task 2"), 500, true,
            3);

  Scheduler::getInstance().printTasks();

  Scheduler::getInstance().run_join();

  return 0;
}
