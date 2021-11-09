public class Lion extends MeatEater
{
    public String type;
    Lion(String name, int weight, int age, String type)
    {
        super(name, weight, age);
        this.type = type;
        this.animal = "lew";
    }

    public String toString()
    {
        return "\n-zwierze: " + animal + "\n-imie: " + name + "\n-waga: " + weight + "\n-wiek: " + age + "\n-typ: " + type +"\n";
    }
}
