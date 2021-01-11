package bsu.fpmi.educational_practice;

public class AnswerEvent extends java.util.EventObject
{
    public static final int NONE = 0, FIRST = 1, SECOND = 2, BOTH = 3;
    protected int state;

    public AnswerEvent(Object source, int state)
    {
        super(source);
        this.state = state;
    }

    public int getState()
    {
        return state;
    }
}