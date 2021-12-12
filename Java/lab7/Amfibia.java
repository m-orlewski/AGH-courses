public class Amfibia extends PojazdPlywajacy
{
    Amfibia(String name)
    {
        super(name);
        this.type = "amfibia";
    }

    public void jedz()
    {
        if (started)
            System.out.println(type + " jedzie");
        else
            System.out.println(type + " nie moze jechac bo nie jest wlaczona");
    }
}