// Вариант 19.
// Сделать 2 точки,сделать прямую и определить по какую сторону лежат точки
import java.applet.Applet;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.util.Random;

class Point_ extends Canvas {
    Color clr;
    int x, y;
    Dimension dim = new Dimension(20, 20);
    public Point_ (int appWidth, int appHeight) {
        super();
        setMaximumSize(dim);
        setBackground(null);
        setBounds(0, 0, dim.width, dim.height);
        clr = Color.black;
        x = new Random().nextInt(appWidth - dim.width) + dim.width / 2;
        y = new Random().nextInt(appHeight - dim.height) + dim.height / 2;
    }
    public void paint (Graphics g) {
        g.setColor(clr);
        g.fillOval(0, 0, dim.width, dim.height);
    }
    public void setColor (Color clr) {
        this.clr = clr;
    }
    public Dimension getMinimumSize () { return dim; }
    public Dimension getPreferredSize () { return dim; }
}

class Line_ {
    Color clr;
    int x1, y1, x2, y2;
    public Line_ (Color c, int x1, int y1, int x2, int y2) {
        clr = c;
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
    }
    public int compare (Point_ p) {
        double tg = (double)(y2 - y1) / (x2 - x1);
        int xt = (int)(x1 - (double)(y1 - p.y) / tg);
        if ( p.x < xt )
            return -1;
        else if ( p.x > xt )
            return 1;

        int yt = (int)(y1 - tg * (x1 - p.x));
        if ( p.y < yt )
            return 1;
        else if ( p.y > yt )
            return -1;
        return 0;
    }
}

public class Main extends Applet {

    private static final long serialVersionUID = 1L;
    static final int CX = 600, CY = 500;
    Canvas point_first;
    Canvas point_second;
    Line_ Line_;
    String s;

    public Color getHtmlColor (String rgb, Color def) {
        if ( rgb == null || rgb.charAt(0) != '#' )
            return def;
        try {
            return new Color(Integer.parseInt(rgb.substring(1), 16));
        } catch (NumberFormatException e) {
            return def;
        }
    }

    public void init () {
        setSize(CX, CY);
        setLayout(null);
        setBackground(Color.white);
        Color clr = Color.BLACK;
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        try {
            clr = getHtmlColor(getParameter("Line_Color"), Color.BLACK);
            x1 = Integer.parseInt((getParameter("x1") == null)?"50":getParameter("x1"));
            y1 = Integer.parseInt((getParameter("y1") == null)?"50":getParameter("y1"));
            x2 = Integer.parseInt((getParameter("x2") == null)?"550":getParameter("x2"));
            y2 = Integer.parseInt((getParameter("y2") == null)?"450":getParameter("y2"));
        } catch (Exception e) {}
        Line_ = new Line_(clr, x1, y1, x2, y2);
        point_first = new Point_(this.getWidth(), this.getHeight());
        point_second = new Point_(this.getWidth(), this.getHeight());

        int ans_first = ((Line_)Line_).compare((Point_)point_first);
        int ans_second = ((Line_)Line_).compare((Point_)point_second);

        Color cl_first = Color.red;
        Color cl_second = Color.red;

        s = new String();

        switch (ans_first) {
            case -1: cl_first = Color.red; break;
            case 1: cl_first = Color.green; break;
            default: cl_first = Color.yellow;
        }
        switch (ans_second) {
            case -1: cl_second = Color.red; break;
            case 1: cl_second = Color.green; break;
            default: cl_second = Color.yellow;
        }
        if(ans_second == ans_first){
            if(ans_second == -1)
                s="dots are left from the line";
            if(ans_second == 1)
                s="dots are right from the line";
            if(ans_second == 0)
                s="dots are on the line";
        }else{
            if(ans_second + ans_first == 0)
                s="dots are on the different sides of the line";
            else{
                s="one dot is on line, and another one is";
                if(ans_second==-1 || ans_first==-1)
                    s+=" rigth";
                else
                    s+=" left";
                s+=" from the line";
            }
        }

        ((Point_)point_first).setColor(cl_first);
        point_first.setLocation(((Point_)point_first).x, ((Point_)point_first).y);
        add(point_first);

        ((Point_)point_second).setColor(cl_second);
        point_second.setLocation(((Point_)point_second).x, ((Point_)point_second).y);
        add(point_second);

        repaint();
    }
    public void paint (Graphics g) {
        g.drawString(s, 0, 280);
        g.setColor(Line_.clr);
        g.drawLine(Line_.x1, Line_.y1, Line_.x2, Line_.y2);
    }

}






/* <html>
<meta http-equiv="Content-Type" content="text/html; charset=Cp65001"/>
<body>
<applet code=var19.class width="500" height="500" >
</applet>
</body>
</html>
*/
