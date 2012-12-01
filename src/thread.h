#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>


/** Creates a thread.
 * Just a wrapper around the C pthread library (Posix threads).
 */
class Thread
{
    public:
        /** Default constructor */
        Thread();
        /** Default destructor */
        virtual ~Thread();

        /** Return the number of core available in the system
         * Works on Linux, Mac OS, and Windows. Maybe *BDS.
         */
        static unsigned int nbCores();
    protected:
    private:
};

#endif // THREAD_H
