import java.util.Scanner;

public class Main
{
	public static void main(String[] args)
	{
		if (args.length < 2)
		{
			System.out.println("Too few arguments.");
			System.out.println("Should be: java [filename] [mode(1/2)] [shift]");
			return;
		}

		Scanner sc = new Scanner(System.in);
		int mode = Integer.valueOf(args[0]);
		int shift = Integer.valueOf(args[1]);
		

		System.out.println("Text: ");
		String text = sc.nextLine();


		if (mode == 1)
		{
			System.out.println("Mode 1: ciphering text.");
			System.out.println("Ciphered: " + cipher(text, shift));
		}
		else if (mode == 2)
		{
			System.out.println("Mode 2: deciphering text.");
			System.out.println("Deciphered: " + decipher(text, shift));
		}
		else
			System.out.println("Wrong mode");
	}

	public static String cipher(String text, int shift)
	{
		shift %= 26;
		String ciphered = "";
		
		for (int i=0; i < text.length(); i++)
		{
			char c = text.charAt(i);
		
			if (c < 'A' || c > 'Z')
			{
				ciphered += c;
				continue;
			}
		
			if (c + shift <= 'Z')
			{
				c += shift;
			}
			else
			{
				int remainder = shift - ('Z' - c + 1);
				c  = 'A';
				c += remainder;			
			}

		
			ciphered += c;
		}

		return ciphered;
	}

	public static String decipher(String text, int shift)
	{
		shift %= 26;
		String deciphered = "";

		for (int i=0; i < text.length(); i++)
		{
			char c = text.charAt(i);

			if (c < 'A' || c > 'Z')
			{
				deciphered += c;
				continue;
			}

			if (c - shift >= 'A')
			{
				c -= shift;
			}
			else
			{
				int remainder = shift - (c - 'A' + 1);
				c = 'Z';
				c -= remainder;
			}

			deciphered += c;
		}
	
		return deciphered;
	}
}
