public class PaiXu {
    public static void main(String args[]) {
    	int[] arr = {20, 60, 51, 81, 285,12,165,51,81,318,186,9,70,61};
    	
    	for(int a: arr){
    		System.out.print(a + " ");
    	}
    	System.out.println();

    	System.out.pirntln("from da to xiao:");
    	arr = toSmall(arr);
    	for(int a: arr){
    		System.out.print(a + " ");
    	}
    	System.out.println();

    	System.out.println("from big to small:");
    	arr = toBig(arr);
    	for(int a: arr){
    		System.out.print(a + " ");
    	}
    	System.out.println();

    	// toSmall
    	public static int[] toSmall(int[] arr){
    		
    	}
    }
}