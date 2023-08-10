// derived.c

#include <stdlib.h>
#include "derived.h"

Derived* Derived_create(int derivedVal)
{
    Derived* me = malloc(sizeof(Derived));
    Derived_init(me, derivedVal);
    return me;    
}

void Derived_init(Derived* const me, int derivedVal)
{
    static const struct BaseVtable vtable = {
        (void (*)(Base const* const me))&Derived_virtualFunc
    };
    Base_init(&me->super, "Derived");
    me->super.vptr = &vtable;
    
    me->attr.derivedVal = derivedVal;
}

void Derived_destroy(Derived* me)
{
    Derived_finalize(me);
    free(me);
}

void Derived_finalize(Derived* me)
{
    Base_finalize(&me->super);
}

void Derived_virtualFunc(Derived const* const me)
{
    /* specific implementation */
    (void)me;
}