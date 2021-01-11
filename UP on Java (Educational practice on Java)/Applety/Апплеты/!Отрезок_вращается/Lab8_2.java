import java.applet.Applet;
import java.awt.*;

import static java.lang.Math.cos;
import static java.lang.Math.sqrt;
import static java.lang.Math.sin;


public class Lab8_2 extends Applet implements Runnable {

    private boolean stop;
    private int x1, x2, y1, y2, xp, yp;
    private double args1;
    private boolean w = true;
    private double modul1, modul2;
    private Color linec, pointc;
    private Thread timer = null;

    public void init() {
        this.xp = 250;
        this.yp = 250;
        this.x1 = Integer.parseInt(getParameter("x1"));
        this.x2 = Integer.parseInt(getParameter("x2"));
        this.y1 = Integer.parseInt(getParameter("y1"));
        this.y2 = Integer.parseInt(getParameter("y2"));
        args1 = 0;
        modul1 = 0;
        this.modul2 = (sqrt((y1 - y2) * (y2 - y1) + (x2 - x1) * (x2 - x1)));
        this.setBackground(new Color(Integer.parseInt(getParameter("color_background"))));
        this.linec = new Color(Integer.parseInt(getParameter("color_line")));
        this.pointc = new Color(70, 0, 0);
        timer = new Thread(this);
        timer.start();
    }

    public void start() {
        super.start();
        stop = false;
        if (timer == null) {
            timer = new Thread(this);
            timer.start();
        }
    }

    public void stop() {
        super.stop();
        stop = true;
    }

    public void destroy() {
        super.destroy();
        stop = true;

    }

    public void run() {
        while (!stop) {
            try {
                Thread.sleep(100);
                repaint();
                args1 += 0.1;
            } catch (Exception err) {
                System.err.println("Thread Error!");
            }
        }

    }

    public void paint(Graphics g) {
        double args = args1;
        if (w) {
            make1(g, args);
        } else {
            make2(g, args);
        }
    }

    private void make1(Graphics g, double args) {
        int xp1, yp1;
        if (y2 > y1)
            yp1 = yp + 1;
        else
            yp1 = yp - 1;
        if (x2 > x1)
            xp1 = xp + 1;
        else
            xp1 = xp - 1;
        modul1++;
        modul2--;


        y1 = yp + (int) (sin(args) * modul1);
        x1 = xp - (int) (cos(args) * modul1);
        y2 = yp - (int) (sin(args) * modul2);
        x2 = xp + (int) (cos(args) * modul2);
        xp = xp1;
        yp = yp1;
        g.setColor(linec);
        g.drawLine(x1, y1, x2, y2);
        g.setColor(pointc);
        g.drawOval(xp - 1, yp - 1, 2, 2);
        if (modul2 < 5) {
            w = false;
        }
    }

    private void make2(Graphics g, double args) {
        int xp1, yp1;
        if (y2 > y1)
            yp1 = yp - 1;
        else
            yp1 = yp + 1;
        if (x2 > x1)
            xp1 = xp - 1;
        else
            xp1 = xp + 1;
        modul1--;
        modul2++;

        y1 = yp + (int) (sin(args) * modul1);
        x1 = xp - (int) (cos(args) * modul1);
        y2 = yp - (int) (sin(args) * modul2);
        x2 = xp + (int) (cos(args) * modul2);
        xp = xp1;
        yp = yp1;
        g.setColor(linec);
        g.drawLine(x2, y2, x1, y1);
        g.setColor(pointc);
        g.drawOval(xp - 1, yp - 1, 2, 2);
        if (modul1 < 5) {
            w = true;
        }
    }

}
