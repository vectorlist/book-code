// ****************************************************************************
//
// Module:  osqueue.h
// Author:  Dick Lam
//
// Purpose: C++ class header file for osMessageQueue
//
// Notes:  This is a base class.  It contains general implementation methods
//         for message queues for sending messages between processes.
//
// ****************************************************************************

#ifndef MODULE_osMessageQueueh
#define MODULE_osMessageQueueh

#include "ipcqueue.h"

// forward declaration
class ipcEventSemaphore;

// class declaration
class osMessageQueue {

public:

   // constructors and destructor
   osMessageQueue(ipcMessageQueue *interface, const char *name);
   osMessageQueue(ipcMessageQueue *interface, const char *name,
                  unsigned long powner);
   virtual ~osMessageQueue();

   // methods for accessing the queue and queue parameters [name, queue id,
   // queue owner process id, and whether this is the owner (creator)]
   char *Name() const;
   unsigned long ID() const;
   unsigned long Pid() const;
   int Owner() const;

   // read/write methods for the queue (only a queue owner may read from
   // the queue, and only queue clients may write to a queue)
   virtual int Read(void *data, long datasize, int wait);
   virtual int Write(void *data, long datasize);

   // methods to examine and remove messages from the queue
   virtual unsigned long Peek();
   virtual int Purge();

protected:

   ipcMessageQueue *myInterface;        // pointer to the interface instance
   unsigned long myPid;                 // process id of queue owner
   unsigned long myID;                  // id of queue
   char *myName;                        // queue name
   int isOwner;                         // flag indicating owner

   ipcEventSemaphore *mySem;            // required for OS/2 only

   // methods for handling the message queue
   void CreateQueue();
   void OpenQueue();
   void CloseQueue();

private:

   // private copy constructor and operator= (define these and make them
   // public to enable copy and assignment of the class)
   osMessageQueue(const osMessageQueue&);
   osMessageQueue& operator=(const osMessageQueue&);

};

#endif

// ****************************************************************************

// end of osqueue.h
