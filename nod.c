/****************************************************************************/
/* nod.c --- nod (node for C language)                                      */
/****************************************************************************/
/* [History]                                                                */
/* 2015.07.22: katahiromz creates v0.                                       */
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
    PNOD pnod = (PNOD)calloc(sizeof(NOD) + data_size, 1);
    if (pnod)
    {
        pnod->next = NULL;
        pnod->prev = NULL;
        pnod->data_size = data_size;
        if (data)
            memcpy(nod_data(pnod), data, data_size);
    }
    return pnod;
}

void nod_delete_chain(PNOD pnod)
{
    PNOD next;
    while (pnod)
    {
        next = pnod->next;
        nod_delete(pnod);
        pnod = next;
    }
}

PNOD nod_advance(PNOD pnod, size_t count)
{
    while (count--)
    {
        if (pnod == NULL)
            break;
        pnod = pnod->next;
    }
    return pnod;
}

size_t nod_distance(PNOD pnod1, PNOD pnod2)
{
    size_t count = 0;
    while (pnod1)
    {
        if (pnod1 == pnod2)
            return count;
        pnod1 = pnod1->next;
        ++count;
    }
    return (size_t)-1;
}

PNOD nod_clone(PNOD pnod)
{
    PNOD created = nod_new(nod_data(pnod), nod_data_size(pnod));
    assert(created);
    return created;
}

size_t nod_chain_length(PNOD pnod)
{
    size_t count = 0;
    while (pnod)
    {
        ++count;
        pnod = pnod->next;
    }
    return count;
}

PNOD nod_push_head(PNOD first, const void *data, size_t data_size)
{
    PNOD pnod = nod_new(data, data_size);
    if (pnod)
    {
        pnod->next = first;
        return pnod;
    }
    return first;
}

void nod_chain_reset_prevs(PNOD pnod)
{
    PNOD prev = NULL;
    while (pnod)
    {
        pnod->prev = prev;
        prev = pnod;
        pnod = pnod->next;
    }
}

/****************************************************************************/
