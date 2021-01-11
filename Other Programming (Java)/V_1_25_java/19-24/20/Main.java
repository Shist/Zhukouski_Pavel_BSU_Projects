// Вариант 20.
// В следующих заданиях выполнить соответствующий рисунок в окне апплета:
// 1. Создать классы Point и Line. Объявить массив из n объектов класса Point.
// Для объекта класса Line определить какие из объектов Point лежат на одной стороне
// от прямой линии и какие - на другой. Реализовать ввод данных для объекта Line и
// случайное задание данных для объектов Point.
import java.applet.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

public class Main extends Applet {

    public static int CX = 400, CY = 400;
    public static  double k;
    public static double b;
    public Main(){
        k = 0.9;
        b = 40;

    }
    public void paint(Graphics g){
        g.drawLine(0,(int)b,CX,(int)(k*CX+b));
        ArrayList<Point> pts = new ArrayList<Point>();

        Random rand = new Random();

        for(int i = 0 ; i < 10; i++){
            pts.add(new Point(rand.nextInt(getWidth()),rand.nextInt(getHeight()) ));
        }
        for(int i = 0; i < 10; i++){
            Point p = pts.get(i);
            if(p.y>k*p.x + b)
            {
                g.setColor(Color.GREEN);
                g.fillOval(p.x,p.y,6,6);
            }
            else if (p.y<k*p.x + b){
                g.setColor(Color.RED);
                g.fillOval(p.x,p.y,6,6);
            }
            else{
                g.setColor(Color.BLUE);
                g.fillOval(p.x,p.y,6,6);
            }
        }
    }
}
class Point {
    public int x;
    public int y;
    public Point(int xr,int yr){
        x = xr;
        y = yr;
    }
}
