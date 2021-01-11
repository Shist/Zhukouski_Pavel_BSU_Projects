
public class Train {
    int number;
    String[] stations;
    String initialStation;
    String endStation;
    int[] prices;
    public Train()
    {}
    public Train(int num, String[] st, String initSt, String endSt, int[] pr) {
        assert (num < 0) : "INVALID NUMBER FORMAT";
        assert (initSt == endSt) : "INVALID NUMBER FORMAT";
        this.number = num;
        this.stations = st;
        this.initialStation = initSt;
        this.endStation = endSt;
        this.prices = pr;
    }
}
