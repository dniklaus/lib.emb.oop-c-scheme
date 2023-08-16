/* derived.c */

#include <stdlib.h>
#include <stdio.h>
#include "derived.h"

Derived* Derived_create(const char* name, int val)
{
    Derived* me = malloc(sizeof(Derived));
    Derived_init(me, name, val);
    return me;    
}

void Derived_init(Derived* const me, const char* name, int val)
{
    static const struct BaseVtable vtable = {
        (void (*)(Base const* const me))&Derived_virtualFunc
    };
    Base_init(&me->super, name);
    me->super.vptr = &vtable;
    
    me->attr.derivedVal = val;

    me->printInfo = &Derived_printInfo;
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
    me->printInfo(me);
}

void Derived_printInfo(Derived const* const me)
{
    printf("Name: %s - Val: %i\n", me->super.getName(&me->super), me->attr.derivedVal);
}