public class PersonPrinter
{
    public Operation sum = (x, y) -> { return x + y; };
    public Operation multiply = (x, y) -> { return x * y; };

    public static void print(Person... people)
    {
        for (Person p : people)
        {
            System.out.print(p + " ");
        }
        System.out.println();
    }

    public void printOperation(Person person1, Person person2, Operation operation)
    {
        System.out.println(operation.calculate(person1.getAge(), person2.getAge()));
    }

    public static void checkIfCanDrinkWithExceptionCatch(Person person)
    {
        try
        {
            person.checkDrinkingAge();
        }
        catch (DrinkException e)
        {
            System.err.println("Catch exception");
        }
    }
}