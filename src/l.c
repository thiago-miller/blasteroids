#if HAVE_CONFIG_H
# include <config.h>
#endif

#include "error.h"
#include "l.h"

List *
list_new (ListDestroy destroy_fun)
{
	List *list = malloc (sizeof (List));
	if (list == NULL)
		error ("Failed to create List");

	*list = (List) {
		.size        = 0,
		.head        = NULL,
		.tail        = NULL,
		.destroy_fun = destroy_fun
	};

	return list;
}

static ListElmt *
list_element_new (const void *data)
{
	ListElmt *element = malloc (sizeof (ListElmt));
	if (element == NULL)
		error ("Failed to create ListElmt");

	*element = (ListElmt) {
		.next = NULL,
		.prev = NULL,
		.data = (void*) data
	};

	return element;
}

bool
list_append (List *list, const void *data)
{
	return list_ins_next (list, list->tail, data);
}

bool
list_append_link (List *list, ListElmt *element)
{
	return list_ins_next_link (list, list->tail, element);
}

bool
list_prepend (List *list, const void *data)
{
	return list_ins_prev (list, list->head, data);
}

bool
list_prepend_link (List *list, ListElmt *element)
{
	return list_ins_prev_link (list, list->head, element);
}

bool
list_ins_next (List *list, ListElmt *element, const void *data)
{
	ListElmt *new_element = list_element_new (data);
	return list_ins_next_link (list, element, new_element);
}

bool
list_ins_next_link (List *list, ListElmt *element, ListElmt *new_element)
{
	// Do not allow a NULL element unless the list is empty
	// Do nor allow a NULL new_element
	if ((element == NULL && list->size != 0) || new_element == NULL)
		return false;

	if (list->size == 0)
		{
			// Handle insertion when the list is empty
			list->head = new_element;
			list->tail = new_element;
		}
	else
		{
			// Handle insertion when the list is not empty
			new_element->next = element->next;
			new_element->prev = element;

			if (element->next == NULL)
				list->tail = new_element;
			else
				element->next->prev = new_element;

			element->next = new_element;
		}

	list->size++;
	return true;
}

bool
list_ins_prev (List *list, ListElmt *element, const void *data)
{
	ListElmt *new_element = list_element_new (data);
	return list_ins_prev_link (list, element, new_element);
}

bool
list_ins_prev_link (List *list, ListElmt *element, ListElmt *new_element)
{
	// Do not allow a NULL element unless the list is empty
	// Do nor allow a NULL new_element
	if ((element == NULL && list->size != 0) || new_element == NULL)
		return false;

	if (list->size == 0)
		{
			// Handle insertion when the list is empty
			list->head = new_element;
			list->tail = new_element;
		}
	else
		{
			// Handle insertion when the list is not empty
			new_element->next = element;
			new_element->prev = element->prev;

			if (element->prev == NULL)
				list->head = new_element;
			else
				element->prev->next = new_element;

			element->prev = new_element;
		}

	list->size++;
	return true;
}

void
list_free (List *list)
{
	while (list->size > 0)
		{
			void *data;
			if (list_remove (list, list->tail, &data) && list->destroy_fun != NULL)
				list->destroy_fun (data);
		}

	free (list);
}

bool
list_remove (List *list, ListElmt *element, void **data)
{
	if (!list_remove_link (list, element))
		return false;

	if (data != NULL)
		*data = element->data;

	free (element);
	return true;
}

bool
list_remove_link (List *list, ListElmt *element)
{
	if (list->size == 0 || element == NULL)
		return false;

	if (element == list->head)
		{
			// Handle removal from the head of the list
			list->head = element->next;
			if (list->head == NULL)
				list->tail = NULL;
			else
				element->next->prev = NULL;
		}
	else
		{
			// Handle removal from other than the head of the list
			element->prev->next = element->next;

			if (element->next == NULL)
				list->tail = element->prev;
			else
				element->next->prev = element->prev;
		}

	list->size--;
	return true;
}
