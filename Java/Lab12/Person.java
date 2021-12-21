enum Gender {MALE, FEMALE};

public class Person
{
    private String fname;
    private String lname;
    private Gender gender;
    private int age;

    public Person(String fname, String lname, Gender gender, int age)
    {
        this.fname = fname;
        this.lname = lname;
        this.gender = gender;
        this.age = age;
    }

    public String toString()
    {
        return fname + " " + lname + " " + gender + " " + age;
    }

    public String getFName() { return fname; }
    public String getLName() { return lname; }
    public Gender getGender() { return gender; }
    public int getAge() { return age; }

    public Person setAge(int age)
    {
        this.age = age;
        return this;
    }
}
