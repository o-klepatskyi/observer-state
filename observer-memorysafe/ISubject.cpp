#include "ISubject.h"
#include <iostream>

void ISubject::addObserver(std::weak_ptr<IObserver> &&observer) {
  if (observer.lock()) {
    std::cout << "Adding " << observer.lock()->getName() << "\n";
    mObservers.push_front(std::move(observer));
  }
}

void ISubject::removeObserver(const std::weak_ptr<IObserver> &observer) {
  if (observer.lock()) {
    std::cout << "Removing " << observer.lock()->getName() << "\n";
    mObservers.remove_if([observer](const std::weak_ptr<IObserver> &ptr) {
      return !observer.owner_before(ptr) && !ptr.owner_before(observer);
    });
  }
}


