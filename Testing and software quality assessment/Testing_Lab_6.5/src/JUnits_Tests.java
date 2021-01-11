import org.junit.Assert;

public class JUnits_Tests
{
    @org.junit.Test
    public void Test_1() throws Exception
    { // Проверка для формулы на двух положительных числах
        String test_name = "Test_1";
        System.out.println(test_name + ":");
        System.out.println("Input data: 5 3");
        String result = Main.main(1);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "0" + ", выражение: 0";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_2() throws Exception
    { // Проверка для формулы на первом отрицательном и втором положительном числах
        String test_name = "Test_2";
        System.out.println(test_name + ":");
        System.out.println("Input data: 5 7");
        String result = Main.main(2);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "-4" + ", выражение: 2a-2b";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_3() throws Exception
    { // Проверка для формулы на первом положительном и втором отрицательном числах
        String test_name = "Test_3";
        System.out.println(test_name + ":");
        System.out.println("Input data: 5 -3");
        String result = Main.main(3);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "-6" + ", выражение: 2b";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_4() throws Exception
    { // Проверка для формулы на отрицательных числах
        String test_name = "Test_4";
        System.out.println(test_name + ":");
        System.out.println("Input data: -5 3");
        String result = Main.main(4);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "-6" + ", выражение: -2b";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_5() throws Exception
    { // Проверка на количество введенных данных (слишком мало)
        String test_name = "Test_5";
        System.out.println(test_name + ":");
        System.out.println("Input data: -5 -7");
        String result = Main.main(5);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "-4" + ", выражение -2a-2b";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_6() throws Exception
    { // Проверка на количество введенных данных (слишком много)
        String test_name = "Test_6";
        System.out.println(test_name + ":");
        System.out.println("Input data: -5 -3");
        String result = Main.main(6);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "0" + ", выражение: 0";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_7() throws Exception
    { // Проверка на количество введенных данных (слишком много)
        String test_name = "Test_7";
        System.out.println(test_name + ":");
        System.out.println("Input data: fhe hgw");
        String result = Main.main(7);
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
    public void Test_8() throws Exception
    { // Проверка на количество введенных данных (слишком много)
        String test_name = "Test_8";
        System.out.println(test_name + ":");
        System.out.println("Input data: 56472 49384");
        String result = Main.main(8);
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
    public void Test_9() throws Exception
    { // Проверка на введённые данные (конкретно на символы)
        String test_name = "Test_9";
        System.out.println(test_name + ":");
        System.out.println("Input data: -44226 -39852");
        String result = Main.main(9);
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
    public void Test_10() throws Exception
    { // Проверка на переполнение сверху
        String test_name = "Test_10";
        System.out.println(test_name + ":");
        System.out.println("Input data: 4");
        String result = Main.main(10);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "Mistake! An invalid number of numbers was entered in the input string. There must be two.";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }

    @org.junit.Test
    public void Test_11() throws Exception
    { // Проверка на переполнение снизу
        String test_name = "Test_11";
        System.out.println(test_name + ":");
        System.out.println("Input data: 8 7 6");
        String result = Main.main(11);
        System.out.println("Result of work of the program: " + result);
        String expected_result = "Mistake! An invalid number of numbers was entered in the input string. There must be two.";
        System.out.println("Expected_result: " + expected_result);
        if (expected_result.equals(result))
            System.out.println(test_name + ": success");
        else
            Assert.assertFalse(test_name + ": fail", true);
        System.out.println();
    }
}