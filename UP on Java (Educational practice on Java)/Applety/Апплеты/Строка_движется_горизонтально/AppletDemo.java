import java.applet.Applet;
import java.awt.*;
import java.util.*;

public class AppletDemo extends Applet implements Runnable {
    String msg;
    Thread t = null;
    int state;
    int length;
    int trig;
    int num;
    volatile boolean rightFlag = true;
    volatile boolean stopFlag;
    volatile boolean colorFlag;
    String colorMass[];

    public void init() {
        setForeground(Color.red);
    }

    public void start() {
        msg = getParameter("text");
        String numSt = getParameter("num");
        if(numSt != null) {
            num = Integer.parseInt(numSt) - 1;
            colorMass = new String[num];
            for(int count = 0; count < num; count++) {
                colorMass[count] = getParameter("color_" + count);
            }
        } else {
            colorMass = new String[1];
            colorMass[0] = "Color.red";
        }
        if(msg == null) msg = "Message not found";
        msg = " " + msg;
        length = msg.length();
        t = new Thread(this);
        stopFlag = false;
        t.start();
    }

    public void run() {
        for( ; ; ) {
            try {
                repaint();
                Thread.sleep(100);
                if(stopFlag)
                    break;
            } catch(InterruptedException e) {}
        }
    }

    public void stop() {
        stopFlag = true;
        t = null;
    }

    public void paint(Graphics g) {
        char ch;

        if(trig < length) {

            if(rightFlag) {
                ch = msg.charAt(0);
                msg = msg.substring(1, msg.length());
                msg += ch;
            } else {
                ch = msg.charAt(msg.length() - 1);
                msg = msg.substring(0, msg.length() - 1);
                msg = ch + msg;
            }

            trig++;
        } else {
            if(rightFlag) {
                rightFlag = false;
                trig = 0;

            }
            else {
                rightFlag = true;
                trig = 0;
            }

        }

        g.drawString(msg, 0, 10);
    }

    public void chColor() {
        if(colorFlag) {
            String colorS = colorMass[(int)(Math.random()*num)];
            setForeground(getHtmlColor(colorS, Color.red));
        }
    }

    public Color getHtmlColor( String strRGB, Color def ) {
        // in form #RRGGBB
        if ( strRGB != null && strRGB.charAt(0)== '#' ) {
            try {
                return new Color(
                        Integer.parseInt( strRGB.substring( 1 ), 16 ) );
            } catch ( NumberFormatException e ) {
                return def;
            }
        }
        return def;
    }
}