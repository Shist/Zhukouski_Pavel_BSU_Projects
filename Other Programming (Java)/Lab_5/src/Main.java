import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            Ball[] Ball_ =
                    {
                            new Ball(4.5),
                            new Ball(6.7),
                            new Ball(4.2),
                            new Ball(3.0),
                            new Ball("B: R = 5.6"),
                            new Ball("B: R = 14.2")

                    };
            int count = 0;
            for (Ball b : Ball_)
            {
                System.out.println("Радиус " + count + "-го шара равен: " + b.getRadius());
                b.Calc_Area(b.getRadius());
                System.out.println("Площадь " + count + "-го шара равен: " + b.getArea());
                b.Calc__Volume(b.getRadius());
                System.out.println("Объем " + count + "-го шара равен: " + b.getVolume());
                System.out.println();
                count++;
            }
        }
        catch (IllegalArgumentException ex)
        {
            System.out.println("Ошибка! Было выброшено исключение. Описание ошибки:\n" + ex.getMessage());
        }
    }
}