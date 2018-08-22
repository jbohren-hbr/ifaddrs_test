ifaddrs_test
============

Build:
```
mkdir build
cd build && cmake .. && make
```

Run test:
```
./test.bash
```

Test returns 0 if `ifconfig` matches the output of `getifaddrs` and 1 if not, and prints the diff to stderr.

Running `./build/print_ifaddrs` will print the interface names and their associated IP addresses.
