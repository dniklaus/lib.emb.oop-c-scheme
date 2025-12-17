/* base.c */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "base.h"

/* pure virtual function virtFunc(), local (not accessible outside this source file) */
static void Base_virtualFunc(Base const* const me);

Base* Base_create(const char* name)
{
    Base* me = malloc(sizeof(Base));
    Base_init(me, name);
    return me;
}

void Base_init(Base* const me, const char* name)
{
    /* static const (immutable) virtual function table allocation, kept in ROM */
    static const BaseVtable vtable = {
        .virtualFunc = Base_virtualFunc        /* initialize pointer to local pure virtualFunc() impl. */
    };
    me->vptr = &vtable;                        /* default assignment to own virtual table */
    me->virtualFunc = Base_virtualFunc_vcall;  /* assign I/F with pointer to inline virtual call */
    
    me->attr.name = malloc(strlen(name)+1);
    memcpy(me->attr.name, name, strlen(name));
    me->attr.name[strlen(name)] = '\0';
    
    me->getName = Base_getName;
}

void Base_destroy(Base* me)
{
    Base_finalize(me);
    free(me);
}

void Base_finalize(Base* me)
{
    free(me->attr.name);
}

/* empty "implementation" of the pure virtual function virtFunc() */
void Base_virtualFunc(Base const* const me)
{
    (void)me;   /* avoid compiler warnings regarding unused parameter */
    assert(0);  /* pure virtual function, shall never be called */
}

const char* Base_getName(Base const* const me)
{
    return me->attr.name;
}