enum Colors { RED, GREEN, YELLOW, BLUE};
enum Kolory { CZERWONY, ZIELONY, ZOLTY, NIEBIESKI};

public class ColourPrinter
{
    public static void printColours()
    {
        for (Colors color : Colors.values())
        {
            System.out.println("Kolor " + color + 
            " po polsku: " + Kolory.values()[color.ordinal()]);
        }
    }

    public static void printGetNameColours()
    {
        for (Kolory kolor : Kolory.values())
        {
            System.out.println(kolor);
        }
    }

    public static void printSaySomethingColours()
    {
        for (Kolory kolor : Kolory.values())
        {
            System.out.println("Kolor to " + kolor);
        }
    }
}