import java.util.Scanner; // Для организации ввода

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            Scanner scan = new Scanner(System.in);
            System.out.print("Пожалуйста, введите значение x: ");
            double x = scan.nextDouble();
            if (x <= -1 || x >= 1)
                throw new IllegalArgumentException("Введено некорректное значение x. Разрешённый диапозон: (-1; 1)");
            System.out.print("Пожалуйста, введите значение k: ");
            int k = scan.nextInt();
            if (k < 2)
                throw new IllegalArgumentException("Введено некорректное значение k. Разрешённый диапозон: [2; +oo)");
            double term = x; // Слагаемое, которое постоянно будет пересчитываться в теле цикла
            double Eps = Math.pow(0.1, k); // Число эпсиллон, которое определяет точность
            double Our_Sum = 0; // Сумма, которую мы посчитаем сами (в цикле)
            for (int n = 0; Math.abs(term) >= Eps/10; n++)
            {
                term = Math.pow(x, 2*n + 1)*Math.pow(-1, n) / (2*n + 1);
                Our_Sum += term; // Прибавляем к сумме очередное слагаемое
            }
            double Math_Sum = Math.atan(x); // Сумма, которую посчитает метод библиотеки Math
            System.out.printf("Значение суммы, которая была посчитана в цикле: %."+k+"f\n", Our_Sum);
            System.out.printf("Значение суммы, которую посчитал метод библиотеки Math: %."+k+"f", Math_Sum);
        }
        catch (IllegalArgumentException ex)
        {
            System.out.println("Ошибка! Было выброшено исключение. Описание ошибки:\n" + ex.getMessage());
        }
    }
}