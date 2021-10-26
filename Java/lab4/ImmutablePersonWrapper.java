public class ImmutablePersonWrapper
{
    private final ImmutablePerson person;

    ImmutablePersonWrapper(ImmutablePerson immutablePerson)
    {
        person = immutablePerson;
    }

    public void printInfoAboutPerson(String s)
    {
        System.out.println(person.getFirstName() + " is " + s);
    }

    public void printInfoAboutPerson(boolean flag)
    {
        System.out.println(person.getFirstName() + " is having good time:" + flag);
    }
}