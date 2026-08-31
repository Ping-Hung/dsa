#include "linked_list.h"

void list_append(struct node_t **a_list, int value)
{
	for (; *a_list; a_list = &(*a_list)->next);
	*a_list = malloc(sizeof(**a_list));
	**a_list = (struct node_t) {.value = value, .next = NULL};
}

void list_reverse(struct node_t **a_list)
{
	struct node_t *rev_list = NULL;
	while (*a_list) {
		struct node_t *neighbor = (*a_list)->next;
		// change pointers
		(*a_list)->next = rev_list;
		rev_list = *a_list;
		// loop update
		*a_list = neighbor;
	}
	*a_list = rev_list;
}

void list_rev(struct node_t **a_list)
{
	if (!(*a_list) || !(*a_list)->next)	
		return;
	 /*
	  * while recursing:
	  * 1) advance *a_list to the last node, 
	  * 2) do appropriate pointer swaps (i.e. propagate NULL to the original front) 
	  */
	struct node_t *curr = *a_list;
	*a_list = (*a_list)->next;

	list_rev(a_list);

	curr->next->next = curr;
	curr->next = NULL;
}

void list_delete_middle(struct node_t **a_list)
{
	// walk the list to the middle
	struct node_t *fast = *a_list;
	while (fast && fast->next) {
		a_list = &(*a_list)->next;
		fast = fast->next->next;
	}
	// *a_list is (addr of) the actual middle node, while a_list is the 
	// (addr of) the *next* field of the node before it
	fast = *a_list;
	*a_list = (*a_list)->next;
	free(fast);
}

static inline void _exchange_pos(struct node_t **n1, struct node_t **n2)
{
	// exchange the relative position of n1 and n2. i.e.,
	struct node_t *t = *n1;
	if (&(*n1)->next == n2) {
		*n1 = *n2;			// *n1 becomes *n2
		*n2 = (*n2)->next;		// *n2 becomes the rest of the list
		(*n1)->next = t;		// *n1 (which now stores old *n2) is linked back to the original *n1
		return;
	}
	if (&(*n2)->next == n1) {
		t = *n2;
		*n2 = *n1;			// *n2 becomes *n1
		*n1 = (*n1)->next;		// *n2 becomes the rest of the list
		(*n2)->next = t;		// *n1 (which now stores old *n2) is linked back to the original *n1
		return;
	}
	t = (*n1)->next;
	(*n1)->next = (*n2)->next;
	(*n2)->next = t;

	t = *n1;
	*n1 = *n2;
	*n2 = t;
}

void list_interchage(struct node_t *head, struct node_t *n1, struct node_t *n2)
{	
	/* find n1 and n2 in list pointed to by head and interchange their relative position in the list. E.g.,
	 * 1 → 2 → 3 → 4 → ∅ ⇒ list_interchange(head, 1, 4) ⇒  4 → 2 → 3 → 1 → ∅ 
	 */

	// head is the addr (of the varialbe) that holds the addr of the first node in the list in the caller's stack frame
	if (n1 != n2) {
		// look for the actual *next* (or pointer fields) that points to n1 and n2
		struct node_t **a_n1 = &head, **a_n2 = &head;
		while (*a_n1 && *a_n1 != n1) {
			a_n1 = &(*a_n1)->next;
		}
		while (*a_n2 && *a_n2 != n2) {
			a_n2 = &(*a_n2)->next;
		}
		_exchange_pos(a_n1, a_n2);
	}
}


struct node_t *list_bubblesort(struct node_t *list)
{
	if (!list || !list->next) {
		return list;
	}

	bool sorted = false;
	struct node_t *last_elem = NULL;
	while (!sorted) {
		sorted = true;
		struct node_t *end = last_elem;

		struct node_t **prev = &list, **curr = &list->next;
		while (*curr && *curr != end) {
			if ((*prev)->value > (*curr)->value) {
				sorted = false;
				last_elem = *prev;
				_exchange_pos(prev, curr);
				prev = &(*prev)->next;
				continue;
			}
			prev = &(*prev)->next;
			curr = &(*curr)->next;
		}
	}

	return list;
}


void list_free(struct node_t **a_list)
{
	while (*a_list) {
		struct node_t *tmp = *a_list;
		*a_list = (*a_list)->next;
		free(tmp);
	}
}
