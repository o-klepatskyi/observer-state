// Copyright (C) 2022 Klaus Iglberger - All Rights Reserved
#include "Person.h"
#include <iostream>

int main() {
	using PersonObserver = Person::PersonObserver;

	Person person("Bjarne", "Stroustrup");

	PersonObserver fornameObserver([](const Person& person, StateChange state) {
			if (state == StateChange::forenameChanged) {
				std::cout << "[forename] Forename changed: " << person.forename() << "\n";
			}
		}
	);

	PersonObserver fullNameObserver([](const Person& person, StateChange state) {
			if (state == StateChange::forenameChanged) {
				std::cout << "[fullname] Forename changed: " << person.forename() << "\n";
			}
			if (state == StateChange::surnameChanged) {
				std::cout << "[fullname] Surname changed: " << person.surname() << "\n";
			}
		}
	);

	PersonObserver addressObserver([](const Person& person, StateChange state) {
			if (state == StateChange::addressChanged) {
				std::cout << "[address] Address changed: " << person.address() << "\n";
			}
		}
	);

	person.attach(&fornameObserver);
	person.attach(&fullNameObserver);
	person.attach(&addressObserver);

	person.address("Aarhus, Denmark");
	person.surname("Gottschling");
	person.forename("Peter");

	return 0;
}