import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class InsertSingleNameDialog extends JDialog
{
	private JPanel contentPane;
	private JButton buttonConfirm;
	private JTextPane nameTextPane;

	private String name;

	public InsertSingleNameDialog(String name)
	{
		setContentPane(contentPane);
		setModal(true);
		getRootPane().setDefaultButton(buttonConfirm);
		setTitle("Вставка нового объекта типа: " + name);

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
		name = nameTextPane.getText();

		dispose();
	}

	@Override
	public String getName()
	{
		return name;
	}
}
