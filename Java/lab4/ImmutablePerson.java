import java.util.Date;

public class ImmutablePerson implements Cloneable
{
    private final String firstName;
    private final String lastName;
    private final Date dateOfBirth;
    
    ImmutablePerson(String firstName, String lastName, Date dateOfBirth)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        this.dateOfBirth = (Date)dateOfBirth.clone();
    }

    public String getInformation()
    {
        return "Imie: " + firstName + " nazwisko: " + lastName 
            + " data urodzenia: " + dateOfBirth.toString();
    }

    public Date getDateOfBirth()
    {
        return (Date)dateOfBirth.clone();
    }

    public String getFirstName()
    {
        return firstName;
    }

    public ImmutablePerson clone() throws CloneNotSupportedException
    {
         return (ImmutablePerson) super.clone();
    }
}