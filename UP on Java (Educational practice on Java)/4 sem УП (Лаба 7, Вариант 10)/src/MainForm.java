import javax.swing.*;
import java.awt.event.*;

public class MainForm
	extends JFrame
{
	private JComboBox<Table> tablePickComboBox;
	private JButton insertButton;
	private JTable dbTable;
	private JPanel contentPane;
	private JScrollPane scrollPane;

	private DatabaseConnector connector;

	public MainForm()
	{
		setSize(800, 900);

		setContentPane(contentPane);
		for (Table value : Table.values())
			tablePickComboBox.addItem(value);

		try
		{
			connector = new DatabaseConnector();
		}
		catch (RuntimeException ex)
		{
			JOptionPane.showMessageDialog(null, ex.getMessage(),
										  "Error", JOptionPane.ERROR_MESSAGE);
			System.exit(-1);
		}

		addWindowListener(new WindowAdapter()
		{
			@Override
			public void windowOpened(WindowEvent e)
			{
				try
				{
					dbTable.setModel(connector.selectTable((Table) tablePickComboBox.getSelectedItem()));
				}
				catch (RuntimeException ex)
				{
					JOptionPane.showMessageDialog(null, ex.getMessage(),
												  "Error", JOptionPane.ERROR_MESSAGE);
				}
			}

			@Override
			public void windowClosing(WindowEvent e)
			{
				try
				{
					connector.close();
				}
				catch (Exception ex)
				{
					JOptionPane.showMessageDialog(null, ex.getMessage(),
												  "Error", JOptionPane.ERROR_MESSAGE);
				}

				System.exit(0);
			}
		});

		tablePickComboBox.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				try
				{
					dbTable.setModel(connector.selectTable((Table) tablePickComboBox.getSelectedItem()));
				}
				catch (RuntimeException ex)
				{
					JOptionPane.showMessageDialog(null, ex.getMessage(),
												  "Error", JOptionPane.ERROR_MESSAGE);
				}
			}
		});

		insertButton.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				switch ((Table)tablePickComboBox.getSelectedItem())
				{
					case Manufacture_Cities:
						{
							InsertSingleNameDialog dialog = new InsertSingleNameDialog("Город производителя");
							dialog.pack();
							dialog.setVisible(true);

							if (dialog.getName() != null)
								connector.insertInTable(Table.Manufacture_Cities, dialog.getName());
						}
						break;
					case Suppliers:
						{
							InsertSingleNameDialog dialog = new InsertSingleNameDialog("Поставщик");
							dialog.pack();
							dialog.setVisible(true);

							if (dialog.getName() != null)
								connector.insertInTable(Table.Suppliers, dialog.getName());
						}
						break;
					case Manufacture_Streets:
						{
							InsertSingleNameDialog dialog = new InsertSingleNameDialog("Улица производства");
							dialog.pack();
							dialog.setVisible(true);

							if (dialog.getName() != null)
								connector.insertInTable(Table.Manufacture_Streets, dialog.getName());
						}
						break;
					case Peripherals:
						{
							InsertmonumDialog dialog = new InsertmonumDialog();
							dialog.pack();
							dialog.setVisible(true);

							if (dialog.getperiph() != null)
								connector.insertInTable(Table.Peripherals, dialog.getperiph());
						}
						break;
				}

				try
				{
					dbTable.setModel(connector.selectTable((Table) tablePickComboBox.getSelectedItem()));
				}
				catch (RuntimeException ex)
				{
					JOptionPane.showMessageDialog(null, ex.getMessage(),
												  "Error", JOptionPane.ERROR_MESSAGE);
				}
			}
		});
	}

	public static void main(String[] args)
	{
		MainForm form = new MainForm();
		form.setVisible(true);
	}
}
