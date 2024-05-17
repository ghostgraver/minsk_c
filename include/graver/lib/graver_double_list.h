/**
 * @file graver_double_list.h
 * @author laolang (xiaodaima2016@163.com)
 * @brief 双链表
 * @version 0.1
 * @date 2024-05-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief 数据指针定义
 */
typedef void* data_ptr;
/**
 * @brief 链表节点
 */
typedef struct g_dlist_node {
    /**
     * @brief 前置节点
     */
    struct g_dlist_node* prev;
    /**
     * @brief 后置节点
     */
    struct g_dlist_node* next;
    /**
     * @brief 节点值
     */
    data_ptr value;
} g_dlist_node;

/**
 * @brief 节点指针
 */
typedef g_dlist_node* g_dlist_node_ptr;

typedef struct g_dlist  g_dlist;
typedef struct g_dlist* g_dlist_ptr;

/**
 * @brief 双链表节点复制函数指针
 */
typedef void* (*g_dlist_copy_func)(g_dlist_node_ptr ptr);
/**
 * @brief 双链表节点释放函数指针
 */
typedef void* (*g_dlist_free_func)(g_dlist_node_ptr ptr);
/**
 * @brief 双链表节点比较函数指针
 */
typedef int (*g_dlist_compare_func)(g_dlist_node_ptr ptr, data_ptr value);

/**
 * @brief 双链表
 */
typedef struct g_dlist {
    /**
     * @brief 头结点
     */
    g_dlist_node_ptr head;
    /**
     * @brief 尾结点
     */
    g_dlist_node_ptr tail;
    /**
     * @brief 链表长度
     */
    size_t length;
    /**
     * @brief 节点复制函数
     */
    g_dlist_copy_func copy;
    /**
     * @brief 节点释放函数
     */
    g_dlist_free_func free;
    /**
     * @brief 节点比较函数
     */
    g_dlist_compare_func compare;
} g_dlist;
/**
 * @brief 链表指针
 */
typedef g_dlist* g_dlist_ptr;

/**
 * @brief 链表迭代器顺序
 */
typedef enum g_dlist_iter_dir {
    /**
     * @brief 顺序
     */
    ORDER,
    /**
     * @brief 逆序
     */
    REVERSE
} g_dlist_iter_dir;

/**
 * @brief 链表迭代器
 */
typedef struct g_dlist_iter {
    /**
     * @brief 下一个节点指针
     */
    g_dlist_node_ptr* next;
    /**
     * @brief 顺序
     */
    g_dlist_iter_dir dir;
} g_dlist_iter;
/**
 * @brief 链表迭代器指针
 */
typedef g_dlist_iter* g_dlist_iter_ptr;

/**
 * @brief 链表节点访问函数
 */
typedef bool (*g_dlist_visit_func)(g_dlist_node_ptr node_ptr);

/**
 * @brief 创建链表
 * 
 * @return g_dlist_ptr 链表指针
 */
g_dlist_ptr g_dlist_create();
/**
 * @brief 设置链表节点复制函数
 * 
 * @param list 链表指针
 * @param copy 链表节点复制函数
 */
void g_dlist_set_copy_method(g_dlist_ptr list, g_dlist_copy_func copy);
/**
 * @brief 获取列表节点复制函数
 * 
 * @param list 链表指针
 * @return g_dlist_copy_func 链表节点复制函数指针
 */
g_dlist_copy_func g_dlist_get_copy_method(g_dlist_ptr list);
/**
 * @brief 设置链表节点释放函数
 * 
 * @param list 链表指针
 * @param free 链表节点释放函数
 */
void g_dlist_set_free_method(g_dlist_ptr list, g_dlist_free_func free);
/**
 * @brief 获取链表节点释放函数
 * 
 * @param list 链表指针
 * @return g_dlist_free_func 链表节点释放函数指针
 */
g_dlist_free_func g_dlist_get_free_method(g_dlist_ptr list);
/**
 * @brief 设置链表节点比较函数
 * 
 * @param list 链表指针
 * @param compare 链表节点比较函数指针
 */
void g_dlist_set_compare_method(g_dlist_ptr list, g_dlist_compare_func compare);
/**
 * @brief 获取链表节点比较函数
 * 
 * @param list 链表指针
 * @return g_dlist_compare_func 链表节点比较函数指针
 */
g_dlist_compare_func g_dlist_get_compare_method(g_dlist_ptr list);
/**
 * @brief 获取链表长度
 * 
 * @param list 链表指针
 * @return size_t 链表长度
 */
size_t g_dlist_length(g_dlist_ptr list);
/**
 * @brief 获取第一个节点
 * 
 * @param list 链表指针
 * @return g_dlist_node_ptr 节点指针
 */
g_dlist_node_ptr g_dlist_first(g_dlist_ptr list);
/**
 * @brief 获取最后一个节点
 * 
 * @param list 链表指针
 * @return g_dlist_node_ptr 节点指针
 */
g_dlist_node_ptr g_dlist_last(g_dlist_ptr list);
/**
 * @brief 获取前置个节点
 * 
 * @param list 链表指针
 * @param node_ptr 指定节点
 * @return g_dlist_node_ptr 节点指针
 */
g_dlist_node_ptr g_dlist_prev_node(g_dlist_ptr list, g_dlist_node_ptr node_ptr);
/**
 * @brief 获取后置节点
 * 
 * @param list 链表指针
 * @param node_ptr 指定节点 
 * @return g_dlist_node_ptr 节点指针
 */
g_dlist_node_ptr g_dlist_next_node(g_dlist_ptr list, g_dlist_node_ptr node_ptr);
/**
 * @brief 获取指定节点值
 * 
 * @param list 链表指针
 * @param node_ptr 指定节点
 * @return data_ptr 节点值
 */
data_ptr g_dlist_node_value(g_dlist_ptr list, g_dlist_node_ptr node_ptr);
/**
 * @brief 释放链表
 * 
 * @param list 链表指针
 */
void g_dlist_release(g_dlist_ptr list);
/**
 * @brief 在头部添加节点
 * 
 * @param list 链表指针
 * @param value 节点值
 * @return g_dlist_node_ptr 添加的节点的指针
 */
g_dlist_node_ptr g_dlist_add_note_head(g_dlist_ptr list, data_ptr value);
/**
 * @brief 在尾部添加节点
 *
 * @param list 链表指针
 * @param value 节点值
 * @return g_dlist_node_ptr 添加的节点的指针
 */
g_dlist_node_ptr g_dlist_add_note_tail(g_dlist_ptr list, data_ptr value);
// /**
//  * @brief 在指定节点后插入节点
//  *
//  * @param list 链表指针
//  * @param node_ptr 指定节点
//  * @param value 节点值
//  * @return g_dlist_node_ptr 插入的节点指针
//  */
// g_dlist_node_ptr g_dlist_insert(g_dlist_ptr list, g_dlist_node_ptr node_ptr, data_ptr value);
// /**
//  * @brief 删除指定节点
//  *
//  * @param list 链表指针
//  * @param node_ptr 要删除的节点
//  */
// void g_dlist_delete_node(g_dlist_ptr list, g_dlist_node_ptr node_ptr);
// /**
//  * @brief 获取链表迭代器
//  *
//  * @param list 链表指针
//  * @return g_dlist_iter_ptr 迭代器指针
//  */
// g_dlist_iter_ptr g_dlist_get_iterator(g_dlist_ptr list);
// /**
//  * @brief 获取迭代器下一个节点
//  *
//  * @param iter_ptr 迭代器指针
//  * @return g_dlist_node_ptr 下一个节点指针
//  */
// g_dlist_node_ptr g_dlist_next(g_dlist_iter_ptr iter_ptr);
// /**
//  * @brief 释放链表迭代器
//  *
//  * @param iter_ptr 迭代器指针
//  */
// void g_dlist_release_iterator(g_dlist_iter_ptr iter_ptr);
// /**
//  * @brief 搜索指定值
//  *
//  * @param list 链表指针
//  * @param value 节点值
//  * @return g_dlist_node_ptr 搜索到的节点指针
//  */
// g_dlist_node_ptr g_dlist_search_key(g_dlist_ptr list, data_ptr value);
// /**
//  * @brief 获取指针索引的节点
//  *
//  * @param list 链表指针
//  * @param index 索引值
//  * @return g_dlist_node_ptr 获取到的节点指针
//  */
// g_dlist_node_ptr g_dlist_search_at(g_dlist_ptr list, long index);

// /**
//  * @brief 从链表中剔除指定节点(不释放节点)
//  *
//  * @param list 链表指针
//  * @param node_ptr 需要剔除的节点
//  */
// void g_dlist_unlink_node(g_dlist_ptr list, g_dlist_node_ptr node_ptr);
// /**
//  * @brief 翻转链表
//  *
//  * @param list 链表指针
//  */
// void g_dlist_reverse(g_dlist_ptr list);
// /**
//  * @brief 链表排序
//  *
//  * @param list 链表指针
//  */
// void g_dlist_sort(g_dlist_ptr list);

/**
 * @brief 初始化节点
 * 
 * @param value 节点值
 * @return g_dlist_node_ptr 节点指针
 */
g_dlist_node_ptr g_dlist_init_node(data_ptr value);

/**
 * @brief 判断指定节点是否存在于链表中
 * 
 * @param list 链表指针
 * @param node_ptr 指定节点
 * @return true 存在
 * @return false 不存在
 */
bool g_dlist_exist_node(g_dlist_ptr list, g_dlist_node_ptr node_ptr);

/**
 * @brief 遍历链表
 * 
 * @param list 链表指针
 * @param g_dlist_visit_func 节点访问函数
 * @return true 操作成功
 * @return false 操作失败
 */
bool g_dlist_visit(g_dlist_ptr list, g_dlist_visit_func visit_func);