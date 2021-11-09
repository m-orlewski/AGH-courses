public class LinkedList
{
    private Node head = null;

    LinkedList() {}

    LinkedList(int arr[])
    {
        head = new Node(arr[0]);
        Node prev = head;

        for (int i=1; i < arr.length; i++)
        {
            prev.setNext(new Node(arr[i]));
            prev = prev.getNext();
        }
    }

    public void display()
    {
        Node node = head;
        while (node != null)
        {
            System.out.print(node.getValue() + " ");
            node = node.getNext();
        }
        System.out.println();
    }

    public void add(int value)
    {
        Node node = head;

        if (node == null)
        {
            node = new Node(value);
            return;
        }

        while (node.getNext() != null)
        {
            node = node.getNext();
        }

        node.setNext(new Node(value));
    }

    public void merge(LinkedList list)
    {
        if (head == null) //list1 empty
        {
            head = list.head;
            return;
        }
        
        if (list.head == null) //list2 empty
        {
            return;
        }

        Node node1 = head;
        Node node2 = list.head;

        while (node1.getNext() != null)
        {
            node1 = node1.getNext();
        }

        node1.setNext(node2);
    }

    public boolean contains(int value)
    {
        Node node = head;
        while (node != null)
        {
            if (node.getValue() == value)
                return true;
        
            node = node.getNext();
        }
        return false;
    }

    public void clear()
    {
        Node node = head.getNext();
        head = null;

        Node temp;
        while (node != null)
        {
            temp = node.getNext();
            node = null;
            node = temp;
        }
    }

    public void remove()
    {
        head = null;
    }
}