public class StaticTest {
    private static int staticInt = 2;
    private int random = 2;

    public StaticTest() {
        staticInt++;
        random++;
    }

    public static void main(String[] args) {
        System.out.println("Class var and Object var:");
        StaticTest test = new StaticTest();
        System.out.println("  ShiLi1: staticInt:" + test.staticInt + "----random:" + test.random);
        StaticTest test2 = new StaticTest();
        System.out.println("  ShiLi2:staticInt:" + test.staticInt + "----random:" + test.random);
	
        System.out.println("static var fuzhi");
        System.out.println("  jing tai yu ju zuo yong:" + A.staticA);
	
        A a = new A();
        System.out.println("  gou zao qi zuo yong:" + a.staticA);
        a.toChange();
        System.out.println("  jing tai fang fa 1 qi zuo yong:" + A.staticA);
	
        a.toChange2();
        System.out.println("  jing tai fang fa 2 qi zuo yong:" + A.staticA);
        System.out.println("chang liang fu zhi");
        System.out.println("  jing tai yu ju fu zhi:" + B.staticB);
    }
}

class A { 
    public static  String  staticA ="A" ;  
    static{  staticA ="A1"; }   
    public A (){  staticA ="A2"; }     
    public static void toChange(){  staticA ="A3"; } 
    public static void toChange2(){  staticA ="A4"; }  
}

class B { 
    public static final String  staticB ;  
    static{  staticB ="B"; }
}