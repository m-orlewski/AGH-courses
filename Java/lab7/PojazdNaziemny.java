abstract public class PojazdNaziemny extends Pojazd
{
    PojazdNaziemny(String name)
    {
        super(name);
    }

    public void jedz()
    {
        if (started)
            System.out.println(type + " jedzie");
        else
            System.out.println(type + " nie moze jechac bo nie jest wlaczona");
    }
}