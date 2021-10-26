class Email
{
    private String msg = "";
    private Employee sender = null;

    Email(Employee sender, String message)
    {
        msg = message;
        this.sender = sender;
    }

    public Employee getFrom()
    {
        return sender;
    }

    public String getMessage()
    {
        return msg;
    }
}