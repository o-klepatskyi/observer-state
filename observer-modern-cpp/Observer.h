#pragma once
// Copyright (C) 2022 Klaus Iglberger - All Rights Reserved
// ---- <Observer.h> --------------------------------------------------------
#include <functional>
#include <exception>

template<class Subject, typename StateTag>
class Observer
{
public:
	using NotifyCallback = std::function<void(const Subject&, StateTag)>;

	explicit Observer(NotifyCallback onUpdate)
		: m_onNotify(std::move(onUpdate)) {
		if (!m_onNotify) {
			throw std::exception("You need to provide non-empty function.");
		}
	}

	void onNotify(const Subject& subject, StateTag property)
	{
		m_onNotify(subject, property);
	}

private:
	NotifyCallback m_onNotify;
};


