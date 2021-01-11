public class Bubble_Sort
{
    public static void Flag_Bubble_Sort(int[] arr, int size)
    { // Метод сортировки "Пузырёк с флажком"
        boolean check = false;
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
                if (arr[j] < arr[j + 1])
                    continue;
                else
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    check = true;
                }
            if (!check)
                break;
        }
    }
}