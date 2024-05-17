#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graver/lib/graver_double_list.h"

void add_node(g_dlist_ptr list, int v);

bool value_visit(g_dlist_node_ptr node_ptr);

int main() {
    g_dlist_ptr list = g_dlist_create();
    for (int i = 1; i <= 5; i++) {
        add_node(list, i);
    }
    g_dlist_visit(list, value_visit);
    printf("\n");

    g_dlist_release(list);

    return 0;
}

void add_node(g_dlist_ptr list, int v) {
    int* v_ptr = (int*)malloc(sizeof(int));
    *v_ptr     = v;
    g_dlist_add_note_tail(list, v_ptr);
}

bool value_visit(g_dlist_node_ptr node_ptr) {
    if (NULL == node_ptr || NULL == node_ptr->value) {
        return false;
    }
    int v = *((int*)node_ptr->value);
    printf("%d ", v);
    return true;
}