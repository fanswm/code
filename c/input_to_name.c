/****************************************************
把from表示的字符串中的所有字符分类:
字母:1;	数字:2;	斜杠	/:3;	空格:	4; 左括号:	5;
右括号:	6;乘号:	7;加号:	8;其他非空格的可打印字符:	9;
再有其他的字符:Error,返回-1;
正常时,返回符号类型的种类:count_lei
******************************************************/
int input_to_name(	char *to_sign[][20],
					char *to_lei[],
					const char *from)
{
	int i, count_lei;

	char *pfrom = from;;
	char (*ptosign) [20], *ptolei;	/*sign用来存符号, lei把符号分类*/

	char tmp[20];				/*tmp临时存放符号串*/
	char *ptmp;

	ptosign = to_sign;
	ptolei = to_lei;

	count_lei = 0;

	while(isspace(*pfrom))			/*去除首空格*/
	{
		pfrom++;
	}

	while(*pfrom)
	{
		if(isalpha(*pfrom))			/*字母:	1*/
		{
			ptmp = tmp;
			while(isalpha(*pfrom))
			{
				*ptmp++ = *pfrom++;
			}
			*ptmp = '\0';

			*ptolei++ = '1';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(isdigit(*pfrom) || *pfrom == '.')		/*数字或小数点:	2*/
		{
			ptmp = tmp;
			while(isdigit(*pfrom) || *pfrom == '.')
			{
				*ptmp++ = *pfrom++;
			}
			*ptmp = '\0';

			*ptolei++ = '2';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == '\/')				/*	"/":	3*/
		{
			ptmp = tmp;
			*ptmp++ = '\/';
			*pfrom++;
			*ptmp = '\0';

			*ptolei++ = '3';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(isspace(*pfrom))		/* 空格:	4*/
		{
			ptmp = tmp;
			while(isspace(*pfrom))
			{
				*pfrom++;				/*所有空格只要连续只算一个空格*/
			}
			*ptmp++ = ' ';
			*ptmp = '\0';

			*ptolei++ = '4';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == '(' || *pfrom == '[' )			/*左括号:	5*/
		{
			ptmp = tmp;
			*ptmp++ = *pfrom++;
			*ptmp = '\0';

			*ptolei++ = '5';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == ')' || *pfrom == ']')			/*右括号:	6*/
		{
			ptmp = tmp;
			*ptmp++ = *pfrom++;
			*ptmp = '\0';

			*ptolei++ = '6';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == 'X' || *pfrom == 'x' || *pfrom == '*')	/*棉布规格分隔符:X	x	*  : 7.并格式化为:星号	*/
		{
			ptmp = tmp;
			*ptmp++ = '*';
			pfrom++;
			*ptmp = '\0';

			*ptolei++ = '7';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == '+')			/*	加号:	8*/
		{
			ptmp = tmp;
			*ptmp++ = *pfrom++;
			*ptmp = '\0';

			*ptolei++ = '8';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(isgraph(*pfrom))					/*其他非空格可打印字符,包括汉字:	9*/
		{
			ptmp = tmp;
			while(*pfrom)
			{
				*ptmp++ = *pfrom++;
			}
			*ptmp = '\0';
			*ptolei++ = '9';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else
		{
			ptosign = to_sign;
			ptolei = to_lei;
			ptosign = NULL;
			ptolei = NULL;
			return -1;
		}
	}

	return count_lei;		/*返回符号类型的种类*/
}