import java.awt.Rectangle;
import java.awt.Shape;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.geom.AffineTransform;
import java.awt.geom.PathIterator;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.io.IOException;
import java.io.Serializable;

public class MyShape implements Shape, Serializable, Cloneable,
		Transferable {
	private static final long serialVersionUID = -6414365760517341436L;
	int leftX;
	int leftY;
	int width;
	int height;
	double a;

	// x^3 + y^3 - 3axy = 0

	public MyShape(int x, int y, int width, int height, double a) {
		super();
		this.leftX = x;
		this.leftY = y;
		this.width = width;
		this.height = height;
		this.a = a;
	}

	@Override
	public Rectangle getBounds() {
		return new Rectangle(leftX, leftY, width, height);
	}

	@Override
	public Rectangle2D getBounds2D() {
		return new Rectangle2D.Float(leftX, leftY, width, height);
	}

	public int getCenterX() {
		return leftX + width / 2;
	}

	public int getCenterY() {
		return leftY + height / 2;
	}

	public double getR(double alpha) {
		return alpha*130;
	}

	@Override
	public boolean contains(double x, double y) {
		if (!getBounds().contains(x, y))
			return false;
		double x0 = x - getCenterX();
		double y0 = getCenterY() - y;
		if (x0 < 0 || y0 < 0)
			return false;
		double alpha = Math.atan(y0 / x0);
		double r = getR(alpha);
		return x0 * x0 + y0 * y0 < r * r;
	}

	@Override
	public boolean contains(Point2D p) {
		return contains(p.getX(), p.getY());
	}

	@Override
	public boolean intersects(double x, double y, double w, double h) {
		return getBounds().intersects(x, y, w, h);
	}

	@Override
	public boolean intersects(Rectangle2D r) {
		return getBounds().intersects(r);
	}

	@Override
	public boolean contains(double x, double y, double w, double h) {
		return contains(x, y) && contains(x + w, y) && contains(x, y + h)
				&& contains(x + w, y + h);
	}

	@Override
	public boolean contains(Rectangle2D r) {
		return contains(r.getX(), r.getY(), r.getWidth(), r.getHeight());
	}

	@Override
	public PathIterator getPathIterator(AffineTransform at) {
		return new DecartsLeafIterator(at);
	}

	@Override
	public PathIterator getPathIterator(AffineTransform at, double flatness) {
		return getPathIterator(at);
	}

	class DecartsLeafIterator implements PathIterator {
		int index = 0;
		boolean start = true;
		boolean done = false;
		double curAngle = -Math.PI;
		double angleStep = Math.PI / 60;
		private AffineTransform at;
		private boolean noTransform = false;
		private int y0 = getCenterY();
		private int x0 = getCenterX();

		public DecartsLeafIterator(AffineTransform at) {
			this.at = at;
		}

		@Override
		public int getWindingRule() {
			return WIND_NON_ZERO;
		}

		@Override
		public boolean isDone() {
			return done;
		}

		@Override
		public void next() {
			if (!start)
				curAngle += angleStep;
		}

		@Override
		public int currentSegment(float[] coords) {
			if (start) {
				coords[0] = x0;
				coords[1] = y0;
				if (noTransform)
					noTransform = false;
				else if (at != null)
					at.transform(coords, 0, coords, 0, 1);
				start = false;
				return SEG_MOVETO;
			} else {
				double r = getR(curAngle);
				coords[0] = (float) (getCenterX() + r * Math.cos(curAngle));
				coords[1] = (float) (getCenterY() - r * Math.sin(curAngle));
				if (at != null)
					at.transform(coords, 0, coords, 0, 1);
				checkForNext(coords[0], coords[1]);
				if (!getBounds().contains(coords[0], coords[1]))
					return SEG_MOVETO;
				return SEG_LINETO;
			}
		}

		@Override
		public int currentSegment(double[] coords) {
			if (start) {
				coords[0] = getCenterX();
				coords[1] = getCenterY();
				at.transform(coords, 0, coords, 0, 1);
				start = false;
				return SEG_MOVETO;
			} else {
				double r = getR(curAngle);
				coords[0] = (float) (getCenterX() + r * Math.cos(curAngle));
				coords[1] = (float) (getCenterY() - r * Math.sin(curAngle));
				at.transform(coords, 0, coords, 0, 1);
				checkForNext(coords[0], coords[1]);
				if (!getBounds().contains(coords[0], coords[1]))
					return SEG_MOVETO;
				return SEG_LINETO;
			}
		}

		private void checkForNext(double x, double y) {
			if (index == 2 && curAngle >= Math.PI) {
				done = true;
				return;
			}
			if ((index == 1 && curAngle >= Math.PI / 2)
					|| (index == 0 && !getBounds().contains(x, y))) {
				index++;
				if (index == 1)
					curAngle = 0;
				else if (index == 2) {
					curAngle = Math.PI / 4 * 3 + angleStep;
					x0 = leftX;
					y0 = leftY;
					noTransform = true;
				}
				start = true;

			}
		}

	}

	public Object clone() {
		try {
			MyShape s = (MyShape) super.clone(); // make a copy of all
															// fields
			return s;
		} catch (CloneNotSupportedException e) { // This should never happen
			return this;
		}
	}

	public static DataFlavor decDataFlavor = new DataFlavor(MyShape.class,
			"MyShape");

	// This is a list of the flavors we know how to work with
	public static DataFlavor[] supportedFlavors = { decDataFlavor,
			DataFlavor.stringFlavor };

	@Override
	public DataFlavor[] getTransferDataFlavors() {
		return (DataFlavor[]) supportedFlavors.clone();
	}

	@Override
	public boolean isDataFlavorSupported(DataFlavor flavor) {
		return (flavor.equals(decDataFlavor) || flavor
				.equals(DataFlavor.stringFlavor));
	}

	@Override
	public Object getTransferData(DataFlavor flavor)
			throws UnsupportedFlavorException, IOException {
		if (flavor.equals(decDataFlavor)) {
			return this;
		} else if (flavor.equals(DataFlavor.stringFlavor)) {
			return toString();
		} else
			throw new UnsupportedFlavorException(flavor);
	}

	@Override
	public String toString() {
		return leftX + " " + leftY + " " + width + " " + height + " " + a;
	}

	public static MyShape getFromString(String s) {
		String[] arr = s.split(" ");
		return new MyShape(Integer.parseInt(arr[0]),
				Integer.parseInt(arr[1]), Integer.parseInt(arr[2]),
				Integer.parseInt(arr[3]), Double.parseDouble(arr[4]));
	}

	public void translate(double x, double y) {
		leftX += x;
		leftY += y;
	}
}
