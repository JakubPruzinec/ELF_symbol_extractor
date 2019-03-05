# ELF_symbol_extractor
Simple elf symbols extraction demonstration tool. `nm` dumps ELF object file symbols information to standard output. `nm` supports both, 32bit and 64bit ELF files.  
Output: [value | bind | type | name]  
  
Dependencies: elfutils  
  
Installation, execution and removal:  
```
$ sudo apt-get install -y elfutils libelf-dev     // ubunutu-based only
$ make
$ ./nm <elf-file>
$ make clear                                      // uninstall
```
  
Don't forget to checkout:  
http://refspecs.linuxbase.org/elf/elf.pdf  
https://github.com/kushaldas/elfutils/blob/master/libelf/gelf.h  
https://github.com/kushaldas/elfutils/blob/master/libelf/libelf.h  
ftp://ftp2.uk.freebsd.org/sites/downloads.sourceforge.net/e/el/elftoolchain/Documentation/libelf-by-example/20120308/libelf-by-example.pdf  
https://docs.oracle.com/cd/E19683-01/817-0679/6mgfb878d/index.html
