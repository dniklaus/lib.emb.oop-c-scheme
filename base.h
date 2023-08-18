/* base.h */

#ifndef _BASE_H_
#define _BASE_H_

typedef struct Base Base;
typedef struct BaseVtable BaseVtable;               /* forward declaration of Base's virtual function table */
typedef struct BaseAttr
{
    char* name;
} BaseAttr;

struct Base
{
    BaseVtable const* vptr;                         /* Base's pointer to immutable virtual function table */
    BaseAttr attr;
    void (*virtualFunc)(Base const* const me);      /* interface function virtFunc() (pure virtual) */
    const char* (*getName)(Base const* const me);
};

/* Base's virtual function table */
struct BaseVtable
{
    void (*virtualFunc)(Base const* const me);      /* pointer to virtual function virtualFunc() */
};

/* Function prototypes */
Base* Base_create(const char* name);
void Base_init(Base* const me, const char* name);
void Base_destroy(Base* const me);
void Base_finalize(Base* const me);

const char* Base_getName(Base const* const me);

/* inline virtual call */
static inline void Base_virtualFunc_vcall(Base const* const me)
{
    (*me->vptr->virtualFunc)(me); /* late binding: calls the function in the current virtual table */
}

#endif
