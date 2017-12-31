#ifndef H_EVENT_LISTENER
#define H_EVENT_LISTENER

enum class MessengerEventType;

class MessengerEventListener
{
public:
	virtual void eventsCallback(MessengerEventType eventType) = 0;
};


#endif // !H_EVENT_LISTENER
