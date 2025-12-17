#include <stdio.h>
#include "derived.h"

int main() 
{
  Derived d1, d2;       /* multiple instances on stack of Derived */

  Derived_init(&d1, "Derived1", 1);  /* init d1 instance */
  Derived_init(&d2, "Derived2", 2);  /* init d2 instance */

  d1.printInfo(&d1);
  d2.printInfo(&d2);
  
  Derived_finalize(&d1);
  Derived_finalize(&d2);

  return 0;
}