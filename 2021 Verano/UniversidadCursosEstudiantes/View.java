import java.util.Scanner;
import java.util.Locale;

public class View{
	
	private static Scanner sc = new Scanner(System.in).useLocale(Locale.US);

	public View(){
		
	}
	public static void print(String text){
		System.out.println(text);
	}

	public static void clearScreen() {  
		System.out.print("\033[H\033[2J");  
		System.out.flush();  
	}  

	public static void pause() {  
		System.out.println("Presione cualquier tecla para continuar...");
		sc.nextLine();  
	}  
	
	public static String getString(){
		return sc.nextLine();
	}

	public static int getInt(){
		int value = sc.nextInt();
		sc.nextLine();
		return value;
	}

	public static float getFloat(){
		float value = sc.nextFloat();
		sc.nextLine();
		return value;
	}
}