import java.util.*;

public class Ball implements Body, Comparable<Ball>, Iterator<Object>
{
    private int fieldNumber = 0; // TODO Добавить это в метод итератора, чтобы не нагружать программу

    private double R = 0.0; // Радиус
    double getRadius(){return R;}
    //TODO Добавить еще поле (например, цвет), чтобы был выбор для метода CompareTo

    Ball(double R) // Конструктор
    {
        try
        {
            if (R == 0.0 || R < 0.0)
            {
                // TODO Посмотреть исключения через assert
                throw new IllegalArgumentException();
            }
        }
        catch (IllegalArgumentException e)
        {
            System.out.println("Введено некорректное значение радиуса шара R.");
            System.exit(1);
        }
        this.R = R;
    }

    Ball (String str)
    { // "B: R = 14.5" - шар радиуса 14.5
        String num_str = str.substring(7);
        this.R = Double.parseDouble(num_str);
    }

    private double S = 0.0; // Площадь
    double getArea(){return S;}

    private double V = 0.0; // Объем
    double getVolume(){return V;}

    public void Calc_Area(double R) // Вычислить площадь
    {
        S = 4.0*Math.PI*R*R;
    }

    public void Calc__Volume(double R) // Вычислить объем
    {
        V = (4.0/3.0)*Math.PI*R*R*R;
    }

    public int compareTo(Ball b)
    {
        if(this.getRadius()<b.getRadius())
            return -1;
        else if(b.getRadius()<this.getRadius())
            return 1;
        return 0;
    }

    public Iterator<Object> iterator() {return this;}

    public boolean hasNext() {return fieldNumber < 3;}

    public Object next()
    {
        switch (fieldNumber)
        {
            case 0:
                fieldNumber++;
                return getRadius();
            case 1:
                fieldNumber++;
                return getArea();
            case 2:
                fieldNumber++;
                return getVolume();
            default:
                return null;
        }
    }

    public String toString() { return "R = " + getRadius() + ", S = " + getArea() + ", V = " + getVolume(); }
}