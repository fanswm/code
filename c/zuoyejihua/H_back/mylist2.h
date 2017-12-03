#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef char *Data_type;
/* 如果把这个数据类型换成非指针的类型，
下面所有包含此类型的函数全部重写 */

struct LIST_NODE
{
	Data_type data;
	struct LIST_NODE * next;
};

typedef struct LIST_NODE List_node;
typedef List_node *pList_node;

/* 数据传输方法 */
void list_data_copy_method(pList_node *node, \
				const Data_type data);

/* 数据比较方法：
相等：0
大于：>0
小于：<0*/
int list_data_compare(const Data_type data1,\
			const Data_type data2);
/* 计算数据长度的方法 */
size_t list_data_length(Data_type data);
/* 初始化 */
pList_node list_init(pList_node *head);
/* 申请一个新的节点 */
pList_node list_new_node(const Data_type data);
/* 显示链表（字符串数据） */
void list_display(pList_node head);

/* 释放一个节点，危险，如果这个节点不是尾节点！！！ */
void list_free_one_node(pList_node *node);

/* 删除尾节点 */
void list_pop_tail(pList_node *head);

/* 在尾部添加节点 */
pList_node list_append(pList_node *head,\
			const Data_type data);

/* 在头部添加节点 */
pList_node list_push_head(pList_node *head,\
			const Data_type data);

/* 删除头部节点 */
pList_node list_del_head(pList_node *head);

/* 查找数据，返回所在节点的指针 */
pList_node list_find_data(pList_node *head,\
		const Data_type data);

/* 在中间添加节点, by pointer */
pList_node list_insert_middle_node(pList_node *head,\
			pList_node *after,\
			const Data_type insert_data);

/* 删除中间节点(用指针) */
pList_node list_del_middle_node_by_pointer(pList_node *head,\
			pList_node *del);

/* 删除找到的第一个数据 data的节点 */
pList_node list_del_middle_node_by_data(pList_node *head,\
					const Data_type data);

/* 统计链表的总节点数 */
unsigned int list_count_node(pList_node head);

/* 释放所有节点 */
void list_free_all(List_node **head);

