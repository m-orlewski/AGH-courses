import java.util.Objects;

public class Person
{
    private String name = "";
    private String surname = "";
    private int age = -1;

    Person(String name, String surname, int age)
    {
        this.name = name;
        this.surname = surname;
        this.age = age;
    }

    public String toString()
    {
        return "Person{name='" + this.name + "', surname='"
        + this.surname + "', age=" + this.age + "}"; 
    }

    public boolean equals(Object person)
    {
        if (this == person) return true;
        if (person instanceof Person)
        {
            Person temp = (Person) person;
            if (temp.name == name &&
                temp.surname == surname &&
                temp.age == age)
                return true;
        }
        return false;
    }

    public int hashCode()
    {
        return Objects.hash(name, surname, age);
    }

    public int getAge()
    {
        return this.age;
    }

    public void checkDrinkingAge() throws DrinkException
    {
        if (this.age < 18)
        {
            System.out.println(this + " cannot drink alcohol");
            throw new DrinkException();
        }
        else
        {
            System.out.println(this + " can drink alcohol");
        }
    }
}