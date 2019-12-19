/* #include <time.h>
   get local time and format to mysql style. 
****************************************************/
void time_get_local_format_mysql_style(char *datetime)
{
    time_t timer;
    struct tm *gmt;

    timer = time(NULL);
    gmt = localtime(&timer);
    if(gmt->tm_year + 1900 < 9999)
    {
        strftime(datetime, 21, "%Y-%m-%d %H:%M:%S", gmt);
        printf("%s\n", datetime);
    }
    return;
}

/*int main(void)
{
	char str[1024];
	time_get_local_format_mysql_style(str);
	printf("str: %s\n", str);
	getch();
}*/