
# Tcp Port Scanner in C

This is a little project in C.  
For learn:
- low level socket 
- threads 
- concurrence race (mutex)

---

### How to build 

```bash 
make 
```

or 

```bash 
gcc -Wall -Wextra -pedantic -g -pthread scan.c main.c -o prog
```
- `-pthread` flag is required for use the lib.


---

### How to run

Usage:
```
./prog <host> [start_port] [end_port]
```

- `host`: target IPv4 address ( ie: 127.0.0.1 )
- `start_port`: first port to scan ( default = 1 )
- `end_port`: last port to scan ( default = 63000 )


**Example:** 

```bash 
./prog 192.168.1.10 1 1000
```

Only open port are printed.

---

### How it work 

I learned to use a **worker pool** ( 8 threads here ), passing a struct as args.  
The counter is in the struct, and a function with a mutex update the counter for nexts iterations.  
Each iterations setup a socket and try connect to the port and them print when the connect() is a success.

---

#### Memory leaks:
Tested by:

```bash
valgrind --leak-check=full ./prog 127.0.0.1 1 1000
valgrind --tool=helgrind   ./prog 127.0.0.1 1 1000
```


#### Limitations: 

This is a V2 project, the V1 was just very simple sequencial socket calls.  

- This is Tcp only and IPv4 only.
- Two return `open` or `close` : need to updgrade in futur for see better filters.
- Ephemerals ports using by the programme himself are detected, can be confusing.
- No port range validation for now ( trust the user, bad idea! ).


#### Structure:

```
scan.h  --> declarations usefuls for main.c only
scan.c  --> declarations for static functions + all implementations
main.c  --> arguments parsing and orchestration ( threads )
Makefile 
```




