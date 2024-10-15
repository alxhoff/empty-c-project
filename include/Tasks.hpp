#ifndef __TASKS_HPP__
#define __TASKS_HPP__

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>

enum class eTaskTypes { NetworkTask, ComputationTask, FileIOTask };

class Task {
 private:
  static constexpr int MAX_PRIORITY = 5;

  int pid;
  std::string name;
  bool recurring;
  int priority;
  bool finished;

 public:
  Task(int pid, std::string name, bool recurring, int priority,
       bool finished = false);
  virtual ~Task() = default;
  friend std::ostream& operator<<(std::ostream& os, const Task& obj);
  virtual void print(std::ostream& os) const = 0;

  bool isFinished() const;
  void setFinished();

  const std::string toString() const;

  const std::string& getName() const;
  void setName(std::string value);
  bool getReccuring() const;
  void setReccuring(bool val);
  bool getPriority() const;
  void setPriority(int priority);

  virtual void execute() = 0;
};

class NetworkTask : public Task {
 private:
  struct in_addr ipv4;

 public:
  NetworkTask(int pid, std::string name, std::string ipv4_address = "0.0.0.0",
              bool recurring = false, int priority = 0);
  void print(std::ostream& os) const override;

  std::string getIpv4Address() const;

  void execute() override;
};

class ComputationTask : public Task {
 private:
  int factorial;

 public:
  ComputationTask(int pid, std::string name, int factorial = 1,
                  bool recurring = false, int priority = 0);
  void print(std::ostream& os) const override;

  void setFactorial(int value);
  int getFactorial() const;

  void execute() override;
};

class FileIOTask : public Task {
 private:
  std::string fileName;
  int count;

  void writeToFile(const std::string content);
  std::string readFromFile() const;

  void incrementCount();

 public:
  FileIOTask(int pid, std::string name, std::string file_name, int count = 0,
             bool recurring = false, int priority = 0);
  void print(std::ostream& os) const override;

  const std::string& getFilename() const;
  void execute() override;
};

#endif  //__TASKS_HPP__
