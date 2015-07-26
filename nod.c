/****************************************************************************/
/* nod.c --- nod (node for C language)                                      */
/****************************************************************************/
/* [History]                                                                */
/* 2015.07.22: katahiromz creates v0.                                       */
/* 2015.07.25: katahiromz creates v1.                                       */
/****************************************************************************/

#ifdef __cplusplus
    #include <cstdlib>
    #include <cstring>
    #include <cassert>
#else
    #include <stdlib.h>
    #include <string.h>
    #include <assert.h>
#endif

#include "nod.h"

/****************************************************************************/

PNOD nod_new(const void *data, size_t data_size)
{
    PNOD p = (PNOD)calloc(sizeof(NOD) + data_size, 1);
    if (p != NULL)
    {
        p->next = NULL;
        p->prev = NULL;
        p->data_size = data_size;
        if (data != NULL)
        {
            memcpy(nod_data(p), data, data_size);
        }
    }
    return p;
}

void nod_delete_chain(PNOD p)
{
    PNOD next;
    PNOD x = p;
    while (x != NULL)
    {
        next = x->next;
        nod_delete(x);
        x = next;
    }
}

PNOD nod_advance(PNOD p, size_t count)
{
    PNOD x = p;
    while (count-- > 0U)
    {
        if (x == NULL)
        {
            break;
        }
        x = x->next;
    }
    return x;
}

size_t nod_distance(const NOD *p1, const NOD *p2)
{
    const NOD *x = p1;
    size_t count = 0U;
    while (x != NULL)
    {
        if (x == p2)
        {
            break;
        }
        x = x->next;
        ++count;
    }
    if (x == NULL)
    {
        count = (size_t)-1;
    }
    return count;
}

PNOD nod_clone(const NOD *p)
{
    PNOD created = nod_new(nod_const_data(p), nod_data_size(p));
    assert(created != NULL);
    return created;
}

size_t nod_chain_length(const NOD *p)
{
    const NOD *x = p;
    size_t count = 0U;
    while (x != NULL)
    {
        ++count;
        x = x->next;
    }
    return count;
}

PNOD nod_push_head(PNOD first, const void *data, size_t data_size)
{
    PNOD ret = first;
    PNOD p = nod_new(data, data_size);
    if (p != NULL)
    {
        p->next = first;
        ret = p;
    }
    return ret;
}

PNOD nod_chain_fix_prevs(PNOD p)
{
    PNOD x = p;
    PNOD prev = NULL;
    while (x != NULL)
    {
        x->prev = prev;
        prev = x;
        x = x->next;
    }
    return prev;
}

PNOD nod_chain_last(PNOD p)
{
    PNOD x = p;
    PNOD prev = NULL;
    while (x != NULL)
    {
        prev = x;
        x = x->next;
    }
    return prev;
}

/****************************************************************************/
