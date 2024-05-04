#pragma once
#include "GameObject.h"
#include "Observer.h"
#include <vector>
class Subject
{
private:
	std::vector<Observer*> observers_;
	int numObservers_;
public:
	//Subject() {
	//	numObservers_
	//}
	void addObserver(Observer* observer)
	{
		// Add to array...
		observers_.push_back(observer);
		numObservers_++;
	}

	void removeObserver(Observer* observer)
	{
		// Remove from array...
		observers_.erase((std::find(observers_.begin(),observers_.end(),observer),observers_.end()));
	}
protected:
	void notify(const GameObject& entity, Event event)
	{
		for (int i = 0; i < numObservers_; i++)
		{
			observers_[i]->onNotify(entity, event);
		}
	}

};

class Physics : public Subject
{
public:
	//void updateEntity(GameObject& entity) {
	//	notify(entity,EVENT_TOUCH);
	//}
};

