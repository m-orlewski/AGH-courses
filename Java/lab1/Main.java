import java.util.Scanner;

public class Main
{
	static public void main(String[] args)
	{
		double r;
		Scanner scanner = new Scanner(System.in);
		System.out.println("Podaj promien: ");
		r = scanner.nextDouble();

		System.out.println("Pole = " + Math.PI*r*r + '\n' + "Obwod = " + 2*Math.PI*r);
	}
}
