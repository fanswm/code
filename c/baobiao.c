/* By: gcc version 3.4.5(mingw-vista special r3) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	DATA_LEN	(sizeof(DATA))
#define	NODE_LEN	(sizeof(NODE))
#define STRING_LEN	1024
#define DATA_ITEMS	6
#define ERROR_NUM	1
#define ERROR_LEVEL	9
#define ERROR_FILE_NAME	"error_logfile.txt"
#define SAME_NODES_MAX	3
#define ALL_SAME_NODES_MAX	10

typedef unsigned int MY_U_INT;
typedef unsigned char MY_BOOL;

struct my_data
{
        char *name;
        double jihua;
        double hengsi;
        double guobeng;
        double tiaojie;
        char *zhushi;
};
typedef struct my_data DATA;

struct node
{
        struct node *pre;
        struct node *next;
        struct node *tail;
        DATA *p_data;
};

typedef struct node NODE;

struct same_node
{
	MY_U_INT count;	/* how much? */
	char *name;	/* who? max: STRING_LEN */
	MY_U_INT **pp_pos;	/* where? */
};
typedef struct same_node SAME_NODE;
struct all_same_nodes
{
	MY_U_INT count;
	SAME_NODE **pp_same_nodes;
};
typedef struct all_same_nodes ALL_SAME_NODES;

/* func_name: errornumber: description */
void error_write_logfile(const char *func_name, \
			int error_num, \
			MY_U_INT error_level,\
			const char *error_note)
{
	FILE *fp;
	if((fp = fopen(ERROR_FILE_NAME, "a")) == NULL)
	{
		if((fp = fopen(ERROR_FILE_NAME, "w")) == NULL)
		{
			printf("func: error_write_logfile: error: connot open error_logfile!\n");
			exit(0);
		}
	}
	fprintf(fp, "%s():%d:%d:%s\n", func_name, error_num, error_level, error_note);
	fclose(fp);	
}

/* if ch == ' ','\t','\n', return 1 */
unsigned char char_is_blank(const char ch)
{
        return (ch == ' ' || ch == '\t' || ch == '\n') ? 1 : 0;
}

/* *str include not like blank, return 0
  require func: char_is_blank()	*/
unsigned int str_is_blank_or_zero(const char *str)
{
        const char *p;
        unsigned int is_blk_or_zero = 1;
        
        if(!str)
        {
        	return 1;
        }

        p = str;
        while(*p)
        {
                if(*p == '.')
                {
                        p++;
                        continue;
                }
                if(*p != '0' && !char_is_blank(*p))
                {
                        is_blk_or_zero = 0;
                }
                p++;
        }
        return is_blk_or_zero;
}

/* str init: set *p = '\0' */
void str_init(char (*p)[STRING_LEN])
{
	int n;
	if(p == NULL)
	{
		error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "pointer == NULL");
		return;
	}
	for(n = 0; n < DATA_ITEMS; n++)
	{
		strcpy(p, "\0");
		p++;
	}
}

/* show char of str, like UNIX od */
void str_display_char_like_unix_od(const char *str)
{
	const char *p = str;
	while(*p)
	{
		if(*p == ' ')
		{
			printf("\\b ");
		}
		else if(*p == '\t')
		{
			printf("\\t ");
		}
		else if(*p == '\n')
		{
			printf("\\n ");
		}
		else
		{
			printf("%c ", *p);
		}
		p++;
	}
	printf("\n");
}

/* del head and tail blank, middle blank keep single */
char *str_del_head_and_tail_blank_middle_keep_one(char *to, const char *from)
{
        const char *pfrom;
        char *pto, *p, *pth, *plastblk;
        int isblk, l;

	if(!from)
	{
		return NULL;
	}
        isblk = 0;
        l = strlen(from) + 1;

        pto = (char *) malloc(l);
        memset(pto, '\0', l);

        p = pto;
        pfrom = from;
        while(*pfrom == ' ')	/* del head blank */
        {
                pfrom++;
        }
        while(*pfrom)
        {
                if(*pfrom == ' ')
                {
                        isblk = 1;
                        plastblk = pto;
                        *pto++ = *pfrom++;
                        while(*pfrom == ' ')
                        {
                                pfrom++;
                        }
                }
                else
                {
                        isblk = 0;
                	*pto++ = *pfrom++;
                }
        }
        if(isblk)
        {
                *plastblk = '\0';
        }

	strcpy(to, p);
	free(p);
	p = NULL;
	return to;
}

/* free **pp */
void str_free_ppointer(char **pp, MY_U_INT num)
{
	char **p1, **p2;
	p1 = pp;
	
	while(num > 0 && p1)
	{
		printf("func: %s: %s\n", __FUNCTION__, *p1);
		free(*p1);
		p2 = p1;
		free(p1);
		num--;
		p1 = p2;
		p1++;
	}
}

/* display char **, by sum 
  frend use: str_free_ppointer() */
void str_display_ppointer_by_sum(char **pp, const MY_U_INT sum)
{
	char **p;
	MY_U_INT n = sum;
	printf("%s start\n", __FUNCTION__);
	p = pp;
	while(n > 0)
	{
		printf("%s\n", *p);
		n--;
		p++;
	}
	printf("%s end\n", __FUNCTION__);
}

/* copy DATA *p_data to DATA **pdt */
DATA *data_copy(DATA *to, const DATA *from)
{
	DATA *p;
	
	if(!from)
	{
		return NULL;
	}
	p = to;
	strcpy(p->name, from->name);
	p->jihua = from->jihua;
	p->hengsi = from->hengsi;
	p->guobeng = from->guobeng;
	p->tiaojie = from->tiaojie;
	strcpy(p->zhushi, from->zhushi);

	return to;
}

/* init *DATA *pdt */
void data_init(DATA **ppdt)
{
        DATA **p;
        if(!ppdt)
        {
        	error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "The pointer == NULL!");
        }
        p = ppdt;

        strcpy((*p)->name, "\0");
        (*p)->jihua = 0.0;
        (*p)->hengsi = 0.0;
        (*p)->guobeng = 0.0;
        (*p)->tiaojie = 0.0;
        strcpy((*p)->zhushi, "\0");
}

/* show one list */
void node_display_one(const NODE *pointer)
{
        const NODE *p;
        p = pointer;
        if(!p)
        {
        	error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "The pointer == NULL!");	
        }
        else
        {
        	printf("%s\t%.3f\t%.3f\t%.3f\t%.3f\t%s\n", p->p_data->name, p->p_data->jihua,\
                            p->p_data->hengsi, p->p_data->guobeng,\
                            p->p_data->tiaojie, p->p_data->zhushi
                        );
	}
}

void node_display_all_same_nodes(ALL_SAME_NODES *ap)
{
	SAME_NODE **pp_s;
	MY_U_INT a_count, s_count, **pp_count;
	
	printf("%s start!\n", __FUNCTION__);
	pp_s = NULL;
	a_count = 0;
	if(NULL == ap)
	{
		error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "ALL_SAME_NODES * == NULL!");
		return;
	}
	a_count = ap->count;
	pp_s = ap->pp_same_nodes;
	while(a_count > 0)
	{
		s_count = (*pp_s)->count;
		printf("s_count = %d\n", s_count);
		pp_count = (*pp_s)->pp_pos;
		
		printf("%s: name: %s\n", __FUNCTION__, (*pp_s)->name);
		while(s_count > 0)
		{
			printf("pos: %d\t", *(*pp_count));
			pp_count++;
			s_count--;
		}
		printf("\ndisplay all same nodes next:\n");
		pp_s += 1;
		a_count--;
	}
	printf("display all same nodes end!\n");
	printf("%s end!\n", __FUNCTION__);
}

/* count node size */
MY_U_INT node_count_size(const NODE *pnode)
{
        MY_U_INT sum = 0;
        if(!pnode)
        {
        	return 0;
        }
        sum = sizeof(pnode) * 4 + sizeof(pnode->p_data); /* next, pre, this, tail: 4 */
        sum += (sizeof(pnode->p_data->jihua) * (DATA_ITEMS - 2) + strlen(pnode->p_data->name) +strlen(pnode->p_data->zhushi));
        return sum;
}

/* free one node: *pnode */
void node_free_one(NODE *pnode)
{
	if(!pnode)
	{
		error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "The pointer == NULL!");
		return;
	}
        free(pnode->p_data->name);
        free(pnode->p_data->zhushi);
        free(pnode->p_data);
        pnode->next = NULL;
        pnode->pre = NULL;
        pnode->tail = NULL;
        free(pnode);
        pnode = NULL;
}

/*return SAME_NODE ** pp */
/* create a SAME_NODE **pp, and set pp->pp_pos = MY_U_INT **pp
   and set p->count = 0 */
SAME_NODE **node_create_same_node_and_init(void)
{
	SAME_NODE **p;
	p = (SAME_NODE **)malloc(sizeof(SAME_NODE *));
	(*p) = (SAME_NODE *)malloc(sizeof(SAME_NODE));
	(*p)->name = (char *)malloc(STRING_LEN);
	(*p)->pp_pos = (MY_U_INT **)malloc(sizeof(MY_U_INT *));
	*((*p)->pp_pos) = (MY_U_INT *)malloc(sizeof(MY_U_INT));
	
	if(p && (*p) && (*p)->name && (*p)->pp_pos)
	{
		;
	}
	else
	{
		error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "mem malloc error!");
		return NULL;
	}
	(*p)->count = 0;
	return p;
}

SAME_NODE *node_create_same_node_and_init2(void)
{
	SAME_NODE *p;
	p = (SAME_NODE *)malloc(sizeof(SAME_NODE));
	p->name = (char *)malloc(STRING_LEN);
	p->pp_pos = (MY_U_INT **)malloc(sizeof(MY_U_INT *));
	*(p->pp_pos) = (MY_U_INT *)malloc(sizeof(MY_U_INT));
	p->count = 0;
	
	if(p != NULL && p->pp_pos != NULL)
	{
		;
	}
	else
	{
		error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "mem malloc error!");
		return NULL;
	}
	return p;
}

/* cteate all_same_nodes */
ALL_SAME_NODES *node_create_all_same_nodes_and_init(void)
{
	ALL_SAME_NODES *ap;
	
	/*printf("%s start!\n", __FUNCTION__);*/
	ap = (ALL_SAME_NODES *)malloc(sizeof(ALL_SAME_NODES));
	
	if(ap != NULL && ap->pp_same_nodes != NULL)
	{
		*(ap->pp_same_nodes) = node_create_same_node_and_init2();
	}
	else
	{
		error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "mem malloc error!");
		return NULL;
	}
	ap->count = 0;
	/*printf("%s end!\n", __FUNCTION__);*/
	return ap;
}

/* free all_same_nodes->same_node */
void node_free_all_same_nodes(ALL_SAME_NODES *ap)
{
	MY_U_INT sum_a, sum_s;
	SAME_NODE **p1, **p2;
	MY_U_INT **up1, **up2;
	
	printf("%s start!\n", __FUNCTION__);
	
	p1 = NULL;
	p2 = NULL;
	if(ap == NULL)
	{
		error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "first pointer == NULL");
		return;
	}
	sum_a = ap->count;
	p1 = ap->pp_same_nodes;	
	while(sum_a > 0)
	{
		sum_s = (*p1)->count;
		up1 = (*p1)->pp_pos;
		while(sum_s > 0)
		{
			up2 = up1;
			free(*up1);
			*up1 = NULL;
			
			up1 = up2;
			up1++;
			sum_s--;
		}
		free((*p1)->pp_pos);
		(*p1)->pp_pos = NULL;
		
		free((*p1)->name);
		(*p1)->name = NULL;
		(*p1)->count = 0;
		p2 = p1;
		free(*p1);
		(*p1) = NULL;
		free(p1);
		p1 = NULL;
		
		p1 = p2;		
		p1++;
		sum_a--;
	}
	ap->count = 0;
	free(ap->pp_same_nodes);
	ap->pp_same_nodes = NULL;
		printf("%s end!\n", __FUNCTION__);
}

/* ERROR: create list by data */
NODE *list_create_head_by_index(NODE *head, DATA **pdt)
{
        NODE *pn;

        pn = (NODE *)malloc(NODE_LEN);
        if(!pn)
        {
                error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "mem malloc p_node error!");
                return;
        }
        if(!pdt)
        {
        	error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "The pointer == NULL!");
        }

        if(head == NULL)
        {
                head = pn;
                head->pre = NULL;
                head->next = NULL;
        }
        else
        {
                head->tail->next = pn;
                pn->pre = head->tail;
                pn->next = NULL;
        }
        head->tail = pn;
        head->tail->p_data = *pdt;
        return head;
}

/* create list by data
  require func: data_copy() */
NODE *list_create_head_by_write(NODE *head, DATA **pdt)
{
        NODE *pn;

        pn = (NODE *)malloc(NODE_LEN);
        if(pn == NULL)
        {
      		error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "mem malloc p_node error1!");
                exit(0);
        }
        pn->p_data = (DATA *)malloc(DATA_LEN);
        pn->p_data->name = (char *) malloc(strlen((*pdt)->name) + 1);
        pn->p_data->zhushi = (char *)malloc(strlen((*pdt)->zhushi) + 1);
        if(pn->p_data == NULL || pn->p_data->name == NULL || pn->p_data->zhushi == NULL)
        {
                error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "mem malloc p_node error2!");
                exit(0);
        }

        if(head == NULL)
        {
                head = pn;
                head->pre = NULL;
                head->next = NULL;
        }
        else
        {
                head->tail->next = pn;
                pn->pre = head->tail;
                pn->next = NULL;
        }
        head->tail = pn;
        head->tail->p_data = data_copy(head->tail->p_data, (*pdt));
        return head;
}


/* show all list */
void list_display_all(const NODE *head)
{
        const NODE *p;
        p = head;
        while(p != NULL)
        {
                printf("%s\t%.3f\t%.3f\t%.3f\t%.3f\t%s\n", p->p_data->name, p->p_data->jihua,\
                            p->p_data->hengsi, p->p_data->guobeng,\
                            p->p_data->tiaojie, p->p_data->zhushi
                        );
                p = p->next;
        }
}

/* sort list */
NODE *list_sort_by_data_name(NODE *head)
{
        ;
}


/* ERROR: insert and sort by data name with rule: from less to grate. */
NODE *list_insert_with_rule_by_index(NODE *head, DATA **pdt)
{
        NODE *p1, *p2, *tmp, *pn;
        if(head == NULL)
        {
                return (list_create_head_by_index(head, pdt));
        }

        pn = (NODE *)malloc(NODE_LEN);
        if(pn == NULL)
        {
                error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "mem malloc p_node error!");
                exit(0);
        }
        memset(pn, '\0', NODE_LEN);
        pn->p_data = *pdt;
        pn->pre = NULL;
        pn->next = NULL;
        pn->tail = NULL;

        p1 = head;
        while(p1 != NULL && strcmp(p1->p_data->name, pn->p_data->name) <= 0)
        /* search first that not less or equal */
        {
                tmp = p1;
                p1 = p1->next;
        }

        if(p1 == head)	/* insert before head */
        {
                head = pn;
                head->tail = p1->tail;
                head->pre = NULL;
                head->next = p1;
        }
        else if(p1 == NULL) /* insert after tail */
        {
                head->tail->next = pn;

                pn->pre = head->tail;
                pn->tail = NULL;
                pn->next = NULL;

                head->tail = pn;
        }
        else
        {
                p1 = tmp;
                p2 = p1->next;
                p1->next = pn;
                pn->pre = p1;
                pn->next = p2;
                pn->tail = NULL;
        }
        return head;
}

/* insert and sort by data name with rule: from less to grate.
  require func: list_create_head_by_write() */
NODE *list_insert_with_rule_by_write(NODE *head, DATA **pdt)
{
        NODE *p1, *p2, *tmp, *pn;

        if(head == NULL)
        {
                return (list_create_head_by_write(head, pdt));
        }

        pn = (NODE *)malloc(NODE_LEN);
        if(pn == NULL)
        {
                printf("func: list_insert_with_rule_by_write: error: mem malloc p_node error1!\n");
                error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "mem malloc p_node error1!");
                exit(0);
        }

        pn->p_data = (DATA *)malloc(DATA_LEN);
        pn->p_data->name = (char *) malloc(strlen((*pdt)->name) + 1);
        pn->p_data->zhushi = (char *)malloc(strlen((*pdt)->zhushi) + 1);
        if(pn->p_data == NULL || pn->p_data->name == NULL || pn->p_data->zhushi == NULL)
        {
                printf("func: list_insert_with_rule_by_write: error: mem malloc p_node error2!\n");
                error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "mem malloc p_node error2!");
                exit(0);
        }

        memset(pn->p_data->name, '\0', strlen((*pdt)->name));
        memset(pn->p_data->zhushi, '\0', strlen((*pdt)->zhushi));

        pn->p_data = data_copy(pn->p_data, (*pdt));
        pn->pre = NULL;
        pn->next = NULL;
        pn->tail = NULL;

        p1 = head;
        while(p1 != NULL && strcmp(p1->p_data->name, pn->p_data->name) <= 0)
        /* search first that not less or equal */
        {
                tmp = p1;
                p1 = p1->next;
        }

        if(p1 == head)	/* insert before head */
        {
                head = pn;
                head->tail = p1->tail;
                head->pre = NULL;
                head->next = p1;
        }
        else if(p1 == NULL) /* insert after tail */
        {
        	head->tail->next = pn;

        	pn->pre = head->tail;
        	pn->tail = NULL;
        	pn->next = NULL;

        	head->tail = pn;
        }
        else
        {
                p1 = tmp;
                p2 = p1->next;
                p1->next = pn;
                pn->pre = p1;
                pn->next = p2;
                pn->tail = NULL;
        }
        return head;
}

/* read data from file; save to list by head
  repuire func:	str_is_blank_or_zero();
  		list_insert_with_rule_by_write()
		data_init() */
NODE *list_read_data_from_file_save_to_list(NODE *head, const char *filename)
{
        FILE *f;
        DATA *pdt, **ppdt;
        int i, j, n;
        char ch, *p, str[DATA_ITEMS][STRING_LEN];
        double num;
	
        pdt = (DATA *) malloc(DATA_LEN);
        ppdt = &pdt;
        if(pdt == NULL)
        {
                printf("func: list_read_data_from_file_save_to_list: error: malloc pdt mem error!\n");
                error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "mem malloc pdt error!");
                return NULL;
        }

        pdt->name = (char *)malloc(STRING_LEN);
        pdt->zhushi = (char *)malloc(STRING_LEN);
        if(pdt->name == NULL || pdt->zhushi == NULL)
        {
                printf("func: list_read_data_from_file_save_to_list: error: malloc char * mem error!\n");
                error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "malloc char * mem error!!");
                return NULL;
        }

        if((f = fopen(filename, "r")) == NULL)
        {
                printf("func: list_read_data_from_file_save_to_list: open file: %s error!\n", filename);
                error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "open file error!");
                return NULL;
        }
        while(!feof(f))
        {
        	for(n = 0; n < DATA_ITEMS; n++)
		{
			strcpy(str[n], "\0");
		}	/* str_init() */
                j = 0;
                ch = fgetc(f);
                while( ch != '\n' && !feof(f) )	/* read every line */
                {
                        i = 0;
                        p = str[j];
                        while(ch != '\t' && ch != '\n' && !feof(f))
                        {
                                *p = ch;
                                i++;
                                p++;
                                if(i > STRING_LEN - 1)
                                {
                                        printf("func: list_read_data_from_file_save_to_list: error: your length of item so long!\n");
                                        error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "your length of item so long!");
                                        while(ch != '\t' || ch != '\n')
                                        {
                                                ch = fgetc(f);
                                        }/* skip others of this item */
                                        break;
                                }
                                ch = fgetc(f);
                        }/* now: ch == '\t' or '\n' */
                        *p = '\0';
                        j++;
                        if(j > DATA_ITEMS)	/* except: j == DATA_ITEMS */
                        {
                                printf("j= %d\n", j);
                                printf("func: list_read_data_from_file_save_to_list: error: your file itmes is so many!\n");
                                error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "your file itmes is so many!");
                                return NULL;	/* end this program */
                        }
                        if(ch != '\n')
                        {
                                ch = fgetc(f);
                        }
                }/* now: ch == '\n' */

                        if(!str_is_blank_or_zero(str[0]))
                        {
                        	strcpy((*ppdt)->name, str[0]);
                        	num = atof(str[1]);
                        	(*ppdt)->jihua = num;
                        	num = atof(str[2]);
                        	(*ppdt)->hengsi = num;
                        	num = atof(str[3]);
                        	(*ppdt)->guobeng = num;
                        	num = atof(str[4]);
                        	(*ppdt)->tiaojie = num;
                        	strcpy((*ppdt)->zhushi, str[5]);
                                if(!feof(f))
                                {
                                        head = list_insert_with_rule_by_write(head, ppdt);
                                }
                        }
                        else
                        {
                                data_init(ppdt);
                                continue;
                        }
        }
        fclose(f);

        free(pdt->name);
        pdt->name = NULL;
        free(pdt->zhushi);
        pdt->zhushi = NULL;
        free(pdt);
        pdt = NULL;
        return head;
}

/* free list */
void list_free_all_from_write(NODE *head)
{
        NODE *p1, *p2;
        p1 = head;
        while(p1 != NULL)
        {
                p2 = p1->next;
                free(p1->p_data->name);
                p1->p_data->name = NULL;
                free(p1->p_data->zhushi);
                p1->p_data->zhushi = NULL;
                free(p1->p_data);
                p1->p_data = NULL;
                free(p1);
                p1 = NULL;
                p1 = p2;
        }
}
/* all items use bytes size 
  require func: node_count_size() */
MY_U_INT list_count_size(NODE *head)
{
        MY_U_INT sum;
        NODE *h;

        sum = 0;
        h = head;
        while(h)
        {
                sum += node_count_size(h);
                h = h->next;
        }

        return sum;
}

/* count *head items */
MY_U_INT list_count_items(const NODE *head)
{
        MY_U_INT num;
        const NODE *h;

        num = 0;
        h = head;
        if(!h)
        {
                return 0;
        }
        while(h)
        {
                num++;
                h = h->next;
        }
        return num;
}

/* list have node pointer: return 1, else: 0 */
unsigned char list_find_node_pointer_in_list(NODE * pointer, NODE *head)
{
	NODE *ppos;
	unsigned char have = 0;
	ppos = head;
	while(ppos)
	{
		if(pointer == ppos)
		{
			have = 1;
			break;
		}
		ppos = ppos->next;
	}
	return have;
}

/* find pos item, return pointer, if pos not include, return NULL.
  head at 0	*/
const NODE *list_find_pos_return_node_pointer(MY_U_INT pos, const NODE *head)
{
	const NODE *h;
	MY_U_INT n = 0;
	h = head;

	while(h)
	{
		if(n == pos)
		{
			return h;
		}
		n++;
		h = h->next;
	}
	return NULL;
}

/* list: find first name return pos, none: return -1 ;
  str example: "T/C29T\0" */
int list_find_name_return_pos(const char *name, const NODE *head)
{
	MY_U_INT pos;
	unsigned char have;
	const NODE *h;
 	
 	pos = 0;
 	have = 0;
 	h = head;
 	
 	while(h)
 	{
 		if(strcmp(name, h->p_data->name) == 0)
 		{
		 	have = 1;
		 	break;
 		}
 		pos++;
	 	h = h->next;
 	}
 	return(have ? pos : -1);
}

/* list: find first name return node pointer, none: return NULL ;
  str example: "T/C29T\0" */
NODE *list_find_name_return_node_pointer(const char *str, NODE *head)
{
	unsigned char have;
	NODE *h;
 	
 	have = 0;
 	h = head;
 	
 	while(h)
 	{
 		if(strcmp(str, h->p_data->name) == 0)
 		{
		 	have = 1;
		 	break;
 		}
	 	h = h->next;
 	}
 	return(have ? h : NULL);
}

/* del item by node pointer: if list not include pointer, return head;
  else processing .
  require func: node_free_one(), list_find_node_pointer_in_list() */
NODE *list_del_item_by_node_pointer(NODE *pointer, NODE *head)
{
	if(!pointer)
	{
		return head;
	}
	if(list_find_node_pointer_in_list(pointer, head))
	{
		if(pointer == head)
		{
			pointer->next->pre = NULL;
			pointer->next->tail = head->tail;
			head = pointer->next;
		}
		else if( pointer == head->tail )
		{
			head->tail = pointer->pre;
			pointer->pre->next = NULL;
		}
		else
		{
			pointer->pre->next = pointer->next;
		}

		node_free_one(pointer);
	}
	
	return head;
}

/* del pos item, return head, if pos==head,return head->next;
  else if pos==head->tail, processing;
  head at 0 pos
  repuire func: list_del_item_by_node_pointer() */
NODE *list_del_item_by_pos(MY_U_INT pos, NODE *head)
{
	NODE *ppos;
	MY_U_INT n = 0;

	ppos = head;
	while(ppos)
	{
		if(pos == n)
		{
			break;
		}
		n++;
		ppos = ppos->next;
	}
	return (list_del_item_by_node_pointer(ppos, head));
}

/* del item by name, return head, if pos==head,return NULL;
  if pos==head->tail, processing;
  head at 0 pos
  repuire func: list_find_name_return_node_pointer(); 
  		list_del_item_by_node_pointer() */
NODE *list_del_item_by_name(const char *name, NODE *head)
{
	NODE *find;
	find = list_find_name_return_node_pointer(name, head);
	return (list_del_item_by_node_pointer(find, head));
}

/* save all list name to str[] 
  repuire func: list_count_items() 
  end: str_display_pointer() */ 
char **list_save_all_name_to_list(const NODE *head)
{
	const NODE *h;
	char **pp, **p;
	MY_U_INT sum;
	
	sum = list_count_items(head);
	if(!sum)
	{
		return NULL;
	}
	pp = (char **)malloc(sizeof(char **) * sum);
	if(!pp)
	{
		error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "char ** mem malloc error!\n");
		printf("func: %s: error: mem malloc error!\n", __FUNCTION__);
		return NULL;
	}
	memset(pp, '\0', sizeof(char **) * sum);
	p = (char **)pp;
	
	h = head;	
	while(h)
	{
		if(h->p_data)
		{
			(*p) = (char *)malloc(strlen(h->p_data->name) + 1);
			if((*p) == NULL)
			{
				error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "char * mem malloc error!");
				return NULL;
			}
			strcpy((*p), h->p_data->name);
			/*printf("s:%s\n", *p);*/
			p++;			
		}
		h = h->next;
	}
	*p = NULL;

	return ((char **)pp);
}

/* have same node, what? how much? pos? save to ALL_SAME_NODE *p 
  require func: list_save_all_name_to_list() 
  		list_count_items()
  		str_free_ppointer() 
  warning: source name must sort;
  		head at 0 pos! */
ALL_SAME_NODES *list_count_same_node_save_to_pointer(NODE *head)
{	
	char **ppstr, tmp[STRING_LEN], *pstr;
	NODE *p;
	ALL_SAME_NODES *ap;
	SAME_NODE **sp;
	MY_U_INT pre_pos, pos, **pp_pos_t;
	MY_BOOL is_same, changed, pre_same;
	
	printf("%s start!\n", __FUNCTION__);
	pstr = tmp;
	strcpy(pstr, "\0");
	p = head;
	ap = node_create_all_same_nodes_and_init();
	
	sp = ap->pp_same_nodes;
	
	pos = 0;
	pre_pos = 0;
	pp_pos_t = (*sp)->pp_pos;
	
	is_same = 0;
	pre_same = 0;
	changed = 0;
	if(NULL == head || NULL == ap)
	{
		error_write_logfile(__FUNCTION__, ERROR_NUM, ERROR_LEVEL, "NODE *head == NULL || *ap == NULL!");
		return NULL;
	}
	while(NULL != p)
	{
			printf("de 2\n");
		pre_same = is_same;
			printf("debug 3\n");
		if(strcmp(pstr, p->p_data->name) == 0)
		{
			is_same = 1;
			changed = 0;
		}
		else
		{
			is_same = 0;
			changed = 1;
		}
		if(is_same)
		{
			if(!changed && !pre_same)	/* new *sp creating */
			{
				ap->count += 1;
				
				(*sp)->name = (char *)malloc(strlen(pstr) + 1);
				strcpy((*sp)->name, pstr);				
				(*sp)->count += 1;
				pp_pos_t = (*sp)->pp_pos;
				*(*pp_pos_t) = pre_pos;
				
				pp_pos_t += 1;
				(*sp)->count += 1;
				*pp_pos_t = (MY_U_INT *)malloc(sizeof(MY_U_INT));
				*(*pp_pos_t) = pos;
				
				pp_pos_t += 1;
				*pp_pos_t = (MY_U_INT *)malloc(sizeof(MY_U_INT));					
			}
			else
			{
				*pp_pos_t = (MY_U_INT *)malloc(sizeof(MY_U_INT));
				*(*pp_pos_t) = pos;
				(*sp)->count += 1;
				
				pp_pos_t += 1;				
				*pp_pos_t = (MY_U_INT *)malloc(sizeof(MY_U_INT));
			}
		}
		else
		{
			if(pre_same)	/* is_same = 0, pre_same = 1 */
			{
				printf("next sp is start!\n");
				pp_pos_t = NULL;
				sp += 1;
				*sp = node_create_same_node_and_init2();
				pp_pos_t = (*sp)->pp_pos;	
			}
		}
		printf("(*sp)->count = %d\n", (*sp)->count);
		strcpy(pstr, p->p_data->name);
		p =  p->next;
		pre_pos = pos;
		pos++;	
	}
	sp = NULL;
	pp_pos_t = NULL;
	ppstr = NULL;
	
	printf("ap->count = %d\t*(ap->pp_same_node) ->name = %s\n", ap->count, (*(ap->pp_same_nodes))->name);
	printf("%s end!\n\n", __FUNCTION__);
	return ap;		
}

int main(int argc, char *argv[])
{
        DATA mydata1, mydata2, *pdata1, *pdata2, **ppdata, **ppdata2;
        NODE *head;
        MY_U_INT n;
        char **ppstr;
        ALL_SAME_NODES *ap;

        char *name1 = "T/C20X16ka\0";
        char *name2 = "C/T20x16ka\0";
        char *zhushi = "qiaqi\0";
        /* test list_cteate */
        head = NULL;
        n = 0;
        ppstr = NULL;

        pdata1 = &mydata1;
        pdata2 = &mydata2;

        pdata1->name = name1;
        pdata1->zhushi = zhushi;
        pdata1->jihua = 300.0;
        pdata1->hengsi = 320.0;
        pdata1->guobeng = 315.0;
        pdata1->tiaojie = 318.5;

        ppdata = &pdata1;
	/*
        head = list_create_head_by_write(head, ppdata);
        head = list_create_head_by_write(head, ppdata);

        ppdata2 = &pdata2;

        pdata2->name = name2;
        pdata2->zhushi = zhushi;
        pdata2->jihua = 300.0;
        pdata2->hengsi = 320.0;
        pdata2->guobeng = 315.0;
        pdata2->tiaojie = 318.5;
        head = list_insert_with_rule_by_write(head, ppdata2);
        */

        head = list_read_data_from_file_save_to_list(head, "yuebao.txt");
        /*list_display_all(head);
        printf("count: %d\n", list_count_items(head));*/
        
        /*node_display_one(list_find_pos_return_node_pointer(3, head));*/
        
        /*head = list_del_item_by_pos(3, head);
        list_display_all(head);
        printf("count: %d\n", list_count_items(head));*/
        
        /*printf("str C/T36T at pos: %d\n", list_find_name_return_pos("T/C32T\0", head));
        node_display_one(list_find_name_return_node_pointer("T/C32T\0", head));
        head = list_del_item_by_name("T/C32T\0",head);
        list_display_all(head);
        printf("list_size: %d\n", list_count_size(head));*/
        
        /*n = list_count_items(head);
        ppstr = list_save_all_name_to_list(head);
        printf("ppstr = %s\n", *ppstr);
        str_display_ppointer_by_sum(ppstr, n);        
        str_free_ppointer(ppstr, n);*/
        
        /*ap = node_create_all_same_nodes_and_init();
        node_free_all_same_nodes(ap);*/
        
        ap = list_count_same_node_save_to_pointer(head);
        node_display_all_same_nodes(ap);
        node_free_all_same_nodes(ap);

        list_free_all_from_write(head);
}

