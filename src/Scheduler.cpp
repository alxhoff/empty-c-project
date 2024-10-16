#include "Scheduler.hpp"

#include <iostream>
#include <thread>

Scheduler::Scheduler() : running(false), stopRequested(false) {}

void Scheduler::populateQueue() {
  for (std::shared_ptr<Task> task : taskList) {
    if (!task->isFinished())
      pq.push(task);
  }
}

void Scheduler::setFinishedTasks() const {
  for (std::shared_ptr<Task> task : taskList) {
    if (!task->getReccuring())
      task->setFinished();
  }
}

void Scheduler::runTasks() const {
  std::vector<std::thread> threads;

  while(!pq.empty()) {
    threads.emplace_back(&Task::execute, pq.top());
  }

  for (std::thread& t : threads) {
    if (t.joinable()) {
      t.join();
    }
  }
}

Scheduler& Scheduler::getInstance() {
  static Scheduler instance;
  return instance;
}

void Scheduler::addTask(std::unique_ptr<Task> t) {
  std::cout << "Adding task -> " << *t << std::endl;
  std::lock_guard<std::mutex> guard(run_lock);
  taskList.push_back(std::move(std::shared_ptr<Task>(std::move(t))));
}

void Scheduler::schedule() {
  while (!stopRequested) {
    std::unique_lock<std::mutex> lock(run_lock);
    populateQueue();
    runTasks();
    setFinishedTasks();
    // If stopRequested is true then waiting is stopped early
    cv.wait_for(lock, std::chrono::seconds(1),
                [&]() { return stopRequested.load(); });
  }
}

void Scheduler::run() {
  std::lock_guard<std::mutex> lock(run_lock);

  if (running)
    return;  // Already running

  // Start thread
  stopRequested = false;
  running = true;
  thread = std::thread(&Scheduler::schedule, this);
}

void Scheduler::stop() {
  std::lock_guard<std::mutex> lock(run_lock);

  if (!running)
    return;

  // Signal thread to stop
  stopRequested = true;
  cv.notify_all();

  // Wait for it to stop
  if (thread.joinable()) {
    thread.join();
  }

  // Thread stopped
  running = false;
}

void Scheduler::run_join(){
    if(!running)
        run();

    if(thread.joinable())
        thread.join();
}

void Scheduler::printTasks() const {
  std::lock_guard<std::mutex> guard(run_lock);
  for (std::shared_ptr<Task> t : taskList) {
    std::cout << *t << std::endl;
  }
}

