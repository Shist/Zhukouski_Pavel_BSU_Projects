import java.applet.Applet;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;


public class Str extends Applet implements Runnable{
    String myString;
    Color [] colors;
    int numberOfColors;
    String paramNameNum = "num";
    String paramNameText = "text";
    int direction = 1;
    int stringWidth;
    int position = 0;
    Thread thread = null;
    int currentColor = 0;

    public void init() {
        myString = getParameter(paramNameText);
        numberOfColors = Integer.parseInt((getParameter(paramNameNum)));
        colors = new Color[numberOfColors];
        for (int i = 0; i < numberOfColors; i++) {
            colors[i] = Color.decode(getParameter("color_" + i));
        }
        if (thread == null) {
            repaint();
            thread = new Thread(this);
            thread.start();
        }
    }

    public void paint(Graphics g) {
        g.setFont(new Font("TimesRoman", Font.PLAIN, 40));
        g.setColor(colors[currentColor]);
        stringWidth = g.getFontMetrics().stringWidth(myString);
        g.drawString(myString, position, getHeight()/2);
    }


    public void drawNext() {
        if (direction == 1) {
            position += 2;
            if (position + stringWidth > getWidth()) {
                position = getWidth() - stringWidth;
                direction = 0;
                currentColor++;
            }
        }
        else {
            position -= 2;
            if (position < 0) {
                direction = 1;
                position = 0;
                currentColor ++;
            }
        }
        if (currentColor == numberOfColors)
            currentColor = 0;
        repaint();
    }

    public void run() {
        while(true) {
            try {
                drawNext();
                Thread.sleep(50);
            }
            catch(Exception ex) {
                break;
            }
        }
    }

    public void destroy() {
        if (thread != null ) {
            thread.interrupt();
            thread = null;
        }
    }

}
