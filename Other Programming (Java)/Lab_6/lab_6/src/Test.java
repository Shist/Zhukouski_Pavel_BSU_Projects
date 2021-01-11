
public class Test {
    public static void main(String[] args) {
        try {
            Administrator admin = new Administrator("Galina Petrovna Obozova");
            String[] st1 = {"Minsk", "Gomel", "Adler"};
            int[] pr1 = {0, 10, 15};
            Train tr1 = new Train(718, st1, st1[0], st1[2], pr1);
            String[] st2 = {"Minsk", "Gomel"};
            int[] pr2 = {0, 13};
            Train tr2 = new Train(709, st2, st2[0], st2[1], pr2);
            String[] st3 = {"Minsk", "Osipovichi", "Bobruisk", "Zhlobin", "Gomel"};
            int[] pr3 = {0, 3, 5, 7, 11};
            Train tr3 = new Train(720, st3, st3[0], st3[4], pr1);
            Administrator.addTrain(tr1);
            Administrator.addTrain(tr2);
            Administrator.addTrain(tr3);
            ConnectorAdmin conAdm = new ConnectorAdmin("adm.dat");
            conAdm.write(admin);
            Administrator newAdmin = conAdm.read();
            Passenger pass = new Passenger("Ishchanka Mikita Syarheevich");
            Request req = pass.makeRequest("Gomel", "12:15", "13.10.2018");
            newAdmin.showTrains(req);
            Check ch = newAdmin.makeCheck(pass.chooseTrain(), req);
            ch.show();
        } catch (Exception e) {
            System.err.println(e);
        }
    }

}

