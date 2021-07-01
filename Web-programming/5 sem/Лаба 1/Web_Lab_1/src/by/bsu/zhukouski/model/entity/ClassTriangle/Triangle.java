/** @author Pavel Zhukouski, 3 course, 12 group
 * @version 2.0
 * Class Triangle */

package by.bsu.zhukouski.model.entity.ClassTriangle;

import by.bsu.zhukouski.enums.EnumTriangleType.Type;
import by.bsu.zhukouski.enums.EnumPorS.PorS;

public class Triangle {

    /** First side */
    protected double a;

    /** Getter for side a */
    public double get_a()
    {
        return a;
    }

    /** Setter for side a */
    public void set_a(double a)
    {
        /** Case when first side is null */
        if (a == 0)
            throw new RuntimeException("Error 1: First side is null");
        /** Case when first side is negative */
        if (a < 0)
            throw new RuntimeException("Error 2: First side is negative");
        /** Case when triangle doesn't exist */
        if (b != 0 && c != 0 && b + c <= a)
            throw new RuntimeException("Error 3: Triangle with entered first side does not exist");
        this.a = a;
        calculateType();
        calculatePerimeter();
        calculateSquare();
    }

    /** Second side */
    protected double b;

    /** Getter for side b */
    public double get_b()
    {
        return b;
    }

    /** Setter for side b */
    public void set_b(double b)
    {
        /** Case when second side is null */
        if (b == 0)
            throw new RuntimeException("Error 4: Second side is null");
        /** Case when first side is negative */
        if (b < 0)
            throw new RuntimeException("Error 5: Second side is negative");
        /** Case when triangle doesn't exist */
        if (a != 0 && c != 0 && a + c <= b)
            throw new RuntimeException("Error 6: Triangle with entered second side does not exist");
        this.b = b;
        calculateType();
        calculatePerimeter();
        calculateSquare();
    }

    /** Third side */
    protected double c;

    /** Getter for side c */
    public double get_c()
    {
        return c;
    }

    /** Setter for side c */
    public void set_c(double c)
    {
        /** Case when third side is null */
        if (c == 0)
            throw new RuntimeException("Error 7: Third side is null");
        /** Case when third side is negative */
        if (c < 0)
            throw new RuntimeException("Error 8: Third side is negative");
        /** Case when triangle doesn't exist */
        if (a != 0 && b != 0 && a + b <= c)
            throw new RuntimeException("Error 9: Triangle with entered third side does not exist");
        this.c = c;
        calculateType();
        calculatePerimeter();
        calculateSquare();
    }

    /** Maximum side */
    protected double max;

    /** Getter for maximum side */
    public double get_max()
    {
        return max;
    }

    /** Average side */
    protected double avr;

    /** Getter for average side */
    public double get_avr()
    {
        return avr;
    }

    /** Minimal side */
    protected double min;

    /** Getter for minimal side */
    public double get_min()
    {
        return min;
    }

    /** Perimeter */
    protected double P;

    /** Getter for perimeter */
    public double get_P()
    {
        return P;
    }

    /** Semi-Perimeter */
    protected double p;

    /** Getter for semi-perimeter */
    public double get_p()
    {
        return p;
    }

    /** Square */
    protected double S;

    /** Getter for square */
    public double get_S()
    {
        return S;
    }

    /** Triangle type */
    protected Type TrType;

    /** Getter for triangle type */
    public Type get_TrType()
    {
        return TrType;
    }

    /** Constructor
     * @param a - First side of triangle
     * @param b - Second side of triangle
     * @param c - Third side of triangle */
    public Triangle(double a, double b, double c)
    {
        set_a(a);
        set_b(b);
        set_c(c);
    }

    /** Default Constructor */
    protected Triangle()
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
    }

    /** Method for calculating the type of triangle */
    private void calculateType()
    {
        /** Calculation of side ratios */
        /** If side a - the biggest */
        if (a > b && a > c)
        {
            max = a;
            if (b > c)
            {
                avr = b;
                min = c;
            }
            /** If b < c */
            else
            {
                avr = c;
                min = b;
            }
        }
        /** If side a - the smallest */
        else if (a < b && a < c)
        {
            min = a;
            if (b > c)
            {
                max = b;
                avr = c;
            }
            /** If b < c */
            else
            {
                max = c;
                avr = b;
            }
        }
        /** If side a - average */
        else
        {
            avr = a;
            if (b > c)
            {
                max = b;
                min = c;
            }
            /** If b < c */
            else
            {
                max = c;
                min = b;
            }
        }
        /** Calculation of triangle type */
        if (a == b && a == c && b == c)
            TrType = Type.equilateral;
        else if (a == b || a == c || b == c)
            TrType = Type.isosceles;
        else if (max*max == avr*avr + min*min)
            TrType = Type.rectangular;
        else
            TrType = Type.arbitrary;
    }

    /** Method that calculates triangle perimeter */
    private void calculatePerimeter()
    {
        /** Calculation of triangle perimeter */
        P = a + b + c;
    }

    /** Method that calculates triangle semi-perimeter and square */
    private void calculateSquare()
    {
        /** Calculation of triangle semi-perimeter */
        p = P / 2;

        /** Calculation of triangle square */
        S = Math.sqrt(p*(p-a)*(p-b)*(p-c));
    }

    /** Transforms all the main information about triangle into the string */
    public String toString()
    {
        /** String with all the information about current triangle */
        return "First side: a = " + a + "\n" + "Second side: b = " + b + "\n" + "Third side: c = " + c +
                "\n" + "Type: " + TrType + "\n" + "Perimeter: P = " + P + "\n" + "Square: S = " + S;
    }

    /** Prints all the information about current triangle on console */
    public void consoleOutput()
    {
        System.out.println(toString() + "\n");
    }

    /** Function OutputTrInfo prints info about entered type of triangles in array TrArr on perimeter or square
     * @param TrArr - Array we all triangles
     * @param TrType - Type of triangles, we're interested in
     * @param p - parameter we needed: Perimeter or Square */
    public static void OutputTrInfo(Triangle[] TrArr, Type TrType, PorS p)
    {
        /** Amount of TrType triangles */
        int Trs = 0;
        /** Maximum parameter (P or S) among the TrType triangles */
        double MaxParam = 0.0;
        /** Minimal parameter (P or S) among the TrType triangles */
        double MinParam = Double.MAX_VALUE;
        /** If we need to calculate among perimeter */
        if (p == PorS.P)
        {
            for (Triangle tr : TrArr)
            {
                if (tr.get_TrType() == TrType)
                {
                    Trs++;
                    if (tr.get_P() > MaxParam)
                        MaxParam = tr.get_P();
                    if (tr.get_P() < MinParam)
                        MinParam = tr.get_P();
                }
            }
            System.out.println("There are " + Trs + " " + TrType + " triangles");
            System.out.println("The maximal perimeter among them is " + MaxParam);
            System.out.println("The minimal perimeter among them is " + MinParam);
        }
        /** If we need to calculate among square */
        else
        {
            for (Triangle tr : TrArr)
            {
                if (tr.get_TrType() == TrType)
                {
                    Trs++;
                    if (tr.get_S() > MaxParam)
                        MaxParam = tr.get_S();
                    if (tr.get_S() < MinParam)
                        MinParam = tr.get_S();
                }
            }
            System.out.println("There are " + Trs + " " + TrType + " triangles");
            System.out.println("The maximal square among them is " + MaxParam);
            System.out.println("The minimal square among them is " + MinParam);
        }
        System.out.println();
    }
}
