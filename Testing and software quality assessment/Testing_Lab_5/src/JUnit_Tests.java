import org.junit.Assert;

public class JUnit_Tests
{
    @org.junit.Test
    public void Test_1() throws Exception
    { // Проверка для сортировки
        String test_name = "Test_1";
        System.out.println(test_name + ":");
        System.out.println("Input data: 84 67 21 56 42 54");
        String result = Main.main(1);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "21 42 54 56 67 84";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_2() throws Exception
    { // Проверка для сортировки (но уже на отрицательных числах)
        String test_name = "Test_2";
        System.out.println(test_name + ":");
        System.out.println("Input data: -572 -48 -6 -25 -792");
        String result = Main.main(2);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "-792 -572 -48 -25 -6";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_3() throws Exception
    { // Проверка на символы
        String test_name = "Test_3";
        System.out.println(test_name + ":");
        System.out.println("Input data: hgw fhw fpw");
        String result = Main.main(3);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "Mistake! Incorrect input entered.";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_4() throws Exception
    { // Проверка на переполнение
        String test_name = "Test_4";
        System.out.println(test_name + ":");
        System.out.println("Input data: 78427 -56277 84722");
        String result = Main.main(4);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "Mistake! Key values that are too large or too small have been entered.";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_5() throws Exception
    { // Проверка на количество элементов
        String test_name = "Test_5";
        System.out.println(test_name + ":");
        System.out.println("Input data: 5");
        String result = Main.main(5);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "Mistake! An invalid number of numbers was entered in the input string. There must be at least two.";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_6() throws Exception
    { // Проверка на количество элементов
        String test_name = "Test_6";
        System.out.println(test_name + ":");
        System.out.println("Input data: 8 7 3 3 3 2 1");
        String result = Main.main(6);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "1 2 3 3 3 7 8";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }
}