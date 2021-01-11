import java.util.ArrayList;

import static java.lang.Thread.sleep;

public class CarPark {

    public ArrayList<Car> Park = new ArrayList<Car>();

    public boolean flag = true;

    CarPark(Car c1, Car c2, Car c3, Car c4, Car c5)
    {
        Park.add(c1);
        Park.add(c2);
        Park.add(c3);
        Park.add(c4);
        Park.add(c5);
    }

    public void JoinPark(Car c) throws InterruptedException {
        flag = false;
        sleep(1000);
        Park.add(c);
        flag = true;
    }

    public void LeavePark(Car c) throws InterruptedException {
        flag = false;
        sleep(1000);
        Park.remove(c);
        flag = true;
    }

}
