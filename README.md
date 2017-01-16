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

# How to use it

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
