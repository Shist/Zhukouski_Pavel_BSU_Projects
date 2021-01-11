// Вариант 4.
// Стандартный входной поток.
// Найти все вопросительные предложения и вывести каждое с новой строки.
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{

    static ArrayList<String> tl = new ArrayList<String>(); //list of lines
    static String tmpLine = new String();

    static void procLine(String line)
    {

        int idx = 0;
        while(idx<line.length()){

            if(line.charAt(idx) == '.' || line.charAt(idx) == '!')
            {
                tmpLine = "";
                line = line.substring(idx+1);
                idx = 0;
            }
            else if(line.charAt(idx) == '?')
            {

                tmpLine += line.substring(0, idx+1);
                tl.add(tmpLine);
                tmpLine = "";

                line = line.substring(idx+1);
                idx = 0;
            }
            idx++;
        }
        if (line.indexOf('.') == -1 && line.indexOf('!') == -1 && line.indexOf('?') == -1)
        {
            tmpLine += line;
        }
    }

    public static void main(String[] args)
    {

        Scanner sc = new Scanner(System.in);

        System.out.println("Insert your text line by line:");

        tmpLine = "";
        while(sc.hasNextLine())
        {
            String buffer = sc.nextLine();
            if(buffer.equals("exit"))
                break;
            procLine(buffer);
        }
        if(!tmpLine.isEmpty())
            tl.add(tmpLine);
        sc.close();

        for(String s : tl)
            System.out.println(s);
    }
}
