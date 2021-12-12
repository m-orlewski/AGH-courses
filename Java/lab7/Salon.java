import java.util.List;
import java.util.ArrayList;

public class Salon
{
    private String name;
    private List<Pojazd> lista = new ArrayList<Pojazd>();

    Salon(String name)
    {
        this.name = name;
    }

    Salon(Salon salon, String name)
    {
        this.name = name;
        
        for (Pojazd pojazd: salon.lista)
        {
            this.lista.add(pojazd); //do zmiany
        }
    }

    public void dodajPojazd(Pojazd pojazd)
    {
        lista.add(pojazd);
        System.out.println("Dodaje nowy pojazd");
    }

    public void usunPojazd(Pojazd pojazd)
    {
        if (lista.remove(pojazd))
        {
            System.out.println("usuwam " + pojazd + " z " + name);
        }
    }

    public void zawieraPojazd(Pojazd pojazd)
    {
        System.out.println(lista.contains(pojazd));
    }

    public void wypiszWszystkiePojazdy()
    {
        for (Pojazd pojazd: lista)
        {
            System.out.print(pojazd.typ() + ", ");
        }
        System.out.print("\n");
    }
}