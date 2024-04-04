Implement an ioctl command to change the first and second pointers in the first sculldev of the scull device.

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
