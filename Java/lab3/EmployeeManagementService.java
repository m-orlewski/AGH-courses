import java.util.List;
import java.util.ArrayList;

public class EmployeeManagementService
{
    private List<Employee> employee_list = new ArrayList<Employee>();

    public void addNewEmployee(Employee employee)
    {
        employee_list.add(employee);
        System.out.println("Employee added " + employee.getFirstName() + " " + employee.getLastName());
    }

    public void printAllEmployees()
    {
        for (Employee employee: employee_list)
        {
            System.out.println("Employee: " + employee);
        }
    }

    public void changeEmail(Employee employee, String new_email)
    {
        int i = employee_list.indexOf(employee);

        if (i == -1)
        {
            System.out.println("Nie ma takiego pracownika.");
        }
        else
        {
            employee_list.get(i).setEmail(new_email);
        }
    }

    public void fireEmployee(Employee employee)
    {
        employee_list.remove(employee);
    }

    public void sendMailToAllEmployees(String msg)
    {
        for (Employee employee: employee_list)
        {
            employee.receiveMail(null, msg);
        }
    }
}
