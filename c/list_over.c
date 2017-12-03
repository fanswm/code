#include "list_over.h"


int main(void)
{
	pList_node head, phead,*pphead;
	
	pphead = &phead;
	
	phead = list_init(pphead);
		
	phead = list_new_node("first\0");
	list_display(phead);
	
	list_append(pphead, "second\0");
	list_display(phead);
	
	phead = list_push_head(pphead, "push head\0");
	phead = list_push_head(pphead, "push 2head\0");
	list_display(phead);
		
	printf("del head:\n");
	phead = list_del_head(pphead);
	list_display(phead);
	
	head = list_find_data(pphead, "first\0");
	printf("head->data = %s\n", head->data);
	
	phead = list_del_middle_node_by_data(pphead, "first\0");
	list_display(phead);
	
	printf("count: %d\n", list_count_node(phead));
	
	head = list_find_data(pphead, "second\0");
	phead = list_insert_middle_node(pphead, &head, "middle\0");
	list_display(phead);
	
	printf("count: %d\n", list_count_node(phead));
	
	list_free_all(pphead);
}


/* 数据传输方法 */
void list_data_copy_method(pList_node *node, \
				const Data_type data)
{
	assert(NULL != node && NULL != data);
	strcpy((*node)->data, data);
}

/* 数据比较方法：
相等：0
大于：>0
小于：<0*/
int list_data_compare(const Data_type data1,\
			const Data_type data2)
{
	return (strcmp(data1, data2));
}

/* 计算数据长度的方法 */
size_t list_data_length(Data_type data)
{
	size_t len;
	len = strlen(data);
	return len;
}

/* 初始化 */
pList_node list_init(pList_node *head)
{
	assert(NULL !=head);
	*head = NULL;
}

/* 申请一个新的节点 */
pList_node list_new_node(const Data_type data)
{
	pList_node *pn, new_node;
	
	new_node = (pList_node)malloc(sizeof(List_node));
	pn = &new_node;
	
	if(NULL == new_node)
	{
		printf("error: out of memeory.\n");
		return NULL;
	}
	else
	{
		(*pn)->data = (Data_type)calloc(list_data_length(data), 1);
		if((*pn)->data == NULL)
		{
			printf("error: out of memeory.\n");
			return NULL;
		}
		else
		{
			list_data_copy_method(pn, data);
			(*pn)->next = NULL;
		}
	}
	return new_node;
}

/* 显示链表（字符串数据） */
void list_display(pList_node head)
{
	pList_node p;
	assert(NULL != head);
	p = head;
	while(p != NULL)
	{
		printf("%s\t", p->data);
		p = p->next;
	}
	printf("\n");
}

/* 释放一个节点，危险，如果这个节点不是尾节点！！！ */
void list_free_one_node(pList_node *node)
{
	assert(NULL != node && NULL != (*node));
	
	free((*node)->data);
	(*node)->data = NULL;
	free(*node);
	*node = NULL;
}

/* 删除尾节点 */
void list_pop_tail(pList_node *head)
{
	pList_node tmp, *pt;
	
	assert(NULL != head);
	if(NULL == *head)
	{
		return;
	}
	else if(NULL == (*head)->next)
	/* 头节点就是尾节点 */
	{
		pt = head;
		list_free_one_node(pt);
	}
	else
	{
		tmp = *head;
		while(NULL != tmp->next)
		{
			tmp = tmp->next;
		}/* 找到尾节点 */
		pt = &tmp;
		list_free_one_node(pt);		
	}
	tmp = NULL;
	pt = NULL;
}

/* 在尾部添加节点 */
pList_node list_append(pList_node *head,\
			const Data_type data)
{
	pList_node p = NULL;
	assert(NULL != head && NULL != data);
	
	if(NULL == *head)
	{
		*head = list_new_node(data);
	}
	else
	{
		p = *head;
		while(NULL != p->next)
		{
			p = p->next;
		}
		p->next = list_new_node(data);
	}
	return (*head);
}

/* 在头部添加节点 */
pList_node list_push_head(pList_node *head,\
			const Data_type data)
{
	pList_node p1, p2;
	assert(NULL != head && NULL != data);
	p1 = NULL;
	p2 = list_new_node(data);
	
	p1 = *head;
	p2->next = p1;
	*head = p2;
	
	return (*head);
}

/* 删除头部节点 */
pList_node list_del_head(pList_node *head)
{
	pList_node p;
	assert(NULL != head);
	
	p = *head;
	if(NULL == *head)
	{
		printf("NULL == *head!\n");
		return NULL;
	}
	else if(NULL == (*head)->next)
	{
		printf("*head->next == NULL\n");
		list_free_one_node(head);
		*head = NULL;
	}
	else
	{
		*head = p->next;
		list_free_one_node(&p);
		p = NULL;
	}	
	return (*head);
}

/* 查找数据，返回所在节点的指针 */
pList_node list_find_data(pList_node *head,\
		const Data_type data)
{
	pList_node p;
	assert(NULL != head && data != NULL);
	
	p = *head;
	while(NULL != p)
	{
		if(list_data_compare(p->data, data) == 0)
		{
			break;
		}
		p = p->next;
	}
	return p;
}

/* 在中间添加节点, by pointer */
pList_node list_insert_middle_node(pList_node *head,\
			pList_node *after,\
			const Data_type insert_data)
{
	pList_node p1, p2;
	assert(NULL != *head 
		&& NULL != insert_data
		&& NULL != *after);
	p1 = NULL;
	p2 = (*head)->next;
	
	while(p2 != NULL)
	{
		p2 = p2->next;
	}
	
	if(*head == *after || *after == p2)
	/* after是头结点（只有一个节点的链表）
	或者after是尾结点 */
	{
		return (list_append(head, insert_data));
	}
	else
	{	
		p1 = *after;
		p2 = (*after)->next;
		p1->next = list_new_node(insert_data);
		(p1->next)->next = p2;
		
		return (*head);
	}
}

/* 删除中间节点(用指针) */
pList_node list_del_middle_node_by_pointer(pList_node *head,\
			pList_node *del)
{
	pList_node p1, p2;
	assert(NULL != *head 
		&& *del != NULL);
	p1 = NULL;
	p2 = (*head)->next;
	
	while(p2 != NULL)
	{
		p2 = p2->next;
	}/* p2 = 尾节点 */
	
	if(*del == *head)/* 如果*del是头节点 */
	{
		p2 = NULL;
		return list_del_head(del);
	}
	else if(*del == p2) /* 如果del是尾节点 */
	{
		p2 = NULL;
		return (*head);
	}
	else
	{
		p2 = (*head)->next;
		p1 = *head;
		while(p2 != *del)
		{
			p1 = p2;
			p2 = p2->next;
		}/* p2 == *del; p1 == before *del */
		p1->next = p2->next;
		return (*head);
		p2 = NULL;		
	}
}

/* 删除找到的第一个数据 data的节点 */
pList_node list_del_middle_node_by_data(pList_node *head,\
					const Data_type data)
{
	pList_node p;
	p = list_find_data(head, data);
	return list_del_middle_node_by_pointer(head, &p);
}

/* 统计链表的总节点数 */
unsigned int list_count_node(pList_node head)
{
	unsigned int count = 0;
	pList_node p;
	p = head;
	while(p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}

/* 释放所有节点 */
void list_free_all(List_node **head)
{
	pList_node tmp, *p;
	p = head;
	tmp = *p;
	if(NULL == head || (*head) == NULL)
	{
		return;
	}
	while(tmp != NULL)
	{
		tmp = tmp->next;
		
		free((*p)->data);
		(*p)->data = NULL;
		free(*p);
		(*p) = tmp;
	}
}




