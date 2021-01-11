//Якимович Елизавета
//12 группа
//Лабораторная № 8
//вариант 8

import java.applet.Applet;
import java.awt.*;
public class SectorCircle extends Applet  implements  Runnable{
    final static String paramBackGround = "AppBackGroundColor";
    final static String centerXString = "CenterX";
    final static String centerYString = "CenterY";
    final static String radiusString = "Radius";
    final static String startAngleString = "StartAngle";
    final static String endAngleString = "EndAngle";
    final static String fillColorString = "PieColor";
    Color pieColor = null;
    int centerX, centerY, radius;
    int startAngle, endAngle, angle;
    Thread appletThread = null;


    public Color getHtmlColor(String strRGB) {
        // in form #RRGGBB
        if (strRGB != null && strRGB.charAt(0)== '#') {
            try {
                return new Color(Integer.parseInt( strRGB.substring(1), 16 ) );
            } catch ( NumberFormatException e ) {
                return new Color( 90, 90, 160 );
            }
        }
        return new Color( 90, 90, 160 );
    }

    public int getCoordinate(String str){
        try{
            int x = Integer.parseInt(str);
            if (x <= 0 || x >= 400)
                return 200;
        }
        catch(Exception ex){
        }
        return 200;
    }

    public int getRadius(String str){
        int num = 0;
        try{
            num =  Integer.parseInt(str);
        }
        catch (Exception ex){
            num = 0;
        }
        finally {
            if (num == 0 || centerX - num <= 0 || centerY - num <= 0)
                num = centerX < centerY ? centerX : centerY;
        }
        return num;
    }

    public int getAngle(String str) {
        int angle = 0;
        try{
            angle = Integer.parseInt(str);
        }
        catch (Exception ex){
            angle = 0;
        }
        return checkAngle(angle);
    }

    public void checkTwoAngle(){
        if (startAngle == endAngle){
            startAngle = 0;
            endAngle = 90;
        }
    }

    public int checkAngle(int angle){
        while (angle >= 360)
            angle -= 360;
        while (angle < 0)
            angle +=360;
        return angle;
    }

    public void init(){
       if (appletThread == null) {
            Color col = getHtmlColor(getParameter( paramBackGround ));
            setBackground(col);
            centerX = getCoordinate(getParameter(centerXString));
            centerY = getCoordinate(getParameter(centerYString));
            radius = getRadius(getParameter(radiusString));
            startAngle = getAngle(getParameter(startAngleString));
            endAngle = getAngle(getParameter(endAngleString));
            checkTwoAngle();
            angle = endAngle - startAngle;
            pieColor = getHtmlColor(getParameter(fillColorString));
            appletThread = new Thread( this);
        }
        appletThread.start();
    }

    synchronized void drawNext() {
        repaint();
        startAngle -= 15;
    }

    public void run(){
        while ( true )
            try {
                    Thread.sleep( 150 );
                drawNext();
            } catch ( Exception e ) {
                break;
            }

    }

    public void destroy() {
        if (appletThread != null ) {
            appletThread.interrupt();
            appletThread = null;
        }
    }

    public void paint(Graphics g) {
        g.setColor(pieColor);
        g.fillArc(centerX - radius ,centerY - radius, radius, radius, startAngle, angle);
    }
}
