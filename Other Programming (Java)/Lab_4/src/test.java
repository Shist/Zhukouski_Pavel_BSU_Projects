import java.util.*;

public class test
{
    public static void main(String[] args)
    {

        PolynomialParser parser = new PolynomialParser();
        // TODO
        // Создать массив полиномов (4, 5 штук)
        // Создать исключения для "" (пустого полинома)
        // TODO
        Vector<Map<Integer, Integer>> polyn_ = new Vector<>();
        Map<Integer, Integer> members_0 = new HashMap<>(); // Данные для 1 полинома
        members_0.put(0, 7);
        members_0.put(1, 3);
        members_0.put(2, 3);
        polyn_.add(members_0);
        Map<Integer, Integer> members_1 = new HashMap<>(); // Данные для 2 полинома
        members_1.put(0, 4);
        members_1.put(1, 2);
        members_1.put(2, 4);
        polyn_.add(members_1);
        Map<Integer, Integer> members_2 = new HashMap<>(); // Данные для 3 полинома
        members_2.put(0, 6);
        members_2.put(1, 3);
        members_2.put(2, 4);
        polyn_.add(members_2);
        Map<Integer, Integer> members_3 = new HashMap<>(); // Данные для 4 полинома
        members_3.put(0, 5);
        members_3.put(1, 4);
        members_3.put(2, 5);
        polyn_.add(members_3);
        Map<Integer, Integer> members_4 = new HashMap<>(); // Данные для 5 полинома
        members_4.put(0, 4);
        members_4.put(1, 1);
        members_4.put(2, 2);
        polyn_.add(members_4);

        // Создание массива полиномов с помощью конструктора и контейнера Map
        Polynom[] Polynom_ = new Polynom[5];
        for (int i = 0; i < Polynom_.length; i++)
        {
            Polynom_[i] = new Polynom(polyn_.elementAt(i));
            System.out.println(((i+1) + "-й полином: " + Polynom_[i]));
        }

        // Сложение
        System.out.println("\n Сложение: ");
        System.out.println(Polynom_[0].add(Polynom_[1]));

        // Вычитание
        System.out.println("Вычитание: ");
        System.out.println(Polynom_[0].subtract(Polynom_[1]));

        // Умножение
        System.out.println("Умножение: ");
        System.out.println(Polynom_[0].multiply(Polynom_[1]));
    }
}