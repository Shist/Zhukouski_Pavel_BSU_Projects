/** @author Pavel Zhukouski, 3 course, 12 group
 * @version 2.0
 * Class TrianglePrism */

package by.bsu.zhukouski.model.entity.ClassTriangle.ClassTrianglePrism;

import by.bsu.zhukouski.model.entity.ClassTriangle.Triangle;

public class TrianglePrism extends Triangle {

    /** Height of the prism */
    protected double h;

    /** Getter for height */
    public double get_h()
    {
        return h;
    }

    /** Setter for height */
    public void set_h(double h)
    {
        /** Case when height is null */
        if (h == 0)
            throw new RuntimeException("Error 10: height of prism is null");
        /** Case when first side is negative */
        if (h < 0)
            throw new RuntimeException("Error 11: height of prism is negative");
        this.h = h;
        calculateVolume();
    }

    /** Volume of the prism*/
    private double V;

    /** Getter for volume */
    public double get_V()
    {
        return V;
    }

    /** Main Constructor
     * @param a - First side of triangle at the base
     * @param b - Second side of triangle at the base
     * @param c - Third side of triangle at the base
     * @param h  - Height of the prism*/
    public TrianglePrism(double a, double b, double c, double h)
    {
        set_a(a);
        set_b(b);
        set_c(c);
        set_h(h);
    }

    /** Constructor in case of already existing triangle
     * @param Tr - Triangle that is on the base of prism
     * @param h - Height of prism*/
    public TrianglePrism(Triangle Tr, double h)
    {
        set_a(Tr.get_a());
        set_b(Tr.get_b());
        set_c(Tr.get_c());
        set_h(h);
    }

    /** Default Constructor (in case if we will extend this class in future) */
    protected TrianglePrism()
    {
        a = 0.0;
        b = 0.0;
        c = 0.0;
        max = 0.0;
        avr = 0.0;
        min = 0.0;
        P = 0.0;
        p = 0.0;
        S = 0.0;
        TrType = null;
        h = 0.0;
        V = 0.0;
    }

    /** Calculation of volume */
    private void calculateVolume()
    {
        V = get_a() * get_b() * get_c() * h;
    }

    /** Transforms all the main information about triangle prism into the string */
    @Override
    public String toString()
    {
        /** String with all the information about current triangle prism */
        return "First side of base: a = " + get_a() + "\n" + "Second side of base: b = " + get_b() + "\n" +
                "Third side of base: c = " + get_c() + "\n" + "Type of triangle at base: " + get_TrType() + "\n" +
                "Perimeter of base: P = " + get_P() + "\n" + "Square of base: S = " + get_S() +
                "\n" + "Height: " + h + "\n" + "Volume: V = " + V;
    }
}
