import javax.swing.*;
import java.awt.event.ActionEvent;

public class MainFrame extends javax.swing.JFrame {

    public static String s, filename, indfilename;

    private JTextField tfFileName;
    private JPanel pRoot;
    private JPanel p1;
    private JButton btRun;
    private JTextField tfResult;
    private JTextField tfIndFileName;
    private JTextArea taResult;
    private JScrollPane scrollPane;
    private JTextField tf;
    private JTextField tfKey;
    private JTextField tfFIO;
    private JTextField tfID;
    private JTextField tfInfo;
    private JTextField tfTrainerFIO;
    private JTextField tfRate;
    private JTextField tfMins;
    private JTextField tfDate;
    private JButton BtDelByKey;
    private JButton BtAppend;
    private JButton BtDelAll;
    private JButton BtPrintSortedReverseByFIO;
    private JButton BtPrintSortedByFIO;
    private JButton BtPrintAll;
    private JPanel PanButs;
    private JButton BtFindByKey;
    private JButton BtFindBiggerKey;
    private JButton BtFindLessKey;
    public static String str;



    boolean areFilesOk()
    {
        filename = tfFileName.getText(); //*
        indfilename = tfIndFileName.getText(); //*
        if(filename.isEmpty())
        {
            JOptionPane.showMessageDialog(null,"Filename is wrong!");
            return false;
        }
        if(indfilename.isEmpty())
        {
            JOptionPane.showMessageDialog(null,"Index filename is wrong!");
            return false;
        }
        return  true;
    }

    MainFrame() {

        BtAppend.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                areFilesOk();
                int errNum = -1;
                String[] arr = new String[12];
                //проверка на то, введено ли всё
                arr[0] = "-a";
                arr[1] = tfKey.getText(); //-
                arr[2] = "Cp866";  //*
                arr[3] = filename; //*
                arr[4] = indfilename; //*
                arr[5] = tfFIO.getText();
                arr[6] = tfID.getText();
                arr[7] = tfInfo.getText();
                arr[8] = tfTrainerFIO.getText();
                arr[9] = tfDate.getText();
                arr[10] = tfMins.getText();
                arr[11] = tfRate.getText();
                for (int i = 5; i < 12; i++)
                    if (errNum == -1 && arr[i].isEmpty())
                        errNum = i;
                String [] arrRes = {"ФИО", "ID секции","Информация о секции","ФИО тренера","Дата","Минуты","Рейтинг"};

                if (errNum != -1) {
                    JOptionPane.showMessageDialog(null,"Значение " + arrRes[errNum-5].toString() + " не верно!");
                    taResult.setText("Значение " + arrRes[errNum - 5] + " не верно!");
                } else {
                    Main.main(arr);
                    taResult.setText("Appended successfully!");
                }
            }

        });
        //удалить всё
        BtDelAll.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                areFilesOk();
                String [] arrDel = new String[1];
                arrDel[0] = "-d";
                Main.main(arrDel);
                taResult.setText("Deleted successfully!");
            }
        });
        //удалить по ключу
        BtDelByKey.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                areFilesOk();
                String [] arrDel = new String[3];
                arrDel[0] = "-dk";
                arrDel[1] = "i";
                arrDel[2] = tfKey.getText();
                if(tfKey.getText().isEmpty()){
                    JOptionPane.showMessageDialog(null,"Поле ключ пусто!");
                    taResult.setText("Поле ключ пусто!");
                }

                Main.main(arrDel);
                taResult.setText("Deleted successfully!");

            }
        });

        BtFindByKey.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                areFilesOk();
                String [] arrDel = new String[3];
                arrDel[0] = "-f";
                arrDel[1] = "i";
                arrDel[2] = tfKey.getText();
                if(tfKey.getText().isEmpty()){
                    JOptionPane.showMessageDialog(null,"Поле ключ пусто!");
                    taResult.setText("Поле ключ пусто!");
                }
                Main.main(arrDel);
                if ( str != null && !str.isEmpty()) {
                    str = str.substring(5, str.length());
                    taResult.setText(str);
                    str = "";
                }

            }
        });


        BtFindBiggerKey.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                areFilesOk();
                String [] arrDel = new String[3];
                arrDel[0] = "-fr";
                arrDel[1] = "i";
                arrDel[2] = tfKey.getText();

                if(tfKey.getText().isEmpty()){
                    JOptionPane.showMessageDialog(null,"Поле ключ пусто!");
                    taResult.setText("Поле ключ пусто!");
                }
                Main.main(arrDel);
                if ( str != null && !str.isEmpty()) {
                    str = str.substring(5, str.length());
                    taResult.setText(str);
                    str = "";
                }

            }
        });

        BtFindLessKey.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                areFilesOk();
                String [] arrDel = new String[3];
                arrDel[0] = "-fl";
                arrDel[1] = "i";
                arrDel[2] = tfKey.getText();

                if(tfKey.getText().isEmpty()){
                    JOptionPane.showMessageDialog(null,"Key is empty!");
                    taResult.setText("Key is empty!");
                }
                Main.main(arrDel);
                if ( str != null && !str.isEmpty()) {
                    str = str.substring(5, str.length());
                    taResult.setText(str);
                    str = "";
                }

            }

        });

        BtPrintAll.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                areFilesOk();
                String []arr = new String[1];
                arr[0] = "-p";
                Main.main(arr);
                if ( str != null && !str.isEmpty()) {
                    str = str.substring(5, str.length());
                    taResult.setText(str);
                    str = "";
                }

            }
        });

        BtPrintSortedByFIO.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                areFilesOk();
                String [] arrDel = new String[2];
                arrDel[0] = "-ps";
                arrDel[1] = "i";
                Main.main(arrDel);
                if ( str != null && !str.isEmpty()) {
                    str = str.substring(5, str.length());
                    taResult.setText(str);
                    str = "";
                }

            }
        });

        BtPrintSortedReverseByFIO.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                areFilesOk();
                String [] arrDel = new String[2];
                arrDel[0] = "-psr";
                arrDel[1] = "i";
                Main.main(arrDel);
                if ( str != null && !str.isEmpty()) {
                    str = str.substring(5, str.length());
                    taResult.setText(str);
                    str = "";
                }

            }
        });

        this.setResizable(false);
        setContentPane(pRoot);

        setVisible(true);
        initComponents();
    }

    private void formWindowClosed(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosed
        // TODO add your handling code here:
        System.exit(0);
    }//GEN-LAST:event_formWindowClosed

    private void jMenuItem2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem2ActionPerformed
        // TODO add your handling code here:
        System.exit(0);
    }//GEN-LAST:event_jMenuItem2ActionPerformed

    private java.io.File fileData = new java.io.File("books.dat");

    private void jMenuItem1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem1ActionPerformed
        // TODO add your handling code here:
        javax.swing.JFileChooser file = new javax.swing.JFileChooser();
        file.setMultiSelectionEnabled(false);
        file.setSelectedFile(fileData);
        if (file.showOpenDialog(this) == javax.swing.JFileChooser.APPROVE_OPTION) {
            fileData = file.getSelectedFile();
        }
    }//GEN-LAST:event_jMenuItem1ActionPerformed

    private void jMenuItem4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem4ActionPerformed
        // TODO add your handling code here:
        javax.swing.JOptionPane.showMessageDialog(this,
                "                                    \t-a  [file [encoding]] - append data \n" +
                        "                                    \t-d                         - clear all data \n" +
                        "                                    \t-dk  {i|a|n} key    - clear data by key \n" +
                        "                                    \t-p                         - print data unsorted \n" +
                        "                                    \t-ps  {i|a|n}          - print data sorted by FIO/sectionID/trainerFIO \n" +
                        "                                    \t-psr {i|a|n}          - print data reverse sorted by FIO/sectionID/trainerFIO \n" +
                        "                                    \t-f   {i|a|n} key      - find record by key\n" +
                        "                                    \t-fr  {i|a|n} key      - find records > key\n" +
                        "                                    \t-fl  {i|a|n} key      - find records < key\n" +
                        "                                    \t-?, -h                   - command line syntax");
    }//GEN-LAST:event_jMenuItem4ActionPerformed

    private void jMenuItem1FocusGained(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_jMenuItem1FocusGained
        // TODO add your handling code here:
        this.statusLabel.setText("Choose a file to work with");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem1FocusGained

    private void jMenuItem1FocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_jMenuItem1FocusLost
        // TODO add your handling code here:
        this.statusLabel.setText("");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem1FocusLost

    private void jMenuItem2FocusGained(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_jMenuItem2FocusGained
        // TODO add your handling code here:
        this.statusLabel.setText("Exit application");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem2FocusGained

    private void jMenuItem2FocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_jMenuItem2FocusLost
        // TODO add your handling code here:
        this.statusLabel.setText("");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem2FocusLost

    private void jMenuItem2MouseEntered(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jMenuItem2MouseEntered
        // TODO add your handling code here:
        this.statusLabel.setText("Exit application");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem2MouseEntered

    private void jMenuItem2MouseExited(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jMenuItem2MouseExited
        // TODO add your handling code here:
        this.statusLabel.setText("");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem2MouseExited

    private void jMenuItem1MouseEntered(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jMenuItem1MouseEntered
        // TODO add your handling code here:
        this.statusLabel.setText("Choose a file to work with");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem1MouseEntered

    private void jMenuItem1MouseExited(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jMenuItem1MouseExited
        // TODO add your handling code here:
        this.statusLabel.setText("");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem1MouseExited

    private void jMenuItem4FocusGained(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_jMenuItem4FocusGained
        // TODO add your handling code here:
        this.statusLabel.setText("Show information about the application");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem4FocusGained

    private void jMenuItem4FocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_jMenuItem4FocusLost
        // TODO add your handling code here:
        this.statusLabel.setText("");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem4FocusLost

    private void jMenuItem4MouseEntered(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jMenuItem4MouseEntered
        // TODO add your handling code here:
        this.statusLabel.setText("Show information about the application");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem4MouseEntered

    private void jMenuItem4MouseExited(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jMenuItem4MouseExited
        // TODO add your handling code here:
        this.statusLabel.setText("");
        this.statusLabel.repaint();
    }//GEN-LAST:event_jMenuItem4MouseExited

    /**
     * @param args the command line arguments
     */

    /*
    считываю из tf'ов данные, запускаю main в Main


     */
    public static void main(String args[]) {
        String[] arr = new String[1];


        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new MainFrame().setVisible(true);
            }
        });
    }

    private void initComponents() {

        jTextField1 = new javax.swing.JTextField();
        jToolBar1 = new javax.swing.JToolBar();
        statusLabel = new javax.swing.JLabel();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        jMenuItem1 = new javax.swing.JMenuItem();
        jMenuItem2 = new javax.swing.JMenuItem();
        jMenu4 = new javax.swing.JMenu();
        jMenuItem4 = new javax.swing.JMenuItem();

        jTextField1.setText("jTextField1");
        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("My Swing GUI");
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosed(java.awt.event.WindowEvent evt) {
                formWindowClosed(evt);
            }
        });

        this.validate(); // обновляем фрейм
        jToolBar1.setRollover(true);
        jToolBar1.add(statusLabel);

        jMenu1.setText("File");

        jMenuItem1.setText("Open");
        jMenuItem1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                jMenuItem1MouseEntered(evt);
            }

            public void mouseExited(java.awt.event.MouseEvent evt) {
                jMenuItem1MouseExited(evt);
            }
        });
        jMenuItem1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem1ActionPerformed(evt);
            }
        });
        jMenuItem1.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusGained(java.awt.event.FocusEvent evt) {
                jMenuItem1FocusGained(evt);
            }

            public void focusLost(java.awt.event.FocusEvent evt) {
                jMenuItem1FocusLost(evt);
            }
        });
        jMenu1.add(jMenuItem1);

        jMenuItem2.setText("Exit");
        jMenuItem2.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                jMenuItem2MouseEntered(evt);
            }

            public void mouseExited(java.awt.event.MouseEvent evt) {
                jMenuItem2MouseExited(evt);
            }
        });
        jMenuItem2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem2ActionPerformed(evt);
            }
        });
        jMenuItem2.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusGained(java.awt.event.FocusEvent evt) {
                jMenuItem2FocusGained(evt);
            }

            public void focusLost(java.awt.event.FocusEvent evt) {
                jMenuItem2FocusLost(evt);
            }
        });
        jMenu1.add(jMenuItem2);

        jMenuBar1.add(jMenu1);

        jMenu4.setText("Help");

        jMenuItem4.setText("About    ?");
        jMenuItem4.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                jMenuItem4MouseEntered(evt);
            }

            public void mouseExited(java.awt.event.MouseEvent evt) {
                jMenuItem4MouseExited(evt);
            }
        });
        jMenuItem4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem4ActionPerformed(evt);
            }
        });
        jMenuItem4.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusGained(java.awt.event.FocusEvent evt) {
                jMenuItem4FocusGained(evt);
            }

            public void focusLost(java.awt.event.FocusEvent evt) {
                jMenuItem4FocusLost(evt);
            }
        });
        jMenu4.add(jMenuItem4);

        jMenuBar1.add(jMenu4);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(jToolBar1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 400, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addContainerGap(249, Short.MAX_VALUE)
                                .addComponent(jToolBar1, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE))
        );

        pack();
        setLocationRelativeTo(null);
    }// </editor-fold>//GEN-END:initComponents


    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu4;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem2;
    private javax.swing.JMenuItem jMenuItem4;
    private javax.swing.JTextField jTextField1;
    private javax.swing.JToolBar jToolBar1;
    private javax.swing.JLabel statusLabel;

}
