public class Puppy{
	int puppyAge;
	public Puppy(String name){
		System.out.println("The dog's name is " + name);
	}

	public void setAge(int age){
		puppyAge = age;
	}

	public int getAge(){
		System.out.println("The dog's Age is: " + puppyAge);
		return puppyAge;
	}

	public static void main(String []args){

		Puppy myPuppy = new Puppy("tommy");

		myPuppy.setAge(2);
		myPuppy.getAge();
		System.out.println("the age is:" + myPuppy.puppyAge);

	}
}