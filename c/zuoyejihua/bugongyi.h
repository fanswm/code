/**********************************************************************

********************************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef _MYCHAR_H_
#define _MYCHAR_H_
#include "mychar.h"
#endif

#ifndef _MYLIST_H_
#define _MYLIST_H_
#include "mylist.h"
#endif

#ifndef _MYSTR_H_
#define _MYSTR_H_
#include "mystr.h"
#endif

#ifndef _MYFILE_H_
#define _MYFILE_H_
#include "myfile.h"
#endif

#define BUGONGYI_COL		14
#define BUZUOYEJIHUA_COL	13
#define STR_BUFF_SZIE		255
#define BUGONGYI_NAME_SIZE	255

struct BUGONGYI
{
	char name[BUGONGYI_NAME_SIZE];	/* mian bu pin zhong */
	unsigned int zj;	/* zong jing gen shu */
	float tf;		/* tou fen */
	
	unsigned int zjcd;	/* zheng jing chang du */
	unsigned int zjzs;	/* zheng jing zhou shu */
	float mzps;	/* mei zhou pi shu */
	
	unsigned int mgzs;	/* mei gang zheng jing zhou shu */
	float mycd;	/* mo yin chang du */
	float kh;	/* kou hao */
	
	float kf;	/* kou fu */
	float Tsl;	/* jing sha suo lv */
	float Wsl;	/* wei sha suo lv */
	
	float Gt;	/* jing sha zong yong sha liang */
	float Gw;	/* wei sha zong yong sha liang */
	float Gt2;	/* yong sha liang t2 */
	float Gt3;	/* yong sha liang t3 */
	float Gw2;	/* yong sha liang w2 */
	float Gw3;	/* yong sha liang w3 */
	
	float zbxs;	/* zhe biao xi shu */
	
	float jm;
	float wm;	/* wei mi */
	float fk;	/* fu kuan */
	
	char Tname1[BUGONGYI_NAME_SIZE];	/* jing sha 1 */
	char Tname2[BUGONGYI_NAME_SIZE];
	char Tname3[BUGONGYI_NAME_SIZE];
	char Wname1[BUGONGYI_NAME_SIZE];	/* wei sha 1 */
	char Wname2[BUGONGYI_NAME_SIZE];
	char Wname3[BUGONGYI_NAME_SIZE];
};

typedef struct BUGONGYI Bgy;
typedef Bgy *pBgy;

void bgy_display(pBgy p);

/* for example£º625X8+636X1+682X2 

   include <stdlib.h> */
void bgy_get_toufen_zjzs_from_str(float *toufen,\
				unsigned int *zjzs,\
				const char *from);
				
/* convert List_node to Bgy */
pBgy bgy_list_convert_to_pbgy(pBgy pbgy, const pList_node list_head);






















































