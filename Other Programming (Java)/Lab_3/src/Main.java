import java.util.Scanner; // Для организации ввода
import java.util.Random; // Рандом

public class Main
{ // Вариант 10 (работа с матрицей)
    public static int generateRandomIntIntRange(int min, int max)
    { // Функция рандома целых чисел с диапозоном
        Random r = new Random();
        return r.nextInt((max - min) + 1) + min;
    }

    public static void main(String[] args)
    {
        try
        {
            Scanner scan = new Scanner(System.in);
            System.out.print("Пожалуйста, введите значение n (размерность матрицы): ");
            int n = scan.nextInt();
            if (n < 1)
                throw new IllegalArgumentException("Введено некорректное значение n. Разрешённый диапозон: [1; +oo)");
            int[][] matrix = new int[n][n];
            System.out.println("Исходная матрица:");
            for (int i = 0; i < matrix.length; i++)
            {
                matrix[i] = new int[10];
                for (int j = 0; j < matrix.length; j++)
                {
                    matrix[i][j] = generateRandomIntIntRange(-n, n);
                    System.out.print(matrix[i][j]+ "\t");
                }
                System.out.println();
            }
            System.out.println("Транспонированная матрица:");
            for (int i = 0; i < matrix.length; i++)
            {
                for (int[] matrix1 : matrix)
                {
                    System.out.print(matrix1[i] + "\t");
                }
                System.out.println();
            }
        }
        catch (IllegalArgumentException ex)
        {
            System.out.println("Ошибка! Было выброшено исключение. Описание ошибки:\n" + ex.getMessage());
        }
    }
}