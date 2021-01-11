import java.awt.*;
import java.applet.*;

class Drawing extends Canvas {

    Color color;

    public int[] xPoints = new int[4];
    public int[] yPoints = new int[4];
    //Dimension dim = new Dimension( 20, 20 );

    public Drawing( Color bc, Color fc, int[] xPoints, int[] yPoints) {
        super();
        color = fc;
        this.xPoints = xPoints;
        this.yPoints = yPoints;
        setBackground( bc );
        //setMaximumSize( dim );
        setBounds( 0, 0, 400, 400 );

    }

    public void paint(Graphics g) {
        g.setColor( color );
        g.fillPolygon(xPoints, yPoints, 4);

    }
}


public class QuadApplet extends Applet {

    public final static int[] X_POINTS = {
            0, 40, 40, 0,
    };
    public final static int[] Y_POINTS = {
            0, 0, 40, 40,
    };

    public final static double ANGLE = Math.PI / 100;

    Drawing c;

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

    public int getHtmlCoordinate(String strC, int def){
        if(strC != null){
            try{
                return Integer.parseUnsignedInt(strC);
            }
            catch (NumberFormatException e){
                return def;
            }
        }
        return def;
    }

    public void init() {
        setSize( 400, 400 );
        setLayout( null );
        Color col = getHtmlColor(
                getParameter( "BackgroundColor" ), new Color( 255, 255, 255 ));
        setBackground( col );
        Color colx = getHtmlColor(
                getParameter( "QuadColor" ), new Color( 64, 64, 64 ));

        int[] tempX = new int[4];
        int[] tempY = new int[4];
        for(int i = 0; i < 4; i++){
            tempX[i] = getHtmlCoordinate(getParameter( "x" + (i+1) ), X_POINTS[i]);
            tempY[i] = getHtmlCoordinate(getParameter( "y" + (i+1) ), Y_POINTS[i]);

        }
        c = new Drawing( col, colx , tempX, tempY);
        add(c);
    }

    public void start() {
        startThread();
    }

    public void stop() {
        stopThread();
    }

    public void destroy() {
        stopThread();
    }

    private AppletThread t = null;

    private void createThread() {
        if ( t == null ) {
            t = new AppletThread( this );
        }
    }

    private void startThread() {
        createThread();
        t.start();
    }

    private void stopThread() {
        if ( t != null ) {
            t.interrupt();
            t = null;
        }
    }


//    public void paint(Graphics g) {
//        g.drawString("Hello World!", 20, 20);
//    }
}

class AppletThread extends Thread {
    QuadApplet pa = null;
    //Random r = new Random( new Date().getTime());
    int xx[] = new int[4];
    int yy[] = new int[4];
    int step = 1;

    public AppletThread( QuadApplet pa ) {
        super();
        this.pa = pa;

        xx[0] = pa.c.xPoints[0];
        yy[0] = pa.c.yPoints[0];
        for(int i = 1; i < 4;++i){
            xx[i] = pa.c.xPoints[i] - xx[0];
            yy[i] = pa.c.yPoints[i] - yy[0];
        }
    }

    public void run() {
        while ( true ) {
            try {
                Thread.sleep( 10 );
                doMove();
                if(++step > 200) {
                    step = 1;
                }
            } catch ( InterruptedException e ) {
                break;
            }
        }
    }

    public synchronized void doMove() {
        for(int i = 1; i < 4; i++){
//			pa.c.X_POINTS[i] =(int) (pa.c.X_POINTS[0]+(xx[i]-pa.c.X_POINTS[0])*Math.cos(step * Math.PI/100) + (yy[i]-pa.c.Y_POINTS[0])*Math.sin(step * Math.PI / 100));
//
//			pa.c.Y_POINTS[i]= (int) (pa.c.Y_POINTS[0]-(xx[i]-pa.c.X_POINTS[0])*Math.sin(step * Math.PI/100) + (yy[i]-pa.c.Y_POINTS[0])*Math.cos(step * Math.PI / 100));
            pa.c.xPoints[i] =(int) (xx[0]+xx[i]*Math.cos(step * QuadApplet.ANGLE) + yy[i]*Math.sin(step * QuadApplet.ANGLE));
            pa.c.yPoints[i]= (int) (yy[0]-xx[i]*Math.sin(step * QuadApplet.ANGLE) + yy[i]*Math.cos(step * QuadApplet.ANGLE));
        }
        pa.c.repaint();
    }
}