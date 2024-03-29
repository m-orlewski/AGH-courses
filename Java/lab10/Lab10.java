import java.util.Scanner;

public class Lab10 {
    // Celem dzisiejszych zajęć jest napisanie prostej "gry"
    // Na początku program powinien przyjąć od użytkownika dwie wartości:
    // - rozmiar planszy (liczba większa od 3, jeśli użytkownik poda mniejszą powinien polecieć wyjątek(np. TooSmallGameSizeException) nastepnie zostac zlapany i wyswietlona informacja uzytkownikowi "Podano zbyt mały rozmiar, spróbuj ponownie")
    // - prawdopodobienstwo wystapienia wody( wieksze od 0, analogiczna sytuacja do rozmiaru)
    // Na postawie tych wartości należy stworzyć kwadratową planszą (tablice tablic, lub listę list). Następnie należy ją wypełnić znakami:
    // - znak W -> woda z prawdopodobienstwem podanym przez uzytkownika
    // - znak S -> skarb, jeden na całą planszę
    // - znak G -> gracz, jeden na całą planszę
    // - pozostałe pola wypelnic znakiem *
    // Potem nalezy ja wyswietlic
    // Nastepnie program powinien zaczac zbierac opcje od uzytkownika:
    // - l -> gracz porusza sie w lewo
    // - p -> gracz porusza sie w prawo
    // - g -> gracz porusza sie w gore
    // - d -> gracz porusza sie w dol
    // Po wybraniu opcji plansza powinna przerysowac sie na nowo
    // Gra powinna obsługiwać wyjątki takie jak:
    // - wejscie w wodę -> powinien poleciec wyjatek -> gra konczy sie napisem "Wszedłeś w wodę, koniec gry"
    // - nierozpoznanie opcji -> CommandNotRecognisedException
    // - wejscie w pole skarbu -> powinien poleciec wyjatek -> gra konczy sie napisem "Wygrałeś!!!"
    // Wejscie w pole skarbu lub wody konczy wykonywanie programu

    public static void main(String args[])
    {
        System.out.print("Podaj rozmiar planszy (>3): ");
        Scanner scanner = new Scanner(System.in);
        int size = scanner.nextInt();
        Map map = new Map();

        try
        {
            map.setSize(size);
        }
        catch (TooSmallGameSizeException e)
        {
            System.err.println("Exception: Rozmiar planszy musi byc > 3");
            System.exit(0);
        }

        System.out.print("Podaj prawd. wystapienia wody: ");
        double prob = scanner.nextDouble();

        try
        {
            map.setWaterProbability(prob);
        }
        catch (TooSmallWaterProbabilityException e)
        {
            System.err.println("Exception: Prawd. musi byc > 0");
            System.exit(0);
        }

        map.fillMap();
        map.print();

        map.gameLoop();

    }

}
