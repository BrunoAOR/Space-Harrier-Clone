#include "Messenger.h"

#include "Engine/globals.h"
#include "MessengerEventListener.h"
#include "MessengerEventType.h"


std::map<MessengerEventType, std::list<MessengerEventListener*>> Messenger::m_listenersMap;


bool Messenger::addListener(MessengerEventListener * listener, MessengerEventType eventType)
{
	if (m_listenersMap.count(eventType) == 0)
	{
		m_listenersMap[eventType].push_back(listener);
	}
	else
	{
		std::list<MessengerEventListener*>& list = m_listenersMap[eventType];
		if (std::find(list.begin(), list.end(), listener) == list.end())
		{
			list.push_back(listener);
		}
		else
		{
			OutputLog("WARNING: Attempting to add an event listener for an event for which said listener is already included! Nothing will happen.");
			return false;
		}
	}
	return true;
}


bool Messenger::removeListener(MessengerEventListener * listener, MessengerEventType eventType)
{
	if (m_listenersMap.count(eventType) == 1)
	{
		std::list<MessengerEventListener*>& list = m_listenersMap[eventType];
		auto it = std::find(list.begin(), list.end(), listener);
		if (it != list.end())
		{
			list.erase(it);
			if (list.size() == 0)
			{
				m_listenersMap.erase(eventType);
			}
			return true;
		}
	}
	OutputLog("WARNING: Attempting to remove an event listener which is not actually listening to the requested event! Nothing will happen.");
	return false;	
}


bool Messenger::broadcastEvent(MessengerEventType eventType)
{
	bool broadcasted = false;
	for (MessengerEventListener* listener : m_listenersMap[eventType])
	{
		listener->eventsCallback(eventType);
		broadcasted = true;
	}
	return broadcasted;
}
