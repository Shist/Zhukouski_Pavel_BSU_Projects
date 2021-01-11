/** @author Pavel Zhukouski, 3 course, 12 group
 * @version 2.0
 * Main */

/**
 Changes from the previous version:
 1) All fields in the Triangle class are protected, getters are made for all, and setters for the sides of the triangle
 2) Now all exception checks are done in setters, which is more convenient and faster
 2) Now for calculating the perimeter / area of triangles of the selected type, a separate function has been made in
 the Triangle class under named OutputTrInfo. Its creation has significantly reduced the code and made it possible to
 use the function multiple times. The selected parameters (according to the selected type of triangle and the selected
 characteristic (perimeter or area)).
 3) The names of all methods are made with a small letter
 4) Corrected packages tree
*/

package by.bsu.zhukouski.view;

import by.bsu.zhukouski.enums.EnumTriangleType.Type;
import by.bsu.zhukouski.enums.EnumPorS.PorS;
import by.bsu.zhukouski.model.entity.ClassTriangle.Triangle;
import by.bsu.zhukouski.model.entity.ClassTriangle.ClassTrianglePrism.TrianglePrism;
import by.bsu.zhukouski.model.entity.ClassTriangle.ClassTrianglePyramid.TrianglePyramid;

/** The main class */
public class Main {

    public static void main(String[] args) {
        /** Dimension */
        int N = 10;
        /** Creating an array of 10 objects of class Tryangle*/
        Triangle[] Trngls = new Triangle[N];

        Trngls[0] = new Triangle(5.0, 5.0, 5.0);
        Trngls[1] = new Triangle(7.0, 7.0, 7.0);
        Trngls[2] = new Triangle(13.5, 13.5, 13.5);
        Trngls[3] = new Triangle(8.0, 8.0, 4.5);
        Trngls[4] = new Triangle(9.0, 12.0, 12.0);
        Trngls[5] = new Triangle(4.3, 6.1, 6.1);
        Trngls[6] = new Triangle(3.0, 4.0, 5.0);
        Trngls[7] = new Triangle(4.3, 2.7, 3.3);
        Trngls[8] = new Triangle(10.4, 8.0, 9.1);
        Trngls[9] = new Triangle(7.0, 6.0, 4.0);

        /** Output basic information about triangles */
        for (int i = 0; i < N; i++) {
            System.out.println("Triangle number " + (i + 1) + ":");
            Trngls[i].consoleOutput();
        }

        /** Output of the additional information about triangles */
        Triangle.OutputTrInfo(Trngls, Type.equilateral, PorS.P);
        Triangle.OutputTrInfo(Trngls, Type.equilateral, PorS.S);
        Triangle.OutputTrInfo(Trngls, Type.isosceles, PorS.P);
        Triangle.OutputTrInfo(Trngls, Type.isosceles, PorS.S);
        Triangle.OutputTrInfo(Trngls, Type.rectangular, PorS.P);
        Triangle.OutputTrInfo(Trngls, Type.rectangular, PorS.S);
        Triangle.OutputTrInfo(Trngls, Type.arbitrary, PorS.P);
        Triangle.OutputTrInfo(Trngls, Type.arbitrary, PorS.S);

        /** Way of creating triangle prism with 3 sides and height */
        TrianglePrism TrPr1 = new TrianglePrism(3.0, 4.0, 5.0, 3.0);
        /** Way of creating triangle prism with 1 triangle and height */
        TrianglePrism TrPr2 = new TrianglePrism(Trngls[0], 3.0);

        /** Output information about first prism */
        System.out.println("First Triangle Prism:");
        TrPr1.consoleOutput();
        /** Output information about second prism */
        System.out.println("Second Triangle Prism:");
        TrPr2.consoleOutput();

        /** Way of creating triangle pyramid with 3 sides and height */
        TrianglePyramid TrPyr1 = new TrianglePyramid(3.0, 4.0, 5.0, 3.0);
        /** Way of creating triangle pyramid with 1 triangle and height */
        TrianglePyramid TrPyr2 = new TrianglePyramid(Trngls[0], 3.0);

        /** Output information about first pyramid */
        System.out.println("First Triangle Pyramid:");
        TrPyr1.consoleOutput();
        /** Output information about second pyramid */
        System.out.println("Second Triangle Pyramid:");
        TrPyr2.consoleOutput();
    }
}
