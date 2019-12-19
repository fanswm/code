#include "myerror.h"

/* func_name: errornumber: description */
MyBoolType error_write_logfile(const char *func_name,\
			int error_num,\
			int error_level,\
			const char *error_note,\
			const char *logfilename)
{
	FILE *fp;
	if((fp = fopen(logfilename, "a")) == NULL)
	{
		if((fp = fopen(logfilename, "w")) == NULL)
		{
			printf("func: error_write_logfile: error: connot open error_logfile!\n");
			return 0;
		}
	}
	fprintf(fp, "file: %s func: %s(): line: %d\n\t%d\t%d\t%s\n",\
				__FILE__, func_name, __LINE__,\
				error_num, error_level, error_note);
	fclose(fp);
	return 1;
}
