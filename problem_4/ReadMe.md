Display the first 50 characters of the first quantum of each of the 4 scull devices using proc filesystem.

```
make clean
make
sudo sh scull_unload
sudo sh scull_load
cat in.txt>/dev/scull0
cat in.txt>/dev/scull1
cat in.txt>/dev/scull2
cat in.txt>/dev/scull3
cat /proc/scullmem
```
