import java.lang.reflect.Method;
import java.lang.reflect.Type;
import java.util.Arrays;
import java.util.Scanner;

public class Lab11 {
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

            Method[] m = Math.class.getMethods();
            for (Method method : m)
            {
                Type[] tt = method.getGenericParameterTypes();
                if (tt.length == 1 || tt.length == 2)
                {
                    System.out.println(method);
                }
            }

            System.out.println("\nPodaj nazwe metody: ");
            String methodName = sc.nextLine();
            String[] arguments = getArgs(methodName);


            try
            {
                Method method;
                boolean found = false;
                for (int i=0; i < m.length; i++)
                {
                    if (m[i].toString().contains(" java.lang.Math." + arguments[0] + "("))
                    {
                        found = true;
                        break;
                    }
                }

                if (!found) //no such method, force exception
                    method = Math.class.getMethod(arguments[0]);
                
                if (arguments.length == 2)
                {
                    method = Math.class.getMethod(arguments[0], double.class);
                }
                else if (arguments.length == 3)
                {
                    method = Math.class.getMethod(arguments[0], double.class, double.class);
                }
                else
                {
                    throw new IllegalArgumentException();
                }
                
                double[] params = new double[arguments.length-1];
                for (int i=0; i < params.length; i++)
                {
                    params[i] = Double.parseDouble(arguments[i+1]);
                }

                Object result;
                if (params.length == 1)
                    result = method.invoke(Math.class, params[0]);
                else if (params.length == 2)
                    result = method.invoke(Math.class, params[0], params[1]);
                else
                    throw new IllegalArgumentException();  

                System.out.println(arguments[0] + " = " + result);
            }
            catch (NoSuchMethodException e)
            {
                System.err.println("Exception: No such method found.");
            }
            catch (IllegalArgumentException e)
            {
                System.err.println("Exception: Illegal arguments.");
            }
            catch (Exception e)
            {
                System.err.println("Unexpected exception.");
            }
    
    }

    public static String[] getArgs(String arg) {
        return Arrays.stream(arg.split("[\\s+(),]"))
                .filter(w -> !w.isEmpty())
                .toArray(String[]::new);
    }

   // Celem dzisiejszych zajęć jest skorzystanie z mechanizmu refleksji
//    Na początku wypisujemy wszystkie możliwe metody z klasy Math które maja 1 lub 2 argumenty
    // Następnie użytkownik wpisuje funkcję matematyczną do wywołania, np. tan(1.0), należy obsłużyc wszystkie funkcje z klasy Math, które zawierają 1 lub 2 argumenty
    // Metodę w klasie Math należy znaleźć przy użyciu metody "getMethod" z klasy Class
    // Następnie wypisujemy wynik równania i kończymy program
    // Oczywiście program musi obsługiwać wyjątki takie jak: wywołanie metody która nie istnieje w klaie Math, Wywoałenie metody ze złą liczbą argumentów, czy podaniem do funkcji typu argumentu innego niz int/float/double
    // Mamy napisaną metodę getArgs do której podajemy np: "sin(4.12)" i otrzymujemy tablicę: [sin, 4.12]
}
