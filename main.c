#include <stdio.h>
#include <stdlib.h>
#include <tinyalloc.h>

/* Import user configuration: */
#ifdef __Unikraft__
#include <uk/config.h>
#endif /* __Unikraft__ */

#include "msp430.h"
extern int _my_fram_begin, _my_fram_end;



int main(__unused int argc, __unused char *argv[])
{
  printf("Hello World!\n");
  printf("Trying to allocate 50 Bytes (handler: 16)...\n");
  void* ptr = pmalloc(16, 50);
  if( ptr != 0) {
    printf("Allocation successful!, ptr is: %p\n", ptr);
  } else {
    printf("Allocation unsuccessful!, ptr is: 0x0\n");
  }
  printf("Freeing allocation (handler: 16)...\n");
  pfree(16);

}
