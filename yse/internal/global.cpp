/*
  ==============================================================================

    global.cpp
    Created: 27 Jan 2014 10:18:28pm
    Author:  yvan

  ==============================================================================
*/

#include "../internalHeaders.h"


YSE::INTERNAL::global & YSE::INTERNAL::Global() {
    static global s;
    return s;
}

YSE::INTERNAL::logImplementation & YSE::INTERNAL::global::getLog() {
  return *log;
}

YSE::INTERNAL::listenerImplementation & YSE::INTERNAL::global::getListener() {
  return *li;
}

void YSE::INTERNAL::global::addSlowJob(ThreadPoolJob * job) {
  slowThreads.addJob(job, false);
}

void YSE::INTERNAL::global::addFastJob(ThreadPoolJob * job) {
  fastThreads.addJob(job, false);
}

void YSE::INTERNAL::global::waitForFastJob(ThreadPoolJob * job) {
  if (fastThreads.contains(job)) {
    fastThreads.waitForJobToFinish(job, -1);
  }
}

void YSE::INTERNAL::global::waitForSlowJob(ThreadPoolJob * job) {
  if (slowThreads.contains(job)) {
    slowThreads.waitForJobToFinish(job, -1);
  }
}

bool YSE::INTERNAL::global::containsSlowJob(ThreadPoolJob * job) {
  return slowThreads.contains(job);
}

YSE::INTERNAL::global::global() : slowThreads(1), update(false), active(false) {}

void YSE::INTERNAL::global::init() {
  log = logImplementation::getInstance();
  li = listenerImplementation::getInstance();

  slowThreads.setThreadPriorities(0);
  fastThreads.setThreadPriorities(10);

  REVERB::Manager().create();
}

void YSE::INTERNAL::global::close() {
  // first wait for all threads to exit
  slowThreads.removeAllJobs(true, -1);
  fastThreads.removeAllJobs(true, -1);

  // remove managers
  listenerImplementation::deleteInstance();
  
  // these have to come last!
  logImplementation::deleteInstance();
}
