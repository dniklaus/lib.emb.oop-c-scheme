// derived.h

#ifndef _DERIVED_H_
#define _DERIVED_H_

#include "base.h"     /* the base class interface */

typedef struct Derived Derived;
typedef struct DerivedAttr 
{
    int derivedVal;
} DerivedAttr;

struct Derived
{
    Base super;       /* inherits Base, must be at this struct's first position */
    DerivedAttr attr;
    void (*printInfo)();
};

Derived* Derived_create(const char* name, int val);
void Derived_init(Derived* const me, const char* name, int val);
void Derived_destroy(Derived* me);
void Derived_finalize(Derived* me);

void Derived_virtualFunc(Derived const* const me);

void Derived_printInfo(Derived const* const me);

#endif
