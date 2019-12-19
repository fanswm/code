/*  */
size_t time_is_leapyear(size_t year)
{
	return ( (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ? 1: 0);
}
