/**********************************************************************

********************************************************************************************/
#include "bugongyi.h"

void bgy_display(pBgy p)
{
	printf("品种名称: %s\n", p->name);	/* 1 */
	printf("总经根数: %d\n", p->zj);	/* 2 */
	printf("头份: %4.1f\n", p->tf);		/* 3 */
	
	printf("整经轴数: %d\n", p->zjzs);	/* 4 */
	printf("整经长度: %d\n", p->zjcd);	/* 5 */	
	printf("每轴匹数: %3.1f\n", p->mzps);	/* 6 */
	
	printf("每缸轴数: %d\n", p->mgzs);	/* 7 */
	printf("墨印长度: %4.2f\n", p->mycd);	/* 8 */
	printf("筘号: %4.1f\n", p->kh);		/* 9 */
	
	printf("筘幅: %4.1f\n", p->kf);		/* 10 */
	printf("经纱缩率: %3.1f\n", p->Tsl);	/* 11 */
	printf("纬纱缩率: %3.1f\n", p->Wsl);	/* 12 */
	
	printf("经纱用纱量: %6.4f\n", p->Gt);	/* 13 */
	printf("纬纱用纱量: %6.4f\n", p->Gw);	/* 14 */
	printf("第二种经纱用纱量: %6.4f\n", p->Gt2);/* 15 */
	printf("第三种经纱用纱量: %6.4f\n", p->Gt3);/* 16 */
	
	printf("第二种纬纱用纱量: %6.4f\n", p->Gw2);/* 17 */
	printf("第三种纬纱用纱量: %6.4f\n", p->Gw3);/* 18 */
	
	printf("折标系数: %6.4f\n", p->zbxs);	//19
	
	printf("经密: %6.4f\n", p->jm);		//20
	printf("纬密: %6.4f\n", p->wm);		//21
	printf("幅宽: %6.4f\n", p->fk);		//22
	
	printf("第一种经纱: %s\n", p->Tname1);	//23
	printf("第二种经纱: %s\n", p->Tname2);	//24
	printf("第三种经纱: %s\n", p->Tname3);	//25
	
	printf("第一种纬纱: %s\n", p->Wname1);	//26
	printf("第二种纬纱: %s\n", p->Wname2);	//27
	printf("第三种纬纱: %s\n", p->Wname3);	//28
}

/* for example：625X8+636X1+682X2 

   include <stdlib.h> */
void bgy_get_toufen_zjzs_from_str(float *toufen,\
				unsigned int *zjzs,\
				const char *from)
{
	unsigned int zs, z;
	float t, zj;
	char *str;
	size_t count;
	pList_node phead, *pphead;
	
	pphead = NULL;
	phead = NULL;
	zs = 0;
	z = 0;
	t = 0.0;
	zj = 0.0;
	
	assert(NULL != toufen && NULL != zjzs && NULL != from);
	
	pphead = &phead;
	list_init(pphead);
	count = str_get_every_str_save_to_list_sep_by_char(pphead, from,\
				'X', 'x', '+');
	
	assert(NULL != phead);
	for(; count > 0; )
	{
		str = phead->data;
		t = atof(str);		
		phead = phead->next;
		
		str = phead->data;
		z = atol(str);		
		phead = phead->next;
		
		zs += z;
		zj += (t * z);
		count -= 2;
	}
	*toufen = (zj / zs);
	*zjzs = zs;
	list_free_all(pphead);
}

/* convert List_node to Bgy */
pBgy bgy_list_convert_to_pbgy(pBgy pbgy, const pList_node list_head)
{
	pList_node p = list_head;

	if(list_head == NULL || pbgy == NULL)
	{
		pbgy = NULL;
		return NULL;
	}
	
	strcpy(pbgy->name, p->data); 	p = p->next;/* 棉布品种 */
	pbgy->zj = atol(p->data); 	p = p->next;/* 总经根数 */
	pbgy->tf = atof(p->data); 	p = p->next;/* 整经头份 */
	
	pbgy->zjzs = atof(p->data);	p = p->next;/* 整经轴数 */
	pbgy->zjcd = atol(p->data);	p = p->next;/* 整经长度 */
	pbgy->mzps = atof(p->data);	p = p->next;/* 每轴匹数 */
	
	pbgy->mgzs = atol(p->data);	p = p->next;/* 每缸整经轴数 */
	pbgy->mycd = atof(p->data);	p = p->next;/* 墨印长度 */
	pbgy->kh = atof(p->data);	p = p->next;/* 筘号 */
	
	pbgy->kf = atof(p->data);	p = p->next;/* 筘幅 */
	pbgy->Tsl = atof(p->data);	p = p->next;/* 经纱缩率 */
	pbgy->Wsl = atof(p->data);	p = p->next;/* 纬纱缩率 */
	
	pbgy->Gt = atof(p->data);	p = p->next;/* 经纱用纱量 */
	pbgy->Gw = atof(p->data);	p = p->next;/* 纬纱用纱量 */
	pbgy->Gt2 = atof(p->data);	p = p->next;/* 用纱量t2 */
	pbgy->Gt3 = atof(p->data);	p = p->next;/* 用纱量t3 */
	pbgy->Gw2 = atof(p->data);	p = p->next;/* 用纱量w2 */
	pbgy->Gw3 = atof(p->data);	p = p->next;/* 用纱量w3 */
	
	pbgy->zbxs = atof(p->data);	p = p->next;//折标系数
	
	pbgy->jm = atof(p->data);	p = p->next;//经密
	pbgy->wm = atof(p->data);	p = p->next;//纬密
	pbgy->fk = atof(p->data);	p = p->next;//幅宽
	
	strcpy(pbgy->Tname1, p->data); 	p = p->next;//第一种经纱
	strcpy(pbgy->Tname2, p->data); 	p = p->next;//第二种经纱
	strcpy(pbgy->Tname3, p->data); 	p = p->next;//第三种经纱
	strcpy(pbgy->Wname1, p->data); 	p = p->next;//第一种纬纱
	strcpy(pbgy->Wname2, p->data); 	p = p->next;//第二种纬纱
	strcpy(pbgy->Wname3, p->data); 	p = NULL;//第三种纬纱
	return pbgy;
}


/*
int main(void)
{
	pList_node head;
	int row;
	Bgy gy;
	size_t include_char;
	FileSizeType cols;
	char str[100];
	unsigned int zs, *z;
	float tf, *t;
	
	pBgy pbgy = &gy;
	pList_node *pphead = &head;
	
	z = &zs;
	t = &tf;
	
	//test bgy_get_toufen_zjzs_from_str();
	/*
	bgy_get_toufen_zjzs_from_str(t,z,"625x3+636x4+500x5\0");
	printf("toufen: %f\t zs: %d\n", tf, zs);
	*/
	
	
	//test file_search_name_line_save_every_str_to_list
	/*
	list_init(pphead);
	//row = file_search_name_line_save_every_str_to_list(pphead,"C/T16X12X108X54X47卡\0","./bugongyi.txt");
	//printf("row = %d\n", row);
	//list_display(head);
	//printf("list_count_nodes: %d\n", list_count_node(head));
	
	//test bgy_list_convert_to_pbgy
	//bgy_list_convert_to_pbgy(pbgy, head);
	//bgy_display(pbgy);
	
	//test file_get_col_of_str_save_to_list()
	file_get_col_of_str_save_to_list(pphead, 1, ".\\file\\in_kaitaipinzhong.txt");
	list_display(head);
	list_free_all(pphead);
	
	list_init(pphead);
	file_get_col_of_str_save_to_list(pphead, 2, ".\\file\\in_kaitaipinzhong.txt");
	list_display(head);
	list_free_all(pphead);	
	
	/*
	// test str_get_every_str_save_to_list_sep_by_char
	list_init(pphead);
	str_get_every_str_save_to_list_sep_by_char(pphead,\
			"aaa,bbb ccc	ddd\0",
			',',
			' ',
			'\t');
	list_display(head);
	
	*/
	/*
	include_char = char_is_the_any_char('e', 4, 'a', 'b', 'c', 'd');
	printf("include_char = %d\n", include_char);
	*/
	/*
	//test file_get_cols()
	cols = file_get_cols("test.txt\0");
	printf("cols = %d\n", cols);
	cols = file_get_rows("test.txt\0");
	printf("rows = %d\n", cols);
	
}*/



