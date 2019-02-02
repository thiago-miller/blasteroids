#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct _ListElmt
{
	void             *data;
	struct _ListElmt *next;
	struct _ListElmt *prev;
} ListElmt;

typedef void (*ListDestroy) (void *data);

typedef struct
{
	size_t      size;
	ListElmt   *head;
	ListElmt   *tail;
	ListDestroy destroy_fun;
} List;

List *  list_new              (ListDestroy destroy_fun);
void    list_free             (List *list);
bool    list_append           (List *list, const void *data);
bool    list_append_link      (List *list, ListElmt *element);
bool    list_prepend          (List *list, const void *data);
bool    list_prepend_link     (List *list, ListElmt *element);
bool    list_ins_prev         (List *list, ListElmt *element, const void *data);
bool    list_ins_prev_link    (List *list, ListElmt *element, ListElmt *new_element);
bool    list_ins_next         (List *list, ListElmt *element, const void *data);
bool    list_ins_next_link    (List *list, ListElmt *element, ListElmt *new_element);
bool    list_remove           (List *list, ListElmt *element, void **data);
bool    list_remove_link      (List *list, ListElmt *element);
#define list_size(list)       ((list)->size)
#define list_head(list)       ((list)->head)
#define list_tail(list)       ((list)->tail)
#define list_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_data(element)    ((element)->data)
#define list_prev(element)    ((element)->prev)
#define list_next(element)    ((element)->next)

#endif /* l.h */
