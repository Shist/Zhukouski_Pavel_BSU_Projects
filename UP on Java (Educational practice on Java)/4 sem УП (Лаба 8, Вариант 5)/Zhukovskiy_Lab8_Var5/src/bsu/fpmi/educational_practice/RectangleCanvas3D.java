/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bsu.fpmi.educational_practice;

import java.awt.Canvas;
import java.awt.Graphics;

/**
 *
 * @author Asus
 */
public class RectangleCanvas3D extends Canvas {
    
    private int width, height, X = 5, Y = 5;
    private boolean raised = false;
    
    public RectangleCanvas3D(int width, int height) {
        this.width = width;
        this.height = height;
    }
    
    public void setUpRaised(boolean raised) {
        this.raised = raised;
    }
    
    public void setUpCoordinates(int newX, int newY) {
        this.X = newX;
        this.Y = newY;
    }
    
    @Override
    public void paint(Graphics g) {
        g.draw3DRect(this.X, this.Y, this.width, this.height, raised);
    }
}
