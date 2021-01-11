import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

import javax.swing.table.AbstractTableModel;

class TableInfo extends AbstractTableModel
{

    String[] colnames =
    {
        "Количество", "Название"
    };
    Class[] classes = new Class[]
    {
        String.class, String.class
    };
    private int сс = 2;

    ArrayList<String[]> info;
    // Конструктор
    public TableInfo()
    {
    	info= new ArrayList<String[]>();
    }

    // Получение элемента
    public Object getValueAt(int rowIndex, int columnIndex)
    {
        return info.get(rowIndex)[columnIndex];

    }

    ;

    // Добавление элемента
    public void setValueAt(String[] value)
    {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    ;

    // Изменение элемента
    public void updateValue(String newValue, int rowIndex, int columnIndex)
    {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    ;

    // количество строк
    public int getRowCount()
    {
        return info.size();
    }

    ;

    // количество столбцов
    public int getColumnCount()
    {
        return сс;
    }

    ;

    public String getColumnName(int col)
    {
        return colnames[col];
    }

    
    @Override
    public Class getColumnClass(int col)
    {
        return classes[col];
    }


    void LoadData(Class res, String filepath)
    {
    	//info.clear();
    	try {
			Scanner sc = new Scanner(new File (filepath));
			while (sc.hasNextLine()){
				String[] buf = sc.nextLine().split("\\|");
				String push[] = new String[2];
				push[0] = buf[0];
				push[1] = buf[1];
				info.add(push);
			}
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
    	
        fireTableChanged(null);
    }
}
