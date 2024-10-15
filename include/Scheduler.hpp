#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

#include "Tasks.hpp"

#include <atomic>
#include <list>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

struct CompareTask {
  bool operator()(const std::shared_ptr<Task>& left,
                  const std::shared_ptr<Task>& right) {
    if (left->getPriority() == right->getPriority())
      return left->getName() < right->getName();
    return left->getPriority() < right->getPriority();
  }
};

class Scheduler {
 private:
  std::list<std::shared_ptr<Task>> taskList;
  std::priority_queue<std::shared_ptr<Task>, std::vector<std::shared_ptr<Task>>,
                      CompareTask>
      pq;
  Scheduler();
  Scheduler(const Scheduler&) = delete;
  Scheduler& operator=(const Scheduler&) = delete;
  std::atomic<bool> running;
  std::atomic<bool> stopRequested;
  mutable std::mutex run_lock;
  std::condition_variable cv;
  std::thread thread;

  void populateQueue();
  void runTasks() const;
  void setFinishedTasks() const;
  void schedule();

 public:
  static Scheduler& getInstance();

  void addTask(std::unique_ptr<Task> t);

  void run();
  void stop();
  void run_join();

  void printTasks() const;
};

#endif  //__SCHEDULER_HPP__
