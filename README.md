# Rename
A C++ utility that is used to possibly rename many files at once.

## Compilation
In order to compile the program:

```bash
$ clang++ massRename.cpp -o rename -std=c++17
```

If compiling on Linux, then you need to enable to experimental flag `-lstdc++fs`.

## Usage
In order to run the program:
```bash
./rename file1,file2,fil3 file4,file5,file6
```

This will rename:
 - file1 to file4,
 - file2 to file5,
 - file3 to file6.

## To do 
 - [ ] Add functionality for specifying one name for all renamed files
