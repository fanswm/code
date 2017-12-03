/*  create "addressBook" by name:filename. if not have:create.

    if OK, return 1;
    else return 0       */
size_t file_create_file(const char *filename)
{
    FILE *book;

    if((book = fopen(filename,"r")) == NULL)
    {
        printf("Cannot open addressbook file. now try created!\n");

        if((book = fopen(filename,"w")) == NULL)
        {
            printf("Create addressbook failed! Please contact Administrator.\n");
            return 0;
        }
        else
        {
            printf("Create addressbook OK!\n");
            fclose(book);
            return 1;
        }
    }
    else
    {
        printf("open addressbook OK!\n");
        fclose(book);
        return 1;
    }
}

/*
int main(void)
{
    file_create_file("D:\\tt.txt");
}
*/

