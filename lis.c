/****************************************************************************/
/* lis.c --- lis (singly linked list for C language)                        */
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

#include <stdio.h>
#include "lis.h"

/****************************************************************************/
/* status checking */

#ifndef lis_status_bad
    #define lis_status_bad(plis)    /* empty */
#endif

/****************************************************************************/

int lis_valid(PLIS plis)
{
    if (plis == NULL)
        return 0;

    if (!lis_length_valid(plis))
        return 0;

    if (plis->count == 0)
    {
        if (plis->first || plis->last)
            return 0;
    }
    else
    {
        if (plis->first == NULL || plis->last == NULL)
            return 0;
    }

    return 1;
} /* lis_valid */

int lis_length_valid(PLIS plis)
{
    size_t i, count;
    PNOD pnod;

    count = plis->count + 1;
    pnod = plis->first;
    for (i = 0; i < count; ++i) {
        if (pnod == NULL)
            break;
        pnod = pnod->next;
    }
    if (pnod != NULL && i != plis->count)
        return 0;

    return 1;
} /* lis_length_valid */

int lis_contains(PLIS plis, PNOD pnod)
{
    PNOD p;
    assert(lis_valid(plis));
    p = plis->first;
    while (p)
    {
        if (p == pnod)
            return 1;
        p = p->next;
    }
    return 0;
} /* lis_contains */

int lis_is_sorted(PLIS plis, LIS_DATA_COMPARE compare)
{
    PNOD pnod, next;

    assert(lis_valid(plis));

    pnod = plis->first;
    while (pnod)
    {
        next = pnod->next;
        if (next == NULL)
            break;
        if ((*compare)(nod_data(pnod), nod_data(next)) > 0)
            return 0;
        pnod = next;
    }

    assert(lis_valid(plis));
    return 1;
} /* lis_is_sorted */

/****************************************************************************/

void lis_init(PLIS plis)
{
    assert(plis);
    plis->first = NULL;
    plis->last = NULL;
    plis->count = 0;
    assert(lis_valid(plis));
} /* lis_init */

void lis_copy(PLIS dest, PLIS src)
{
    PNOD pnod, created;

    assert(lis_valid(dest));
    assert(lis_valid(src));

    lis_clear(dest);
    pnod = src->first;
    if (pnod == NULL)
        return;

    created = nod_clone(pnod);
    dest->first = created;
    dest->last = created;
    dest->count = 1;

    for (;;)
    {
        pnod = pnod->next;
        if (pnod == NULL)
            break;

        created = nod_clone(pnod);
        if (created == NULL)
        {
            lis_status_bad(dest);
            return;
        }
        dest->last->next = created;
        dest->last = created;
        dest->count += 1;
    }

    assert(lis_valid(dest));
    assert(lis_valid(src));
} /* lis_copy */

PLIS lis_clone(PLIS plis)
{
    PLIS created;

    assert(lis_valid(plis));
    created = lis_new();
    if (created)
    {
        lis_copy(created, plis);
    }
    assert(lis_valid(plis));

    return created;
} /* lis_clone */

void lis_clear(PLIS plis)
{
    assert(lis_valid(plis));
    lis_destroy(plis);
    lis_init(plis);
    assert(lis_valid(plis));
} /* lis_clear */

PLIS lis_new(void)
{
    PLIS plis = (PLIS)calloc(sizeof(LIS), 1);
    if (plis)
    {
        lis_init(plis);
        assert(lis_valid(plis));
    }
    else
    {
        lis_status_bad(NULL);
    }
    return plis;
} /* lis_new */

void lis_delete(PLIS plis)
{
    if (plis)
    {
        lis_destroy(plis);
        free(plis);
    }
} /* lis_delete */

void lis_push_front(PLIS plis, const void *data, size_t data_size)
{
    PNOD pnod = nod_new(data, data_size);
    if (pnod == NULL)
    {
        lis_status_bad(plis);
        return;
    }

    if (plis->count == 0)
    {
        plis->first = pnod;
        plis->last = pnod;
    }
    else
    {
        pnod->next = plis->first;
        plis->first = pnod;
    }
    plis->count += 1;
    assert(lis_valid(plis));
} /* lis_push_front */

void lis_push_back(PLIS plis, const void *data, size_t data_size)
{
    PNOD pnod;

    assert(lis_valid(plis));

    pnod = nod_new(data, data_size);
    if (pnod == NULL)
    {
        lis_status_bad(plis);
        return;
    }

    if (plis->count == 0)
    {
        plis->first = pnod;
        plis->last = pnod;
    }
    else
    {
        plis->last->next = pnod;
        plis->last = pnod;
    }
    plis->count += 1;

    assert(lis_valid(plis));
} /* lis_push_back */

void lis_pop_front(PLIS plis)
{
    PNOD pnod;

    assert(lis_valid(plis));
    if (plis->count <= 0)
        return;

    plis->count -= 1;
    pnod = plis->first;
    assert(pnod);
    plis->first = pnod->next;
    nod_delete(pnod);
    assert(lis_valid(plis));
} /* lis_pop_front */

void lis_resize(PLIS plis, size_t count, const void *data, size_t data_size)
{
    size_t diff;
    PNOD pnod, prev;

    assert(lis_valid(plis));
    if (plis->count < count)
    {
        diff = count - plis->count;
        while (diff > 0)
        {
            lis_push_back(plis, data, data_size);
            --diff;
        }
    }
    else if (plis->count > count)
    {
        prev = NULL;
        pnod = plis->first;
        while (pnod && count > 0)
        {
            prev = pnod;
            pnod = pnod->next;
            --count;
        }
        if (count > 0 || pnod == NULL)
            return;

        plis->last = prev;
        nod_delete_chain(pnod);
        if (plis->last)
            plis->last->next = NULL;
        else
            plis->first = NULL;
        plis->count = count;
    }
    assert(lis_valid(plis));
} /* lis_resize */

void lis_insert(PLIS plis, PNOD here,
                size_t count, const void *data, size_t data_size)
{
    PNOD added, prev;

    assert(lis_valid(plis));
    assert(lis_contains(plis, here) || here == NULL);

    if (here == NULL)
    {
        lis_resize(plis, plis->count + count, data, data_size);
        return;
    }

    prev = plis->first;
    while (prev)
    {
        if (prev->next == here)
            break;
        prev = prev->next;
    }

    while (count-- > 0)
    {
        added = nod_new(data, data_size);
        if (added == NULL)
        {
            lis_status_bad(plis);
            return;
        }
        /*
         * prev -- here -- here->next
         *         ^added
         *
         * prev -- added -- here -- here->next
         */
        if (prev)
            prev->next = added;
        else
            plis->first = added;
        added->next = here;
        here = added;
        plis->count += 1;
    }
}

void lis_erase(PLIS plis, PNOD pnod)
{
    PNOD p, prev;

    assert(lis_valid(plis));
    assert(lis_contains(plis, pnod));

    prev = NULL;
    p = plis->first;
    while (p)
    {
        if (p == pnod)
            break;
        prev = p;
        p = p->next;
    }

    /*
     * prev -- pnod -- pnod->next
     *         ^
     * prev     --     pnod->next
     */
    if (prev)
        prev->next = pnod->next;
    plis->count -= 1;

    if (plis->count == 0)
    {
        plis->first = NULL;
        plis->last = NULL;
    }
    else
    {
        if (prev == NULL)
        {
            plis->first = pnod->next;
        }
        else if (pnod->next == NULL)
        {
            plis->last = prev;
        }
    }
    nod_delete(pnod);
    assert(lis_valid(plis));
} /* lis_erase */

void lis_unique(PLIS plis, LIS_DATA_COMPARE compare)
{
    PNOD pnod, next;

    assert(lis_valid(plis));
    if (plis->count == 0)
        return;

    for (pnod = plis->first; pnod; pnod = pnod->next)
    {
        /* a1 a2 a3 b1 b2 c1 c2 c3 d1 */
        /* ^  ^ */
        /* a1    a3 b1 b2 c1 c2 c3 d1 */
        /* ^     ^ */
        /* a1       b1 b2 c1 c2 c3 d1 */
        /* ^        ^ */
        next = pnod->next;
        if (next == NULL)
            break;

        if ((*compare)(nod_data(pnod), nod_data(next)) == 0)
        {
            do
            {
                lis_erase(plis, next);

                next = pnod->next;
                if (next == NULL)
                    break;
            } while ((*compare)(nod_data(pnod), nod_data(next)) == 0);
            if (next == NULL)
                break;
        }
    }
    assert(lis_valid(plis));
} /* lis_unique */

void lis_reverse(PLIS plis)
{
    PNOD pnod, next;
    PNOD chain, new_last;

    assert(lis_valid(plis));
    if (plis->count <= 1)
        return;

    pnod = new_last = plis->first;
    chain = NULL;
    do
    {
        next = pnod->next;

        pnod->next = chain;
        chain = pnod;

        pnod = next;
    } while (pnod);

    plis->first = chain;
    plis->last = new_last;
    assert(lis_valid(plis));
} /* lis_reverse */

void lis_remove(PLIS plis, const void *data, LIS_DATA_COMPARE compare)
{
    PNOD pnod, next;

    assert(lis_valid(plis));
    pnod = plis->first;
    while (pnod)
    {
        next = pnod->next;
        if (compare(data, nod_data(pnod)) == 0)
            lis_erase(plis, pnod);
        pnod = next;
    }
    assert(lis_valid(plis));
} /* lis_remove */

void lis_swap(PLIS plis1, PLIS plis2)
{
    LIS lis;

    assert(lis_valid(plis1));
    assert(lis_valid(plis2));
    if (plis1 == plis2)
        return;

    lis = *plis1;
    *plis1 = *plis2;
    *plis2 = lis;

    assert(lis_valid(plis1));
    assert(lis_valid(plis2));
} /* lis_swap */

void lis_foreach(PLIS plis, LIS_FOREACH fn)
{
    PNOD pnod = plis->first;

    while (pnod)
    {
        if ((*fn)(nod_data(pnod)) == 0)
            break;
        pnod = pnod->next;
    }
} /* lis_foreach */

PNOD lis_merge_nod(PNOD x, PNOD y, LIS_DATA_COMPARE compare)
{
    NOD head;
    PNOD pnod = &head;

    while (x && y)
    {
        if (compare(nod_data(x), nod_data(y)) < 0)
        {
            pnod->next = x;
            x = x->next;
            pnod = pnod->next;
        }
        else
        {
            pnod->next = y;
            y = y->next;
            pnod = pnod->next;
        }
    }

    if (x)
        pnod->next = x;
    else
        pnod->next = y;

    return head.next;
} /* lis_merge_nod */

void lis_merge(PLIS plis1, PLIS plis2, LIS_DATA_COMPARE compare)
{
    PNOD pnod;
    assert(lis_is_sorted(plis1, compare));
    assert(lis_is_sorted(plis2, compare));

    pnod = lis_merge_nod(plis1->first, plis2->first, compare);

    plis1->first = pnod;
    plis1->last = nod_chain_last(pnod);
    plis1->count += plis2->count;

    plis2->first = NULL;
    plis2->last = NULL;
    plis2->count = 0;

    assert(lis_is_sorted(plis1, compare));
    assert(lis_size(plis2) == 0);
} /* lis_merge */

PNOD lis_sort_nod(PNOD pnod, LIS_DATA_COMPARE compare)
{
    PNOD x, y;

    if (pnod == NULL || pnod->next == NULL)
        return pnod;

    x = pnod;
    y = x->next->next;

    while (y)
    {
        x = x->next;
        y = y->next;
        if (y)
            y = y->next;
    }

    y = x->next;
    x->next = NULL;

    x = lis_sort_nod(pnod, compare);
    y = lis_sort_nod(y, compare);
    return lis_merge_nod(x, y, compare);
} /* lis_sort_nod */

void lis_sort(PLIS plis, LIS_DATA_COMPARE compare)
{
    PNOD pnod;

    assert(lis_valid(plis));
    if (plis->count <= 1)
        return;

    pnod = plis->first;
    pnod = lis_sort_nod(pnod, compare);

    plis->first = pnod;
    plis->last = nod_chain_last(pnod);

    assert(lis_valid(plis));
    assert(lis_is_sorted(plis, compare));
} /* lis_sort */

/****************************************************************************/
/* test and sample */

/* #define LIS_TEST */

#ifdef LIS_TEST
    #include <stdio.h>

    int print_long(void *data)
    {
        printf("%ld ", *(long *)data);
        fflush(stdout);
        return 1;
    }

    int compare_long(const void *data1, const void *data2)
    {
        const long *a = (const long *)data1;
        const long *b = (const long *)data2;
        if (*a < *b)
            return -1;
        if (*a > *b)
            return 1;
        return 0;
    }

    int main(void)
    {
        LIS lis1, lis2;
        long n;
        PNOD pnod;
        size_t siz = sizeof(long);

        lis_init(&lis1);
        lis_init(&lis2);

        n = 1;
        lis_push_back(&lis1, &n, siz);
        n = 2;
        lis_push_back(&lis1, &n, siz);
        n = 0;
        lis_push_front(&lis1, &n, siz);

        printf("lis1: ");
        lis_foreach(&lis1, print_long);
        puts("");

        pnod = lis1.first;

        n = 0;
        assert(memcmp(nod_data(pnod), &n, siz) == 0);
        pnod = pnod->next;
        n = 1;
        assert(memcmp(nod_data(pnod), &n, siz) == 0);
        pnod = pnod->next;
        n = 2;
        assert(memcmp(nod_data(pnod), &n, siz) == 0);
        pnod = pnod->next;
        assert(pnod == NULL);

        assert(lis_is_sorted(&lis1, compare_long));

        printf("lis2: ");
        lis_foreach(&lis2, print_long);
        puts("");

        lis_pop_front(&lis1);

        printf("lis1: ");
        lis_foreach(&lis1, print_long);
        puts("");

        n = 4;
        lis_push_front(&lis1, &n, siz);
        n = 9;
        lis_push_back(&lis1, &n, siz);

        lis_copy(&lis2, &lis1);

        printf("lis1: ");
        lis_foreach(&lis1, print_long);
        puts("");

        printf("lis2: ");
        lis_foreach(&lis2, print_long);
        puts("");

        lis_clear(&lis2);

        printf("lis2: ");
        lis_foreach(&lis2, print_long);
        puts("");

        n = 2;
        lis_push_front(&lis2, &n, siz);
        n = 4;
        lis_push_back(&lis2, &n, siz);
        n = 4;
        lis_push_back(&lis2, &n, siz);

        printf("lis2: ");
        lis_foreach(&lis2, print_long);
        puts("");

        lis_unique(&lis2, compare_long);

        printf("lis2: ");
        lis_foreach(&lis2, print_long);
        puts("");

        lis_reverse(&lis2);

        printf("lis2: ");
        lis_foreach(&lis2, print_long);
        puts("");

        n = 999;
        lis_insert(&lis2, lis2.last, 4, &n, siz);

        printf("lis2: ");
        lis_foreach(&lis2, print_long);
        puts("");

        lis_copy(&lis1, &lis2);
        printf("lis1: ");
        lis_foreach(&lis1, print_long);
        puts("");

        lis_sort(&lis1, compare_long);

        printf("lis1: ");
        lis_foreach(&lis1, print_long);
        puts("");

        lis_sort(&lis2, compare_long);
        lis_merge(&lis1, &lis2, compare_long);

        printf("lis1: ");
        lis_foreach(&lis1, print_long);
        puts("");

        lis_destroy(&lis1);
        lis_destroy(&lis2);

        return 0;
    }
#endif  /* def LIS_TEST */

/****************************************************************************/
