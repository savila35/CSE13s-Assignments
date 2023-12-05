#include "pq.h"

#include <stdio.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};
struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        return NULL;
    }
    pq->list = NULL;
    return pq;
}

void pq_free(PriorityQueue **q) {
    if (*q != NULL) {
        ListElement *current = (*q)->list;
	ListElement *temp;
        while (current != NULL) {
            temp = current;
            current = current->next;
            node_free(&temp->tree);
            free(temp);
        }
        free(*q);
        *q = NULL;
    }
}

bool pq_is_empty(PriorityQueue *q) {
    if (q->list == NULL || q == NULL) {
        return true;
    } else {
        return false;
    }
}

bool pq_size_is_1(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        return false;
    }
    int count = 0;
    ListElement *current = q->list;
    while (current != NULL) {
	    count++;
	    current = current->next;
    }
    return (count == 1);
}

bool pq_less_than(ListElement *e1, ListElement *e2) {
    if (e1->tree->weight < e2->tree->weight) {
        return true;
    } else if (e1->tree->weight == e2->tree->weight) {
        if (e1->tree->symbol < e2->tree->symbol) {
            return true;
        }
    }
    return false;
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *new_element = (ListElement *) malloc(sizeof(ListElement));
    new_element->tree = tree;
    new_element->next = NULL;

    if (pq_is_empty(q)) {
        q->list = new_element;
	return;
    } else if (pq_less_than(new_element, q->list)) {
        new_element->next = q->list;
        q->list = new_element;
	return;
    } else {
        ListElement *current = q->list;
        while (true) {
            if (current->next == NULL) {
                current->next = new_element;
		return;
            } else if (pq_less_than(new_element, current->next)) {
                new_element->next = current->next;
                current->next = new_element;
		    return;
            }
            current = current->next;
        }
    }
}

Node *dequeue(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        fprintf(stderr, "error: pq is empty cannot dequeue\n");
        exit(1);
    }
    Node *node = q->list->tree;
    q->list = q->list->next;
    return node;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree);
        e = e->next;
    }
    printf("=============================================\n");
}
