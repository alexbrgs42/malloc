# malloc


## 📖 About

I implemented my Dynamic Allocation Memory Management Library using C and a limited access to its functions !


## 📚 Resources

- [Malloc tutorial](https://wiki-prog.infoprepa.epita.fr/images/0/04/Malloc_tutorial.pdf)

## 💡 Features 

|✅ `malloc`, `realloc`, `calloc` :|
|------------------------------|
  - **AREAS**: Based on its size each allocation can either be stored on a **TINY AREA** or **SMALL AREA** which both have a capacity of at most 100 allocations, or in a **LARGE AREA** only maped for this allocation.|
  - **BEST FIT**: To find the position in **TINY** and **SMALL** areas, the best fit algorithm is performed in avoiding waste of space.
  - **ALIGNEMENT**: Memory is aligned in order to work with real programs.
  - **THREAD SAFE**: use of `mutex`.

|✅ `free` :|
|-------|
  - **DEFRAGMENTATION**: Freed memory is defragmented, merging with their left and/or right free neighbours if they exist.
  - **OPTIMIZATION**: After a first allocation, if every page is freed, an area will remain maped to prevent a loss of efficiency and an astonishing number of total page reclaims.
  - **THREAD SAFE**: use of `mutex`

|✅ `show_alloc_mem` :|
|-----------------|
  - **VISUALS**: State of the allocated memory zones.

    <img width="290" height="135" alt="Screenshot from 2025-07-23 15-56-03" src="https://github.com/user-attachments/assets/0c3ce659-f5df-4d04-ad85-0de96b662a45" />


## 🛠️ Installation

```bash
# Clone the repository
git clone git@github.com:alexbrgs42/malloc.git
cd malloc
```

```bash
# Build the project
make
```

## 🎯 Usage

```bash
# Run a test main:
$ export LD_LIBRARY_PATH="../"
$ ./test1
$ ./test2
$ ./test3
$ ./test4
$ ./test5
```

```bash
# Run a program in gdb
$ gdb /bin/ls
(gdb) set exec-wrapper env 'LD_LIBRARY_PATH=.' 'LD_PRELOAD=libft_malloc.so'
(gdb) run
```
