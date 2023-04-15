#pragma once
// by Tony Van Eerd
#include "MultithreadSubject.h"
#include "ThreadsafeOut.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <string>

using StrSubject = MultithreadSubject<std::string>;

struct MyListener : MultithreadObserver<std::string> {
	std::string m_name;
	MyListener(std::string name) : MultithreadObserver([&](std::string s) {
		lout(s, m_name);
	}), m_name(name) {}
};

void sleep(int dur = 50)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(dur));
}

void do_other_stuff()
{
	sleep(10);
}

void test_independent()
{
	out("--------- test independent");

	std::shared_ptr<MyListener> alice = std::make_shared<MyListener>("alice");
	std::shared_ptr<MyListener> bob = std::make_shared<MyListener>("bob");
	StrSubject foo;

	foo.attach(alice);
	foo.attach(bob);

	auto writing = [](StrSubject* foo, std::string tname) {
		for (int i = 0; i < 20; i++) {
			out(tname, "hello");
			std::string msg = tname; msg += 'A' + i; msg += "hello";
			foo->set(msg);
			//sleep();
			out(tname, "world");
			foo->set(tname + "world");
			//sleep();
		}
	};

	auto listening = [](MyListener* listener) {
		listener->for_every_change();
	};

	std::atomic<bool> stuff_to_do = true;

	auto listening_detail = [&](MyListener* listener) {
		while (stuff_to_do)
		{
			listener->check_for_change();
			do_other_stuff();
		}
	};

	std::thread writer(writing, &foo, "writer");

	std::thread listener1(listening, alice.get());
	std::thread listener2(listening_detail, bob.get());

	writer.join();
	// writing done, stop the listener threads
	alice->stop();
	stuff_to_do = false;
	listener1.join();
	listener2.join();
	out("done");
}

void test_deletion()
{
	out("--------- test deletion");

	StrSubject foo;

	std::atomic<bool> keepWriting = true;
	auto writing = [&keepWriting](StrSubject* foo, std::string tname) {
		for (int i = 0; keepWriting; i++) {
			out(tname, "hello");
			std::string msg = tname; msg += 'A' + i; msg += "hello";
			foo->set(msg);
			//sleep();
			out(tname, "world");
			foo->set(tname + "world");
			//sleep();
		}
	};

	// start writing, at first, with no listeners
	std::thread writer(writing, &foo, "writer");

	// write for a while
	sleep(50);

	// now add some listeners
	{
		std::shared_ptr<MyListener> alice = std::make_shared<MyListener>("alice");
		std::shared_ptr<MyListener> bob = std::make_shared<MyListener>("bob");

		foo.attach(alice);
		foo.attach(bob);

		auto listening = [](MyListener* listener) {
			listener->for_every_change();
		};

		std::atomic<bool> stuff_to_do = true;

		auto listening_detail = [&](MyListener* listener) {
			while (stuff_to_do)
			{
				listener->check_for_change();
				do_other_stuff();
			}
		};

		std::thread listener1(listening, alice.get());
		std::thread listener2(listening_detail, bob.get());

		// wait a while
		sleep(200);

		foo.detach(alice);
		foo.detach(bob);

		// stop alice and bob
		alice->stop();
		stuff_to_do = false;
		listener1.join();
		listener2.join();
		// *DESTROY* alice and bob here
	}

	// keep writing for a while
	sleep(50);
	// stop writer
	keepWriting = false;
	writer.join();

	out("done");
}



void threading_tests()
{
	test_independent();
	test_deletion();
}