import javax.swing.*;
import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class Main {
    static String filename = MainFrame.filename;
    static String filenameBak = "Books.~dat";
    static String idxname = MainFrame.indfilename;
    static String idxnameBak = "Books.~idx";
    static int count = 0;

    public static void main(String[] args) {
        filename = MainFrame.filename;
        idxname = MainFrame.indfilename;
        if (args.length == 13) {
            filename = args[3];
            idxname = args[4];
        }
        try {
            if (args.length >= 1) {
                if (args[0].equals("-?") || args[0].equals("-h")) {
                    System.out.println(
                            "Syntax:\n" +
                                    "\t-a  [file [encoding]] - append data\n" +
                                    "\t-d                    - clear all data\n" +
                                    "\t-dk  {i|a|n} key      - clear data by key\n" +
                                    "\t-p                    - print data unsorted\n" +
                                    "\t-ps  {i|a|n}          - print data sorted\n" +
                                    "\t-psr {i|a|n}          - print data reverse sorted\n" +
                                    "\t-f   {i|a|n} key      - find record by key\n" +
                                    "\t-fr  {i|a|n} key      - find records > key\n" +
                                    "\t-fl  {i|a|n} key      - find records < key\n" +
                                    "\t-?, -h                - command line syntax\n"
                    );
                } else if (args[0].equals("-a")) {
                    // Append file with new object from System.in
                    // -a [file [encoding]]
                    appendFile(args);
                } else if (args[0].equals("-p")) {
                    // Prints data file
                    printFile();
                } else if (args[0].equals("-ps")) {
                    // Prints data file sorted by key
                    if (printFile(args, false) == false) {
                        System.exit(1);
                    }
                } else if (args[0].equals("-psr")) {
                    // Prints data file reverse-sorted by key
                    if (printFile(args, true) == false) {
                        System.exit(1);
                    }
                } else if (args[0].equals("-d")) {
                    // delete files
                    if (args.length != 1) {
                        System.err.println("Invalid number of arguments");
                        System.exit(1);
                    }
                    deleteFile();
                } else if (args[0].equals("-dk")) {
                    // Delete records by key
                    if (deleteFile(args) == false) {
                        System.exit(1);
                    }
                } else if (args[0].equals("-f")) {
                    // Find record(s) by key
                    if (findByKey(args) == false) {
                        System.exit(1);
                    }
                } else if (args[0].equals("-fr")) {
                    // Find record(s) by key large then key
                    if (findByKey(args, new KeyCompReverse()) == false) {
                        System.exit(1);
                    }
                } else if (args[0].equals("-fl")) {
                    // Find record(s) by key less then key
                    if (findByKey(args, new KeyComp()) == false) {
                        System.exit(1);
                    }
                } else {
                    System.err.println("Option is not realised: " + args[0]);
                    System.exit(1);
                }
            } else {
                System.err.println("Main: Nothing to do! Enter -? for options");
            }
        } catch (Exception e) {
            System.err.println("Run/time error: " + e);
            System.exit(1);
        }
        //  System.exit(0);
    }

    private static Scanner fin = new Scanner(System.in);

    // input file encoding:
    private static String encoding = "Cp866";
    private static PrintStream suOut = System.out;

    static Utilities readSportUser(Scanner fin) throws IOException {
        return Utilities.nextRead(fin, suOut)
                ? Utilities.readDetailed(fin, suOut) : null;
    }

    private static void deleteBackup() {
        new File(filenameBak).delete();
        new File(idxnameBak).delete();
    }

    static void deleteFile() {
        deleteBackup();
        new File(filename).delete();
        new File(idxname).delete();
    }

    private static void backup() {
        deleteBackup();
        new File(filename).renameTo(new File(filenameBak));
        new File(idxname).renameTo(new File(idxnameBak));
    }

    static boolean deleteFile(String[] args)
            throws ClassNotFoundException, IOException, KeyNotUniqueException {
        //-dk  {i|a|n} key      - clear data by key
        if (args.length != 3) {
            System.err.println("Invalid number of arguments");
            return false;
        }
        long[] poss = null;
        try (Index idx = Index.load(idxname)) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (pidx == null) {
                return false;
            }
            if (pidx.contains(args[2]) == false) {
                System.err.println("Key not found: " + args[2]);
                return false;
            }
            poss = pidx.get(args[2]);
        }
        backup();
        Arrays.sort(poss);
        try (Index idx = Index.load(idxname);
             RandomAccessFile fileBak = new RandomAccessFile(filenameBak, "rw");
             RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            long pos;
            while ((pos = fileBak.getFilePointer()) < fileBak.length()) {
                Utilities ut = (Utilities)
                        Buffer.readObject(fileBak, pos);
                if (Arrays.binarySearch(poss, pos) < 0) { // if not found in deleted
                    long ptr = Buffer.writeObject(file, ut);
                    idx.put(ut, ptr);
                }
            }
        }
        return true;
    }

    static void appendFile(String[] args)
            throws FileNotFoundException, IOException, ClassNotFoundException,
            KeyNotUniqueException {

        if (!args[1].isEmpty()) {
            FileInputStream stdin = new FileInputStream(args[1]);
            System.setIn(stdin);
            encoding = args[2];

            // hide output:
            suOut = new PrintStream("nul");
        }
        Utilities ut = new Utilities();
        ut.HouseNum = args[5];
        ut.FlatNum = args[6];
        ut.Address = args[7];
        ut.FIO = args[8];
        ut.PaymentDate = args[9];
        ut.PaymentAmount = args[10];
        ut.PenaltyInterest = args[11];
        ut.PaymentDelayedDays = args[12];

        appendFile(ut);
    }

    static void appendFile(Utilities ut)
            throws FileNotFoundException, IOException, ClassNotFoundException,
            KeyNotUniqueException {
        Scanner fin = new Scanner(System.in, encoding);
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            //for (; ; ) {
            idx.test(ut);
            long pos = Buffer.writeObject(raf, ut);
            idx.put(ut, pos);
            //     }
        }
    }

    static void appendFile()
            throws FileNotFoundException, IOException, ClassNotFoundException,
            KeyNotUniqueException {
        Scanner fin = new Scanner(System.in, encoding);
        suOut.println("Enter utilities data: ");
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            for (; ; ) {
                Utilities ut = readSportUser(fin);
                if (ut == null)
                    break;
                idx.test(ut);
                long pos = Buffer.writeObject(raf, ut);
                idx.put(ut, pos);
            }
        }
    }

    private static void printRecord(RandomAccessFile raf, long pos)
            throws ClassNotFoundException, IOException {
        Utilities ut = (Utilities) Buffer.readObject(raf, pos);
        MainFrame.str += "\n#" + count++;
        MainFrame.str += " record at position " + pos + ": \n" + ut + "\n";
    }

    private static void printRecord(RandomAccessFile raf, String key,
                                    IndexBase pidx) throws ClassNotFoundException, IOException {
        long[] poss = pidx.get(key);
        for (long pos : poss) {
            MainFrame.str += "*** Key: " + key + " points to";
            printRecord(raf, pos);
        }
    }

    static void printFile()
            throws FileNotFoundException, IOException, ClassNotFoundException {
        long pos;
        int rec = 0;
        try (RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            while ((pos = raf.getFilePointer()) < raf.length()) {
                printRecord(raf, pos);
            }
            System.out.flush();
        }
    }

    private static IndexBase indexByArg(String arg, Index idx) {
        IndexBase pidx = null;
        if (arg.equals("i")) {
            pidx = idx.FIOs;
        } else if (arg.equals("a")) {
            pidx = idx.FLatNum;
        } else if (arg.equals("n")) {
            pidx = idx.HouseNum;
        } else {
            System.err.println("Invalid index specified: " + arg);
        }
        return pidx;
    }

    static boolean printFile(String[] args, boolean reverse)
            throws ClassNotFoundException, IOException {
        if (args.length != 2) {
            System.err.println("Invalid number of arguments");
            return false;
        }
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (pidx == null) {
                return false;
            }
            String[] keys =
                    pidx.getKeys(reverse ? new KeyCompReverse() : new KeyComp());
            for (String key : keys) {
                printRecord(raf, key, pidx);
            }
        }
        return true;
    }

    static boolean findByKey(String[] args)
            throws ClassNotFoundException, IOException {
        if (args.length != 3) {
            System.err.println("Invalid number of arguments");
            return false;
        }
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (pidx.contains(args[2]) == false) {
                System.err.println("Key not found: " + args[2]);
                return false;
            }
            printRecord(raf, args[2], pidx);
        }
        return true;
    }

    static boolean findByKey(String[] args, Comparator<String> comp)
            throws ClassNotFoundException, IOException {
        if (args.length != 3) {
            System.err.println("Invalid number of arguments");
            return false;
        }
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (pidx.contains(args[2]) == false) {
                System.err.println("Key not found: " + args[2]);
                return false;
            }
            String[] keys = pidx.getKeys(comp);
            for (int i = 0; i < keys.length; i++) {
                String key = keys[i];
                if (key.equals(args[2])) {
                    break;
                }
                printRecord(raf, key, pidx);
            }
        }
        return true;
    }

}