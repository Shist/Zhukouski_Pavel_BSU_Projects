/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.awt.Canvas;
import java.awt.Graphics;

/**
 *
 * @author Pavel Zhukosvkiy
 */
public class RectangleCanvas3D extends Canvas {
    
    private final int width, height, depth;
    private int X = 100, Y = 100;
    private boolean raised = true;
    
    public RectangleCanvas3D(int width, int height, int depth) {
        this.width = width;
        this.height = height;
        this.depth = depth;
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
        assert g != null;
        g.draw3DRect(this.X, this.Y, this.width, this.height, raised);
    }
}
