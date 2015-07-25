/****************************************************************************/
/* vec.h --- nod (node for C language)                                      */
/****************************************************************************/

#ifndef KATAHIROMZ_NOD_H
#define KATAHIROMZ_NOD_H    0  /* Version 0 */

/****************************************************************************/
/* types */

typedef struct NOD
{
    struct NOD *    next;
    struct NOD *    prev;
    size_t          data_size;
    /* char data[data_size]; */
} NOD, *PNOD;

/****************************************************************************/
/* C/C++ switching */

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************/
/* functions */

PNOD nod_new(const void *data, size_t data_size);
PNOD nod_clone(PNOD pnod);

PNOD nod_advance(PNOD pnod, size_t count);
size_t nod_distance(PNOD pnod1, PNOD pnod2);
size_t nod_chain_length(PNOD pnod);

void nod_delete(PNOD pnod);
void nod_delete_chain(PNOD pnod);

PNOD nod_push_head(PNOD first, const void *data, size_t data_size);

PNOD nod_chain_reset_prevs(PNOD pnod);
PNOD nod_chain_last(PNOD pnod);

/****************************************************************************/
/* function macros */

#define nod_data(pnod)          ((void *)((PNOD)(pnod) + 1))
#define nod_data_size(pnod)     ((pnod)->data_size)
#define nod_delete(pnod)        free(pnod)

/****************************************************************************/
/* C/C++ switching */

#ifdef __cplusplus
} /* extern "C" */
#endif

/****************************************************************************/

#endif  /* ndef KATAHIROMZ_NOD_H */
