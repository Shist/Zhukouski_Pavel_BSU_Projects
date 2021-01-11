// Вариант 10.
// Создать программу, которая читает текст из стандартного входного потока
// и печатает в выходной поток предложения исходного текста, в которых встречается фраза,
// указанная как обязательный параметр программы.
import java.util.ArrayList;
import java.util.Scanner;

class Main
{

    static ArrayList<String> tl = new ArrayList<String>(); //list of lines

    static void procLine(String text, String arg)
    {

        int idx = 0;
        while(idx<text.length())
        {

            if(text.charAt(idx) == '.' || text.charAt(idx) == '?' || text.charAt(idx) == '!'){

                if(text.substring(0, idx+1).contains(arg))
                    tl.add(text.substring(0, idx+1));
                text = text.substring(idx+1);
                idx = 0;
            }
            idx++;
        }
    }

    public static void main(String[] args)
    {

        if ( args.length != 1 )
            throw new IllegalArgumentException("You don't enter one argument.");
        // Run --> Edit Configurations --> Program Arguments: (и там нужно ввести нужную фразу)

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
        procLine(text, args[0]);

        sc.close();

        System.out.println("---Full text---: ");
        for(String s : tl){
            System.out.println(s);
        }
        System.out.println("------end------\n");
    }
}
