package main.java.model;
/**
 * File: MyImage.java
 * <p>
 * Description:
 * This file contains MyImage class which is used to create BufferedImage objects.
 *
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 * date 17-04-2021
 * <p>

 * <p>
 * The MIT License (MIT)
 * Copyright (c) 2014 Pavel Zhukouski
 * <p>
 */

import java.io.File;
import java.io.IOException;
import java.awt.image.BufferedImage;
import java.awt.image.PixelGrabber;
import java.awt.Graphics2D;
import javax.imageio.ImageIO;

public class MyImage {

    //////////////////////////// VARIABLES /////////////////////////////////////

    /** Store the Image reference */
    private BufferedImage image;

    /** Store the image width and height */
    private int width, height;

    /** Pixels value - ARGB */
    private int pixels[];

    /** Total number of pixel in an image*/
    private int totalPixels;

    /**
     * Image type example: jpg|png 
     * JPG does not support alpha (transparency is lost) while PNG supports alpha.
     */
    private enum ImageType {
        JPG, PNG
    }

    ;

    private ImageType imgType;

    ////////////////////////////////// CONSTRUCTORS ////////////////////////////

    /** Default constructor */
    public MyImage() {
    }

    /**
     * Constructor to create a new image object
     *
     * @param width width of the image passed by the user
     * @param height height of the image passed by the user
     */
    public MyImage(int width, int height) {
        this.width = width;
        this.height = height;
        this.totalPixels = this.width * this.height;
        this.pixels = new int[this.totalPixels];
        image = new BufferedImage(this.width, this.height, BufferedImage.TYPE_INT_ARGB);
        this.imgType = ImageType.PNG;
        initPixelArray();
    }

    /**
     * Constructor to create a copy of a previously created image object.
     *
     * @param img The image object whose copy is created.
     */
    public MyImage(MyImage img) {
        this.width = img.getImageWidth();
        this.height = img.getImageHeight();
        this.totalPixels = this.width * this.height;
        this.pixels = new int[this.totalPixels];

        this.imgType = img.imgType;
        if (this.imgType == ImageType.PNG) {
            this.image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        } else {
            this.image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        }

        //copy original image pixels value to new image and pixels array
        for (int y = 0; y < this.height; y++) {
            for (int x = 0; x < this.width; x++) {
                this.image.setRGB(x, y, img.getPixel(x, y));
                this.pixels[x + y * this.width] = img.getPixel(x, y);
            }
        }
    }

    /////////////////////////////////////// METHODS ////////////////////////////

    /**
     * This method will modify the image object.
     *
     * @param width The width of the new image.
     * @param height The height of the new image.
     * @param bi The new image that will replace the old image.
     */
    public void modifyImageObject(int width, int height, BufferedImage bi) {
        this.width = width;
        this.height = height;
        this.totalPixels = this.width * this.height;
        this.pixels = new int[this.totalPixels];
        if (this.imgType == ImageType.PNG) {
            this.image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        } else {
            this.image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        }
        Graphics2D g2d = this.image.createGraphics();
        g2d.drawImage(bi, 0, 0, null);
        g2d.dispose();
        initPixelArray();
    }

    public void readImage(File f) {
        try {
            image = ImageIO.read(f);
            String fileType = f.getName().substring(f.getName().lastIndexOf('.') + 1);
            if ("jpg".equals(fileType)) {
                imgType = ImageType.JPG;
            } else {
                imgType = ImageType.PNG;
            }
            this.width = image.getWidth();
            this.height = image.getHeight();
            this.totalPixels = this.width * this.height;
            this.pixels = new int[this.totalPixels];
            initPixelArray();
        } catch (IOException e) {
            System.out.println("Error Occurred!\n" + e);
        }
    }

    /**
     * Read the image using the image file path passed
     *
     * @param filePath the path of the image file
     * Example filePath = "D:\\LogoJava.jpg"
     */
    public void readImage(String filePath) {
        readImage(new File(filePath));
    }

    /**
     * Write the content of the BufferedImage object 'image' to a file
     *
     * @param filePath complete file path of the output image file to be created
     * Example filePath = "D:\\Output.jpg"
     */
    public void writeImage(String filePath) {
        try {
            File f = new File(filePath);
            String fileType = filePath.substring(filePath.lastIndexOf('.') + 1);
            ImageIO.write(image, fileType, f);
        } catch (IOException e) {
            System.out.println("Error Occurred!\n" + e);
        }
    }

    /**
     * Initialize the pixel array
     * Image origin is at coordinate (0,0)
     * (0,0)--------> X-axis
     *     |
     *     |
     *     |
     *     v
     *   Y-axis
     *
     * This method will store the value of each pixels of a 2D image in a 1D array.
     */
    private void initPixelArray() {
        PixelGrabber pg = new PixelGrabber(image, 0, 0, width, height, pixels, 0, width);
        try {
            pg.grabPixels();
        } catch (InterruptedException e) {
            System.out.println("Error Occurred: " + e);
        }
    }

    /**
     * This method will check for equality of two images.
     * If we have two image img1 and img2
     * Then calling img1.isEqual(img2) will return TRUE if img1 and img2 are equal
     * else it will return FALSE.
     *
     * @param img The image to check with.
     * @return TRUE if two images are equal else FALSE.
     */
    public boolean isEqual(MyImage img) {
        //check dimension
        if (this.width != img.getImageWidth() || this.height != img.getImageHeight()) {
            return false;
        }

        //check pixel values
        for (int y = 0; y < this.height; y++) {
            for (int x = 0; x < this.width; x++) {
                if (this.pixels[x + y * this.width] != img.getPixel(x, y)) {
                    return false;
                }
            }
        }

        return true;
    }

    /////////////////////////// GET, SET AND UPDATE METHODS ////////////////////

    /**
     * Return the image width
     *
     * @return the width of the image
     */
    public int getImageWidth() {
        return width;
    }

    /**
     * Return the image height
     *
     * @return the height of the image
     */
    public int getImageHeight() {
        return height;
    }

    /**
     * Return total number of pixels in the image
     *
     * @return the total number of pixels
     */
    public int getImageTotalPixels() {
        return totalPixels;
    }

    /**
     * This method will return the amount of alpha value between 0-255 at the pixel (x,y)
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel
     * @return the amount of alpha (transparency)
     *
     * 0 means transparent
     * 255 means opaque
     */
    public int getAlpha(int x, int y) {
        return (pixels[x + (y * width)] >> 24) & 0xFF;
    }

    /**
     * This method will return the amount of red value between 0-255 at the pixel (x,y)
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel
     * @return the amount of red
     *
     * 0 means none
     * 255 means fully red
     */
    public int getRed(int x, int y) {
        return (pixels[x + (y * width)] >> 16) & 0xFF;
    }

    /**
     * This method will return the amount of green value between 0-255 at the pixel (x,y)
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel 
     * @return the amount of green
     *
     * 0 means none
     * 255 means fully green
     */
    public int getGreen(int x, int y) {
        return (pixels[x + (y * width)] >> 8) & 0xFF;
    }

    /**
     * This method will return the amount of blue value between 0-255 at the pixel (x,y)
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel
     * @return the amount of blue
     *
     * 0 means none
     * 255 means fully blue
     */
    public int getBlue(int x, int y) {
        return pixels[x + (y * width)] & 0xFF;
    }

    /**
     * This method will return the pixel value of the pixel at the coordinate (x,y)
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel
     * @return the pixel value in integer [Value can be negative and positive.]
     */
    public int getPixel(int x, int y) {
        return pixels[x + (y * width)];
    }

    /**
     * This method will return the pixel value of the image as 1D array.
     *
     * @return 1D array containing value of each pixels of the image.
     */
    public int[] getPixelArray() {
        return pixels;
    }

    public BufferedImage getImage() {
        return image;
    }

    public String getImgType() {
        return imgType.name().toLowerCase();
    }

    /**
     * This method will set the amount of alpha value between 0-255 at the pixel (x,y)
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel
     * @param alpha the alpha value to set
     *
     * 0 means transparent
     * 255 means opaque
     */
    public void setAlpha(int x, int y, int alpha) {
        pixels[x + (y * width)] = (alpha << 24) | (pixels[x + (y * width)] & 0x00FFFFFF);
        updateImagePixelAt(x, y);
    }

    /**
     * This method will set the amount of red value between 0-255 at the pixel (x,y)
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel
     * @param red the red value to set
     *
     * 0 means none
     * 255 means fully red
     */
    public void setRed(int x, int y, int red) {
        pixels[x + (y * width)] = (red << 16) | (pixels[x + (y * width)] & 0xFF00FFFF);
        updateImagePixelAt(x, y);
    }

    /**
     * This method will set the amount of green value between 0-255 at the pixel (x,y)
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel
     * @param green the green value to set
     *
     * 0 means none
     * 255 means fully green
     */
    public void setGreen(int x, int y, int green) {
        pixels[x + (y * width)] = (green << 8) | (pixels[x + (y * width)] & 0xFFFF00FF);
        updateImagePixelAt(x, y);
    }

    /**
     * This method will set the amount of blue value between 0-255 at the pixel (x,y)
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel
     * @param blue the blue value to set
     *
     * 0 means none
     * 255 means fully blue
     */
    public void setBlue(int x, int y, int blue) {
        pixels[x + (y * width)] = blue | (pixels[x + (y * width)] & 0xFFFFFF00);
        updateImagePixelAt(x, y);
    }

    /**
     * This method will set pixel(x,y) to ARGB value.
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel
     * @param alpha the alpha value to set [value from 0-255]
     * @param red the red value to set [value from 0-255]
     * @param green the green value to set [value from 0-255]
     * @param blue the blue value to set  [value from 0-255]
     */
    public void setPixel(int x, int y, int alpha, int red, int green, int blue) {
        pixels[x + (y * width)] = (alpha << 24) | (red << 16) | (green << 8) | blue;
        updateImagePixelAt(x, y);
    }

    /**
     * This method will set pixel (x,y) to pixelValue.
     *
     * @param x the x coordinate of the pixel
     * @param y the y coordinate of the pixel
     * @param pixelValue the pixel value to set
     */
    public void setPixelToValue(int x, int y, int pixelValue) {
        pixels[x + (y * width)] = pixelValue;
        updateImagePixelAt(x, y);
    }

    /**
     * This method will set the image pixel array to the value of the 1D pixelArray.
     *
     * @param pixelArray 1D array containing values that is set to the image pixel array.77
     */
    public void setPixelArray(int pixelArray[]) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                pixels[x + y * width] = pixelArray[x + y * width];
                updateImagePixelAt(x, y);
            }
        }
    }

    /**
     * This method will update the image pixel at coordinate (x,y)
     *
     * @param x the x coordinate of the pixel that is set
     * @param y the y coordinate of the pixel that is set
     */
    private void updateImagePixelAt(int x, int y) {
        image.setRGB(x, y, pixels[x + (y * width)]);
    }

    //////////////////////////////  HSI color model Methods ////////////////////

    /**
     * This method will return the hue of the pixel (x,y) as per HSI color model.
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @return H The hue value of the pixel [0-360] in degree.
     */
    public double HSI_getHue(int x, int y) {
        int r = getRed(x, y);
        int g = getGreen(x, y);
        int b = getBlue(x, y);

        double H = Math.toDegrees(Math.acos((r - (0.5 * g) - (0.5 * b)) / Math.sqrt((r * r) + (g * g) + (b * b) - (r * g) - (g * b) - (b * r))));
        H = (b > g) ? 360 - H : H;

        return H;
    }

    /**
     * This method will return the saturation of the pixel (x,y) as per HSI color model.
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @return S The saturation of the pixel [0-1].
     */
    public double HSI_getSaturation(int x, int y) {
        int r = getRed(x, y);
        int g = getGreen(x, y);
        int b = getBlue(x, y);
        double I = (r + g + b) / 3;

        int m = Math.min(Math.min(r, g), b);
        double S = (I > 0) ? 1 - m / I : 0;

        return S;
    }

    /**
     * This method will return the intensity of the pixel (x,y) as per HSI color model.
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @return I The intensity of the pixel [0-255].
     */
    public double HSI_getIntensity(int x, int y) {
        int r = getRed(x, y);
        int g = getGreen(x, y);
        int b = getBlue(x, y);
        double I = (r + g + b) / 3;

        return I;
    }

    /**
     * This method will set the hue value of the pixel (x,y).
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @param hue The hue value that is set [0-360] in degree.
     */
    public void HSI_setHue(int x, int y, double hue) {
        int rgb[] = HSI_getRGBFromHSI(hue, HSI_getSaturation(x, y), HSI_getIntensity(x, y));
        setPixel(x, y, getAlpha(x, y), rgb[0], rgb[1], rgb[2]);
    }

    /**
     * This method will set the saturation value of the pixel (x,y).
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @param saturation The saturation value that is set [0-1].
     */
    public void HSI_setSaturation(int x, int y, double saturation) {
        int rgb[] = HSI_getRGBFromHSI(HSI_getHue(x, y), saturation, HSI_getIntensity(x, y));
        setPixel(x, y, getAlpha(x, y), rgb[0], rgb[1], rgb[2]);
    }

    /**
     * This method will set the intensity value of the pixel (x,y).
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @param intensity The intensity value that is set [0-255].
     */
    public void HSI_setIntensity(int x, int y, double intensity) {
        int rgb[] = HSI_getRGBFromHSI(HSI_getHue(x, y), HSI_getSaturation(x, y), intensity);
        setPixel(x, y, getAlpha(x, y), rgb[0], rgb[1], rgb[2]);
    }

    /**
     * This method will return the RGB value from HSI value.
     *
     * @param H Hue value.
     * @param S Saturation value.
     * @param I Intensity value.
     * @return The rgb value for the corresponding HSI value.
     */
    private int[] HSI_getRGBFromHSI(double H, double S, double I) {
        int rgb[] = new int[3];
        int r = 0, g = 0, b = 0;

        if (H == 0) {
            r = (int) Math.round(I + 2 * I * S);
            g = (int) Math.round(I - I * S);
            b = (int) Math.round(I - I * S);
        } else if (H < 120) {
            r = (int) Math.round(I + I * S * (Math.cos(Math.toRadians(H)) / Math.cos(Math.toRadians(60 - H))));
            g = (int) Math.round(I + I * S * (1 - Math.cos(Math.toRadians(H)) / Math.cos(Math.toRadians(60 - H))));
            b = (int) Math.round(I - I * S);
        } else if (H == 120) {
            r = (int) Math.round(I - I * S);
            g = (int) Math.round(I + 2 * I * S);
            b = (int) Math.round(I - I * S);
        } else if (H < 240) {
            r = (int) Math.round(I - I * S);
            g = (int) Math.round(I + I * S * (Math.cos(Math.toRadians(H - 120)) / Math.cos(Math.toRadians(180 - H))));
            b = (int) Math.round(I + I * S * (1 - (Math.cos(Math.toRadians(H - 120)) / Math.cos(Math.toRadians(180 - H)))));
        } else if (H == 240) {
            r = (int) Math.round(I - I * S);
            g = (int) Math.round(I - I * S);
            b = (int) Math.round(I + 2 * I * S);
        } else if (H < 360) {
            r = (int) Math.round(I + I * S * (1 - Math.cos(Math.toRadians(H - 240)) / Math.cos(Math.toRadians(300 - H))));
            g = (int) Math.round(I - I * S);
            b = (int) Math.round(I + I * S * (Math.cos(Math.toRadians(H - 240)) / Math.cos(Math.toRadians(300 - H))));
        }

        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;

        return rgb;
    }

    ////////////////////////////// HSV color model Methods /////////////////////

    /**
     * This method will return the hue of the pixel (x,y) as per HSV color model.
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @return H The hue value of the pixel [0-360] in degree.
     */
    public double HSV_getHue(int x, int y) {
        int r = getRed(x, y);
        int g = getGreen(x, y);
        int b = getBlue(x, y);

        double H = Math.toDegrees(Math.acos((r - (0.5 * g) - (0.5 * b)) / Math.sqrt((r * r) + (g * g) + (b * b) - (r * g) - (g * b) - (b * r))));
        H = (b > g) ? 360 - H : H;

        return H;
    }

    /**
     * This method will return the saturation of the pixel (x,y) as per HSV color model.
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @return S The saturation of the pixel [0-1].
     */
    public double HSV_getSaturation(int x, int y) {
        int r = getRed(x, y);
        int g = getGreen(x, y);
        int b = getBlue(x, y);

        int max = Math.max(Math.max(r, g), b);
        int min = Math.min(Math.min(r, g), b);

        double S = (max > 0) ? (1 - (double) min / max) : 0;

        return S;
    }

    /**
     * This method will return the value of the pixel (x,y) as per HSV color model.
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @return V The value of the pixel [0-1].
     */
    public double HSV_getValue(int x, int y) {
        int r = getRed(x, y);
        int g = getGreen(x, y);
        int b = getBlue(x, y);

        int max = Math.max(Math.max(r, g), b);
        double V = max / 255.0;

        return V;
    }

    /**
     * This method will set the hue of the pixel (x,y).
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @param hue The hue value that is set [0-360] in degree.
     */
    public void HSV_setHue(int x, int y, double hue) {
        int rgb[] = HSV_getRGBFromHSV(hue, HSV_getSaturation(x, y), HSV_getValue(x, y));
        setPixel(x, y, getAlpha(x, y), rgb[0], rgb[1], rgb[2]);
    }

    /**
     * This method will set the saturation of the pixel (x,y).
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @param saturation The saturation value that is set [0-1].
     */
    public void HSV_setSaturation(int x, int y, double saturation) {
        int rgb[] = HSV_getRGBFromHSV(HSV_getHue(x, y), saturation, HSV_getValue(x, y));
        setPixel(x, y, getAlpha(x, y), rgb[0], rgb[1], rgb[2]);
    }

    /**
     * This method will set the value of the pixel (x,y).
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @param value The value that is set [0-1].
     */
    public void HSV_setValue(int x, int y, double value) {
        int rgb[] = HSV_getRGBFromHSV(HSV_getHue(x, y), HSV_getSaturation(x, y), value);
        setPixel(x, y, getAlpha(x, y), rgb[0], rgb[1], rgb[2]);
    }

    /**
     * This method will return the RGB value from HSV value.
     *
     * @param H Hue of the pixel.
     * @param S Saturation of the pixel.
     * @param V Value of the pixel.
     * @return The rgb value for the corresponding HSV value.
     */
    private int[] HSV_getRGBFromHSV(double H, double S, double V) {
        int rgb[] = new int[3];
        int r = 0, g = 0, b = 0;

        double max = 255.0 * V;
        double min = max * (1 - S);
        double tmp = (max - min) * (1 - Math.abs((H / 60) % 2 - 1));

        H %= 360;

        if (H < 60) {
            r = (int) Math.round(max);
            g = (int) Math.round(tmp + min);
            b = (int) Math.round(min);
        } else if (H < 120) {
            r = (int) Math.round(tmp + min);
            g = (int) Math.round(max);
            b = (int) Math.round(min);
        } else if (H < 180) {
            r = (int) Math.round(min);
            g = (int) Math.round(max);
            b = (int) Math.round(tmp + min);
        } else if (H < 240) {
            r = (int) Math.round(min);
            g = (int) Math.round(tmp + min);
            b = (int) Math.round(max);
        } else if (H < 300) {
            r = (int) Math.round(tmp + min);
            g = (int) Math.round(min);
            b = (int) Math.round(max);
        } else if (H < 360) {
            r = (int) Math.round(max);
            g = (int) Math.round(min);
            b = (int) Math.round(tmp + min);
        }

        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;

        return rgb;
    }

    ////////////////////////////// HSL color model Methods /////////////////////

    /**
     * This method will return the hue of the pixel (x,y) as per HSL color model.
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @return H The hue value of the pixel [0-360] in degree.
     */
    public double HSL_getHue(int x, int y) {
        int r = getRed(x, y);
        int g = getGreen(x, y);
        int b = getBlue(x, y);

        double H = Math.toDegrees(Math.acos((r - (0.5 * g) - (0.5 * b)) / Math.sqrt((r * r) + (g * g) + (b * b) - (r * g) - (g * b) - (b * r))));
        H = (b > g) ? 360 - H : H;

        return H;
    }

    /**
     * This method will return the saturation of the pixel (x,y) as per HSL color model.
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @return S The saturation of the pixel [0-1].
     */
    public double HSL_getSaturation(int x, int y) {
        int r = getRed(x, y);
        int g = getGreen(x, y);
        int b = getBlue(x, y);

        int max = Math.max(Math.max(r, g), b);
        int min = Math.min(Math.min(r, g), b);
        double tmp = (max - min) / 255.0;
        double L = (max + min) / 510.0;

        double S = (L > 0) ? tmp / (1.0 - Math.abs(2 * L - 1.0)) : 0;

        return S;
    }

    /**
     * This method will return the lightness of the pixel (x,y) as per HSL color model.
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @return L The lightness of the pixel [0-1].
     */
    public double HSL_getLightness(int x, int y) {
        int r = getRed(x, y);
        int g = getGreen(x, y);
        int b = getBlue(x, y);

        int max = Math.max(Math.max(r, g), b);
        int min = Math.min(Math.min(r, g), b);
        double L = (max + min) / 510.0;

        return L;
    }

    /**
     * This method will set the hue of the pixel (x,y).
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @param hue The hue value that is set [0-360] in degree.
     */
    public void HSL_setHue(int x, int y, double hue) {
        int rgb[] = HSL_getRGBFromHSL(hue, HSL_getSaturation(x, y), HSL_getLightness(x, y));
        setPixel(x, y, getAlpha(x, y), rgb[0], rgb[1], rgb[2]);
    }

    /**
     * This method will set the saturation of the pixel (x,y).
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @param saturation The saturation value that is set [0-1].
     */
    public void HSL_setSaturation(int x, int y, double saturation) {
        int rgb[] = HSL_getRGBFromHSL(HSL_getHue(x, y), saturation, HSL_getLightness(x, y));
        setPixel(x, y, getAlpha(x, y), rgb[0], rgb[1], rgb[2]);
    }

    /**
     * This method will set the lightness of the pixel (x,y).
     *
     * @param x The x coordinate of the pixel.
     * @param y The y coordinate of the pixel.
     * @param lightness The lightness value that is set [0-1].
     */
    public void HSL_setLightness(int x, int y, double lightness) {
        int rgb[] = HSL_getRGBFromHSL(HSL_getHue(x, y), HSL_getSaturation(x, y), lightness);
        setPixel(x, y, getAlpha(x, y), rgb[0], rgb[1], rgb[2]);
    }

    /**
     * This method will return the RGB value from HSL value.
     *
     * @param H Hue of the pixel.
     * @param S Saturation of the pixel.
     * @param L Lightness of the pixel.
     * @return The rgb value for the corresponding HSL value.
     */
    private int[] HSL_getRGBFromHSL(double H, double S, double L) {
        int rgb[] = new int[3];
        int r = 0, g = 0, b = 0;

        double tmp = S * (1.0 - Math.abs(2 * L - 1.0));
        double min = 255.0 * (L - 0.5 * tmp);
        double tmp2 = tmp * (1.0 - Math.abs((H / 60) % 2 - 1));

        H %= 360;

        if (H < 60) {
            r = (int) Math.round(255 * tmp + min);
            g = (int) Math.round(255 * tmp2 + min);
            b = (int) Math.round(min);
        } else if (H < 120) {
            r = (int) Math.round(255 * tmp2 + min);
            g = (int) Math.round(255 * tmp + min);
            b = (int) Math.round(min);
        } else if (H < 180) {
            r = (int) Math.round(min);
            g = (int) Math.round(255 * tmp + min);
            b = (int) Math.round(255 * tmp2 + min);
        } else if (H < 240) {
            r = (int) Math.round(min);
            g = (int) Math.round(255 * tmp2 + min);
            b = (int) Math.round(255 * tmp + min);
        } else if (H < 300) {
            r = (int) Math.round(255 * tmp2 + min);
            g = (int) Math.round(min);
            b = (int) Math.round(255 * tmp + min);
        } else if (H < 360) {
            r = (int) Math.round(255 * tmp + min);
            g = (int) Math.round(min);
            b = (int) Math.round(255 * tmp2 + min);
        }

        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;

        return rgb;
    }
}//class ImageFX ends here