/****************************************************************************/
/* lis.c --- lis (singly linked list for C language)                        */
/****************************************************************************/
/* [History]                                                                */
/* 2015.07.22: katahiromz creates v0.                                       */
/* 2015.07.25: katahiromz creates v1.                                       */
/* 2015.07.26: katahiromz creates v2.                                       */
/* 2015.08.02: katahiromz creates v3.                                       */
/****************************************************************************/

#include "lis.h"

/****************************************************************************/
/* status checking */

#ifndef lis_status_bad
    #define lis_status_bad(pl)    assert(0)
#endif

/****************************************************************************/
/* C/C++ switching */

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************/

bool lis_valid(const LIS *pl)
{
    bool ret = true;

    if ((pl == NULL))
    {
        ret = false;
    }
    else if (lis_length_valid(pl) == false)
    {
        ret = false;
    }
    else if (pl->count == 0U)
    {
        if ((pl->first != NULL) || (pl->last != NULL))
        {
            ret = false;
        }
    }
    else
    {
        if ((pl->first == NULL) || (pl->last == NULL))
        {
            ret = false;
        }
    }

    return ret;
} /* lis_valid */

bool lis_length_valid(const LIS *pl)
{
    size_t i, count;
    PNOD pn;

    count = pl->count + 1U;
    pn = pl->first;
    for (i = 0U; i < count; ++i)
    {
        if (pn == NULL)
        {
            break;
        }
        pn = pn->next;
    }

    return ((pn == NULL) || (i == pl->count));
} /* lis_length_valid */

bool lis_contains(const LIS *pl, const NOD *pn)
{
    const NOD *p;
    bool ret = false;

    assert(lis_valid(pl));
    p = pl->first;
    while (p != NULL)
    {
        if (p == pn)
        {
            ret = true;
            break;
        }
        p = p->next;
    }

    return ret;
} /* lis_contains */

bool lis_is_sorted(const LIS *pl, LIS_DATA_COMPARE compare)
{
    PNOD pn, next;
    bool ret = true;

    assert(lis_valid(pl));
    assert(compare != NULL);

    pn = pl->first;
    while (pn != NULL)
    {
        next = pn->next;
        if (next == NULL)
        {
            break;
        }

        if ((*compare)(nod_const_data(pn), nod_const_data(next)) > 0)
        {
            ret = false;
            break;
        }
        pn = next;
    }

    assert(lis_valid(pl));
    return ret;
} /* lis_is_sorted */

void lis_init(PLIS pl)
{
    assert(pl != NULL);
    pl->first = NULL;
    pl->last = NULL;
    pl->count = 0U;
    assert(lis_valid(pl));
} /* lis_init */

PLIS lis_clone(PLIS pl)
{
    PLIS created;

    assert(lis_valid(pl));

    created = lis_new();
    if (created != NULL)
    {
        lis_copy(created, pl);
    }
    assert(lis_valid(pl));

    return created;
} /* lis_clone */

void lis_clear(PLIS pl)
{
    assert(lis_valid(pl));
    lis_destroy(pl);
    lis_init(pl);
    assert(lis_valid(pl));
} /* lis_clear */

PLIS lis_new(void)
{
    PLIS pl = (PLIS)malloc(sizeof(LIS));
    if (pl != NULL)
    {
        lis_init(pl);
        assert(lis_valid(pl));
    }
    else
    {
        /* status bad */
        lis_status_bad(NULL);
    }
    return pl;
} /* lis_new */

void lis_delete(PLIS pl)
{
    if (pl != NULL)
    {
        lis_destroy(pl);
        free(pl);
    }
} /* lis_delete */

lis_bool lis_push_front(PLIS pl, const void *data, size_t data_size)
{
    PNOD pn;
    LIS_STATUS_INIT(ret, true);

    assert(lis_valid(pl));
    pn = nod_new(data, data_size);
    if (pn != NULL)
    {
        if (pl->count == 0U)
        {
            pl->first = pn;
            pl->last = pn;
        }
        else
        {
            pn->next = pl->first;
            pl->first = pn;
        }
        pl->count += 1U;
    }
    else
    {
        /* status bad */
        lis_status_bad(pl);
        LIS_STATUS_SET(ret, false);
    }

    assert(lis_valid(pl));
    LIS_STATUS_RETURN(ret);
} /* lis_push_front */

lis_bool lis_push_back(PLIS pl, const void *data, size_t data_size)
{
    PNOD pn;
    LIS_STATUS_INIT(ret, true);

    assert(lis_valid(pl));

    pn = nod_new(data, data_size);
    if (pn != NULL)
    {
        if (pl->count == 0U)
        {
            pl->first = pn;
            pl->last = pn;
        }
        else
        {
            pl->last->next = pn;
            pl->last = pn;
        }
        pl->count += 1U;
    }
    else
    {
        /* status bad */
        lis_status_bad(pl);
        LIS_STATUS_SET(ret, false);
    }

    assert(lis_valid(pl));
    LIS_STATUS_RETURN(ret);
} /* lis_push_back */

lis_bool lis_pop_front(PLIS pl)
{
    PNOD pn;
    LIS_STATUS_INIT(ret, false);

    assert(lis_valid(pl));
    if (pl->count > 0U)
    {
        pl->count -= 1U;
        pn = pl->first;
        assert(pn != NULL);
        pl->first = pn->next;
        nod_delete(pn);
        LIS_STATUS_SET(ret, true);
    }

    assert(lis_valid(pl));
    LIS_STATUS_RETURN(ret);
} /* lis_pop_front */

void lis_insert_nod(PLIS pl, PNOD here, PNOD pn)
{
    PNOD prev;

    assert(lis_valid(pl));
    assert(pn != NULL);
    assert(lis_contains(pl, here));

    if (pl->count == 0L)
    {
        pn->next = NULL;
        pl->first = pn;
        pl->last = pn;
    }
    else
    {
        if (here == NULL)
        {
            pl->last->next = pn;
            pn->next = NULL;
            pl->last = pn;
        }
        else if (here == pl->first)
        {
            pn->next = here;
            pl->first = pn;
        }
        else
        {
            /*
             * prev    --    here
             *
             * prev -- pn -- here
             */
            prev = nod_prev_of(pl->first, here);
            assert(prev != NULL);
            prev->next = pn;
            pn->next = here;
        }
    }
    pl->count += 1U;

    assert(lis_valid(pl));
} /* lis_insert_nod */

void lis_sort(PLIS pl, LIS_DATA_COMPARE compare)
{
    PNOD pn;

    assert(lis_valid(pl));
    assert(compare != NULL);

    if (pl->count > 1U)
    {
        pn = pl->first;
        pn = lis_sort_nod(pn, compare);

        pl->first = pn;
        pl->last = nod_chain_last(pn);
    }

    assert(lis_valid(pl));
    assert(lis_is_sorted(pl, compare));
} /* lis_sort */

void lis_merge(PLIS pl1, PLIS pl2, LIS_DATA_COMPARE compare)
{
    PNOD pn;
    assert(lis_is_sorted(pl1, compare));
    assert(lis_is_sorted(pl2, compare));
    assert(compare != NULL);

    pn = lis_merge_nod(pl1->first, pl2->first, compare);

    pl1->first = pn;
    pl1->last = nod_chain_last(pn);
    pl1->count += pl2->count;

    pl2->first = NULL;
    pl2->last = NULL;
    pl2->count = 0U;

    assert(lis_is_sorted(pl1, compare));
    assert(lis_size(pl2) == 0U);
} /* lis_merge */

void lis_swap(PLIS pl1, PLIS pl2)
{
    LIS lis;

    assert(lis_valid(pl1));
    assert(lis_valid(pl2));

    if (pl1 != pl2)
    {
        lis = *pl1;
        *pl1 = *pl2;
        *pl2 = lis;
    }

    assert(lis_valid(pl1));
    assert(lis_valid(pl2));
} /* lis_swap */

lis_bool lis_construct(PLIS pl, size_t data_size,
                       size_t num_items, const void *items)
{
    PNOD pn;
    size_t i;
    char *p;
    LIS_STATUS_INIT(ret, false);

    assert(pl != NULL);
    lis_init(pl);

#ifdef LIS_QUICK_BUT_RISKY
    lis_resize(pl, num_items, NULL, data_size);
#else
    if (lis_resize(pl, num_items, NULL, data_size))
#endif
    {
        pn = pl->first;
        i = 0;
        p = (char *)items;
        while (pn != NULL)
        {
            memcpy(nod_data(pn), &p[i * data_size], data_size);
            ++i;
        }
        LIS_STATUS_SET(ret, true);
    }

    LIS_STATUS_RETURN(ret);
} /* lis_construct */

lis_bool lis_copy(PLIS dest, const LIS *src)
{
    PNOD pn, created;
    LIS_STATUS_INIT(ret, true);

    assert(lis_valid(dest));
    assert(lis_valid(src));

    lis_clear(dest);

    pn = src->first;
    if (pn != NULL)
    {
        created = nod_clone(pn);
        if (created)
        {
            dest->first = created;
            dest->last = created;
            dest->count = 1U;

            for (;;)
            {
                pn = pn->next;
                if (pn == NULL)
                {
                    break;
                }

                created = nod_clone(pn);
                if (created == NULL)
                {
                    /* status bad */
                    lis_status_bad(dest);
                    LIS_STATUS_SET(ret, false);
                    break;
                }
                dest->last->next = created;
                dest->last = created;
                dest->count += 1U;
            }
        }
        else
        {
            /* status bad */
            lis_status_bad(dest);
            LIS_STATUS_SET(ret, false);
        }
    }

    assert(lis_valid(dest));
    assert(lis_valid(src));
    LIS_STATUS_RETURN(ret);
} /* lis_copy */

lis_bool lis_resize(PLIS pl, size_t count, const void *data, size_t data_size)
{
    size_t diff;
    PNOD pn, prev;
    LIS_STATUS_INIT(ret, true);

    assert(lis_valid(pl));
    if (pl->count < count)
    {
        diff = count - pl->count;
        while (diff > 0)
        {
#ifdef LIS_QUICK_BUT_RISKY
            lis_push_back(pl, data, data_size);
#else
            if (lis_push_back(pl, data, data_size) == false)
            {
                LIS_STATUS_SET(ret, false);
                break;
            }
#endif
            --diff;
        }
    }
    else if (pl->count > count)
    {
        prev = NULL;
        pn = pl->first;
        while ((pn != NULL) && (count > 0U))
        {
            prev = pn;
            pn = pn->next;
            --count;
        }

        if ((count > 0U) || (pn == NULL))
        {
            /* status bad */
            lis_status_bad(pl);
            LIS_STATUS_SET(ret, false);
        }
        else
        {
            pl->last = prev;
            nod_delete_chain(pn);
            if (pl->last != NULL)
            {
                pl->last->next = NULL;
            }
            else
            {
                pl->first = NULL;
            }
            pl->count = count;
        }
    }
    else
    {
        /* do nothing */
    }

    assert(lis_valid(pl));
    LIS_STATUS_RETURN(ret);
} /* lis_resize */

lis_bool lis_assign(PLIS pl, size_t count, const void *data, size_t data_size)
{
    LIS lis;
    LIS_STATUS_INIT(ret, false);

    assert(lis_valid(pl));
    lis_init(&lis);

#ifdef LIS_QUICK_BUT_RISKY
    lis_resize(&lis, count, data, data_size);
#else
    if (lis_resize(&lis, count, data, data_size))
#endif
    {
        lis_swap(&lis, pl);
        lis_destroy(&lis);
        LIS_STATUS_SET(ret, true);
    }

    assert(lis_valid(pl));
    LIS_STATUS_RETURN(ret);
} /* lis_assign */

lis_bool lis_insert(PLIS pl, PNOD here,
                    size_t count, const void *data, size_t data_size)
{
    PNOD added, prev;
    PNOD there = here;
    LIS_STATUS_INIT(ret, true);

    assert(lis_valid(pl));
    assert(lis_contains(pl, there) != 0 || there == NULL);

    if (there == NULL)
    {
#ifdef LIS_QUICK_BUT_RISKY
        lis_resize(pl, pl->count + count, data, data_size);
#else
        ret = lis_resize(pl, pl->count + count, data, data_size);
#endif
    }
    else
    {
        prev = nod_prev_of(pl->first, there);

        while (count-- > 0)
        {
            added = nod_new(data, data_size);
            if (added == NULL)
            {
                /* status bad */
                lis_status_bad(pl);
                LIS_STATUS_SET(ret, false);
                break;
            }

            /*
             * prev -- there -- there->next
             *         ^added
             *
             * prev -- added -- there -- there->next
             */
            if (prev != NULL)
            {
                prev->next = added;
            }
            else
            {
                pl->first = added;
            }
            added->next = there;
            there = added;
            pl->count += 1U;
        }
    }

    assert(lis_valid(pl));
    LIS_STATUS_RETURN(ret);
}

lis_bool lis_erase(PLIS pl, PNOD pn)
{
    PNOD p, prev;
    LIS_STATUS_INIT(ret, false);

    assert(lis_valid(pl));
    assert(lis_contains(pl, pn));

    if (pl->count > 0)
    {
        prev = NULL;
        p = pl->first;
        while (p != NULL)
        {
            if (p == pn)
            {
                break;
            }
            prev = p;
            p = p->next;
        }

        /*
         * prev -- pn -- pn->next
         *         ^
         * prev     --     pn->next
         */
        if (prev != NULL)
        {
            prev->next = pn->next;
        }

        pl->count -= 1U;
        if (pl->count == 0U)
        {
            pl->first = NULL;
            pl->last = NULL;
        }
        else
        {
            if (prev == NULL)
            {
                pl->first = pn->next;
            }
            else if (pn->next == NULL)
            {
                pl->last = prev;
            }
            else
            {
                /* do nothing */
            }
        }
        nod_delete(pn);

        LIS_STATUS_SET(ret, true);
    }

    assert(lis_valid(pl));
    LIS_STATUS_RETURN(ret);
} /* lis_erase */

void lis_unique(PLIS pl, LIS_DATA_COMPARE compare)
{
    PNOD pn, next;

    assert(lis_valid(pl));
    assert(compare != NULL);

    if (pl->count > 1U)
    {
        for (pn = pl->first; pn != NULL; pn = pn->next)
        {
            /* a1 a2 a3 b1 b2 c1 c2 c3 d1 */
            /* ^  ^ */
            /* a1    a3 b1 b2 c1 c2 c3 d1 */
            /* ^     ^ */
            /* a1       b1 b2 c1 c2 c3 d1 */
            /* ^        ^ */
            next = pn->next;
            if (next == NULL)
            {
                break;
            }

            if ((*compare)(nod_data(pn), nod_data(next)) == 0)
            {
                do
                {
                    lis_erase(pl, next);

                    next = pn->next;
                    if (next == NULL)
                    {
                        break;
                    }
                } while ((*compare)(nod_data(pn), nod_data(next)) == 0);

                if (next == NULL)
                {
                    break;
                }
            }
        }
    }
    assert(lis_valid(pl));
} /* lis_unique */

void lis_reverse(PLIS pl)
{
    PNOD pn, next;
    PNOD chain, new_last;

    assert(lis_valid(pl));
    if (pl->count > 1U)
    {
        pn = pl->first;
        new_last = pn;
        chain = NULL;
        do
        {
            next = pn->next;

            pn->next = chain;
            chain = pn;

            pn = next;
        } while (pn != NULL);

        pl->first = chain;
        pl->last = new_last;
    }

    assert(lis_valid(pl));
} /* lis_reverse */

void lis_remove(PLIS pl, const void *data, LIS_DATA_COMPARE compare)
{
    PNOD pn, next;

    assert(lis_valid(pl));
    assert(compare != NULL);

    pn = pl->first;
    while (pn != NULL)
    {
        next = pn->next;
        if ((*compare)(data, nod_data(pn)) == 0)
        {
            lis_erase(pl, pn);
        }
        pn = next;
    }
    assert(lis_valid(pl));
} /* lis_remove */

void lis_foreach(PLIS pl, LIS_FOREACH fn)
{
    PNOD pn = pl->first;

    assert(lis_valid(pl));
    while (pn)
    {
        if ((*fn)(nod_data(pn)) == 0)
        {
            break;
        }
        pn = pn->next;
    }
    assert(lis_valid(pl));
} /* lis_foreach */

PNOD lis_merge_nod(PNOD x, PNOD y, LIS_DATA_COMPARE compare)
{
    NOD head;
    PNOD pn = &head;
    PNOD a = x;
    PNOD b = y;

    assert(compare != NULL);

    while ((a != NULL) && (b != NULL))
    {
        if ((*compare)(nod_data(a), nod_data(b)) < 0)
        {
            pn->next = a;
            a = a->next;
            pn = pn->next;
        }
        else
        {
            pn->next = b;
            b = b->next;
            pn = pn->next;
        }
    }

    if (a != NULL)
    {
        pn->next = a;
    }
    else
    {
        pn->next = b;
    }

    return head.next;
} /* lis_merge_nod */

PNOD lis_sort_nod(PNOD pn, LIS_DATA_COMPARE compare)
{
    PNOD x, y, ret = pn;

    assert(compare != NULL);

    if ((pn != NULL) && (pn->next != NULL))
    {
        x = pn;
        y = x->next->next;

        while (y != NULL)
        {
            x = x->next;
            y = y->next;
            if (y != NULL)
            {
                y = y->next;
            }
        }

        y = x->next;
        x->next = NULL;

        x = lis_sort_nod(pn, compare);
        y = lis_sort_nod(y, compare);
        ret = lis_merge_nod(x, y, compare);
    }
    return ret;
} /* lis_sort_nod */
/* void splice (const_iterator position, list& x, const_iterator i); */
void lis_splice(PLIS pl, PNOD here, PLIS other, PNOD it)
{
	assert(lis_valid(pl));
    assert(lis_valid(other));
    assert(pl != other);
	/* issue : lis_end(pl) is NULL so that I cannot insert node.*/
    assert(here == NULL || lis_contains(pl, here));
    assert(it == NULL || lis_contains(other, it));
	if (it == other->first)
	{
		other->first = other->first->next;
	}
	else if (it == other->last)
	{
		other->last = other->last->prev;
	}
	/* remove node */
	it->prev->next = it->next;
	it->next->prev = it->prev;
	--other->count;

	/* modify insert node info and split */
	it->prev = here->prev;
	it->next = here;

	/* insert node */
	/* issue : how to detect end iterator? */
	if (here == pl->first)
	{
		pl->first = it;
	}
	/* issue : lis_end(pl) is NULL so that I cannot insert node.
	else if (here == lis_end(pl))
	{
		lis_end(pl)->prev = it;
	}
	*/
	here->prev->next = it;
	here->prev = it;
	++pl->count;

    assert(0);
    /*lis_clear(other); Why you destroy list?*/

    assert(lis_valid(pl));
    assert(lis_valid(other));
} /* lis_splice */

static bool node_traceable(NOD const* const from, NOD const* const to)
{
	PNOD nod;
	while (NULL != (nod = from->next)) if (to == nod) return true;
	return false;
}
void lis_splice_range(PLIS pl, PNOD here, PLIS other, PNOD begin, PNOD end)
{
    assert(lis_valid(pl));
    assert(lis_valid(other));
    assert(pl != other);
	/* issue : lis_end(pl) is NULL so that I cannot insert node.*/
	assert(here == NULL || lis_contains(pl, here));
	if (begin == end || (begin->next == end && begin == end->prev))
	{
		lis_splice(pl, here, other, begin);
	}
	else {
		assert(node_traceable(begin, end));
		if (begin == other->first)
		{
			other->first = other->first->next;
		}
		else if (end->prev == other->last)
		{
			other->last = other->last->prev;
		}
		/* remove node */
		begin->prev->next = end;
		end->prev = begin->prev;
		--other->count;

		/* modify insert node info and split */
		begin->prev = here->prev;
		end->prev->next = here;

		/* insert node */
		/* issue : how to detect end iterator? */
		if (here == pl->first)
		{
			pl->first = begin;
		}
		/* issue : lis_end(pl) is NULL so that I cannot insert node.
		else if (here == lis_end(pl))
		{
		lis_end(pl)->prev = it;
		}
		*/
		here->prev->next = begin;
		here->prev = end->prev;
		++pl->count;

		assert(0);
		/*lis_clear(other); Why you destroy list?*/

		assert(lis_valid(pl));
		assert(lis_valid(other));
	}
} /* lis_splice_range */

/****************************************************************************/
/* C/C++ switching */

#ifdef __cplusplus
} /* extern "C" */
#endif

/****************************************************************************/
/* test and sample */

/* #define LIS_TEST */

#ifdef LIS_TEST
    #include <stdio.h>

    bool print_long(void *data)
    {
        printf("%ld ", *(long *)data);
        fflush(stdout);
        return true;
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
        PNOD pn;
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

        pn = lis1.first;

        n = 0;
        assert(memcmp(nod_data(pn), &n, siz) == 0);
        pn = pn->next;
        n = 1;
        assert(memcmp(nod_data(pn), &n, siz) == 0);
        pn = pn->next;
        n = 2;
        assert(memcmp(nod_data(pn), &n, siz) == 0);
        pn = pn->next;
        assert(pn == NULL);

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
