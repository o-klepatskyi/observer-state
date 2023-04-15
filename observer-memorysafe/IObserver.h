#pragma once
#include <string>

class IObserver {
public:
  virtual ~IObserver() {}

  virtual void onNotify() = 0;

  // this method is optional and is here just to have some output
  virtual const std::string &getName() = 0;
};


