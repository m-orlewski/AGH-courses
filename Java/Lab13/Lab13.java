//        Szyfr Cezara
//
//        Napisz program który będzie obsługiwał dwa tryby oraz przesunięcie w alfabecie niezbędne do zakodowania słowa w szyfr cezara
//
//        (tryb oraz przesunięcie przekazane jako argumenty programu):
//
//        1. Input z pliku zostaje zaszyfrowany i zapisany do pliku o tej samej nazwie + _coded_{przesuniecie}.txt (3pkt za obsługę pojedyńczych wyrazów + 2 pkt za obsługe całych
//
//        zdań ze spacjami)
//
//        2. Input z pliku zostaje odszyfrowany i zapisany do pliku o tej samej nazwie + _decoded_{przesuniecie}.txt. (3pkt za obsługę pojedyńczych wyrazów + 2 pkt za obsługe całych
//
//        zdań ze spacjami)
//
//
//        3. Argumenty programu przekazane jako:
//        java lab2 code 2 test.txt
//        java lab2 decode 2 test.txt
//
//                test.txt zawiera słowo TEST
//
//        4. Przykładowy wynik:
//                (To wypisujemy na konsole)
//        Dla alfabetu: ABCDEFGHIJKLMNOPQRSTUVWXYZ
//        Dla pliku z zawartoscia: TEST
//        Przesunięcia: 2
//        Trybu: code
//        Wynik: VGUV
//
//                (To trafia do pliku o nazwie test_coded_2.txt)
//                VGUV

import java.io.*;

public class Lab13
{
	public static void main(String[] args) throws IOException
	{
		if (args.length < 3)
		{
			System.out.println("Too few arguments.");
			System.out.println("Should be: java [filename] [mode(code/decode)] [shift]");
			return;
		}

		String mode = args[0];
        int shift = Integer.valueOf(args[1]);
        String filename = args[2];

        if (!mode.equals("code") && !mode.equals("decode"))
        {
            System.out.println("Wrong mode. Should be \"code\" or \"decode\"");
            return;
        }

        System.out.print("Dla alfabetu: ");
        for (char c='A'; c <= 'Z'; c++)
        {
            System.out.print(c);
        }
        System.out.println();

        FileReader in = new FileReader(filename);
        FileWriter out = new FileWriter(filename.substring(0, filename.indexOf('.')) + "_" + mode + "_" + shift + filename.substring(filename.indexOf('.')));
        BufferedReader b = new BufferedReader(in);
        BufferedWriter w = new BufferedWriter(out);
        String s;

        StringBuilder content = new StringBuilder();
        StringBuilder result = new StringBuilder();


        while ((s = b.readLine()) != null)
        {
            if (content.length() != 0)
                content.append("\n");
            content.append(s);

            if (mode.equals("code"))
            {
                s = cipher(s, shift);
            }
            else
            {
                s = decipher(s, shift);
            }
            if (result.length() != 0)
                result.append("\n");
            result.append(s);
        }
        in.close();
        b.close();

        w.write(result.toString());

        System.out.println("\nDla pliku z zawartoscia:");
        System.out.print(content.toString() + "\n");

        System.out.println("\nPrzesuniecia: " + shift);

        System.out.println("\nTrybu: " + mode);

        System.out.println("\nWynik:");
        System.out.print(result.toString() + "\n");
        
        w.close();
        out.close();

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
