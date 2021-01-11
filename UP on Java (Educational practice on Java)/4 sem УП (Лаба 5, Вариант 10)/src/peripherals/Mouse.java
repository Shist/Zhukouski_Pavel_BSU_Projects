package peripherals;

public abstract class Mouse extends Peripheral
{
    protected Mouse(String name, String per_dscr)
    {
    	super(name, per_dscr);
    }
    int keys_num;
    void SetKeysNum(int k_n){
        keys_num = k_n;
    }
    int getDegree(){
        return keys_num;
    }
}
