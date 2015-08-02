/****************************************************************************/
/* nod.c --- nod (node for C language)                                      */
/****************************************************************************/
/* [History]                                                                */
/* 2015.07.22: katahiromz creates v0.                                       */
/* 2015.07.25: katahiromz creates v1.                                       */
/* 2015.07.26: katahiromz creates v2.                                       */
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
    PNOD p = (PNOD)malloc(sizeof(NOD) + data_size);
    if (p != NULL)
    {
        p->next = NULL;
        p->prev = NULL;
        p->data_size = data_size;
        if (data != NULL)
        {
            memcpy(nod_data(p), data, data_size);
        }
        else
        {
#ifdef NOD_NO_ZERO_INIT
            ;
#else
            memset(nod_data(p), 0, data_size);
#endif
        }
    }
    return p;
} /* nod_new */

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
} /* nod_delete_chain */

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
} /* nod_advance */

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
} /* nod_distance */

PNOD nod_clone(const NOD *p)
{
    PNOD created = nod_new(nod_const_data(p), nod_data_size(p));
    assert(created != NULL);
    return created;
} /* nod_clone */

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
} /* nod_chain_length */

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
} /* nod_push_head */

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
} /* nod_chain_fix_prevs */

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
} /* nod_chain_last */

PNOD nod_prev_of(PNOD p, PNOD here)
{
    PNOD prev = NULL;
    if (here != NULL)
    {
        prev = p;
        while (prev != NULL)
        {
            if (prev->next == here)
            {
                break;
            }
            prev = prev->next;
        }
    }
    return prev;
} /* nod_prev_of */

/****************************************************************************/
