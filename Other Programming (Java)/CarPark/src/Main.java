import java.io.FileNotFoundException;

public class Main {



    public static void main(String[] args) throws InterruptedException {
        Car c1 = new Car("first");
        Car c2 = new Car("second");
        Car c3 = new Car("third");
        Car c4 = new Car("fourth");
        Car c5 = new Car("fifth");

        CarPark cp = new CarPark(c1, c2, c3, c4, c5);

        System.out.println(cp.Park);

        Car c6 = new Car("sixth");
        Car c7 = new Car("seventh");

        cp.JoinPark(c6);

        System.out.println(cp.Park);

        while (!cp.flag) {}

        cp.LeavePark(c3);

        System.out.println(cp.Park);

        while (!cp.flag) {}

        cp.JoinPark(c7);

        System.out.println(cp.Park);

        while (!cp.flag) {}

        cp.LeavePark(c1);

        System.out.println(cp.Park);

    }

}
