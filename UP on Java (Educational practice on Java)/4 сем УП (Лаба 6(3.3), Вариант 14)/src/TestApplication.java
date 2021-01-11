import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class TestApplication
{
    public static void main(String[] args)
    {
        JFrame frame1 = new JFrame("Line: Ordinary Cycloid (variant 14), power by Pavel Zhukovskiy - 1st window");
        frame1.addWindowListener(new WindowAdapter()
        {
            public void windowClosing(WindowEvent e)
            {
                System.exit(0);
            }
        });
        final MyDragAndDrop scribblePane1 = new MyDragAndDrop();
        frame1.getContentPane().add(scribblePane1, BorderLayout.CENTER);
        JToolBar toolbar1 = new JToolBar();
        ButtonGroup group1 = new ButtonGroup();
        JToggleButton draw1 = new JToggleButton("Режим рисования для 1-ого окна...");
        JToggleButton drag1 = new JToggleButton("Режим перетаскивания из 1-ого окна...");
        draw1.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)
            {
                scribblePane1.setDragMode(false);
            }
        });
        drag1.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)
            {
                scribblePane1.setDragMode(true);
            }
        });
        group1.add(draw1);
        group1.add(drag1);
        toolbar1.add(draw1);
        toolbar1.add(drag1);
        frame1.getContentPane().add(toolbar1, BorderLayout.NORTH);
        draw1.setSelected(true);
        scribblePane1.setDragMode(false);
        frame1.setSize(800, 400);
        frame1.setVisible(true);

        JFrame frame2 = new JFrame("Line: Ordinary Cycloid (variant 14), power by Pavel Zhukovskiy - 2nd window");
        frame2.addWindowListener(new WindowAdapter()
        {
            public void windowClosing(WindowEvent e)
            {
                System.exit(0);
            }
        });
        final MyDragAndDrop scribblePane2 = new MyDragAndDrop();
        frame2.getContentPane().add(scribblePane2, BorderLayout.CENTER);
        JToolBar toolbar2 = new JToolBar();
        ButtonGroup group2 = new ButtonGroup();
        JToggleButton draw2 = new JToggleButton("Режим рисования для 2-ого окна...");
        JToggleButton drag2 = new JToggleButton("Режим перетаскивания из 2-ого окна...");
        draw2.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)
            {
                scribblePane2.setDragMode(false);
            }
        });
        drag2.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)
            {
                scribblePane2.setDragMode(true);
            }
        });
        group2.add(draw2);
        group2.add(drag2);
        toolbar2.add(draw2);
        toolbar2.add(drag2);
        frame2.getContentPane().add(toolbar2, BorderLayout.NORTH);
        draw2.setSelected(true);
        scribblePane2.setDragMode(false);
        frame2.setSize(800, 400);
        frame2.setVisible(true);
    }
}
