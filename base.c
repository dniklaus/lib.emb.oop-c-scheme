// base.c

#include <stdlib.h>
#include <string.h>
#include "base.h"

static void Base_virtualFunc(Base const* const me);

Base* Base_create(const char* name)
{
    Base* me = malloc(sizeof(Base));
    Base_init(me, name);
    return me;
}

void Base_init(Base* const me, const char* name)
{
    static const struct BaseVtable vtable = {
        &Base_virtualFunc
    };
    me->vptr = &vtable;
    
    me->attr.name = malloc(strlen(name)+1);
    memcpy(me->attr.name, name, strlen(name));
    me->attr.name[strlen(name)] = '\0';
    
    me->virtualFunc = &Base_virtualFunc_vcall;
    me->getName = &Base_getName;
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

void Base_virtualFunc(Base const* const me)
{
    (void)me;
}

const char* Base_getName(Base const* const me)
{
    return me->attr.name;
}