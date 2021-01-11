//Сектор внутри круга, крутиться против часовой стрелки (в центре они находятся)
//Цвета круга, сектора, длину радиуса, угол сектора, через параметры
import java.applet.Applet;
import java.awt.*;

public class Pie extends Applet implements Runnable {
    Thread thread = null;
    long sleepingTime = 300;
    int centerX, centerY;
    int radix;
    int angle = 90;
    int startAngle = 0;
    int score = 5;
    Color pieColor = Color.blue;
    Color circleColor = Color.red;

    public void readParameters(){
        try{
            radix = Integer.parseInt(getParameter("Radius"));
            if (radix > getWidth()/2 || radix > getHeight()/2 || radix <= 0)
                radix = getHeight() > getWidth() ? getWidth()/2: getHeight()/2;
        }
        catch (Exception ex){
            radix = getHeight() > getWidth() ? getWidth()/2: getHeight()/2;
        }

        try{
            pieColor = Color.decode(getParameter("ColorPie"));
        }
        catch (Exception ex){
            pieColor = Color.CYAN;
        }

        try{
            circleColor = Color.decode(getParameter("ColorCircle"));
        }
        catch (Exception ex){
            circleColor = Color.BLACK;
        }

        try{
            angle = Integer.parseInt(getParameter("Angle"));
            if (angle > 360 || angle < 0)
                angle = 90;
        }
        catch (Exception ex){
            angle = 90;
        }
    }

    public void init(){
        centerX = getWidth() / 2;
        centerY = getHeight() / 2;
        readParameters();
        if (thread == null){
            thread = new Thread(this);
            thread.start();
        }
    }

    public void paint(Graphics gr) {
        gr.setColor(circleColor);
        gr.fillArc(centerX - radix, centerY - radix, radix*2, radix*2, startAngle, 360);
        gr.setColor(pieColor);
        gr.fillArc(centerX - radix, centerY - radix, radix*2, radix*2, startAngle, angle);
    }

    public void count() {
        startAngle += score;
        if(startAngle >360 )
            startAngle = 0;
    }

    public void run(){
        while (true){
            try{
                thread.sleep(sleepingTime);
                count();
                repaint();
            }
            catch (Exception ex){
				break;
            }
        }
    }

    public void destroy(){
        if (thread != null){
            thread.interrupt();
            thread = null;
        }
    }
}
