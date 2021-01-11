// Вариант 18.
// Из стандартного входного потока прочитать текст.
// Разделители - пробелы(один или несколько) и знак табуляции.
// В выходной поток:
// 1) преобразовать строки таким образом, чтобы их длина не была больше 80, при этом нельзя "херачить слова"
// 2) заменить \t на пробелы(без учёта позиционного табулирования)
// 3) заменить несколько пробелов на один
// 4) удалить пробелы:
// * в начале строки
// * в конце строки
// * перед знаками препинания
import java.io.*;

public class Main
{
    public static final String fileNameIn = "in.txt";
    public static final String fileNameOut = "out.txt";
    public static void main(String[] args) {

        try(BufferedReader reader = new BufferedReader(new FileReader(fileNameIn));
            BufferedWriter writer = new BufferedWriter(new FileWriter(fileNameOut)))
        {
            String add = "";
            while(reader.ready())
            {
                String line = reader.readLine();
                String[] mas = transformLine(add + line);
                line = mas[0];
                writer.write(line + "\n");

                add = mas[1];

                while(add.length() > 80) {
                    String[] tmp = transformLine(add);
                    writer.write(tmp[0] + "\n");
                    add = tmp[1];
                }

            }
            if(!add.equals(""))
            {

                writer.write(add + "\n");

            }
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }

    }
    public static String[] transformLine(String line)
    {
        line = line.replaceAll("\\s+", " ").trim();
        line = deleteAllSpaces(line);

        boolean flag = true;
        String[] mas = new String[2];

        if(line.length() > 80)
        {
            mas = makeTransference(line);
        }
        else {
            mas[0] = line;
            mas[1] = "";
        }
        return mas;
    }
    public static String deleteSpace(String line, char c)
    {
        char space = ' ';
        int index = line.length();
        StringBuilder result = new StringBuilder(line);
        while(true)
        {
            index = line.lastIndexOf(c, --index);
            if(index == -1)
                break;

            if(index-1 != -1 && line.charAt(index-1) == space)
                result.delete(index-1, index);
        }
        return result.toString();
    }
    public static String deleteAllSpaces(String line)
    {
        char[] separators = {',','.','!','?', ';',':',';'};
        for (int i = 0; i < separators.length; i++)
            line = deleteSpace(line, separators[i]);
        return line;
    }
    public static String[] makeTransference(String line)
    {
        int index = 80;
        while(line.charAt(index) != ' ')
        {
            index--;
        }
        index++;
        String word = line.substring(index, line.length());
        StringBuilder old = new StringBuilder(line);
        old.delete(index, line.length());
        String[] mas = new String[2];
        mas[0] = old.toString();
        mas[1] = word;
        return mas;
    }
}
