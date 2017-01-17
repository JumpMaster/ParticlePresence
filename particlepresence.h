#ifndef __PRESENCEMANAGER_H__
#define __PRESENCEMANAGER_H__

#include "application.h"

struct User
{
  public:
    String name;
	long lastUpdated = 1;
	String location;
};

class PresenceManager
{
  public:
    PresenceManager();
    void setup();
    void handler(const char *eventName, const char *data);
    void syncRequest();
    bool isAnyone(String location);
    bool isEveryone(String location);
    bool isUser(String name, String location);
  protected:
    void PublishTimerCallback();
    std::vector<User> users;
    Timer publishTimer;
    int nextPublishId;
};

#endif  // End of __PRESENCEMANAGER_H__ definition check