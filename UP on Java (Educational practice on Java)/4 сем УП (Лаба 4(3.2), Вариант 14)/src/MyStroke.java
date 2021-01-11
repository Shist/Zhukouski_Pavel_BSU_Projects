import java.awt.*;
import java.awt.geom.*;

public class MyStroke implements Stroke {
    private BasicStroke stroke;

    MyStroke(float width) {
        this.stroke = new BasicStroke(width);
    }

    public Shape createStrokedShape(Shape shape) {
        GeneralPath shape1 = new GeneralPath();
        double[] coord = new double[2];
        double[] prevCoord = new double[2];
        double t = -5;
        for (PathIterator i = shape.getPathIterator(null); !i.isDone(); i.next()) {
            int type = i.currentSegment(coord);
            switch (type) {
                case PathIterator.SEG_MOVETO:
                    shape1.moveTo(coord[0], coord[1]);
                    break;
                case PathIterator.SEG_LINETO:
                    double x1 = prevCoord[0];
                    double y1 = prevCoord[1];
                    double x2 = coord[0];
                    double y2 = coord[1];
                    double dx = x2 - x1;
                    double dy = y2 - y1;
                    double length = Math.sqrt(dx * dx + dy * dy);
                    dx /= length;
                    dy /= length;
                    x1 += dx * t;
                    y1 += dy * t;
                    length -= t;
                    t = 0;
                    double step = 10;
                    if (!Double.isInfinite(length)) {
                        while (t <= length) {
                            x1 += -dx * step + dy * step;
                            y1 += dy * step + dx * step;
                            shape1.lineTo(x1, y1);

                            x1 += +dy * step;
                            y1 += -dx * step;
                            shape1.lineTo(x1, y1);

                            x1 += dx * step;
                            y1 += dy * step;
                            shape1.lineTo(x1, y1);

                            x1 += -dy * step;
                            y1 += +dx * step;
                            shape1.lineTo(x1, y1);

                            x1 += -dy * step + dx * step;
                            y1 += dx * step + dy * step;
                            shape1.lineTo(x1, y1);

                            t += 3 * step;
                        }
                        t -= length;
                    }
                    break;
            }
            prevCoord[0] = coord[0];
            prevCoord[1] = coord[1];
        }
        return stroke.createStrokedShape(shape1);
    }
}
