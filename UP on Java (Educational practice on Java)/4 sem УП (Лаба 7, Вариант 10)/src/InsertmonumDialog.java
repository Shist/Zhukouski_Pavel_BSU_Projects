import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class InsertmonumDialog extends JDialog
{
	private JPanel contentPane;
	private JButton buttonConfirm;
	private JTextPane nameTextPane;
	private JTextPane cityTextPane;
	private JTextPane streetTextPane;
	private JTextPane yearTextPane;
	private JTextPane suplierTextPane;

	private Peripheral periph;

	public InsertmonumDialog()
	{
		setContentPane(contentPane);
		setModal(true);
		setTitle("Вставка данных о новом периферийном устройстве в БД");
		getRootPane().setDefaultButton(buttonConfirm);

		buttonConfirm.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				onConfirm();
			}
		});
	}

	private void onConfirm()
	{
		try
		{
			periph = new Peripheral(nameTextPane.getText(),
					Integer.parseInt(cityTextPane.getText()),
					Integer.parseInt(streetTextPane.getText()),
					Integer.parseInt(yearTextPane.getText()),
					Integer.parseInt(suplierTextPane.getText()));
		}
		catch (Exception ex)
		{
			JOptionPane.showMessageDialog(null, ex.getMessage(),
										  "Error", JOptionPane.ERROR_MESSAGE);
		}

		dispose();
	}

	public Peripheral getperiph()
	{
		return periph;
	}
}
