// derived.h

#ifndef _DERIVED_H_
#define _DERIVED_H_

#include "base.h"

typedef struct Derived Derived;

typedef struct DerivedAttr DerivedAttr;
struct DerivedAttr
{
    int derivedVal;
};

struct Derived
{
    Base super;
    DerivedAttr attr;
};

Derived* Derived_create(int derivedVal);
void Derived_init(Derived* const me, int derivedVal);
void Derived_destroy(Derived* me);
void Derived_finalize(Derived* me);

void Derived_virtualFunc(Derived const* const me);

#endif
