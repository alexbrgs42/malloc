# malloc

ressources: https://wiki-prog.infoprepa.epita.fr/images/0/04/Malloc_tutorial.pdf

To compile and run a test main:
```bash
$ cd tests
$ make
$ export LD_LIBRARY_PATH="../"
$ ./test1
$ ./test2
$ ./test3
$ ./test4
$ ./test5
```

To run a program in gdb:
```bash
$ gdb /bin/ls
(gdb) set exec-wrapper env 'LD_LIBRARY_PATH=.' 'LD_PRELOAD=libft_malloc.so'
(gdb) run
```
