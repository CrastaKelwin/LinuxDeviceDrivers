Create a proc entry to blank out the first quantum of each scull device.

```
make clean
make
sudo sh scull_unload
sudo sh scull_load
cat /proc/scullmem
cat in.txt>/dev/scull0
cat in.txt>/dev/scull1
cat in.txt>/dev/scull2
cat in.txt>/dev/scull3
cat /dev/scull0
cat /dev/scull1
cat /dev/scull2
cat /dev/scull3
cat /proc/scullmem
cat /dev/scull0
cat /dev/scull1
cat /dev/scull2
cat /dev/scull3
```
