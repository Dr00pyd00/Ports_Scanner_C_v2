
// V2 

#include "scan.h"

#include <stdio.h>
#include <string.h>


#define TOTAL_WORKERS   8


int main(int argc, char **argv) {

    // arguments setup =========================================================================
    
    if ( argc < 2 ) {
    fprintf(stderr, "Bad Args!\nUsage: prog <host> <start> <end>\n");
    return 1;
    }

    const char* HOST = argv[1];
    int START = 1;
    int END = 63000;
    int i;

    if ( argc >= 3 ) {
        if (converStrToInt(argv[2], &START)) {
            fprintf(stderr, "your START is not a number\nDefault Start setup: %d\n", START);
        }
    }

    if ( argc >= 4 ) {
        if (converStrToInt(argv[3], &END)) {
            fprintf(stderr, "your END is not a number\nDefault End setup: %d\n", END);
        }
    }

    printf("Scanning on host:%s | start_port = %d | end_port = %d\n", HOST, START, END );

    // setup + start + end threads ================================================================
    
    struct scan_context myCtx; 
    memset(&myCtx, 0, sizeof(myCtx));
    myCtx.host = HOST;
    myCtx.next_port = START;
    myCtx.end_port = END;
    
    pthread_t threads[TOTAL_WORKERS];
    pthread_mutex_init(&myCtx.m, NULL);
    
    // loops for workers :
    for ( i = 0; i < TOTAL_WORKERS; i++ ) {
        pthread_create(&threads[i], NULL, worker, &myCtx);
    }

    for ( i = 0; i < TOTAL_WORKERS; i++ ) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&myCtx.m);

    return 0;
}



