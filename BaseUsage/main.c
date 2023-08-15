#include "Base.h"
#include <stdio.h>
int main() 
{
  Base b1, b2;              /* multiple instances of Base */
  Base_init(&b1, "Base1");  /* init b1 instance */
  Base_init(&b2, "Base2");  /* init b2 instance */
  printf("Base b1 - Name: %s", b1.getName(&b1));
  printf("Base b2 - Name: %s", b2.getName(&b2));
}
