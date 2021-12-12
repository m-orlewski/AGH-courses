interface Starter
{
    static public void start(Pojazd pojazd)
    {
        if (pojazd.started)
        {
            System.out.println(pojazd + " zaczyna plynac");
        }
        else
        {
            pojazd.started = true;
            pojazd.moving = true;
            System.out.println(pojazd + " uruchamia silnik");
        }
    }

    static public void stop(Pojazd pojazd)
    {
        if (pojazd.started)
        {
            if (pojazd.moving)
            {
                pojazd.moving = false;
                System.out.println(pojazd + " zatrzymuje silnik");
            }
            else
            {
                pojazd.started = false;
                System.out.println(pojazd + " zatrzymuje sie");
            }
        }
        else
        {
                pojazd.started = false;
                System.out.println(pojazd + " zatrzymuje sie");
        }
    }
}