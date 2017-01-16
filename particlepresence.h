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
    bool isUser(String name, String location);
  protected:
    std::vector<User> users;
};

#endif  // End of __PRESENCEMANAGER_H__ definition check