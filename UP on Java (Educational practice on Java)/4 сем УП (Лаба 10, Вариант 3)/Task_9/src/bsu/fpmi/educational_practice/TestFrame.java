/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bsu.fpmi.educational_practice;

import java.awt.Label;

/**
 *
 * @author User
 */
public class TestFrame extends javax.swing.JFrame
{

    /**
     * Creates new form TestFrame
     */
    public TestFrame()
    {
        super("Lab 10, Var 3");
        initComponents();

        taskPanel2.addAnswerListener(new Listener(label2));
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents()
    {

        taskPanel2 = new bsu.fpmi.educational_practice.TaskPanel();
        label2 = new java.awt.Label();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        label2.setText("Result:");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(123, 123, 123)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(label2, javax.swing.GroupLayout.PREFERRED_SIZE, 151, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(taskPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(87, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGap(32, 32, 32)
                .addComponent(label2, javax.swing.GroupLayout.PREFERRED_SIZE, 47, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(41, 41, 41)
                .addComponent(taskPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(86, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private java.awt.Label label2;
    private bsu.fpmi.educational_practice.TaskPanel taskPanel2;
    // End of variables declaration//GEN-END:variables

}

class Listener implements AnswerListener
{
    Label label;

    public Listener(Label label)
    {
        this.label = label;
    }

    @Override
    public void buttonPressed(int info)
    {
        if (info == AnswerEvent.NONE)
        {
            label.setText("Result: None button checked");
        }
        else if (info == AnswerEvent.BOTH)
        {
            label.setText("Result: Both buttons poked");
        }
        else if (info == AnswerEvent.FIRST)
        {
            label.setText("Result: First button poked");
        }
        else if (info == AnswerEvent.SECOND)
        {
            label.setText("Result: Second button poked");
        }
        else 
        {
            label.setText("ERROR");
        }
    }
}
