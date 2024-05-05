#pragma once
#include "Observer.h"
class ScoreBoard : public Observer
{
public:
	int currentScore = 0;
	void onNotify(const GameObject& entity, Event event) {
		if (event == GAIN_SCORE) {
			currentScore++;
		}
	}
};

