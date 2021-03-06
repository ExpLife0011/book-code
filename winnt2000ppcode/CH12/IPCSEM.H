// ****************************************************************************
//
// Module:  ipcsem.h
// Author:  Dick Lam
//
// Purpose: C++ class header file for ipcSemaphore
//
// Notes:  This is an abstract base class.  It is the interface class for
//         semaphores used in signalling between processes and threads.
//
// ****************************************************************************

#ifndef MODULE_ipcSemaphoreh
#define MODULE_ipcSemaphoreh

#include "ipcos.h"

// semaphore type designation and operation type
enum ipcSemaphoreType { unknown = 0, mutex = 1, event = 2 };
enum ipcSemaphoreOp { semcreate = 0, semaccess = 1 };

// forward declaration
class osSemaphore;

// class declaration
class EXPORT ipcSemaphore {

friend class osSemaphore;

public:

   // constructor and destructor
   ipcSemaphore(const char *name,            // unique name for semaphore
                ipcSemaphoreType type,       // mutex or event
                ipcSemaphoreOp operation);   // create or access the semaphore
   virtual ~ipcSemaphore();

   // methods for getting semaphore parameters [name, semaphore id, type
   // of semaphore (mutex or event) and whether this is the owner (creator)
   // of the semaphore]
   char *Name() const;
   unsigned long ID() const;
   ipcSemaphoreType Type() const;
   int Owner() const;

   // pure virtual query method for number of requests made for the semaphore
   // (must be redefined in derived classes)
   virtual unsigned long Query() = 0;

   // class version and object state data types
   enum version { MajorVersion = 1, MinorVersion = 0 };
   enum state { good = 0, bad = 1, badname = 2, notfound = 3 };

   // methods to get the object state
   inline int rdstate() const { return myState; }
   inline int operator!() const { return(myState != good); }

protected:

   osSemaphore *myImpl;    // implementation
   state myState;          // (object state (good, bad, etc.)

private:

   // private copy constructor and operator= (define these and make them
   // public to enable copy and assignment of the class)
   ipcSemaphore(const ipcSemaphore&);
   ipcSemaphore& operator=(const ipcSemaphore&);

};

#endif

// ****************************************************************************

// end of ipcsem.h
