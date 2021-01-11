// Вариант 25.
// прочитать все данные с входного потока, разделить на слов,
// выделить лексемы Java,представляющие собой дробные числа(float) со знаком.
// Хранить эти значения с номерами входных строк. Вывести, предварительно отсортировав
// в порядке убывания значений.
// Слова разделены пробелами. Найти знаковые литералы float и вывести в убывающей порядке с номером строки, в которой встречаются
import java.util.ArrayList;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        System.out.println("Enter text");
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextLine()) {
            System.out.print("You didn`t enter text");
            System.exit(0);
        }
        ArrayList<MyFloat> list = new ArrayList<>();
        short i = 0;
        while (sc.hasNextLine()){
            String str = sc.nextLine();
            i++;
            StringTokenizer st = new StringTokenizer(str);
            while (st.hasMoreTokens()){
                String word = st.nextToken();
                if (CheckFloat.check(word))
                    list.add(new MyFloat(Float.parseFloat(word), i));
            }
        }
        list.sort(null);
        for (MyFloat number: list)
            System.out.print(number + " ");
    }
}

class MyFloat implements Comparable<MyFloat> {

    private float value;
    private short number;
    private float module;

    public float getValue() {
        return value;
    }

    public short getNumber() {
        return number;
    }

    public float getModule() {
        return module;
    }

    public void setValue(float value) {
        this.value = value;
    }

    public void setNumber(short number) {
        this.number = number;
    }

    public void setModule(float module) {
        this.module = module;
    }

    public MyFloat (float v, short num) {
        value = v;
        number = num;
        module = Math.abs(v);
    }

    @Override
    public int compareTo(MyFloat o) {
        if (module > o.getModule())
            return -1;
        else if (module < o.getModule())
            return 1;
        else
            return 0;
    }

    @Override
    public String toString() {
        return value + " (строка №" + number + ")";
    }
}

class CheckFloat {

    static public boolean check (String str){
        if (str.matches("^-?\\d+\\.\\d+[fF]$"))
            return true;
        else
            return false;
    }
}
