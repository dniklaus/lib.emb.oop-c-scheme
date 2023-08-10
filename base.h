// base.h

#ifndef _BASE_H_
#define _BASE_H_

typedef struct Base Base;
typedef struct BaseAttr
{
    char* name;
} BaseAttr;

struct Base
{
    struct BaseVtable const* vptr;
    BaseAttr attr;
    void (*virtualFunc)(Base const* const me);
    void (*getName)(Base const* const me);
};

struct BaseVtable
{
    void (*virtualFunc)(Base const* const me);
};

/* Function prototypes */
Base* Base_create(const char* name);
void Base_init(Base* const me, const char* name);
void Base_destroy(Base* const me);
void Base_finalize(Base* const me);

void Base_getName(Base const* const me);

/* inline virtual calls (-> late binding) */
static inline void Base_virtualFunc_vcall(Base const* const me)
{
    (*me->vptr->virtualFunc)(me);
}

#endif
