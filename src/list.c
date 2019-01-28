#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h>
#include "error.h"
#include "list.h"

List *
list_new (void)
{
	List *l = calloc (1, sizeof (List));
	if (l == NULL)
		error ("Failed to create list object");
	return l;
}

void
list_free (List *l, list_clean_data_fun clean_fun)
{
	List *cur = l;

	while (cur != NULL)
		{
			List *next = cur->next;

			if (clean_fun != NULL && cur->data != NULL)
				clean_fun (cur->data);

			free (cur);
			cur = next;
		}
}

List *
list_ins_next (List *to, List *from, void *data)
{
	if (from == NULL)
		from = list_new ();

	from->next = NULL;
	from->data = data;

	if (to == NULL)
		return from;

	from->next = to->next;
	to->next = from;

	return to;
}

List *
list_rem_next (List *from)
{
	if (from == NULL)
		return NULL;

	List *rem = from->next;

	if (rem == NULL)
		return NULL;

	from->next = rem->next;
	rem->next = NULL;

	return rem;
}
