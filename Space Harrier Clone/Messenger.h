#ifndef H_MESSENGER
#define H_MESSENGER

#include <string>
#include <map>
#include <list>
class MessengerEventListener;
enum class MessengerEventType;


class Messenger
{
public:
	static bool addListener(MessengerEventListener* listener, MessengerEventType eventType);
	static bool removeListener(MessengerEventListener* listener, MessengerEventType eventType);
	static bool broadcastEvent(MessengerEventType eventType);

private:
	Messenger() {}
	static std::map<MessengerEventType, std::list<MessengerEventListener*>> m_listenersMap;
};


#endif // !H_MESSENGER
