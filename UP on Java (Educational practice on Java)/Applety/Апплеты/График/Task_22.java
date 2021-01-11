//Сысой Илья, вариант 5

import java.applet.*;
import java.awt.*;

public class GraphApplet extends Applet {
    private int a = -1;
    private int b = 2;
    private double step = 0.05;
    private double scale;
    String col_func;
    String col_graph;
    int xzero, yzero;
    double xscale = 1.0;
    double yscale = 1.0;

    public void init(){
        col_func = getParameter("colorOfFunction");
        col_graph = getParameter("colorOfPlot");
        setSize(600,600);


    }

    private double function(double x) {
        return x * x - 1;
    }


    public void paint(Graphics g) {
        xscale = getWidth() / 5;
        yscale = getHeight()  / 5;
        xzero =  getWidth()/2;
        yzero = getHeight()/2;
        int width = getWidth();
        int height = getHeight();
        g.setColor(Color.decode(col_graph));
        for (int i = 1; i < 10; ++i) {
            g.drawLine((width / 10) * i, 0, (width / 10) * i, height);
            g.drawLine(0, (height / 10) * i, width, (height / 10) * i);
        }


        g.setColor(Color.black);
        g.drawLine(width / 2, 0, width / 2, height);
        g.drawLine(0, height / 2, getWidth(), height / 2);
        g.setColor(Color.red);

        int k = 1;
        for (int i = -2; i <= 2; i++)
        {
            g.drawString(Integer.toString(i),(width /10)*k+2,height /2+12);
            if ( k != 5) {
                g.drawString(Integer.toString(i),(width /2) + 5,height / 10 * (10 -k) +10 );
                g.drawLine((width / 10) * k, height / 2 - 6, (width / 10) * k, height / 2 + 6);
                g.drawLine((width / 2) - 6, (height / 10 ) * k, (width / 2) + 6, (height / 10 ) * k);
            }k+= 2;
        }
        g.setColor(Color.decode(col_func));
        Graphics2D g2p = (Graphics2D) g;

        drawFunc(g);
    }


    private void drawFunc(Graphics g) {
        for (double x = a; x <= b; x += step) {
                g.drawLine((int) (x*xscale + xzero), (int) (-function(x)*yscale + yzero), (int)((x + step) * xscale + xzero), (int) (-function(x+step)*yscale + yzero));
        }
    }

}
