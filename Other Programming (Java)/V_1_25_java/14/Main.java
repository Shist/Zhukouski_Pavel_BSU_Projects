// Вариант 14.
// Ввести через стандартный поток текст,
// найти слово максимальной длины и вывести слово и сколько раз встречается
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{

    public static int maxCount=0;
    public static String maxString;

    public static void main(String[] args){
        System.out.println("Enter line:");
        try (Scanner in = new Scanner(System.in)){
            read(in);
            System.out.println(maxString+" "+maxCount);
        }catch (Exception e){
            System.err.println(e);
        }
    }

    private static void read(Scanner in) throws Exception {

        class Word {
            String s;
            int count;
            public Word(String s, int c){
                this.s = new String(s);
                this.count=c;
            }
        }
        ArrayList<Word> words = new ArrayList<Word>();
        while (in.hasNext()) {
            String buffer = in.nextLine();
            if(buffer.equals("exit"))
                break;
            String[] arr = buffer.split(" ");
            boolean f = true;
            for (int i = 0; i < arr.length; i++){
                for (int j=0;j<words.size();j++){//проверяет, были ли уже такие слова
                    if(arr[i].compareTo(words.get(j).s)==0){
                        words.get(j).count++;
                        f=false;
                        break;
                    }
                }
                if(f){//слово новое
                    words.add(new Word(arr[i],1));
                }
                f=true;
            }
        }
        int max_word_size = 0;
        for (int i=0;i<words.size();i++){
            if(words.get(i).s.length() > max_word_size && words.get(i).s.compareTo("")!=0)
            {
                maxString=words.get(i).s;
                maxCount = words.get(i).count;
                max_word_size = words.get(i).s.length();
            }
        }
    }
}
