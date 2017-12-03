/********************************************
	from is the source condition code;
	0x04bd8
	前4位，即0在这一年是润年时才有意义，它代表这年润月的大小月，为1则润大月，为0则润小月。
	中间12位，即4bd，每位代表一个月，为1则为大月，为0则为小月。
	最后4位，即8，代表这一年的润月月份，为0则不润。首4位要与末4位搭配使用。
****************************************************/
void time_is_legal_china_calendar_date(size_t year,\
										size_t month,\
										size_t day)
{
	unsigned long from, f4, l4, m12;
	
	from = condition_code;
	l4 = from & 0xf;
	from >>= 4;
	m12 = from & 0xfff;
	from >>= 12;
	f4 = from & 0xf;
	*first4 = f4;
	*mid12 = m12;
	*last4 = l4;
}
