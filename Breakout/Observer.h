#pragma once
#include "GameObject.h"
#include "Define.h"

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(const GameObject& entity, Event event) = 0;
};

