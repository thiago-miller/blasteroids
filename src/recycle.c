#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h>
#include "error.h"
#include "recycle.h"

Recycle *
recycle_new (RecycleCreate create_fun, RecycleDestroy destroy_fun)
{
	Recycle *recycle = malloc (sizeof (Recycle));
	if (recycle == NULL)
		error ("Failed to create Recycle");

	*recycle = (Recycle) {
		.live       = list_new (destroy_fun),
		.trash      = list_new (destroy_fun),
		.create_fun = create_fun
	};

	return recycle;
}

void
recycle_free (Recycle *recycle)
{
	if (recycle == NULL)
		return;

	list_free (recycle->live);
	list_free (recycle->trash);

	free (recycle);
}

ListElmt *
recycle_get_list_element (Recycle *recycle)
{
	ListElmt *element = NULL;

	if (list_size (recycle->trash) == 0)
		{
			list_append (recycle->live, recycle->create_fun ());
			element = list_tail (recycle->live);
		}
	else
		{
			element = list_head (recycle->trash);
			list_remove_link (recycle->trash, element);
			list_append_link (recycle->live, element);
		}

	return element;
}

void
recycle_remove_list_element (Recycle *recycle, ListElmt *element)
{
	list_remove_link (recycle->live, element);
	list_append_link (recycle->trash, element);
}
