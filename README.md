# Base64 Fileconvert

This is a simple C project that aims to be able to convert a file to/from
base64 encoding. 

## Quickstart

Simply use the `make` command to build the project, using the provided Makefile.
The executable name is `f2b64`, which stands for "file to base64". 

The executable takes a single argument: a path to a file. Provide this filepath
and you will receive the contents of the file as a base64-encoded string, as 
follows:

Contents of input file `testfile.txt`
```
abcdefg
abcdefg
abcdefg
abcdefg
1234567890
Stephen Flores

```

Output: 
```
$ f2b64 testfile.txt
Converting file: testfile.txt
YWJjZGVmZwphYmNkZWZnCmFiY2RlZmcKYWJjZGVmZwoxMjM0NTY3ODkwClN0ZXBoZW4gRmxvcmVzCg==
```