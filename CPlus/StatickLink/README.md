###  create the lib
```
gcc -c myfun1.c myfun2.c
ar -r libmyfuncs.a myfun1.o myfun2.o
```

### link
```
gcc -o myfunc -L. myfun.c -lmyfuncs
```

### test extern
```
gcc -c myfun1.c myfun2.c
ar -r libmyfunc1.a myfun1.o
ar -r libmyfunc2.a myfun2.o
```

```
gcc -o myfunc -L. myfun.c -lmyfunc1  -lmyfunc2
```
