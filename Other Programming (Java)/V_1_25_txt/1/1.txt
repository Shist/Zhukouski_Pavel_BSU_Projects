// Вариант 1.
// Из стандартного входного потока прочитать текст
// и в стандартный выходной поток вывести все цитаты.
// Цитата — это текст между двойными кавычками
import java.util.*;
public class Main
{
    public static void main(String[] args)
    {
        String text = "";
        Scanner in = new Scanner(System.in);
        while (in.hasNextLine())
        {
            String buffer = in.nextLine();
            if (buffer.equals("exit"))
                break;
            text += buffer;
        }
        ArrayList<String> Lq = new ArrayList<String>();
        boolean q = false;
        String bufferQ = "";
        for (int i = 0; i < text.length(); i++)
        {
            if(text.charAt(i) == '"' && !q)
                q = true;
            else if (text.charAt(i) == '"' && q)
            {
                bufferQ += '"';
                Lq.add(bufferQ);
                bufferQ = "";
                q = false;
            }
            if (q)
                bufferQ+=text.charAt(i);
        }
        for(String s : Lq)
            System.out.println(s);
    }
}