# 19. Remove Nth Node From End of List
Given the head of a linked list, remove the nth node from the end of the list and return its head.

# Solutions
## Two-Pass
1. Count total nodes.
2. Walk to target node (the `total - n`th node count from beginning).
3. Remove the node.

```c
struct ListNode {
     int val;
     struct ListNode *next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    int total_nodes = 0;
    struct ListNode **a_victim = &head;

    // count total nodes
    for (struct ListNode *l = head; l; l = l->next) {
        total_nodes++;
    }

    // walk the list to target node
    while (*a_victim && total_nodes - n > 0) {
        total_nodes--;
        a_victim = &(*a_victim)->next;
    }

    // remove target node (overwrites the *next* field and releasing memory)
    struct ListNode *victim = *a_victim;
    *a_victim = (*a_victim)->next;
    free(victim);

    return head;
}
```

## Two-Pointers
1. Initialize `fast` and `slow`, both pointing at `head`
~~2. Advance both pointers
    - Ensure `fast` is `n` steps ahead of `slow`~~
    - Don't overthink
2. Move `fast` ahead by `n` steps, then advance `slow` until `fast` reaches the last node.

```c
struct ListNode {
     int val;
     struct ListNode *next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    // Two Pointers: move fast n steps ahead, then maintain the gap
    // invariant: fast is a valid ListNode that is always n steps ahead of slow 
    struct ListNode *fast = head, **slow = &(head)->next;
    for (int i = 0; i < n; i++) {
        fast =  fast->next;
    }
    if (!fast) {
        // total_nodes - n nodes from the head (n nodes away from the last node)
        return head->next;
    }

    // advance fast and slow
    while (fast && fast->next) {
        fast = fast->next;
        slow = &(*slow)->next;
    }

    // remove node
    struct ListNode *victim = *slow;
    *slow = (*slow)->next;
    free(victim);

    return head;
}
```
