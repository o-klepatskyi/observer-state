#pragma once
#include "MultithreadSubject.h"
#include "ThreadsafeOut.h"
#include <thread>

void addEmpty() {
	StrSubject subject;
	subject.attach({});
	subject.set("asd");
	out("-------------------");
}

void observerLifetime() {
	StrSubject subject;

	auto writing = [](StrSubject* foo, std::string tname) {
		for (int i = 0; i < 20; i++) {
			out(tname, "hello");
			std::string msg = tname; msg += 'A' + i; msg += "hello";
			foo->set(msg);
			sleep();
			out(tname, "world");
			foo->set(tname + "world");
			sleep();
		}
	};

	auto listening = [](MyListener* listener) {
		listener->for_every_change();
		out("end listener thread.");
	};

	std::thread writer(writing, &subject, "writer");

	{
		auto observer = std::make_shared<MyListener>("alice");
		subject.attach(observer);
		std::thread listener1(listening, observer.get());
		listener1.detach();
		sleep(1000);
		out("deleteing observer...");
	}
	writer.join();
	out("-------------------");
}

void addEmptyFunction() {
	try {
		MultithreadObserver<int> o({});
	}
	catch (const std::exception& e) {
		out(e.what());
	}
}


void memoryTests() {
	addEmpty();
	observerLifetime();
	addEmptyFunction();
}