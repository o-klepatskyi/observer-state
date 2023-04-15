#include "ConcreteSubject.h"
#include "ConcreteObserver.h"

int main() {
	ConcreteSubject subject;
	ConcreteObserver observer1(subject);
	ConcreteObserver observer2(subject);

	subject.setState(5);

	subject.detach(&observer2);
	std::cout << "After removed observer2:\n";

	subject.setState(10);
}
