#pragma once
// by Tony Van Eerd
#include "Subject.h"
#include "ThreadsafeOut.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

struct MyListener : Subject::Listener {
	std::string name;
	MyListener(std::string name) : name(name) { }
	void onNotify(std::string s) override {
		lout(s, name);
	}
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

	MyListener alice("alice");
	MyListener bob("bob");
	Subject foo;

	foo.addListener(&alice);
	foo.addListener(&bob);

	auto writing = [](Subject* foo, std::string tname) {
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

	auto listening = [](Subject::Listener* listener) {
		listener->for_every_change();
	};

	std::atomic<bool> stuff_to_do = true;

	auto listening_detail = [&](Subject::Listener* listener) {
		while (stuff_to_do)
		{
			listener->check_for_change();
			do_other_stuff();
		}
	};

	std::thread writer(writing, &foo, "writer");

	std::thread listener1(listening, &alice);
	std::thread listener2(listening_detail, &bob);

	writer.join();
	// writing done, stop the listener threads
	alice.stop();
	stuff_to_do = false;
	listener1.join();
	listener2.join();
	out("done");
}

void test_deletion()
{
	out("--------- test deletion");

	Subject foo;

	std::atomic<bool> keepWriting = true;
	auto writing = [&keepWriting](Subject* foo, std::string tname) {
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
		MyListener alice("alice");
		MyListener bob("bob");

		foo.addListener(&alice);
		foo.addListener(&bob);

		auto listening = [](Subject::Listener* listener) {
			listener->for_every_change();
		};

		std::atomic<bool> stuff_to_do = true;

		auto listening_detail = [&](Subject::Listener* listener) {
			while (stuff_to_do)
			{
				listener->check_for_change();
				do_other_stuff();
			}
		};

		std::thread listener1(listening, &alice);
		std::thread listener2(listening_detail, &bob);

		// wait a while
		sleep(200);

		foo.removeListener(&alice);
		foo.removeListener(&bob);

		// stop alice and bob
		alice.stop();
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