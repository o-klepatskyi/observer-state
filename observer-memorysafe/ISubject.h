#pragma once
#include "IObserver.h"
#include <list>
#include <memory>

class ISubject {
public:
  virtual ~ISubject() {}

  virtual void addObserver(std::weak_ptr<IObserver> &&observer);
  virtual void removeObserver(const std::weak_ptr<IObserver> &observer);

  virtual void notify() {
    // go through list of observers
    for (auto it = mObservers.begin(); it != mObservers.end();) {
      if (it->expired()) {
        // delete if it doesn't exist
        it = mObservers.erase(it);
      } else {
        // otherwise notify!
        it->lock()->onNotify();
        it++;
      }
    }
  }

private:
  std::list<std::weak_ptr<IObserver>> mObservers;
};


