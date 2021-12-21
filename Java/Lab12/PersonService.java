import java.util.List;
import java.util.stream.Collectors;
import java.util.Map;

public class PersonService
{
   public static List<Person> filterGender(List<Person> people, Gender gender)
   {
        return people.stream()
                     .filter(e -> e.getGender() == gender)
                     .collect(Collectors.toList());
   }

   public static List<Person> filterAdults(List<Person> people)
   {
        return people.stream()
                     .filter(e -> e.getAge() >= 18)
                     .collect(Collectors.toList());
   }

   public static List<Person> filterLName(List<Person> people, String lname)
   {
        return people.stream()
                     .filter(e -> e.getLName() == lname)
                     .collect(Collectors.toList());
   }

   public static List<Person> filterFName(List<Person> people, String fname)
   {
        return people.stream()
                     .filter(e -> e.getFName() == fname)
                     .collect(Collectors.toList());
   }

   public static int sumAge(List<Person> people)
   {
       return people.stream()
                    .mapToInt(e -> e.getAge())
                    .sum();
   }

   public static Map<String, Integer> mapList(List<Person> people)
   {
        return people.stream()
                     .collect(Collectors.toMap(e -> e.getFName()+" "+e.getLName(), e -> e.getAge()));
   }

   public static List<Person> doubleAge(List<Person> people)
   {
       return people.stream()
                    .map(e -> e.setAge(2 * e.getAge()))
                    .collect(Collectors.toList());
   }
}
