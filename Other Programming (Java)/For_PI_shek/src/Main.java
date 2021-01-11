import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        double value, bestValue = 1000000000.0;
        int requestNumber = 0;
        int cost, production, profit;
        for (int i = 0; i < N; i++) {
            cost = in.nextInt();
            production = in.nextInt();
            profit = in.nextInt();
            value = cost / (0.0 + profit - production);
            if (value < bestValue)
            {
                requestNumber = i;
                bestValue = value;
            }
        }
        requestNumber++;
        System.out.println(requestNumber);
    }
}