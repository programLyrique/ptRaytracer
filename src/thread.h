/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

namespace rt
{

/** Creates a thread.
 * Just a wrapper around the C pthread library (Posix threads).
 * You have to inherit Thread, and implementing run(), which is the method
 * that will be executed in the thread.
 */
class Thread
{
    public:
        /** Default constructor */
        Thread();
        /** Default destructor */
        virtual ~Thread();

        /**
         * To use pthread functions that are not implemented in the class Thread.
         * @return a handle to the thread
         * @todo what if the pointer is NULL ?
         */
        pthread_t getHandle() const { return thread; }

        /**
         * Launches the thread.
         * @return false if the thread failed to execute, true otherwise.
         */
        bool exec();

        /** To wait for the thread to finish
         * @return false if it's not possible to wait for the end of the thread
         */
        bool join();

        /** Return the number of core available in the system
         * Works on Linux, Mac OS, and Windows. Maybe *BDS.
         */
        static unsigned int nbCores();
    protected:
        /**
         * Run will be executed by the thread.
         * Implement here what you want you thread to do.
         */
        virtual void run() = 0;
    private:
        pthread_t thread;
        /**
         * To wrap run() so that run() can be launched with pthread_create.
         * Has to be static because non static member functions have a hidden parameter which
         * points to the object.
         * @param a pointer to the current object !
         */
        static void * startRoutine(void * obj);
};

}
#endif // THREAD_H
