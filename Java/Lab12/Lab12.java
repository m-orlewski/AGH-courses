import java.util.List;
import java.util.Arrays;
import java.util.Map;

public class Lab12
{
    public static void main(String[] args)
    {
        List<Person> people = Arrays.asList(
            new Person("John", "Smith", Gender.MALE, 20),
            new Person("Jane", "Smith", Gender.FEMALE, 25),
            new Person("Jan", "Kowalski", Gender.MALE, 30),
            new Person("Julia", "Nowak", Gender.FEMALE, 16),
            new Person("Julia", "Kowalska", Gender.FEMALE, 80)
        );

        System.out.println("Females: ");
        System.out.println(PersonService.filterGender(people, Gender.FEMALE));
        System.out.println();

        System.out.println("Adults: ");
        System.out.println(PersonService.filterAdults(people));
        System.out.println();

        System.out.println("Smiths: ");
        System.out.println(PersonService.filterLName(people, "Smith"));
        System.out.println();

        System.out.println("Julie: ");
        System.out.println(PersonService.filterFName(people, "Julia"));
        System.out.println();

        System.out.println(PersonService.sumAge(people));
        System.out.println();

        Map<String, Integer> map = PersonService.mapList(people);
        map.forEach((k, v) -> System.out.println("K: " + k + " V: " + v));
        System.out.println();

        System.out.println("Po podwojeniu: ");
        System.out.println(PersonService.doubleAge(people));
        System.out.println();
    }
}

/*
Stworzyc klase
Person: imie, nazwisko, plec(enum), wiek
Stworzyc Klase PersonService która będzie miała nastepujące funkcjonlaności :
- zwrócenie listy zawierajacej osoby podanej plci
- zwrocenie listy osob pelnoletnich >= 18 lat
- zwrocenie listy osob z danym nazwiskiem
- zwrocenie listy osob z danym imieniem
- zwrocenie sumy wieku wszystkich podanych w liscie
- zwrocenie mapy zawierajacej jako klucz imie + nazwisko(polaczone w jednego stringa), jako wartosc wiek
- zwrocenie listy osob z wiekiem pomnożonym przez 2
Przekazujemy do funkcji Listę oraz pozostałe parametry i na niej wykonujemy operacje
 */