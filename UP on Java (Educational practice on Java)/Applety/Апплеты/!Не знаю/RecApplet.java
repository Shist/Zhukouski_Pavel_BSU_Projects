package laba8_4;
import java.awt.*;
import java.awt.geom.*;
import java.applet.Applet;
import java.awt.image.BufferedImage;

/**
 * 4) Изобразить четырехугольник, вращающийся в плоскости экрана вокруг одной из своих
 вершин. Цвет фона, координаты вершин и цвет четырёхугольника задать через параметры
 апплета
 */
public class RecApplet extends java.applet.Applet implements Runnable {

    /**
     *
     */
    private static final long serialVersionUID = 1L;
    private int w, h;
    private BufferedImage bi;
    private Graphics2D big;
    private boolean stop = false;
    private Thread timer = null;

    private Color fonColor = Color.WHITE;
    private Color segmentColor = Color.LIGHT_GRAY;
    private Color pointColor = Color.GREEN;
    private Segment segment;

    // начальное расположение рисунка
    private double lengthSegment;

    // направление смещения оси вращения
    private double movePoint = -1;
    private double shift = 0;
    private double speedPoint = 1;

    // скорость изменения положения в пространстве
    private int speedRepaint = 30;

    // угол на который происходит изменения положения отрезка
    private int grad = 15;

    /** Этот метод будет вызван после загрузки апплета */
    public void init() {
        try {
            // Создаем объекты и устанавливаем начальные значения.
            Dimension dim = getSize();
            w = dim.width;
            h = dim.height;

            // Создаем Segment, задавая длину
            lengthSegment = (double) Math.min(w, h) / 3;
            segment = new Segment(lengthSegment, lengthSegment / 2, grad,
                    segmentColor, pointColor, fonColor);

            bi = (BufferedImage) createImage(w, h);
            big = bi.createGraphics();
            big.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                    RenderingHints.VALUE_ANTIALIAS_ON);

            // Создаем поток, который будет периодически вызывать метод update.
            timer = new Thread(this);
            timer.start();
        } catch (Exception e) {
            System.out.println(e);
        }
    } // end init

    // Этот метод выполняет перерисовку окна апплета
    public void update(Graphics g) {

        try {
            // Получаем указатель на объект Graphics2D
            Graphics2D g2 = (Graphics2D) g;
            grawSegment();

            // Рисуем готовое изображение на экране
            g2.drawImage(bi, 0, 0, this);

        } catch (Exception error) {
            System.out.println(error.getMessage());
        }
    } // end update

    private void grawSegment() {

        /*
         * //Очищаем рисунок big.setBackground(Color.BLUE); big.clearRect(0, 0,
         * w, h);
         */
        // Рисуем отрезок

        shift += movePoint * speedPoint;
        if (shift < -lengthSegment / 2) {
            movePoint *= -1;
            shift = -lengthSegment / 2;
        } else if (shift > lengthSegment / 2) {
            movePoint *= -1;
            shift = lengthSegment / 2;
        }
        segment.setPos(shift, speedPoint);
        segment.rotate();
        big.drawImage(segment.getSegment(), null, 0, 0);
    }

    // Этот метод выполняется в отдельном потоке (timer).
    // Он вызывает перерисовку окна апплета каждую секунду.
    public void run() {
        while (!stop) {
            try {
                repaint();
                Thread.currentThread();
                Thread.sleep(speedRepaint);
            } catch (Exception err) {
            }
        }
    }

    // Этот метод выполняется если пользователь покинул страницу
    // с апплетом. Он останавливает поток (timer) и, соответственно,
    // перерисовку окна апплета.
    public void stop() {
        super.stop();
        stop = true;
    }

    // Этот метод выполняется когда пользователь попадает на страницу
    // с апплетом. Он запускает парралельный поток (timer).
    public void start() {
        super.start();
        stop = false;
        if (timer == null) {
            timer = new Thread(this);
            timer.start();
        }

    } // end start

    // Этот метод выполняется при закрытии страницы с апплетом.
    public void destroy() {
        super.destroy();
        stop = true;
        Thread.currentThread();
        // Ждем пока парралельный поток (timer) завершит работу.
        Thread.yield();
    } // end destroy
} // end public class RotatingSegment

// создание отрезка
class Segment {
    private static double x = 0;
    final double RAD = 10;
    private double length;
    private BufferedImage segment;
    private Color segmentColor;
    private Color pointColor;
    private Color backGroundColor;

    private Rectangle2D.Double r;
    private Ellipse2D.Double p;
    private double rotationAxis;

    private Point2D.Double center;
    private double shift;
    // угол на который происходит изменения положения отрезка
    private int grad;

    Segment(double length, double posPointRotating, int grad,
            Color segmentColor, Color pointColor, Color backGroundColor)
            throws Exception {
        // проверяем параметры
        if (length <= 0 || posPointRotating < 0 || length < posPointRotating)
            throw new Exception(
                    "Ошибка: неверно задан параметр в классе Segment");

        this.grad = grad;
        this.segmentColor = segmentColor;
        this.pointColor = pointColor;
        this.backGroundColor = backGroundColor;
        this.length = length;
        // создаем рисунок
        segment = new BufferedImage((int) length * 3, (int) length * 3,
                BufferedImage.TYPE_INT_ARGB);

        center = new Point2D.Double(length, 3 * length / 2);
        // создаем отрезок
        rotationAxis = center.x + posPointRotating - RAD / 2;
        r = new Rectangle2D.Double(center.x, center.y, length, RAD);
        p = new Ellipse2D.Double(rotationAxis, center.y, RAD, RAD);

        // получаем графический контекст
        Graphics2D g2 = segment.createGraphics();

        // закрашиваем все заданным цветом
        g2.setBackground(backGroundColor);
        g2.clearRect(0, 0, (int) (3 * length), (int) (3 * length));

        // устанавливаем цвет отрезка
        g2.setColor(segmentColor);
        // рисуем отрезок
        g2.fill(r);
        // устанавливаем цвет точки
        g2.setColor(pointColor);
        // рисуем точку
        g2.fill(p);
    }

    // смещает точку вращения
    public void setPos(double shiftX, double shiftY) {

        // создаем отрезок
        this.shift = shiftX;
        center.y = center.y + shiftY * Math.sin(Math.toRadians(grad * x));
        r = new Rectangle2D.Double(center.x, center.y, length, RAD);
        p = new Ellipse2D.Double(rotationAxis + shift, center.y, RAD, RAD);
    }

    // вращает отрезок
    public void rotate() {
        AffineTransform at = AffineTransform.getRotateInstance(
                Math.toRadians(grad * (++x)), rotationAxis + RAD / 2 + shift,
                center.y);

        // получаем графический контекст
        Graphics2D g2 = segment.createGraphics();

        // закрашиваем все заданным цветом
        g2.setBackground(backGroundColor);
        g2.clearRect(0, 0, (int) (3 * length), (int) (3 * length));

        g2.setTransform(at);
        g2.setColor(segmentColor);
        // рисуем отрезок
        g2.fill(r);
        // устанавливаем цвет точки
        g2.setColor(pointColor);
        // рисуем точку
        g2.fill(p);

    }

    // Возвращает изображение
    public BufferedImage getSegment() {
        return segment;
    }
}
