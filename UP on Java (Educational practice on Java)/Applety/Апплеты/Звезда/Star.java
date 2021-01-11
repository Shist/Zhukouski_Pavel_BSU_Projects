import java.applet.Applet;
import java.awt.*;

public class Star extends Applet implements Runnable {

    Thread thread = null;

    int timeSleep = 20;
    int counts = 5;
    Color bgColor = Color.blue;
    Color startColor = Color.yellow;
    int radius = 50;
    int smallradius = 2*radius/5;
    int xPos = 150;
    int yPos = 150;
    int [] xArr = new int[counts * 2];
    int [] yArr = new int[counts * 2];
    double startAngle = 0;

    int step = 5;
    public void init(){
        xPos = Integer.parseInt(getParameter("centerX"));
        yPos = Integer.parseInt(getParameter("centerY"));
        createStar(xArr, yArr, counts);
        if (thread == null)
        {
            thread = new Thread(this);
            thread.start();
        }
    }

    public void createStar(int [] xArr, int [] yArr, int counts){
        double part = 360 * 1.0 / (counts * 2);

        for (int i = 0 ; i < counts * 2; i++){
            if (i % 2 == 0){
                xArr[i] = xPos + (int)(Math.cos(Math.toRadians(i * part + startAngle)) * radius);
                yArr[i] = yPos + (int)(Math.sin(Math.toRadians(i * part + startAngle)) * radius);
            }
            else{
                xArr[i] = xPos + (int)(Math.cos(Math.toRadians(i * part + startAngle)) * smallradius);
                yArr[i] = yPos + (int)(Math.sin(Math.toRadians(i * part + startAngle)) * smallradius);
            }
        }

    }

    public void run() {
        while (true){
            try {
                Thread.sleep(timeSleep);
                writeNext();
            }
            catch (Exception e){
                System.out.print(e);
                break;
            }
        }

    }

    public void writeNext(){
        startAngle += step;
        if (startAngle % 360 == 0)
            startAngle = 0;
        createStar(xArr,yArr,counts);
        repaint();
    }

    public void paint(Graphics gr) {
        gr.setColor(bgColor);
        gr.fillRect(0, 0, this.getWidth(), this.getHeight());

        gr.setColor(startColor);
        gr.fillPolygon(xArr, yArr, counts * 2);
    }

    public void destroy(){
        if (thread != null){
            thread.interrupt();
            thread = null;
        }
    }
}