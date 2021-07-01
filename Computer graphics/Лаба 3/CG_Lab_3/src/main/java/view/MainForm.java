package main.java.view;

import main.java.controller.Threshold;
import main.java.model.MyImage;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class MainForm {

    private JPanel pMain;
    private JButton bChooseImage;
    private JButton bAdaptive;
    private JButton bAutoGlobal;
    private JButton bAutoGlobalRed;
    private JButton bSaveCurrentImage;
    private JPanel pImage;
    private JLabel lImage;
    private JButton bAutoGlobalGreen;
    private JButton bAutoGlobalBlue;

    MyImage myImage = null;
    MyImage myImageThresholded = null;

    MainForm() {

        ActionListener AL = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                JFileChooser jFileChooser = new JFileChooser();
                jFileChooser.setFileFilter(new FileNameExtensionFilter("Image Files", "jpg", "png"));
                int result = jFileChooser.showOpenDialog(null);
                if (result == JFileChooser.APPROVE_OPTION) {
                    File file = jFileChooser.getSelectedFile();
                    myImage = new MyImage();
                    myImage.readImage(file);
                    lImage.setIcon(new ImageIcon(myImage.getImage().getScaledInstance(pImage.getWidth(), pImage.getHeight(), Image.SCALE_SMOOTH)));

                    pMain.revalidate();
                    pMain.repaint();
                }
            }
        };

        bChooseImage.addActionListener(AL);

        bSaveCurrentImage.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (myImage != null) {
                    JFileChooser jFileChooser = new JFileChooser();
                    jFileChooser.setFileFilter(new FileNameExtensionFilter("Image Files", "jpg", "png"));
                    if (jFileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
                        File file = jFileChooser.getSelectedFile();
                        try {
                            ImageIO.write(myImageThresholded.getImage(), myImageThresholded.getImgType(), new File(file.getAbsolutePath().endsWith(myImageThresholded.getImgType())
                                    ? file.getAbsolutePath() : file.getAbsolutePath() + "." + myImageThresholded.getImgType()));
                        } catch (IOException ex) {
                            jFileChooser.showSaveDialog(null);
                        }
                    } else {
                        System.out.println("No file choosen!");
                    }
                } else {
                    JOptionPane.showMessageDialog(null, "Choose image to threshold", "Image is not chosen", JOptionPane.WARNING_MESSAGE);
                }
            }
        });

        bAdaptive.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (myImage != null) {
                    myImageThresholded = new MyImage(myImage);
                    Threshold.adaptiveThreshold_Mean(myImageThresholded, 3, 3);
                    lImage.setIcon(new ImageIcon(myImageThresholded.getImage().getScaledInstance(pImage.getWidth(), pImage.getHeight(), Image.SCALE_SMOOTH)));
                    pMain.revalidate();
                    pMain.repaint();
                } else {
                    JOptionPane.showMessageDialog(null, "Choose image to threshold", "Image is not chosen", JOptionPane.WARNING_MESSAGE);
                }
            }
        });

        bAutoGlobal.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (myImage != null) {
                    myImageThresholded = new MyImage(myImage);
                    Threshold.autoThreshold(myImageThresholded);
                    lImage.setIcon(new ImageIcon(myImageThresholded.getImage().getScaledInstance(pImage.getWidth(), pImage.getHeight(), Image.SCALE_SMOOTH)));
                    pMain.revalidate();
                    pMain.repaint();
                } else {
                    JOptionPane.showMessageDialog(null, "Choose image to threshold", "Image is not chosen", JOptionPane.WARNING_MESSAGE);
                }
            }
        });

        bAutoGlobalRed.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (myImage != null) {
                    myImageThresholded = new MyImage(myImage);
                    Threshold.autoThreshold_usingRedValueOfPixels(myImageThresholded);
                    lImage.setIcon(new ImageIcon(myImageThresholded.getImage().getScaledInstance(pImage.getWidth(), pImage.getHeight(), Image.SCALE_SMOOTH)));
                    pMain.revalidate();
                    pMain.repaint();
                } else {
                    JOptionPane.showMessageDialog(null, "Choose image to threshold", "Image is not chosen", JOptionPane.WARNING_MESSAGE);
                }
            }
        });

        bAutoGlobalBlue.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (myImage != null) {
                    myImageThresholded = new MyImage(myImage);
                    Threshold.autoThreshold_usingBlueValueOfPixels(myImageThresholded);
                    lImage.setIcon(new ImageIcon(myImageThresholded.getImage().getScaledInstance(pImage.getWidth(), pImage.getHeight(), Image.SCALE_SMOOTH)));
                    pMain.revalidate();
                    pMain.repaint();
                } else {
                    JOptionPane.showMessageDialog(null, "Choose image to threshold", "Image is not chosen", JOptionPane.WARNING_MESSAGE);
                }
            }
        });

        bAutoGlobalGreen.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (myImage != null) {
                    myImageThresholded = new MyImage(myImage);
                    Threshold.autoThreshold_usingGreenValueOfPixels(myImageThresholded);
                    lImage.setIcon(new ImageIcon(myImageThresholded.getImage().getScaledInstance(pImage.getWidth(), pImage.getHeight(), Image.SCALE_SMOOTH)));
                    pMain.revalidate();
                    pMain.repaint();
                } else {
                    JOptionPane.showMessageDialog(null, "Choose image to threshold", "Image is not chosen", JOptionPane.WARNING_MESSAGE);
                }
            }
        });
    }

    public static void main(String[] args) {
        JFrame jFrame = new JFrame("MainForm");
        jFrame.setContentPane(new MainForm().pMain);
        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jFrame.pack();
        jFrame.setMinimumSize(new Dimension(900, 700));
        jFrame.setVisible(true);
    }
}
