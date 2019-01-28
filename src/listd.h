#ifndef LIST_H
#define LIST_H

typedef struct _List
{
	void         *data;
	struct _List *next;
	struct _List *prev;
} List;

typedef void (*list_clean_data_fun) (void *);

#define list_next(l) ((l)->next)
#define list_prev(l) ((l)->prev)
#define list_data(l) ((l)->data)

List * list_new         (void);
void   list_free        (List *l, list_clean_data_fun clean_fun);
List * list_concat      (List *l1, List *l2);
List * list_ins_next    (List *head, void *data);
List * list_remove_link (List *head, List *l);
List * list_ins_prev    (List *head, void *data);

#endif /* list.h */
