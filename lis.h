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
typedef bool (*LIS_FOREACH)(void *data);

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

void lis_init(PLIS pl);
void lis_copy(PLIS dest, const LIS *src);
void lis_clear(PLIS pl);

PLIS lis_new(void);
void lis_delete(PLIS pl);
PLIS lis_clone(PLIS pl);

void lis_push_front(PLIS pl, const void *data, size_t data_size);
void lis_push_back(PLIS pl, const void *data, size_t data_size);
void lis_pop_front(PLIS pl);

void lis_insert(PLIS pl, PNOD here,
                size_t count, const void *data, size_t data_size);
void lis_resize(PLIS pl, size_t count, const void *data, size_t data_size);

void lis_erase(PLIS pl, PNOD pn);
void lis_remove(PLIS pl, const void *data, LIS_DATA_COMPARE compare);

void lis_foreach(PLIS pl, LIS_FOREACH fn);

PNOD lis_merge_nod(PNOD x, PNOD y, LIS_DATA_COMPARE compare);
PNOD lis_sort_nod(PNOD pn, LIS_DATA_COMPARE compare);

void lis_merge(PLIS pl1, PLIS pl2, LIS_DATA_COMPARE compare);
void lis_sort(PLIS pl, LIS_DATA_COMPARE compare);
void lis_unique(PLIS pl, LIS_DATA_COMPARE compare);
void lis_reverse(PLIS pl);

void lis_swap(PLIS pl1, PLIS pl2);

bool lis_valid(const LIS *pl);
bool lis_length_valid(const LIS *pl);
bool lis_contains(const LIS *pl, const NOD *pn);
bool lis_is_sorted(const LIS *pl, LIS_DATA_COMPARE compare);

/****************************************************************************/
/* function macros */

#define lis_empty(pl)     ((pl)->count == 0U)
#define lis_size(pl)      ((pl)->count)

#define lis_front(pl)     nod_data((pl)->first)
#define lis_back(pl)      nod_data((pl)->last)

#define lis_destroy(pl)   nod_delete_chain((pl)->first)

/****************************************************************************/
/* C/C++ switching */

#ifdef __cplusplus
} /* extern "C" */
#endif

/****************************************************************************/

#endif  /* ndef KATAHIROMZ_LIS_H */
