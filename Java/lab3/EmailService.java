public class EmailService
{
    public void generateEmailForNewEmployee(Employee employee, String domain)
    {
        String email = employee.getFirstName() + "." + employee.getLastName() + domain;
        employee.setEmail(email);
    }

    public void sendMail(Employee sender, Employee receiver, String msg)
    {
        receiver.receiveMail(sender, msg);
    }
}