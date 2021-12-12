abstract public class Pojazd
{
    protected String name;
    protected String type;
    public boolean started = false;
    public boolean moving = false;

    Pojazd(String name)
    {
        this.name = name;
    }

    public String toString()
    {
        return (type + " " + name);
    }

    public String typ()
    {
        return type;
    }

    public String name()
    {
        return name;
    }

    public boolean isStarted()
    {
        return started;
    }
}