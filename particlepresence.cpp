#include "presencemanager.h"
#include "application.h"

PresenceManager::PresenceManager() : publishTimer(1000, &PresenceManager::PublishTimerCallback, *this, true) {}

void PresenceManager::setup() {
    bool result = Particle.subscribe("presence", &PresenceManager::handler, this, MY_DEVICES);    /*
    if (result)
        Particle.publish("LOG", "subscribe succeeded", 60, PRIVATE);
    else
        Particle.publish("LOG", "subscribe failed", 60, PRIVATE);
    */
}

void PresenceManager::syncRequest() {
    Particle.publish("presence", "request", 60, PRIVATE);
}

void PresenceManager::PublishTimerCallback() {
    Particle.publish("presence", String::format("update:%s:%s:%d", users[nextPublishId].name.c_str(), users[nextPublishId].location.c_str(), users[nextPublishId].lastUpdated), 60, PRIVATE);
    nextPublishId++;
    
    if (nextPublishId < users.size())
        publishTimer.reset();
    else
        nextPublishId = 0;
}

void PresenceManager::handler(const char *eventName, const char *data) {
    
    String command = data;
    
    if (command.startsWith("update")) { // update:username:home:0
        int nameEnd = command.indexOf(":", 7);
        String name = command.substring(7, nameEnd);
        String location = command.substring(nameEnd+1, command.lastIndexOf(":"));
        long updated = command.substring(command.lastIndexOf(":")+1).toInt();
        
        if (updated == 0)
            updated = Time.now();
            
        for (int i = 0; i < users.size(); i++) {
            if (users[i].name.equals(name)) {
                if (updated > users[i].lastUpdated) {
                    users[i].lastUpdated = updated;
                    users[i].location = location;
                }
                name = NULL;
            }
        }
        
        if (name != NULL) {
            User new_user;
            new_user.name = name;
            new_user.lastUpdated = updated;
            new_user.location = location;
            users.push_back(new_user);
        }

        //Particle.publish("handler", String::format("User %s is %s at %d", user.c_str(), isHome ? "home" : "away", update), 60, PRIVATE);
    } else if (command.startsWith("remove")) { // rempve:username
        String name = command.substring(command.indexOf(":")+1);
        
        for (int i = 0; i < users.size(); i++) {
            if (users[i].name.equals(name)) {
                users.erase(users.begin() + i);
            }
        }
    
    } else if (command.startsWith("request")) { // request
        if (users.size() > 0)
            PublishTimerCallback();
    }
}

bool PresenceManager::isAnyone(String location) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].location.equals(location))
            return true;
    }
    
    return false;
}


bool PresenceManager::isEveryone(String location) {
    for (int i = 0; i < users.size(); i++) {
        if (!users[i].location.equals(location))
            return false;
    }
    
    return true;
}

bool PresenceManager::isUser(String user, String location) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].name.equals(user) && users[i].location.equals(location))
            return true;
    }
    
    return false;
}