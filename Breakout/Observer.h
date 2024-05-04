#pragma once
#include "GameObject.h"
enum Event {
	SCORE,
	MILESTONE
};
class Observer
{
public:
	virtual ~Observer() {}
	//virtual void onNotify(const GameObject& entity, Event event) = 0;
	virtual void onNotify(const GameObject& entity, Event event);
};

