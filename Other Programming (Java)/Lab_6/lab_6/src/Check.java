
public class Check {

    Request req;
    int price;
    public Check(Request r, int pr)
    {
        this.req=r;
        this.price=pr;
    }
    public void show()
    {
        if(this.price==-1)
        {
            System.out.println("Sorry, we can't find train with such parameters");
        }
        else
        {
            System.out.println( "Congratulations! You finished registration on the train.");
            System.out.println( "Destination-"+ req.destination);
            System.out.println( "Date-"+ req.date);
            System.out.println( "Time-"+ req.time);
            System.out.println( "To pay-"+ price);
        }

    }
}
