#include "thread.h"

#ifdef _WIN32
#include <windows.h>
#elif MACOS
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#endif


namespace rt
{


Thread::Thread() : thread(0)
{

}

Thread::~Thread()
{
    //dtor
}

bool Thread::exec()
{
    return pthread_create(thread, 0, startRoutine, this) == 0;
}

bool Thread::join()
{
    if(thread != 0) // Le thread existe.
        return pthread_join(*thread, 0) == 0;
    else
        return false;
}

void * Thread::startRoutine(void * obj)
{
    Thread * t = static_cast<Thread*> (obj);
    t->run ();
    return 0;
}

unsigned int nbCores()
{
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif MACOS
    int nm[2];
    size_t len = 4;
    uint32_t count;

    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);

    if(count < 1) {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if(count < 1) { count = 1; }
    }
    return count;
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}


}
