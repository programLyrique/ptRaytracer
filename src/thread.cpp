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

}

bool Thread::exec()
{
    return pthread_create(&thread, NULL, startRoutine, this) == 0;
}

bool Thread::join()
{
    if(thread != 0) // Le thread existe, car on espère que 0 n'est pas une valeur valide d'identifiant de thread
        return pthread_join(thread, NULL) == 0;
    else
        return false;
}

void * Thread::startRoutine(void * obj)
{
    Thread * t = static_cast<Thread*> (obj);
    t->run ();
    return NULL;
}

unsigned int Thread::nbCores()
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

bool Mutex::lock()
{
    return pthread_mutex_lock(&mutex) == 0;
}

bool Mutex::unlock()
{
    return pthread_mutex_unlock(&mutex) == 0;
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&mutex);
}

}
