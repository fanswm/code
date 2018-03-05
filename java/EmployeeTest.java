import java.io.Employee;
public class EmployeeTest{
	public static void main(String []ages){
		Employee empOne = new Employee("ONETEST");
		Employee empTwo = new Employee("TWOTEST");

		empOne.empAge(26);
		empOne.empDesignation("GaoJiChengXuYuan");
		empOne.empSalary(1000);
		empOne.printEmployee();

		empTwo.empAge(21);
		empTwo.empDesignation("CaiNiaoChengXuYuan");
		empTwo.empSalary(500);
		empTwo.printEmployee();
	}
}