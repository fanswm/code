import java.util.Date;
import java.text.*;

public class TestDate{
	public static void main(String[] args){
		Date date = new Date();
		System.out.println(date.toString());

		long times = date.getTime();
		System.out.println("times = " + times);

		SimpleDateFormat ft = new SimpleDateFormat("yyy.MM.dd 'at' hh:mm;ss a zzz");
		System.out.println("Current Date: " + ft.format(date));
	}
}