import java.awt.AlphaComposite;
import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Polygon;
import java.awt.Rectangle;
import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.geom.PathIterator;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import java.awt.image.BufferedImageOp;

public class SignShape implements Shape {
	public Polygon rectangular;
	public Polygon shadow;
	public Polygon inner_rectangular;
	public int startX, startY;
	public int size;

	public SignShape(int startX, int startY, int sz) {
		this.startX = startX;
		this.startY = startY;
		this.size = sz;
		rectangular = createRectangular(sz);
		inner_rectangular = createRectangularRame(sz, 5);
		shadow = createShadow(sz, 5);
	}

	private Polygon createRectangular(int sz) {
		Polygon rct = new Polygon();
		rct.addPoint(startX , startY);
		rct.addPoint(startX, startY + sz);
		rct.addPoint(startX + 2*sz, startY + sz);
		rct.addPoint(startX + 2*sz, startY);
		return rct;
	}

	private Polygon createRectangularRame(int sz, int d)
	{
		Polygon Rame = new Polygon();
		Rame.addPoint(startX - d, startY - d);
		Rame.addPoint(startX - d, startY + sz + d);
		Rame.addPoint(startX + 2*sz + d, startY + sz + d);
		Rame.addPoint(startX + 2*sz + d, startY - d);
		Rame.addPoint(startX - d, startY - d);
		Rame.addPoint(startX , startY);
		Rame.addPoint(startX + 2*sz, startY);
		Rame.addPoint(startX + 2*sz, startY + sz);
		Rame.addPoint(startX, startY + sz);
		Rame.addPoint(startX , startY);
		return Rame;
	}

	private Polygon createShadow(int sz, int d) {
		Polygon rct = new Polygon();
		rct.addPoint(startX + 2*sz + d, startY + (int)(0.55*sz));
		rct.addPoint(startX + 2*sz + d + (int)(0.8*(sz + d)), startY + (int)(0.3*(sz + d)));
		rct.addPoint(startX + 2*sz + d + (int)(2.8*(sz + d)), startY + (int)(0.3*(sz + d)));
		rct.addPoint(startX + 2*sz + d, startY + sz + d);
		return rct;
	}
	
	public Rectangle getBounds() {
		return rectangular.getBounds();
	}

	public Rectangle2D getBounds2D() {
		return rectangular.getBounds2D();
	}

	public boolean contains(double x, double y) {
		return rectangular.contains(x, y);
	}

	public boolean contains(Point2D p) {
		return rectangular.contains(p);
	}

	public boolean contains(Rectangle2D r) {
		return rectangular.contains(r);
	}

	public boolean contains(double x, double y, double w, double h) {
		return rectangular.contains(x, y, w, h);
	}

	public boolean intersects(double x, double y, double w, double h) {
		return rectangular.intersects(x, y, w, h);
	}

	public boolean intersects(Rectangle2D r) {
		return rectangular.intersects(r);
	}

	public PathIterator getPathIterator(AffineTransform at) {
		return rectangular.getPathIterator(at);
	}

	public PathIterator getPathIterator(AffineTransform at, double flatness) {
		return rectangular.getPathIterator(at, flatness);
	}

	public void draw(Graphics g, Component c, BufferedImageOp filter) {
		Graphics2D g2d = (Graphics2D)g;
		
		BufferedImage img = new BufferedImage(c.getWidth(), c.getHeight(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D imgGr = img.createGraphics();
		
		imgGr.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.6f));
		imgGr.setPaint(new GradientPaint(startX, startY + size, Color.BLACK, startX, startY, Color.LIGHT_GRAY));
		imgGr.fill(shadow);

		imgGr.setPaint(new GradientPaint(startX, startY + size, Color.WHITE, startX, startY, Color.GRAY));
		imgGr.fill(this);
		
		imgGr.setColor(Color.YELLOW);
		imgGr.fill(inner_rectangular);
		
		imgGr.setFont(new Font("Arial", 10, (int)(size*0.7)));
		imgGr.setColor(Color.YELLOW);
		imgGr.drawString("WAIT", startX + (int)(0.1*size), startY + (int)(0.75*size));
		
		
		g2d.drawImage(img, filter, startX, startY);
	}
}