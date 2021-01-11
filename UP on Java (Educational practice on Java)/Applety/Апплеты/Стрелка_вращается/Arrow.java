
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;

public class Arrow extends Canvas {
	
	private static final long serialVersionUID = 1L;
	Color clr;
	int radius;
	Point point;
	double angle;
	Dimension dim;
	Graphics gImg = null;
	Image mImg;

	public Arrow(Color color, int radius, int x, int y) {
		super();
		angle = Math.PI;
		clr = color;
		point = new Point(x, y);
		this.radius = radius;
		dim = new Dimension(2*radius, 2*radius);
		setMaximumSize(dim);
		setBounds(0, 0, dim.width, dim.height);
	}

	public void paint(Graphics g) {
		if (mImg != null)
			g.drawImage(mImg, 0, 0, null);
	}

	void prepareDraw(Graphics g) {
		g.setColor(clr);
	}

	void rotateBy(double angle) {
		this.angle = (this.angle + angle) % (2 * (Math.PI));
	}

	public void update(Graphics g) {		
		mImg = createImage(dim.width, dim.height);
		gImg = mImg.getGraphics();
		
		prepareDraw(gImg);
		draw(gImg);
		paint(g);
	}

	void draw(Graphics g) {
		int radX = (int) (radius * Math.sin(angle));
		int radY = (int) (radius * Math.cos(angle));

		int x = radius - radX;
		int y = radius - radY;
		int d = radius / 5;
		double a = 0.5;
		g.drawLine(radius, radius, x, y);

		int X[] = { x, (int) (x + d * Math.sin(angle + a)), (int) (x + d * Math.sin(angle - a)) };
		int Y[] = { y, (int) (y + d * Math.cos(angle + a)), (int) (y + d * Math.cos(angle - a)) };
		g.fillPolygon(X, Y, 3);
		// g.drawLine( point.x+radius, point.y, point.x+radius-5, point.y );
		// g.drawLine( point.x+radius, point.y, point.x+radius+5, point.y );
	}

	public Dimension getMinimumSize() {
		return dim;
	}

	public Dimension getPreferredSize() {
		return dim;
	}
}
