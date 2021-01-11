import java.awt.BasicStroke;
import java.awt.Shape;
import java.awt.Stroke;
import java.awt.geom.GeneralPath;
import java.awt.geom.PathIterator;

public class MyStroke implements Stroke
{
	BasicStroke stroke;

	double vectorstep = 1;
	double anglestep = 0.5;
	double amp = 6;
	
	
	public MyStroke(float width)
	{
		this.stroke = new BasicStroke(width);
	}

	public Shape createStrokedShape(Shape shape)
	{
		GeneralPath newshape = new GeneralPath(); // Start with an empty shape

		float[] coords = new float[2];
		float[] prevCoord = new float[2];
		double angle =0;

		
		for (PathIterator i = shape.getPathIterator(null); !i.isDone();
				i.next())
		{
			int type = i.currentSegment(coords);
			switch (type)
			{
			case PathIterator.SEG_MOVETO:
				newshape.moveTo(coords[0], coords[1]);
				break;

			case PathIterator.SEG_LINETO:
				double x1 = prevCoord[0];
				double y1 = prevCoord[1];
				double x2 = coords[0];
				double y2 = coords[1];

				double dx = x2 - x1;
				double dy = y2 - y1;

				double cosvectorX = x1;
				double cosvectorY = y1;

				double vectorangle =  Math.PI/2 + Math.atan(dy/dx);

				double r = Math.sqrt(dx*dx + dy*dy);
				while ((x1-cosvectorX)*(x1-cosvectorX) + (y1-cosvectorY)*(y1-cosvectorY) < dx*dx +dy*dy)
				{
					angle += anglestep;
					double delta = amp*Math.cos(angle);
					cosvectorX+=vectorstep*dx/r;
					cosvectorY+=vectorstep*dy/r;
					newshape.lineTo(cosvectorX + delta*Math.cos(vectorangle), cosvectorY + delta*Math.sin(vectorangle));
				}
				break;

			}

			prevCoord[0] = coords[0];
			prevCoord[1] = coords[1];
		}

		return stroke.createStrokedShape(newshape);
	}

}
