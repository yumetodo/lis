/****************************************************************************/
/* vec.h --- nod (node for C language)                                      */
/****************************************************************************/

#ifndef KATAHIROMZ_NOD_H
#define KATAHIROMZ_NOD_H    1  /* Version 1 */

#include <stddef.h>

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
PNOD nod_clone(const NOD *p);

PNOD nod_advance(PNOD p, size_t count);
size_t nod_distance(const NOD *p1, const NOD *p2);
size_t nod_chain_length(const NOD *p);

void nod_delete_chain(PNOD p);

PNOD nod_push_head(PNOD first, const void *data, size_t data_size);

PNOD nod_chain_fix_prevs(PNOD p);
PNOD nod_chain_last(PNOD p);

/****************************************************************************/
/* function macros */

#define nod_data(p)          ((void *)&(((PNOD)p)[1]))
#define nod_const_data(p)    ((const void *)&(((const NOD*)p)[1]))
#define nod_data_size(p)     ((p)->data_size)
#define nod_delete(p)        free(p)

/****************************************************************************/
/* C/C++ switching */

#ifdef __cplusplus
} /* extern "C" */
#endif

/****************************************************************************/

#endif  /* ndef KATAHIROMZ_NOD_H */
