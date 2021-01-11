import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeNode;

import peripherals.*;
// 10) Каталог магазина периферийных устройств компьютера (принтеры, сканеры, плоттеры, мониторы и т.п.)
public class Main extends javax.swing.JFrame {

    /**
     * Creates new form Main
     */
	public void printTable(Class res, String filepath){
		System.out.println(filepath);
	}
	
	public void initDynamicTree(){
		dynamicTree = new DynamicTree();
		dynamicTree.populateTree();

		dynamicTree.addTreeSelectionListener(new TreeSelectionListener() {

			@Override
			public void valueChanged(TreeSelectionEvent e) {
				DefaultMutableTreeNode node = (DefaultMutableTreeNode) dynamicTree
						.getLastSelectedPathComponent();

				/* if nothing is selected */
				if (node == null)
					return;
				TreeNode[] p = node.getPath();
				Class res = null;
				String filepath = "";
				int L = p.length;
				if (L == 1 || L == 2 || L == 3 || (L == 4 && p[0].getIndex(p[1]) == 2) && p[1].getIndex(p[2]) == 0)
					return;
				switch (p[0].getIndex(p[1])) {
					case 0: // GraphicsTablets
						if (p[1].getIndex(p[2]) == 0) { // ScreenGraphicsTablets
							res = ScreenGraphicsTablet.class;
							filepath = "peripherals\\GraphicsTablets\\ScreenGraphicsTablets\\"
									+ DynamicTree.c1_1.getChildAt(
									p[2].getIndex(p[3])).toString();
						}
						if (p[1].getIndex(p[2]) == 1) { // UnscreenGraphicsTablets
							res = UnscreenGraphicsTablet.class;
							filepath = "peripherals\\GraphicsTablets\\UnscreenGraphicsTablets\\"
									+ DynamicTree.c1_2.getChildAt(
									p[2].getIndex(p[3])).toString();
						}
						break;
					case 1: // Headphones
						if (p[1].getIndex(p[2]) == 0) { // WiredHeadphones
							res = WiredHeadphone.class;
							filepath = "peripherals\\Headphones\\WiredHeadphones\\"
									+ DynamicTree.c2_1.getChildAt(
									p[2].getIndex(p[3])).toString();
						}
						if (p[1].getIndex(p[2]) == 1) { // WirelessHeadphones
							res = WirelessHeadphone.class;
							filepath = "peripherals\\Headphones\\WirelessHeadphones\\"
									+ DynamicTree.c2_2.getChildAt(
									p[2].getIndex(p[3])).toString();
						}
						break;
					case 2: // Keyboards
						if (p[1].getIndex(p[2]) == 0) { // WiredKeyboards
							if (p[2].getIndex(p[3]) == 0){ // MechanicalKeyboards
								res = MechanicalKeyboard.class;
								filepath = "peripherals\\Keyboards\\WiredKeyboards\\MechanicalKeyboards\\"
										+ DynamicTree.c3_1_1.getChildAt(
										p[3].getIndex(p[4])).toString();
							}
							if (p[2].getIndex(p[3]) == 1){ // MembraneKeyboards
								res = MembraneKeyboard.class;
								filepath = "peripherals\\Keyboards\\WiredKeyboards\\MembraneKeyboards\\"
										+ DynamicTree.c3_1_2.getChildAt(
										p[3].getIndex(p[4])).toString();
							}
						}
						if (p[1].getIndex(p[2]) == 1) { // WirelessKeyboards
							res = WirelessKeyboard.class;
							filepath = "peripherals\\Keyboards\\WirelessKeyboards\\"
									+ DynamicTree.c3_2.getChildAt(
									p[2].getIndex(p[3])).toString();
						}
						break;
					case 3: // Microphones
						if (p[1].getIndex(p[2]) == 0) { // WiredMicrophones
							res = WiredMicrophone.class;
							filepath = "peripherals\\Microphones\\WiredMicrophones\\"
									+ DynamicTree.c4_1.getChildAt(
									p[2].getIndex(p[3])).toString();
						}
						if (p[1].getIndex(p[2]) == 1) { // WirelessMicrophones
							res = WirelessMicrophone.class;
							filepath = "peripherals\\Microphones\\WirelessMicrophones\\"
									+ DynamicTree.c4_2.getChildAt(
									p[2].getIndex(p[3])).toString();
						}
						break;
					case 4: // Mouses
						if (p[1].getIndex(p[2]) == 0) { // WiredMouses
							res = WiredMouse.class;
							filepath = "peripherals\\Mouses\\WiredMouses\\"
									+ DynamicTree.c5_1.getChildAt(
									p[2].getIndex(p[3])).toString();
						}
						if (p[1].getIndex(p[2]) == 1) { // WirelessMouses
							res = WirelessMouse.class;
							filepath = "peripherals\\Mouses\\WirelessMouses\\"
									+ DynamicTree.c5_2.getChildAt(
									p[2].getIndex(p[3])).toString();
						}
						break;
					default:
						break;
				}
				if (res != null)
					tm.LoadData(res, filepath + ".txt");
			}
		});
	}
    public Main() {
    	initDynamicTree();
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">                          
    private void initComponents() {


        jScrollPane = new javax.swing.JScrollPane();
        jTable = new javax.swing.JTable();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);



        jTable.setModel(tm);
        jScrollPane.setViewportView(jTable);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(dynamicTree, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 442, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(dynamicTree, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(jScrollPane)
        );

        pack();
    }// </editor-fold>                        

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Main().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify                     
	private DynamicTree dynamicTree;
    private javax.swing.JScrollPane jScrollPane;
    private javax.swing.JTable jTable;
    private TableInfo tm = new TableInfo();
    // End of variables declaration                   
}
