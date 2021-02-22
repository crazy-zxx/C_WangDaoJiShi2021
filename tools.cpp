//
// Created by xylx on 2021/2/22.
//
#include <time.h>
#include "tools.h"

#if defined(WIN16) || defined(WIN32) || defined(WIN64)      //Windows
double getTime() {
    clock_t t;
    return (double)clock()/CLOCKS_PER_SEC*1000;
}

#elif defined(__linux__) || defined(__DARWIN_SUF_UNIX03)    //Linux 、 Unix 、 MacOS
#include <sys/time.h>   //提供struct timeval
double getTime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)(t.tv_sec * 1000000 + t.tv_usec)/1000;
}

#endif