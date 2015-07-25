/****************************************************************************/
/* lis.h --- lis (singly linked list for C language)                        */
/****************************************************************************/

#ifndef KATAHIROMZ_LIS_H
#define KATAHIROMZ_LIS_H    1  /* Version 1 */

#ifndef KATAHIROMZ_NOD_H
    #include "nod.h"
#endif

/****************************************************************************/
/* types */

typedef struct LIS
{
    NOD *           first;
    NOD *           last;
    size_t          count;
} LIS, *PLIS;

/* NOTE: LIS_FOREACH returns 0 to cancel operation. */
typedef int (*LIS_FOREACH)(void *data);

/* NOTE: LIS_DATA_COMPARE returns 0 if equal; -1 if less; 1 if greater. */
typedef int (*LIS_DATA_COMPARE)(const void *data1, const void *data2);

/****************************************************************************/
/* C/C++ switching */

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************/
/* functions */

void lis_init(PLIS plis);
void lis_copy(PLIS dest, PLIS src);
void lis_destroy(PLIS plis);
void lis_clear(PLIS plis);

PLIS lis_new(void);
void lis_delete(PLIS plis);
PLIS lis_clone(PLIS plis);

void *lis_front(PLIS plis);
void *lis_back(PLIS plis);

void lis_push_front(PLIS plis, const void *data, size_t data_size);
void lis_push_back(PLIS plis, const void *data, size_t data_size);
void lis_pop_front(PLIS plis);

void lis_insert(PLIS plis, PNOD here,
                size_t count, const void *data, size_t data_size);
void lis_resize(PLIS plis, size_t count, const void *data, size_t data_size);

void lis_erase(PLIS plis, PNOD pnod);
void lis_remove(PLIS plis, const void *data, LIS_DATA_COMPARE compare);

void lis_foreach(PLIS plis, LIS_FOREACH fn);

PNOD lis_merge_nod(PNOD x, PNOD y, LIS_DATA_COMPARE compare);
PNOD lis_sort_nod(PNOD pnod, LIS_DATA_COMPARE compare);

void lis_merge(PLIS plis1, PLIS plis2, LIS_DATA_COMPARE compare);
void lis_sort(PLIS plis, LIS_DATA_COMPARE compare);

void lis_swap(PLIS plis1, PLIS plis2);

int lis_valid(PLIS plis);
int lis_length_ok(PLIS plis);
int lis_contains(PLIS plis, PNOD pnod);
int lis_is_sorted(PLIS plis, LIS_DATA_COMPARE compare);

/****************************************************************************/
/* function macros */

#define lis_empty(plis)     ((plis)->count == 0)
#define lis_size(plis)      ((plis)->count)

#define lis_front(plis)     nod_data((plis)->first)
#define lis_back(plis)      nod_data((plis)->last)

#define lis_destroy(plis)   nod_delete_chain((plis)->first)

/****************************************************************************/
/* C/C++ switching */

#ifdef __cplusplus
} /* extern "C" */
#endif

/****************************************************************************/

#endif  /* ndef KATAHIROMZ_LIS_H */
