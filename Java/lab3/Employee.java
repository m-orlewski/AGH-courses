public class Employee
{
    private int id = -1;
    private String first_name = "";
    private String last_name = "";
    private String email = "";
    private Email received = null; 

    Employee(int i, String fname, String lname)
    {
        id = i;
        first_name = fname;
        last_name = lname;
    }

    public String toString()
    {
        return first_name + " , " + last_name;
    }

    public String getFirstName() { return first_name; }
    public String getLastName() { return last_name; }
    public String getEmail() { return email; }

    public void setEmail(String new_email) { email = new_email; }
    
    public void receiveMail(Employee sender, String msg)
    {
        received = new Email(sender, msg);
    }

    public Email getLastEmailMessage()
    {
        return received;
    }
}