#include <iostream>

#include "IObserver.h"
#include "ISubject.h"

class LoggingObserver : public IObserver {
private:
  std::string mName;

public:
  LoggingObserver(const std::string &name) : mName(name) {}

  void onNotify() override { std::cout << mName << " - logging!\n"; }

  const std::string &getName() { return mName; }
};

class SoundObserver : public IObserver {
private:
  std::string mName;

public:
  SoundObserver(const std::string &name) : mName(name) {}

  void onNotify() override { std::cout << mName << " - sound!\n"; }

  const std::string &getName() { return mName; }
};

class PhysicsObserver : public IObserver {
private:
  std::string mName;

public:
  PhysicsObserver(const std::string &name) : mName(name) {}

  void onNotify() override { std::cout << mName << " - physics!\n"; }

  const std::string &getName() { return mName; }
};

int main() {
  ISubject subject;
  std::shared_ptr<IObserver> observer1 =
      std::make_shared<LoggingObserver>("observer1");
  std::shared_ptr<IObserver> observer2 =
      std::make_shared<SoundObserver>("observer2");

  subject.addObserver(observer1);
  subject.addObserver(observer2);

  {
    std::shared_ptr<IObserver> observer3 =
        std::make_shared<PhysicsObserver>("observer3 (i will be gone)");
    subject.addObserver(observer3);
    subject.notify();
  }

  subject.notify();

  subject.removeObserver(observer1);

  subject.notify();

  return 0;
}
