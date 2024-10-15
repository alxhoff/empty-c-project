#include "Tasks.hpp"

#include <fstream>
#include <iostream>

Task::Task(int pid, std::string name, bool recurring, int priority,
           bool finished)
    : pid(pid),
      name(name),
      recurring(recurring),
      priority(priority),
      finished(finished) {};

std::ostream& operator<<(std::ostream& os, const Task& obj) {
  obj.print(os);
  return os;
}

bool Task::isFinished() const {
  return finished;
}

void Task::setFinished() {
  finished = true;
}

const std::string Task::toString() const {
  return "Task(name: " + name + ", priority: " + std::to_string(priority) +
         ", reccuring: " + (recurring ? "true" : "false") + ")";
}

const std::string& Task::getName() const {
  return name;
}

void Task::setName(std::string value) {
  name = value;
}

bool Task::getReccuring() const {
  return recurring;
}

void Task::setReccuring(bool val) {
  recurring = val;
}

bool Task::getPriority() const {
  return priority;
}

NetworkTask::NetworkTask(int pid, std::string name, std::string ipv4_address,
                         bool recurring, int priority)
    : Task(pid, name, recurring, priority, false) {
  inet_aton(ipv4_address.c_str(), &ipv4);
};

std::string NetworkTask::getIpv4Address() const {
  std::string address(inet_ntoa(ipv4));
  return address;
}

void NetworkTask::print(std::ostream& os) const {
  os << toString() << "NetworkTask Address: " << getIpv4Address();
}

void NetworkTask::execute() {
  std::cout << *this << std::endl;
}

ComputationTask::ComputationTask(int pid, std::string name, int factorial,
                                 bool recurring, int priority)
    : Task(pid, name, recurring, priority, false), factorial(factorial) {};

void ComputationTask::setFactorial(int value) {
  factorial = value;
}

int calc_factorial(int n){
    if (n <= 1) return 1;
    return n * calc_factorial(n-1);
}

int ComputationTask::getFactorial() const {
  return factorial;
}

void ComputationTask::print(std::ostream& os) const {
  os << toString() << "ComputationTask factorial: " << calc_factorial(getFactorial())
     << std::endl;
}

void ComputationTask::execute() {
  std::cout << *this << std::endl;
}

FileIOTask::FileIOTask(int pid, std::string name, std::string file_name,
                       int count, bool recurring, int priority)
    : Task(pid, name, recurring, priority, false),
      fileName(file_name),
      count(count) {};

void FileIOTask::writeToFile(const std::string content) {
  std::ofstream outFile(fileName);
  if (outFile.is_open()) {
    outFile << content;
    outFile.close();
  } else {
    std::cerr << "Unabl to write to file: " << fileName << std::endl;
  }
}

std::string FileIOTask::readFromFile() const {
  std::ifstream inFile(fileName);
  std::string content, line;

  if (inFile.is_open()) {
    while (std::getline(inFile, line)) {
      content += line + "\n";
    }
    inFile.close();
  } else {
    std::cerr << "Unable to read from file: " << fileName << std::endl;
  }

  return content;
}

void FileIOTask::incrementCount() {
  count++;
}

const std::string& FileIOTask::getFilename() const {
  return fileName;
}

void FileIOTask::print(std::ostream& os) const {
  os << toString() << "FileIOTask filename: " << getFilename() << std::endl;
  os << readFromFile();
}

void FileIOTask::execute() {
  writeToFile(std::to_string(count));
  incrementCount();
  std::cout << *this << std::endl;
}
