Eternity
========
Christian image viewer

Dependencies
-------------
On Debian system, execute following command to install dependencies. You will need to have
at least Debian Testing to have sufficient package versions, please check this 
[link](https://serverfault.com/a/382101) to get familiar with package pining if you are using stable
system:

```bash
sudo apt-get update && sudo apt-get install libglew-dev libglfw3-dev libcmocka-dev
```

Building
--------
```
cd Eternity
mkdir build && cd build
cmake ..
make
```

To build without unit tests, do `cmake -DEnableTesting=OFF ..` instead.
