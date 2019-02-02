#ifndef RECYCLE_H
#define RECYCLE_H

#include "list.h"

typedef void * (*RecycleCreate) (void);
typedef ListDestroy RecycleDestroy;

typedef struct
{
	List          *live;
	List          *trash;
	RecycleCreate  create_fun;
} Recycle;


Recycle *  recycle_new (RecycleCreate create_fun, RecycleDestroy destroy_fun);
void       recycle_free (Recycle *recycle);
ListElmt * recycle_get_list_element (Recycle *recycle);
void       recycle_remove_list_element (Recycle *recycle, ListElmt *element);
#define    recycle_list_head(recycle) (list_head ((recycle)->live))
#define    recycle_list_tail(recycle) (list_tail ((recycle)->live))
#define    recycle_list_empty(recycle) (list_size ((recycle)->live) == 0)

#endif /* recycle.h */
