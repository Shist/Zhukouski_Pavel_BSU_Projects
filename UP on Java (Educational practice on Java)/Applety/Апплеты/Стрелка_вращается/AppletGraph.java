import java.applet.Applet;
import java.awt.Color;
import java.awt.Point;

public class AppletGraph extends Applet {
	
	private static final long serialVersionUID = 1L;
	static final int CX = 500, CY = 500;
	Arrow c;

	public Color getHtmlColor(String strRGB, Color def) {
		
		if (strRGB != null && strRGB.charAt(0) == '#') {
			try {
				return new Color(Integer.parseInt(strRGB.substring(1), 16));
			} catch (NumberFormatException e) {
				return def;
			}
		}
		return def;
	}
	public int getIntValue(String strInt,int def) {
		try {
			return Integer.parseInt(strInt);
		}catch(NumberFormatException e) {
			return def;
		}	
	}
	
	public void init() {
        setSize( CX, CY );
        setLayout( null );
        Color col = getHtmlColor(getParameter( "AppBkColor" ), new Color( 0, 0, 0 ));
        setBackground( col );
        Color colx = getHtmlColor(getParameter( "ArrowColor" ), new Color( 0, 255, 0 ));
        Point point =new Point(getIntValue(getParameter( "X" ),200),getIntValue(getParameter( "Y" ),200));
        int radius = getIntValue(getParameter( "Radius" ),150);
        c = new Arrow( colx, radius,point.x,point.y );
      
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
}
