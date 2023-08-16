#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "base.h"
#include "derived.h"

int main() 
{
  uint8_t n = 10;
  Base* b[n];

  for (int i = 0; i < 10; i++)
  {
    char name[strlen("DerivedN")+1];
    sprintf(name, "Derived%i", i);
    b[i] = (Base*)Derived_create((const char*)name, i);
  }

  for (int i = 0; i < 10; i++)
  {
    b[i]->virtualFunc(b[i]);
  }

  for (int i = 0; i < 10; i++)
  {
    Derived_destroy((Derived*)b[i]);
  }

  return 0;
}