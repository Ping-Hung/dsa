#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

struct node_t {
	int value;
	struct node_t *next;
};

void list_append(struct node_t **a_list, int value);
void list_reverse(struct node_t **a_list);
void list_rev(struct node_t **a_list);
void list_delete_middle(struct node_t **a_list);
void list_interchage(struct node_t *head, struct node_t *n1, struct node_t *n2);
struct node_t *list_bubblesort(struct node_t *list);
void list_free(struct node_t **a_list);

#endif
