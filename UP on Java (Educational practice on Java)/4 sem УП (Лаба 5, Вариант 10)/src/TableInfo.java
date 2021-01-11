import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

import javax.swing.table.AbstractTableModel;

class TableInfo extends AbstractTableModel
{

    String[] colnames =
    {
        "����������", "��������"
    };
    Class[] classes = new Class[]
    {
        String.class, String.class
    };
    private int �� = 2;

    ArrayList<String[]> info;
    // �����������
    public TableInfo()
    {
    	info= new ArrayList<String[]>();
    }

    // ��������� ��������
    public Object getValueAt(int rowIndex, int columnIndex)
    {
        return info.get(rowIndex)[columnIndex];

    }

    ;

    // ���������� ��������
    public void setValueAt(String[] value)
    {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    ;

    // ��������� ��������
    public void updateValue(String newValue, int rowIndex, int columnIndex)
    {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    ;

    // ���������� �����
    public int getRowCount()
    {
        return info.size();
    }

    ;

    // ���������� ��������
    public int getColumnCount()
    {
        return ��;
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
