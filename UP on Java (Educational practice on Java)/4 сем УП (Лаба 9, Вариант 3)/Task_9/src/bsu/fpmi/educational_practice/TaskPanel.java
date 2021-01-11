package bsu.fpmi.educational_practice;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.util.Vector;
import javax.swing.*;
import javax.swing.plaf.basic.BasicRadioButtonUI;

public class TaskPanel extends Panel
{
    protected String Label_Text;
    protected String RadioButton_1_Text;
    protected String RadioButton_2_Text;
    protected String Button_Text;

    protected Label Label = new Label();
    protected ButtonGroup RB_Group = new ButtonGroup();
    protected JRadioButton RadioButton_1 = new JRadioButton();
    protected JRadioButton RadioButton_2 = new JRadioButton();
    protected Button Button = new Button();


    public String getLabel_Text()
    {
        return Label_Text;
    }

    public void setLabel_Text(String text)
    {
        this.Label_Text = text;

        Label.setText(text);
    }


    public String getRadioButton_1_Text()
    {
        return RadioButton_1_Text;
    }

    public void setRadioButton_1_Text(String text)
    {
        this.RadioButton_1_Text = text;

       RadioButton_1.setText(text);
    }


    public String getRadioButton_2_Text()
    {
        return RadioButton_2_Text;
    }

    public void setRadioButton_2_Text(String text)
    {
        this.RadioButton_2_Text = text;

       RadioButton_2.setText(text);
    }


    public String getButton_Text()
    {
        return Button_Text;
    }

    public void setButton_Text(String text)
    {
        this.Button_Text = text;

        Button.setLabel(text);
    }


    protected Vector<AnswerListener> listeners = new Vector<AnswerListener>();

    public void addAnswerListener(AnswerListener l)
    {
        listeners.addElement(l);
    }

    public void removeAnswerListener(AnswerListener l)
    {
        listeners.removeElement(l);
    }

    public void fireEvent(AnswerEvent e)
    {
        Vector list = (Vector) listeners.clone();

        for (int i = 0; i < list.size(); i++)
        {
            AnswerListener listener = (AnswerListener) list.elementAt(i);
            listener.buttonPressed(e.getState());
        }
    }


    public TaskPanel()
    {
        Button.addActionListener((ActionEvent e) ->
        {
            int info = AnswerEvent.NONE;

            if (RadioButton_1.isSelected() && RadioButton_2.isSelected())
            {
                info = AnswerEvent.BOTH;
            }
            else if (!RadioButton_1.isSelected() && RadioButton_2.isSelected())
            {
                info = AnswerEvent.SECOND;
            }
            else if (RadioButton_1.isSelected() && !RadioButton_2.isSelected())
            {
                info = AnswerEvent.FIRST;
            }

            fireEvent(new AnswerEvent(this, info));
        });

        JPanel panel = new JPanel();

        panel.setBounds(100, 50, 80, 200);
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        add(panel);

        panel.add(Label);
        panel.add(RadioButton_1);
        panel.add(RadioButton_2);
        panel.add(Button);

        setLabel_Text("RB_Label");
        setRadioButton_1_Text("RadioButton_1");
        setRadioButton_2_Text("RadioButton_2");
        setButton_Text("Confirm_Buttun");

        RB_Group.add(RadioButton_1);
        RB_Group.add(RadioButton_2);
    }
}
