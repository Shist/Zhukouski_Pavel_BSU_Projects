import java.io.*;

public class Main
{
    public static int Foo(int[] uy)
    {
        int M = uy.length - 1;
        int[][] W = new int[M + 1][M + 1];
        for (int i = 1; i <= M; i++)
            W[i][i] = 0;
        for (int p = 2; p <= M; p++)
            for (int i = 1; i <= M - p + 1; i++)
            {
                int j = i - 1 + p;
                W[i][j] = Integer.MAX_VALUE;
                for (int b = i; b <= j - 1; b++)
                    W[i][j] = Math.min(uy[i - 1] * uy[b] * uy[j] + W[i][b] + W[b + 1][j], W[i][j]);
            }
        return W[1][M];
    }

    public static void main(String[] args) throws IOException
    {
        FileReader reader = new FileReader("input.txt");
        BufferedReader in = new BufferedReader(reader);
        PrintWriter out = new PrintWriter(new FileWriter("output.txt"));
        String s = in.readLine();
        String str = "";
        for (int i = 0; i < s.length(); i++)
        {
            if (s.charAt(i) == ' ')
                break;
            str += s.charAt(i);
        }
        int S = Integer.parseInt(str) + 1;
        int[] matrix_arr = new int[S];
        int i = 0;
        s = in.readLine();
        String s_temp = "";
        while(s != null)
        {
            str = "";
            for (int j = 0; j < s.length(); j++)
            {
                if (s.charAt(j) == ' ')
                    break;
                str += s.charAt(j);
            }
            matrix_arr[i] = Integer.parseInt(str);
            i++;
            s_temp = s;
            s = in.readLine();
        }
        String str_2 = "";
        for (i = 0; i < s_temp.length(); i++)
        {
            if (s_temp.charAt(i) == ' ')
            {
                i++;
                while (i < s_temp.length())
                {
                    str_2 += s_temp.charAt(i);
                    i++;
                }
            }
        }
        matrix_arr[S - 1] = Integer.parseInt(str_2);
        out.print(Foo(matrix_arr));
        in.close();
        out.close();
    }
}