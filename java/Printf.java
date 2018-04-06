import java.util.Date;

// use "printf" output
// key:
// use: 'java.io.PrintStream':printf method
// first arg: format, 2th: 
public class Printf{
	public static void main(String[] args){
		// %s: string
		System.out.printf("%s", new Integer(1212));

		// %n: newline
		System.out.printf("%s%n", "end line");

		// more args
		System.out.printf("%s = %s%n", "Name", "Zhangsan");

		//%S: Caps Lock
		System.out.printf("%S = %s%n", "Name", "Zhangsan");

		// more args: 
		// 1$:1th string; 3$: 3th string;...
		System.out.printf("%1$s = %3$s %2$s%n", "Name", "san", "Zhang");
	}
}