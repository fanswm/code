#include <stdio.h>
#include <string.h>

#ifndef _MYTYPE_H_
#define	_MYTYPE_H_
#include "mytype.h"
#endif

#define ERROR_FILE_NAME "error_log.txt\0"

/* func_name: errornumber: description */
MyBoolType error_write_logfile(const char *func_name,
			int error_num,
			int error_level,
			const char *error_note,
			const char *logfilename);