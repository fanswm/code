/* open a file: "filename", by mode: "mode" 
   mode:
	"r" open file for read; 
	"w" create file for write; 
	"a" append a txtfile; 
	"rb" open a binary file for read; 
	"wb" create a binary file for write; 
	"ab" append to binary file; 
	"r+" open txtfile for read/write; 
	"w+" create a txtfile for read/write; 
	"a+" open a txtfile for read/write; 
	"rb+" open a binary file for read/write; 
	"wb+" create a binary file for read/write; 
	"ab+" open a binary file for read/write;

   OK: return FILE *fp;
   else: return NULL
   
	MUST fclose(fp);
***********************************************/
FILE *file_open_file_by_mode(const char *filename, const char *mode)
{
    FILE *fp;
    
    if( (fp = fopen(filename, mode)) == NULL)
    {
        printf("open filename: %s failed! Please connect Administrator.\n", filename);
        return NULL;
    }
    return fp;
}