public class SwitchTest{
	public static void main(String[] args){
		char grade = args[0].charAt(0);
		//char grade = 'C';
	
		switch(grade){
			case 'A':
				System.out.println("YouXiu");
				break;
			case 'B':
				System.out.println("LiangHao");
				break;
			case 'D':
			case 'E':
				System.out.println("JiGe");
				break;
			case 'F':
				System.out.println("Please Study Hard");
				break;
			default:
				System.out.println("Unknow");
				break;
		}
		System.out.println("Your Grade:" + grade);
	}
	// Test:
	// java SwitchTest F
	// Please Study Hard;
}