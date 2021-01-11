import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;

public class RoadSignApp extends JFrame implements Runnable
{

    RoadSignApp(int width, int height, String RoadName)
    {
        super(RoadName);
        setVisible(true);
        this.setSize(width, height);

        setFSuspend(false);
        Graphics g = null;
        transform = new AffineTransform();

        JFrame J = new JFrame(); // Создание объекта класса JFrame

        J.paint(g);
    }

    public AffineTransform transform;

     private static final long serialVersionUID = 1L;

    private volatile boolean fSuspend = false;

    public synchronized boolean getFSuspend() {
        return fSuspend;
    }

    public synchronized void setFSuspend(boolean value) {
        fSuspend = value;
    }

    public void suspend() {
        setFSuspend(true);
    }

    public boolean isSuspended() {
        return getFSuspend();
    }

    void drawNext() { }

    public void paint(Graphics g) {
    	
    	Graphics2D g2d = (Graphics2D)g;

		BufferedImage img = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D grImg = img.createGraphics();
		grImg.setComposite(AlphaComposite.DstOver);
		//grImg.setPaint(new GradientPaint(0, getHeight()*7/10, Color.YELLOW, getWidth(), 0, Color.GRAY, true));
		grImg.fillRect(0, 0, getWidth(), getHeight());
		g2d.drawImage(img, 0, 0, this);
    		
    	
       SignShape a = new SignShape(40, 150, 60);
       a.draw(g, this, new AffineTransformOp(AffineTransform.getRotateInstance(0.2617993877991494D, 0.0D, 190.0D), 1));
       
       SignShape b = new SignShape(40, 70, 60);
       b.draw(g, this, null);
    }
    public void run() {
        suspend();
        while (true)
            try {
                Thread.sleep(100);
                if (isSuspended() == false) {
                    drawNext();
                }
            } catch (Exception e) {
                break;
            }
    }
}