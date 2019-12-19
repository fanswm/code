/**********************************
	if someone function debug:
	append debug to logfile: "filename";
*********************************************/
void error_write_logfile(const char *func_name, \
			int error_num, \
			unsigned int error_level,\
			const char *error_note,\
			const char *filename)
{
	FILE *fp;
	if((fp = fopen(filename, "a")) == NULL)
	{
		if((fp = fopen(filename, "w")) == NULL)
		{
			printf("func: error_write_logfile: error: connot open error_logfile!\n");
			exit(0);
		}
	}
	fprintf(fp, "%s():%d:%d:%s\n", func_name, error_num, error_level, error_note);
	fclose(fp);	
}