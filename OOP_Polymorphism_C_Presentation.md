# OOP and Polymorphism in C

---

## Title
- Object-Oriented Programming and Polymorphism in C
- Dieter Niklaus, 2025-12-17

---
## Agenda
- Motivation
- The three main OOP concepts
- OOP with C
- Usage Example
  
---

## Motivation
- Structure large projects
- Reusability & maintainability
- GOF Patterns
- enable OOP with C

---

## The three main OOP concepts
- Encapsulation
- Inheritance
- Polymorphism

---

## Encapsulation
- Combine data and the functions working on that data
- Interface for access control, ensure controlled access to member values and functions
- Reveal only information about the "what" (functionality) of a class, but not the "how" (the internal representation)
- Defines an interface to the outside and document it at the same time
- Provide significantly improved testability, stability, changeability, and maintainability of the software or its modules

---

## Inheritance
- Derive new "classes" from existing ones
- Add new functionality to the base class by the implementation of the derived class

---

## Polymorphism
- Uniform interface, different implementations
- Builds directly on inheritance

---

## OOP with C – Overview
- struct as class
- Function pointers for methods
- Vtable concept for polymorphism

---

## Encapsulation in C (Example)
- struct + function pointers

```c
typedef struct Base Base;
typedef struct BaseAttr BaseAttr;

struct BaseAttr 
{
    char* name;
}

struct Base 
{
    BaseAttr attr;
    const char* (*getName)(Base const* const me);
} ;
```

---

## Inheritance in C (Example)
- struct embedding: base class as first member

```c
typedef struct Derived Derived;
typedef struct DerivedAttr DerivedAttr;

struct DerivedAttr 
{
    int derivedVal;
} 

struct Derived
{
    Base super; // "Inheritance"
    DerivedAttr attr;
    void (*printInfo)(Derived const* const me);
}
```

## Polymorphism in C 
- Virtual function table
- Function pointers in a  for late binding

---

## Polymorphism in C - Base - Example
- header base.h
```c
typedef struct Base Base;
typedef struct BaseAttr BaseAttr;
typedef struct BaseVtable BaseVtable;

struct BaseAttr 
{
    char* name;
}

struct Base 
{
    BaseVTable const* vptr;
    BaseAttr attr;
    void (*virtualFunc)(Base const* const me);      // void virtualFunc(): I/F, will be impl. by Derived
    const char* (*getName)(Base const* const me);   // const char* getName()
} ;

struct BaseVtable 
{
    void (*virtualFunc)(Base const* const me);
};

// inline virtual Call:
static inline void Base_virtualFunc_vcall(Base const* const me)
{
    (*me->vptr->virtualFunc)(me);   // late binding: calls the func in the current virtual table
}
```
- source base.c
```c
static void Base_virtualFunc(Base const* const me);

void Base_init(Base* const me, const char* name)
{
    /* static const (immutable) virtual function table allocation, kept in ROM */
    static const BaseVtable vtable = {
        .virtualFunc = Base_virtualFunc         /* initialize pointer to local pure virtualFunc() */
    };
    me->vptr = &vtable;                         /* default assignment to own virtual table */
    me->attr.name = malloc(strlen(name)+1);
    memcpy(me->attr.name, name, strlen(name));
    me->attr.name[strlen(name)] = '\0';

    me->virtualFunc = Base_virtualFunc_vcall;  /* assign I/F with pointer to inline virtual call */
    
    me->getName = Base_getName;
}

/* empty "implementation" of the pure virtual function virtFunc() */
void Base_virtualFunc(Base const* const me)
{
    (void)me; /* avoid compiler warnings regarding unused parameter */ 
    assert(0); /* pure virtual function, shall never be called */
}

const char* Base_getName(Base const* const me) 
{
    return me->attr.name;
}

```

---

## Polymorphism in C - Derived - Example
- Header file derived.h
```C
#include "base.h"     /* the base class interface */
struct DerivedAttr;
{
    int derivedVal;
} DerivedAttr;

typedef struct Derived
{
    Base super;       /* inherits Base, must be at first position */
    DerivedAttr attr;
    void (*printInfo)(Derived const* const me);
} Derived;

void Derived_virtualFunc(Derived const* const me);
void Derived_printInfo(Derived const* const me);

```

- Source file derived.c
```C
void Derived_init(Derived* const me, const char* name, int val)
{
    /* static const (immutable) virtual func. table allocation, kept in ROM */
    static const BaseVtable vtable = {
        /* init ptr to own virtualFunc() impl. with "me" upcast */
        .virtualFunc = (void (*)(Base const* const me))Derived_virtualFunc 
    };
    Base_init(&me->super, name);
    
    /* assign own vtable to Base's vptr (overwrite) */
    me->super.vptr = &vtable;
    
    me->attr.derivedVal = val;
    
    me->printInfo = Derived_printInfo;
}

/* Derived's specific implementation of virtualFunc() */
void Derived_virtualFunc(Derived const* const me)
{
    me->printInfo(me);
}

void Derived_printInfo(Derived const* const me)
{
    printf("Name: %s - Val: %i\n", me->super.getName(&me->super), me->attr.derivedVal);
}
```

---

## Naming conventions & idioms
- Prefixes: Base_, Derived_
- struct types: Base, Derived, BaseVtable
- Methods as function pointers in struct

---

## Example: Polymorphic array

```c
Base* b[10];

// create objects on Heap
for (int i = 0; i < 10; i++) {
    b[i] = (Base*)Derived_create();
}

// use objects
for (int i = 0; i < 10; i++) {
    b[i]->doWork(b[i]);
}

// clean-up 
for (int i = 0; i < 10; i++) {
    Derived_destroy(b[i]);
}
```

```C
// create objects on Stack
Derived1 d1;
Derived2 d2;
Derived3 d3;

// initialize the objects
Derived1_init(&d1);
Derived2_init(&d2);
Derived3_init(&d3);

// use the objects
Base* b[3];
    b[0] = &d1;
    b[1] = &d2;
    b[2] = &d3;

for (int i = 0; i < 3; i++) {
    b[i]->doWork(b[i]);
}
```

---

## Conclusion
- OOP concepts possible in C
- Requires discipline and conventions

---

## Questions?
