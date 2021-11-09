abstract public class PlantEater extends Animal{
    PlantEater() {}
    
    PlantEater(String name, int weight, int age)
    {
        super(name, weight, age);
    }

    public void eatPlant()
    {
        System.out.println(animal + " je ziarna");
    }
}
