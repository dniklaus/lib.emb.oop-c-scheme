#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "derived.h"

int main() 
{
  uint8_t n = 10;
  Base* b[n];

  /* create 10 objects of Derived type, assign them to an array of pointers to Base type */
  for (int i = 0; i < 10; i++)
  {
    char name[strlen("DerivedN")+1];
    sprintf(name, "Derived%i", i);
    b[i] = (Base*)Derived_create((const char*)name, i);
  }

  /* polymorph call to virtualFunc() on objects of Derived type (through I/F on Base type) */
  for (int i = 0; i < 10; i++)
  {
    b[i]->virtualFunc(b[i]);
  }

  /* clean-up */
  for (int i = 0; i < 10; i++)
  {
    Derived_destroy((Derived*)b[i]);
  }

  /* trials on a Base object */
  b[0] = Base_create("Base0");
  // b[0]->virtualFunc(b[0]);  /* would abort at run-time*/
  printf("Base - Name: %s\n", b[0]->getName(b[0]));
  Base_destroy(b[0]);

  return 0;
}