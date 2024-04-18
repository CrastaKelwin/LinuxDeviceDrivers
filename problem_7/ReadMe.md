Modify lseek to move fops to the ith qpos of the first quantum. Suppose the call is lseek (fd, 5, SEEK_SET), move to the 5th quantum.

```
make clean
make
sudo sh scull_unload
sudo sh scull_load
gcc use_semaphore.c
cat main.c>/dev/scull0
cat /dev/scull0
./a.out
r
```
