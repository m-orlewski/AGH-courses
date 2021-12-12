abstract public class PojazdPlywajacy extends Pojazd
{
    PojazdPlywajacy(String name)
    {
        super(name);
    }

    public void plyn()
    {
        if (started)
            System.out.println(type + " plynie");
        else
            System.out.println(type + " nie moze plynac bo nie jest wlaczona");
    }
}