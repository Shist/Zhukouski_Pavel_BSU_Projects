package peripherals;

public abstract class Peripheral
{
    String name;
    String per_dscr; // Peripheral description
    public String getName()
    {
        return name;
    }
    public void setName(String name)
    {
        this.name = name;
    }
    public String GetPeripheral() { return per_dscr; }
    public void SetPeripheral(String peripheral) { this.per_dscr = peripheral; }
    protected Peripheral(String name, String peripheral)
    {
        super();
        this.name = name;
        this.per_dscr = peripheral;
    }
}