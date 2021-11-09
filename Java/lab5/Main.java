public class Main
{
    public static void main(String[] args)
    {
        int arr1[] = {1, 2, 3};
        int arr2[] = {5, 6};
        LinkedList list1 = new LinkedList(arr1);
        LinkedList list2 = new LinkedList(arr2);

        System.out.println("\nList1: ");
        list1.display();

        System.out.println("\nList1(add(4))");
        list1.add(4);
        list1.display();   

        System.out.println("\nList1(merge(List2)): ");
        list1.merge(list2);
        list1.display(); 

        System.out.println("\nList1 contains 5, 8: ");
        System.out.println(list1.contains(5));
        System.out.println(list1.contains(8));

        int arr3[] = {1, 2, 3};
        LinkedList list3 = new LinkedList(arr3);
        
        System.out.println("\nList3: ");
        list3.display();
        list3.remove();
        System.out.println("\nList3(after remove): ");
        list3.display();
        
        System.out.println("\nList1(after clear): ");
        list1.clear();
        list1.display();
    }
}