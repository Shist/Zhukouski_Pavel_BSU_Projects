import java.util.Scanner;
 class Passenger {

    public String name;

    public Passenger(String str) {
        this.name = str;
    }
    public Request makeRequest(String destination,String time,String date)
    {
        Request req=new Request(destination,date,time);
        return req;
    }
    public int chooseTrain()
    {
        System.out.println("Enter the number of your train:");
        int n;
        Scanner in = new Scanner(System.in);
        n=in.nextInt();
        return n;
    }
}
