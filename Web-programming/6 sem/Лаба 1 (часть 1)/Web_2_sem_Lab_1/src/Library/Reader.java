package Library;

/**
 * class that represent reader entity
 * @date Zhukouski Pavel
 */
public class Reader {
    private int ID;         // ID читателя
    private String rName;   // Имя читателя
    private String rDate;   // Дата, когда читатель взял эту книгу
    private int bID;        // ID книги, экземпляр которой взял читатель

    public int getReaderID(){
        return ID;
    }
    public void setReaderID(int id){
        this.ID=id;
    }
    public String getReaderName(){
        return rName;
    }
    public void setReaderName(String reader_name){
        this.rName=reader_name;
    }
    public String getReaderDate(){
        return rDate;
    }
    public void setReaderDate(String reader_date){
        this.rDate=reader_date;
    }
    public int getBookID(){
        return bID;
    }
    public void setBookID(int b_id){
        this.bID=b_id;
    }

    public Reader(int id, String reader_name, String reader_date, int b_id) {
        setReaderID(id);
        setReaderName(reader_name);
        setReaderDate(reader_date);
        setBookID(b_id);
    }
    @Override
    public String toString() {
        return "\n### READER INFORMATION ###\n" +
                "ID = " + getReaderID() + "\n" +
                "Reader's name: \"" + getReaderName() + "\"\n" +
                "Date when reader took the book: " + getReaderDate() + "\n" +
                "ID of the book that reader has taken: " + getBookID() + "\n";
    }
}
