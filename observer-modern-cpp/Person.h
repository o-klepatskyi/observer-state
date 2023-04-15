#pragma once
// Copyright (C) 2022 Klaus Iglberger - All Rights Reserved
// ---- <Person.h> --------------------------------------------------------
#include "Subject.h"
#include "Observer.h"
#include <string>

enum class StateChange
{
	forenameChanged,
	surnameChanged,
	addressChanged
};

class Person : public Subject<Person, StateChange> {
public:
	using PersonObserver = Observer<Person, StateChange>;

	explicit Person(std::string forename, std::string surname)
		: forename_{ std::move(forename) },
		surname_{ std::move(surname) }
	{}

	void forename(std::string newForename) {
		forename_ = std::move(newForename);
		notify(StateChange::forenameChanged);
	}
	void surname(std::string newSurname)
	{
		surname_ = std::move(newSurname);
		notify(StateChange::surnameChanged);
	}

	void address(std::string newAddress)
	{
		address_ = std::move(newAddress);
		notify(StateChange::addressChanged);
	}

	std::string const& forename() const {
		return forename_;
	}
	std::string const& surname() const {
		return surname_;
	}
	std::string const& address() const {
		return address_;
	}

private:
	std::string forename_;
	std::string surname_;
	std::string address_ = {};
};