#include "TaskFactory.hpp"

TaskFactory::TaskFactory() : next_pid(1) {
  registerCreator<ComputationTask, std::string, int, bool, int>(
      eTaskTypes::ComputationTask);
  registerCreator<NetworkTask, std::string, std::string, bool, int>(
      eTaskTypes::NetworkTask);
  registerCreator<FileIOTask, std::string, std::string, int, bool, int>(
      eTaskTypes::FileIOTask);
}

int TaskFactory::getPID() {
    return next_pid++;
}

TaskFactory& TaskFactory::getInstance() {
  static TaskFactory instance;
  return instance;
}

