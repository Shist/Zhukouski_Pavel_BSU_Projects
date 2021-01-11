import java.applet.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

public class Stolb extends Applet
{
    static ArrayList<String> name;
    static ArrayList<Double> golos;
    static ArrayList<Color> colors;
    static String param;
    static int sum_golos = 0;

    int Graph_offset = 20;             // смещение от начала координат
    int Graph_Height = 150;
    int Y_Tick_Height = Graph_Height / 5; // коэффициент деления по оси Y
    int Graph_Width = 500;
    int X_Tick_Width = 0; //Graph_Width / golos.length; // коэффициент деления
    // по оси X
    private Color getColor()
    {
        Random rand = new Random();
        return new Color(rand.nextInt(256), rand.nextInt(256),rand.nextInt(256));
    }

    public void init()
    {
        name = new ArrayList<String>();
        golos = new ArrayList<Double>();
        colors = new ArrayList<Color>();
        String[] params;
        double znachenie;
        for (int i = 1;(param = getParameter("param_"+ i)) != null; i++)
        {
            params = param.split(" ", 2);
            znachenie = Double.parseDouble(params[0]);
            name.add(params[1]);
            golos.add(znachenie);
            sum_golos += znachenie;
            colors.add(getColor());
        }
        X_Tick_Width = Graph_Width / golos.size();
    }

    public void paint(Graphics g)
    {
        g.drawString(getParameter("param_0") , Graph_offset + 40 , Graph_offset - 10);
        g.setColor(Color.black);

        // отображение оси y
        g.drawLine(Graph_offset + Graph_Width, Graph_offset,
                Graph_offset + Graph_Width, Graph_offset + Graph_Height);
        // отображение меток оси y
        for(int i=0; i<=5; i++)
        {
            g.drawString(String.valueOf((int)i*20),  // 20 точек на метку
                    Graph_offset + Graph_Width + 10,
                    Graph_offset + Graph_Height -(i*Y_Tick_Height));

            // отображение линии сетки
            g.drawLine(Graph_offset,
                    Graph_offset + Graph_Height -(i*Y_Tick_Height),
                    Graph_offset + Graph_Width + 5,
                    Graph_offset + Graph_Height -(i*Y_Tick_Height));
        }

        // отображение оси x
        g.drawLine(Graph_offset, Graph_offset + Graph_Height,
                Graph_offset + Graph_Width, Graph_offset +
                        Graph_Height);

        // отображение меток оси x
        for(int i=0; i< golos.size(); i++)
        {
            // отображение линий на оси x
            g.drawLine(Graph_offset + X_Tick_Width*i +
                            X_Tick_Width/2,
                    Graph_offset + Graph_Height,
                    Graph_offset + X_Tick_Width*i + X_Tick_Width/2,
                    Graph_offset + Graph_Height + 5);
        }

        // вывод данных

        for(int i = 0; i < golos.size(); i++)
        {
            double zn = ((100 * golos.get(i) / sum_golos));
            g.setColor(colors.get(i));
            int bar_height = (int) Math.ceil((zn * Graph_Height / 100));
            g.drawString(name.get(i),
                    Graph_offset + X_Tick_Width*i + X_Tick_Width / 4,
                    Graph_offset + Graph_Height + 20);
            g.drawString(String.format("%.2f", zn) + "%",
                    Graph_offset + X_Tick_Width*i + X_Tick_Width / 4,
                    Graph_offset + Graph_Height + 40);
            g.fillRect(Graph_offset + X_Tick_Width*i +
                            X_Tick_Width/4,
                    Graph_offset + Graph_Height - bar_height,
                    X_Tick_Width/2,  bar_height);
        }
    }
}

