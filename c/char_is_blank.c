/* if ch == ' ','\t','\n', return 1 */
unsigned char char_is_blank(const char ch)
{
        return ((ch == ' ' || ch == '\t' || ch == '\n') ? 1 : 0);
}
