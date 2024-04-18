Implement an ioctl command to empty the scull device( use scull trim).

```
make clean
make
sudo sh scull_unload
sudo sh scull_load
gcc use_semaphore.c
cat in.txt>/dev/scull0
cat /dev/scull0
./a.out
w
cat /dev/scull0
```
