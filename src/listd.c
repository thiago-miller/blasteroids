#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h>
#include "error.h"
#include "listd.h"

List *
list_new (void)
{
	List *l = calloc (1, sizeof (List));
	if (l == NULL)
		error ("Failed head create list object");
	return l;
}

void
list_free (List *l, list_clean_data_fun clean_fun)
{
	List *cur = l;

	while (cur != NULL)
		{
			List *next = cur->next;

			if (clean_fun != NULL)
				clean_fun (cur->data);

			free (cur);
			cur = next;
		}
}

List *
list_concat (List *l1, List *l2)
{
	if (l1 == NULL)
		return l2;

	if (l2 == NULL)
		return l1;

	l1->prev = NULL;
	l1->next = l2;
	l2->prev = l1;

	return l1;
}

List *
list_ins_next (List *head, void *data)
{
	List *l = list_new ();
	l->data = data;

	if (head == NULL)
		return l;

	l->next = head->next;
	l->prev = head;

	if (head->next != NULL)
		head->next->prev = l;

	head->next = l;

	return head;
}

List *
list_ins_prev (List *head, void *data)
{
	List *l = list_new ();
	l->data = data;

	if (head == NULL)
		return l;

	l->prev = head->prev;
	l->next = head;

	if (head->prev != NULL)
		head->prev->next = l;

	head->prev = l;

	return l;
}

List *
list_remove_link (List *head, List *l)
{
	if (head == NULL)
		return NULL;

	if (l == NULL)
		return head;

	if (head == l)
		head = head->next;

	if (l->prev != NULL)
		l->prev->next = l->next;

	if (l->next != NULL)
		l->next->prev = l->prev;

	l->next = NULL;
	l->prev = NULL;

	return head;
}
