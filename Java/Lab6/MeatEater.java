public class MeatEater extends Animal{
    MeatEater() {}

    MeatEater(String name, int weight, int age)
    {
        super(name, weight, age);
    }

    public void eatMeat()
    {
        System.out.println(animal + " je mieso");
    }
}
