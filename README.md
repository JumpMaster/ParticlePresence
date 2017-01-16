# ParticlePresence

A library used to keep track of who is present in the home.

# How does it work?

By publishing events with the event name "presence" any listening Particle devices with the library will keep a record of who is and isn't home.  If a device restarts or comes out of standby it will request a status update for all Particle devices.

To send the updates a third party system will be required.  I myself use IFTTT to publish an event when devices are connected and disconnected from my Google WiFi router.  This has so far been extremely reliable.

# Supported commmands (data)

#### update

`update:username:location:timeofevent`

username is self explanatory.  Location is any string value.  timeofevent is the epoch time of the last change or 0 to signify the time as now.  The 0 will be replaced with the current epoch time.

#### request

`request`

This calls all particles to public their presence information.  Needs to have checks/delays added as to not send more then 4 publishes a second causing them to fail.

#### remove

`remove:username`

Removes a user from the system

# How to add it to a project

 - Add the two files precensemanager.cpp and presencemanager.h to your project.
 - Add `#include "presencemanager.h"` to your application.
 - Decare a PresenceManager object `PresenceManager pm`
 - Run `pm.setup()` and `pm.syncRequest()` in the `setup()` section of your code.

```
#include "PresenceManager.h"

PresenceManager pm;

void setup() {
  pm.setup();
  pm.syncRequest();
}

void loop() {
}
```

# How to use it
So you've added this to your projects.  You're using IFTTT (other services are available) to publish events when you arrive home/at work or when you connect to your IFTTT device.  But how can you use the data?

The are two commands for checking the information.

You wan't to know if anyone is at home so you can set the alarm?  Use the `isAnyone(String location)` function.

```
bool is_armed;
if (!pm.isAnyone("home") && !is_armed) {
  arm_the_alarm();
else if (pm.isAnyone("home") && is_armed) {
  disarm_the_alarm();
}
```

Or maybe you want to know if a specific user is at home.  Use the `isUser(String user, String location)` function.

```
bool safe_is_locked;
if (!pm.isUser("kevin", "home") && !safe_is_locked) {
  lock_the_safe();
} else if (pm.isUser("kevin", "home") && safe_is_locked) {
  unlock_the_safe();
}
```

Might not be the best idea to use this library to lock a safe but you get the idea.
