import java.applet.Applet;
import java.awt.*;

public class DrawApplet extends Applet{
    public void init() {
        setSize(600, 600);        
    }
    
    public void paint(Graphics g) {                  
        g.setColor(Color.BLUE);
        for (int i = 1; i <= 4; ++i) {
            g.drawLine((getWidth() / 10) * i, 0, (getWidth() / 10) * i, getHeight());
            g.drawLine(0, (getHeight() / 10) * i, getWidth(), (getHeight() / 10) * i);
        }
        for (int i = 6; i <= 10; ++i) {
            g.drawLine((getWidth() / 10) * i, 0, (getWidth() / 10) * i, getHeight());
            g.drawLine(0, (getHeight() / 10) * i, getWidth(), (getHeight() / 10) * i);
        }

        g.setColor(Color.BLACK);
        g.drawLine(getWidth() / 2, 0, getWidth() / 2, getHeight());
        g.drawLine(getWidth() / 2, 0, getWidth() / 2, getHeight());
        
        g.drawLine(0, getHeight() / 2, getWidth(), getHeight() / 2); 
        g.drawLine(0, getHeight() / 2, getWidth(), getHeight() / 2); 
        
        for (int i = 5; i >= -5; i--) {
            g.drawString(Integer.toString(-i), (getWidth() / 10) * (5 - i) + 4, getHeight() / 2 + 11);
            if (i != 0)
                g.drawString(Integer.toString(i), getWidth() / 2 + 2, getHeight() / 10 * (5 - i) + 11);
        }
        
        g.setColor(Color.RED);
        drawFunc(g);
    }
    
    private double function(double x) {
        return x * x - 1;
    }

    private void drawFunc(Graphics g) {
        double xscale = getWidth() / 10, yscale = getHeight() / 10;
        double x0 = getWidth() / 2, y0 = getHeight() / 2;
        for (double x = -1; x <= 2; x += 0.05) {
                g.drawLine((int) (x*xscale + x0), (int) (-function(x)*yscale + y0),
                (int)((x + 0.05) * xscale + x0), (int) (-function(x+0.05)*yscale + y0));
        }
    }
}