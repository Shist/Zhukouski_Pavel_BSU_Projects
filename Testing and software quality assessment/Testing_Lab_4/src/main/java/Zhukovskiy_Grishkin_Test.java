import junit.framework.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Assert;

public class Zhukovskiy_Grishkin_Test extends TestCase // TestCase - класс от JUNIT
{
    public Zhukovskiy_Grishkin_Test(String TestName)
    { // Конструктор
        super(TestName); // super - вызывает конструктор класса-родителя
    }

    @org.junit.Test
    public void test_1()
    {
        System.out.println("test_1: Print something");
    }

    @org.junit.Test
    public void test_2()
    {
        System.out.println("test_2: The work of Always-True-Method");
        Assert.assertTrue("test_2: The work of Always-True-Method", true);
    }

    @org.junit.Test
    public void test_3()
    {
        System.out.println("test_3: The work of Always-False-Method");
        Assert.assertFalse("test_3: The work of Always-False-Method", true);
    }

    @Before
    public void setUp()
    { // Специальный метод для общей инициализации и зачистки (уборки) наших тестовых методов.
        System.out.println("\nThis is initialization code of method\n");
    }

    @After
    public void tearDown()
    { // Специальный метод для общей инициализации и зачистки (уборки) наших тестовых методов.
        System.out.println("\nThis is end code of method\n");
    }

    public static Test suite() // Специальный метод JUNIT для запуска тестов
    { // НАБОР ТЕСТОВ
        TestSuite suite = new TestSuite(); // Создаём набор тестов

        suite.addTest(new Zhukovskiy_Grishkin_Test("test_1"));
        suite.addTest(new Zhukovskiy_Grishkin_Test("test_2"));
        suite.addTest(new Zhukovskiy_Grishkin_Test("test_3"));

        suite.addTest(new Zhukovskiy_Grishkin_Test("test_3"));
        suite.addTest(new Zhukovskiy_Grishkin_Test("test_2"));
        suite.addTest(new Zhukovskiy_Grishkin_Test("test_1"));

        return suite;
    }
}