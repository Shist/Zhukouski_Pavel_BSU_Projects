import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main
{
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        Pattern pattern = Pattern.compile("^(([1-7]T[AB]X|7TEX)[ ]([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]|[0-9][1-9][0-9]{2}|[1-9][0-9]{3}))$");
        int n = Integer.parseInt(in.nextLine());
        int result = 0;
        for (int i = 0; i < n; i++) {
            String str = in.nextLine();
            Matcher matcher = pattern.matcher(str);
            if (matcher.find())
                result++;
        }
        System.out.println(result);
        in.close();
    }
}