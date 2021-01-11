package bsu.fpmi.educational_practice;

import java.beans.*;

public class TaskPanelInfo extends SimpleBeanInfo
{
    static PropertyDescriptor prop(String name, String description)
    {
        try
        {
            PropertyDescriptor p = new PropertyDescriptor(name, TaskPanel.class);
            p.setShortDescription(description);
            return p;
        }
        catch (IntrospectionException e)
        {
            return null;
        }
    }

    static PropertyDescriptor[] props =
    {
        prop("Label_Text", "Label_Text"),
        prop("RadioButton_1_Text", "RadioButton_1_Text"),
        prop("RadioButton_2_Text", "RadioButton_2_Text"),
        prop("Button_Text", "Button_Text"),
    };


    @Override
    public PropertyDescriptor[] getPropertyDescriptors()
    {
        return props;
    }


    @Override
    public int getDefaultPropertyIndex()
    {
        return 0;
    }
}
