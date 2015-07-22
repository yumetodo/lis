/****************************************************************************/
/* lis.h --- lis (singly linked list for C language)                        */
/****************************************************************************/

#ifndef KATAHIROMZ_LIS_H
#define KATAHIROMZ_LIS_H    0  /* Version 0 */

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

void lis_init(PLIS plst);
void lis_copy(PLIS dest, PLIS src);
void lis_destroy(PLIS plst);
void lis_clear(PLIS plst);

PLIS lis_new(void);
void lis_delete(PLIS plst);
PLIS lis_clone(PLIS plst);

void *lis_front(PLIS plst);
void *lis_back(PLIS plst);

void lis_push_front(PLIS plst, const void *data, size_t data_size);
void lis_push_back(PLIS plst, const void *data, size_t data_size);
void lis_pop_front(PLIS plst);

void lis_resize(PLIS plst, size_t count, const void *data, size_t data_size);

void lis_erase(PLIS plst, PNOD pnod);
void lis_remove(PLIS plst, const void *data, LIS_DATA_COMPARE compare);

void lis_foreach(PLIS plst, LIS_FOREACH fn);

void lis_swap(PLIS plst1, PLIS plst2);

#ifndef NDEBUG
    int lis_valid(PLIS plst);
    int lis_contains(PLIS plst, PNOD pnod);
    int lis_is_sorted(PLIS plst, LIS_DATA_COMPARE compare);
#endif

/****************************************************************************/
/* function macros */

#define lis_empty(plst)     ((plst)->count == 0)
#define lis_size(plst)      ((plst)->count)

#define lis_front(plst)     nod_data((plst)->first)
#define lis_back(plst)      nod_data((plst)->last)

#define lis_destroy(plst)   nod_delete_chain((plst)->first)

/****************************************************************************/
/* C/C++ switching */

#ifdef __cplusplus
} /* extern "C" */
#endif

/****************************************************************************/

#endif  /* ndef KATAHIROMZ_LIS_H */
