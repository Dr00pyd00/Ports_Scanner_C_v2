
#ifndef SCANNER_H
#define SCANNER_H


#include <netinet/in.h>
#include <pthread.h>

// Structs ====================================================

struct scan_context {
    const char *host;
    int next_port;
    int end_port;
    pthread_mutex_t m;
};



// Declarations ===============================================

int converStrToInt(char* str, int* dst);

void *worker(void *args);



#endif




