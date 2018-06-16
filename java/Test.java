public class Test {
    public static void main(String[] args) {
    System.out.println(String.format("%1$,09d", -3123));
System.out.println(String.format("%1$9d", -31));
System.out.println(String.format("%1$-9d", -31));
System.out.println(String.format("%1$(9d", -31));
System.out.println(String.format("%1$#9x", 5689));
}
}