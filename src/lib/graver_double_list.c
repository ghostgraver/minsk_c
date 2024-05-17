#include "graver/lib/graver_double_list.h"

#include <stdlib.h>

g_dlist_ptr g_dlist_create() {
    // 头节点
    g_dlist_node_ptr node_head = (g_dlist_node_ptr)malloc(sizeof(g_dlist_node));
    node_head->prev            = NULL;
    node_head->next            = NULL;
    node_head->value           = NULL;

    // 尾节点
    g_dlist_node_ptr node_tail = (g_dlist_node_ptr)malloc(sizeof(g_dlist_node));
    node_tail->prev            = NULL;
    node_tail->next            = NULL;
    node_tail->value           = NULL;

    // 链接头尾节点
    node_head->next = node_tail;
    node_tail->prev = node_head;

    // 链表
    g_dlist_ptr list = (g_dlist_ptr)malloc(sizeof(g_dlist));
    list->head       = node_head;
    list->tail       = node_tail;
    list->length     = 0;
    list->copy       = NULL;
    list->free       = NULL;
    list->compare    = NULL;

    return list;
}

void g_dlist_set_copy_method(g_dlist_ptr list, g_dlist_copy_func copy) {
    if (NULL == list || NULL == copy) {
        return;
    }
    list->copy = copy;
}

g_dlist_copy_func g_dlist_get_copy_method(g_dlist_ptr list) {
    return NULL == list ? NULL : list->copy;
}

void g_dlist_set_free_method(g_dlist_ptr list, g_dlist_free_func free) {
    if (NULL == list || NULL == free) {
        return;
    }
    list->free = free;
}

g_dlist_free_func g_dlist_get_free_method(g_dlist_ptr list) {
    return NULL == list ? NULL : list->free;
}

void g_dlist_set_compare_method(g_dlist_ptr list, g_dlist_compare_func compare) {
    if (NULL == list || NULL == compare) {
        return;
    }
    list->compare = compare;
}

g_dlist_compare_func g_dlist_get_compare_method(g_dlist_ptr list) {
    return NULL == list ? NULL : list->compare;
}

size_t g_dlist_length(g_dlist_ptr list) {
    if (NULL == list) {
        return 0;
    }

    return list->length;
}

g_dlist_node_ptr g_dlist_first(g_dlist_ptr list) {
    if (NULL == list || 0 == list->length) {
        return NULL;
    }

    return list->head->next;
}

g_dlist_node_ptr g_dlist_last(g_dlist_ptr list) {
    if (NULL == list || 0 == list->length) {
        return NULL;
    }

    return list->tail->prev;
}

g_dlist_node_ptr g_dlist_prev_node(g_dlist_ptr list, g_dlist_node_ptr node_ptr) {
    if (NULL == list || NULL == node_ptr) {
        return NULL;
    }

    if (!g_dlist_exist_node(list, node_ptr)) {
        return NULL;
    }

    return list->head->next == node_ptr ? NULL : node_ptr->prev;
}

g_dlist_node_ptr g_dlist_next_node(g_dlist_ptr list, g_dlist_node_ptr node_ptr) {
    if (NULL == list || NULL == node_ptr) {
        return NULL;
    }

    if (!g_dlist_exist_node(list, node_ptr)) {
        return NULL;
    }

    return node_ptr->next == list->tail ? NULL : node_ptr->next;
}

data_ptr g_dlist_node_value(g_dlist_ptr list, g_dlist_node_ptr node_ptr) {
    if (NULL == list || NULL == node_ptr) {
        return NULL;
    }

    if (!g_dlist_exist_node(list, node_ptr)) {
        return NULL;
    }

    return node_ptr->value;
}

void g_dlist_release(g_dlist_ptr list) {
    if (NULL == list) {
        return;
    }

    if (list->length > 0) {
        g_dlist_node_ptr node = list->head->next;
        while (list->tail != node) {
            g_dlist_node_ptr t = node;
            node               = node->next;
            if (NULL == list->free) {
                free(t);
            } else {
                list->free(t);
            }
        }
    }

    free(list->head);
    free(list->tail);
    list->head   = NULL;
    list->tail   = NULL;
    list->length = 0;
    free(list);
    list = NULL;
}

g_dlist_node_ptr g_dlist_add_note_head(g_dlist_ptr list, data_ptr value) {
    if (NULL == list) {
        return NULL;
    }
    g_dlist_node_ptr node  = g_dlist_init_node(value);
    node->next             = list->head->next;
    node->prev             = list->head;
    list->head->next->prev = node;
    list->head->next       = node;
    list->length++;
    return node;
}

g_dlist_node_ptr g_dlist_add_note_tail(g_dlist_ptr list, data_ptr value) {
    if (NULL == list) {
        return NULL;
    }
    g_dlist_node_ptr node  = g_dlist_init_node(value);
    node->prev             = list->tail->prev;
    node->next             = list->tail;
    list->tail->prev->next = node;
    list->tail->prev       = node;
    list->length++;
    return node;
}

g_dlist_node_ptr g_dlist_init_node(data_ptr value) {
    g_dlist_node_ptr node = (g_dlist_node_ptr)malloc(sizeof(g_dlist_node));
    node->prev            = NULL;
    node->next            = NULL;
    node->value           = value;
    return node;
}

bool g_dlist_exist_node(g_dlist_ptr list, g_dlist_node_ptr node_ptr) {
    if (NULL == list || NULL == node_ptr) {
        return NULL;
    }

    g_dlist_node_ptr node = list->head->next;
    bool             find = false;
    while (list->tail != node) {
        if (node == node_ptr) {
            find = true;
            break;
        }
        node = node->next;
    }
    return find;
}

bool g_dlist_visit(g_dlist_ptr list, g_dlist_visit_func visit_func) {
    if (NULL == list || 0 == list->length || NULL == visit_func) {
        return false;
    }

    bool ret = true;

    g_dlist_node_ptr node = list->head->next;
    while (list->tail != node) {
        if (!visit_func(node)) {
            ret = false;
            break;
        }
        node = node->next;
    }

    return ret;
}