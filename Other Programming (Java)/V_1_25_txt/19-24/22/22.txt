// Вариант 22.
// Задача с параболой - одна из лабораторных по апплетам
import java.applet.Applet;
import java.awt.*;
import java.util.StringTokenizer;

public class Main extends Applet
{
    private int rGrid;
    private int gGrid;
    private int bGrid;
    private int rPlot;
    private int gPlot;
    private int bPlot;
    private int[] xPoints;
    private int[] yPoints;
    int n;

    public void init(){
        setSize(600, 500);
        String param = getParameter("colorOfGrid"), grid, plot;
        if(param != null)
            grid = param;
        else
            grid = "10 10 10";
        param = getParameter("colorOfPlot");
        if(param != null)
            plot = param;
        else
            plot = "255 255 255";
        StringTokenizer st = new StringTokenizer(grid);
        rGrid = Integer.parseInt(st.nextToken());
        gGrid = Integer.parseInt(st.nextToken());
        bGrid = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(plot);
        rPlot = Integer.parseInt(st.nextToken());
        gPlot = Integer.parseInt(st.nextToken());
        bPlot = Integer.parseInt(st.nextToken());
    }

    public void paint(Graphics g){
        n = (int) ( 3 / 0.05 + 1);
        xPoints = new int[n];
        yPoints = new int[n];
        double x, y;
        int i = 0;
        x = -1;
        double p = (getHeight() + getWidth())/14;
        while (x <= 2.05){
            y = Math.pow(x, 2) - 1;
            xPoints[i] = (int)(x*p);
            yPoints[i++] = -1*(int)(y*p);
            System.out.println(x + "   " + y);
            x += 0.05;
        }
        int height = getHeight();
        int width = getWidth();
        g.setColor(new Color(rGrid, gGrid, bGrid));
        g.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 20));
        g.drawLine(width/2, 0, width/2, height);//y
        g.drawLine(0, (int)(height*(2/3.)), width, (int)(height*(2/3.)));//x
        g.drawLine(width/2, 0, width/2 - height/45, height/30);//cursor for y
        g.drawLine(width/2, 0, width/2 + height/45, height/30);//cursor for y
        g.drawString("Y", width/2 - 20, height/15);
        g.drawLine(width, (int)(height*(2/3.)), width - width/35, (int)(height*(2/3.)) - height/35);//cursor for x
        g.drawLine(width, (int)(height*(2/3.)), width - width/35, (int)(height*(2/3.)) + height/35);//cursor for x
        g.drawString("X", width - width/20, (int)(height*(2/3.)) + height/20);
        g.translate(width/2, (int)(height*(2/3.)));
        g.drawLine((int)-p, height/45, (int)-p, -1*(height/45));//-1x
        g.drawLine((int)p, height/45, (int)p, -1*(height/45));//1x
        g.drawLine((int)(2*p), height/45, (int)(2*p), -1*(height/45));//2x
        for (i = -3; i < 2; i++)
            g.drawLine(-1*(width/70), (int)(i*p), width/70, (int)(i*p));
        g.setColor(new Color(rPlot, gPlot, bPlot));
        for (i = 0; i < n - 1; i++)
            g.drawLine(xPoints[i], yPoints[i], xPoints[i+1], yPoints[i+1]);
    }
}
