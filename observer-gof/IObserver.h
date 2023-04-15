#pragma once
// ---- <IObserver.h> --------------------------------------------------------

class IObserver {
public:
	virtual ~IObserver() {}

	virtual void onNotify() = 0;
};