public class OuterClass
{
    interface Inner
    {
        public String getName();

        public void saySomething();
    }

    public class InnerClassFirst implements Inner
    {
        public String getName()
        {
            return "first";
        }

        public void saySomething()
        {
            System.out.println("Say something first");
        }
    }

    public static class InnerClassSecond implements Inner
    {
        public String getName()
        {
            return "second";
        }

        public void saySomething()
        {
            System.out.println("Say something second");
        }
    }

    public Inner instantiateFirst()
    {
        return new InnerClassFirst();
    }

    public Inner instantiateSecond()
    {
        return new InnerClassSecond();
    }
}