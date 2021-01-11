//Вариант 3
//Создать программу, котоая читает текст из стандартного входного потока,
//разбивает его на предложения и выводит их в стандартный поток по одному
//предложению в строке, переводя все слова Восклицательных предложений
//в верхний регистр.
import java.util.ArrayList;
import java.util.Scanner;
public class Main
{
    static ArrayList<String> tl = new ArrayList<String>(); //list of lines
    static void procLine(String line)
    {
        int idx = 0;
        while (idx < line.length())
        {
            if (line.charAt(idx) == '.' || line.charAt(idx) == '?')
            {
                tl.add(line.substring(0, idx + 1));
                line = line.substring(idx + 1);
                idx = 0;
            }
            else if (line.charAt(idx) == '!')
            {
                tl.add(line.substring(0, idx+1).toUpperCase());
                line = line.substring(idx+1);
                idx = 0;
            }
            idx++;
        }
    }
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Insert your text line by line:");
        String text = "";
        while(sc.hasNextLine())
        {
            String buffer = sc.nextLine();
            if(buffer.equals("exit"))
                break;
            text = text + buffer;
        }
        procLine(text);
        sc.close();
        for(String s : tl)
            System.out.println(s);
    }
}
