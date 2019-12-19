size_t time_is_leapyear(size_t year)
{
	if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/******************************************
	yaer:month include days?
	return days;
	require function:
		size_t time_is_leapyear(size_t year);
********************************************/
size_t time_days_in_month(size_t year, size_t month)
{
    size_t day, leap;
    leap = time_is_leapyear(year);
    switch(month)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		day = 31;
		break;
        case 4: case 6: case 9: case 11: 
		day = 30;
		break;
        case 2:
		day = 28 + leap;
		break;
	default:
		break;
    }
    return day;
}

/*int main()
{
    size_t y,m;
    scanf("%d %d",&y,&m);
    printf("%d\n",time_days_in_month(y,m));
    getch();
}*/