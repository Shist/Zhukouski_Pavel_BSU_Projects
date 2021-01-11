// Вариант 17.
// считать с консоли размерность n матрицы.
// Матрицу заполнить рандомными числами из диапазона от -n до n.
// Транспонировать матрицу и вывести результат

import java.util.Random;
import java.util.Scanner;

/* Вариант 17
 * считать с консоли размерность n матрицы.
 * Матрицу заполнить рандомными числами из диапазона от -n до n.
 * Транспонировать матрицу и вывести результат
 */

public class Main
{

    static int[][] getMatrix (int n) {
        int[][] matrix = new int[n][n];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                matrix[i][j] = new Random().nextInt(2*n+1) - n;
        return matrix;
    }

    public static void main(String[] args) {

        System.out.println("Enter matrix dimension:");
        Scanner in = new Scanner(System.in);
        int n = 0;
        while (true) {
            try {
                n = in.nextInt();
                if ( n <= 1 )
                    throw new IllegalArgumentException("n <= 1");
                break;
            }
            catch (Exception e) {
                System.out.println(e.getMessage() + "\nTry again...");
                in.nextLine();
            }
        }
        in.close();

        int[][] matrix = getMatrix(n);
        System.out.println("Matrix:");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                System.out.printf("%4d ", matrix[i][j]);
            System.out.println();
        }
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = tmp;
            }
        System.out.println("Transpon matrix:");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                System.out.printf("%4d ", matrix[i][j]);
            System.out.println();
        }
        System.out.println("the end.");
    }
}
