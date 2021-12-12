interface StarterPlywajacych
{
    static public void start(PojazdPlywajacy pojazd)
    {
        if (pojazd.started)
        {
            pojazd.moving = true;
            System.out.println(pojazd + " zaczyna plynac");
        }
        else
        {
            pojazd.started = true;
            System.out.println(pojazd + " uruchamia silnik");
        }
    }
}