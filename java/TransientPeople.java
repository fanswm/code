import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

class People implements Serializable{
	String name;
	transient Integer age;
	public People(String name, int age){
		this.name = name;
		this.age = age;
	}

	public String toString(){
		return "Name =" + name + " , Age = " + age;
	}
}

public class TransientPeople{
	public static void main(String[] ages) throws FileNotFoundException, IOException,ClassNotFoundException{
		People a = new People("LiLei", 30);
		System.out.println(a);
		ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream("d://people.txt"));
		os.writeObject(a);
		os.close();
		ObjectInputStream is = new ObjectInputStream(new FileInputStream("d://people.txt"));
		a = (People)is.readObject();
		System.out.println(a);
		is.close();
	}
} 