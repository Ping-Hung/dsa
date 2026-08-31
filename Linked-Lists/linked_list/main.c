#include "linked_list.h"

static void display(struct node_t *list);
static int power(int a, int exp);
static inline struct node_t *kth_node(int k, struct node_t *list);
int p(int a, int exp);

int main(int argc, char *argv[]) 
{
	printf("%lu %lu\n", sizeof(int), sizeof(long));

	// arrange
	struct node_t *list = NULL;

	// act and assert (print out)

	for (int i = 0; i < 21; ++i) {
		int expected = power(2, i);
		int test = p(2, i);
		list_append(&list, expected);
		if (test != expected) {
			printf("power(2, %d) = %d != %d = p(2, %d)\n", 
					i, expected, test, i);
			break;
		}
	}
	printf("build list\n");
	display(list);

	printf("reverse list\n");
	list_reverse(&list);
	display(list);

	printf("reverse list (recursive)\n");
	list_rev(&list);
	display(list);

	printf("delete middle node\n");
	list_delete_middle(&list);
	display(list);

	int n1 = 5, n2 = 17;
	printf("interchange the %dth and the %dth node\n", n1, n2);
	list_interchage(list, kth_node(n1, list), kth_node(n2, list));
	display(list);

	printf("randomizing list (value swaps)...\n");
	struct node_t *node = list;
	for (int i = 1; i <= 5; i++) {
		struct node_t *kth = kth_node(20 - i, list);
		if (node && kth) {
			int tmp = node->value;
			node->value = kth->value;
			kth->value = tmp;
		}
		node = node->next;
	}
	display(list);


	printf("bubblesort list\n");
	list = list_bubblesort(list);
	display(list);

	// teardown
	printf("release memory (deallocate)\n");
	list_free(&list);
	display(list);
	return EXIT_SUCCESS;
}

static void display(struct node_t *list)
{
	for (; list; list = list->next)
		printf("%d->", list->value);
	printf("NULL\n");
}

static int power(int a, int exp)
{
	if (exp <= 0)	return 1;

	if (exp & 1)	return a * power(a * a, exp >> 1);
	
	return power(a * a, exp >> 1);
}

int p(int a, int exp)
{
	if (exp <= 0)	return 1;

	int result = 1;
	while (exp > 0) {
		if (exp & 1)
			result *= a;
		a *= a;
		exp >>= 1;
	}
	return result;
}

static inline struct node_t *kth_node(int k, struct node_t *list)
{
	// k = 1 is the same as k = 0, just list itself
	while (k > 1 && list && list->next) {
		k -= 1;
		list = list->next;
	}
	return list;
}

