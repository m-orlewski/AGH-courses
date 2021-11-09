abstract public class Animal
{
    protected String animal;
    protected String name = "";
    protected int weight = -1;
    protected int age = -1;

    Animal() {}

    Animal(String name, int weight, int age)
    {
        this.name = name;
        this.weight = weight;
        this.age = age;
    }

    public String toString()
    {
        return "\n-zwierze: " + animal + "\n-imie: " + name + "\n-waga: " + weight + "\n-wiek: " + age + "\n";
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public boolean compare(Animal animal)
    {
        return (this == animal);
    }
}
