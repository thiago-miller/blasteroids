#ifndef LIST_H
#define LIST_H

typedef struct _List
{
	void         *data;
	struct _List *next;
} List;

typedef void (*list_clean_data_fun) (void *);

#define list_next(l) ((l)->next)
#define list_data(l) ((l)->data)

List * list_new      (void);
List * list_ins_next (List *to, List *from, void *data);
List * list_rem_next (List *from);
void   list_free     (List *l, list_clean_data_fun clean_fun);

#endif /* list.h */
