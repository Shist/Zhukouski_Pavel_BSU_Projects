// Вариант 23.
// Есть фраза, переданная через параметры апплета. Сделать так, чтобы она собиралась в центре апплета по буквам, которые двигаются из 4 углов по очереди
import java.applet.Applet;
import java.awt.*;
import java.util.ArrayList;

public class Main extends Applet
{
    private static final long serialVersionUID = 1L;
    private boolean animationDone = false;


    String str;
    int xPointForStart;
    int yPointForStart;
    ArrayList<Letter> letters;

    int windowWidth = this.getWidth();
    int windowHeight = this.getHeight();

    int ctr = 0;
    int speed = 1;

    public void init() {
        str = getParameter("text");

        windowWidth = this.getWidth();
        windowHeight = this.getHeight();

        letters = new ArrayList<>();

        xPointForStart = (int) str.length() * 5;
        yPointForStart = (int) (windowHeight * 0.5 - 10);

        int checker = 1;
        for (int i = 0; i < str.length(); i++) {
            if (checker == 1) {
                letters.add(new Letter(str.charAt(i), 10, 10, checker));
                checker = 2;
                continue;
            }
            if (checker == 2) {
                letters.add(new Letter(str.charAt(i), 10, this.getHeight() - 5, checker));
                checker = 3;
                continue;
            }
            if (checker == 3) {
                letters.add(new Letter(str.charAt(i), this.getWidth() - 10, this.getHeight() - 10, checker));
                checker = 4;
                continue;
            }
            if (checker == 4) {
                letters.add(new Letter(str.charAt(i), this.getWidth() - 10, 10, checker));
                checker = 1;
                continue;
            }
        }


        new Thread(() -> {
            while (!animationDone) {
                updateAnimation();
                repaint();
                delayAnimation();
            }
        }).start();
    }

    public void delayAnimation() {
        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void updateAnimation() {
        if (ctr < letters.size()) {
            if (letters.get(ctr).checker == 1 && letters.get(ctr).y != yPointForStart) {
                letters.get(ctr).x += speed;
                letters.get(ctr).y += 1;

                if (ctr != 0 && letters.get(ctr).y == yPointForStart) {

                    if (letters.get(ctr).x - letters.get(ctr - 1).x <= 0) {
                        while (letters.get(ctr).x - letters.get(ctr - 1).x != 8) {
                            letters.get(ctr).x += speed;
                        }
                    } else if (letters.get(ctr).x - letters.get(ctr - 1).x >= 0) {
                        while (letters.get(ctr).x - letters.get(ctr - 1).x != 8) {
                            letters.get(ctr).x -= speed;
                        }
                    }

                }
            } else if (letters.get(ctr).checker == 2 && letters.get(ctr).y != yPointForStart) {
                letters.get(ctr).x += speed;
                letters.get(ctr).y -= 1;

                if (ctr != 0 && letters.get(ctr).y == yPointForStart) {
                    if (letters.get(ctr).x - letters.get(ctr - 1).x <= 0) {
                        while (letters.get(ctr).x - letters.get(ctr - 1).x != 8) {
                            letters.get(ctr).x += speed;
                        }
                    } else if (letters.get(ctr).x - letters.get(ctr - 1).x >= 0) {
                        while (letters.get(ctr).x - letters.get(ctr - 1).x != 8) {
                            letters.get(ctr).x -= speed;
                        }
                    }
                }
            } else if (letters.get(ctr).checker == 3 && letters.get(ctr).y != yPointForStart) {
                letters.get(ctr).x -= speed;
                letters.get(ctr).y -= 1;

                if (ctr != 0 && letters.get(ctr).y == yPointForStart) {
                    if (letters.get(ctr).x - letters.get(ctr - 1).x <= 0) {
                        while (letters.get(ctr).x - letters.get(ctr - 1).x != 8) {
                            letters.get(ctr).x += speed;
                        }
                    } else if (letters.get(ctr).x - letters.get(ctr - 1).x >= 0) {
                        while (letters.get(ctr).x - letters.get(ctr - 1).x != 8) {
                            letters.get(ctr).x -= speed;
                        }
                    }
                }
            } else if (letters.get(ctr).checker == 4 && letters.get(ctr).y != yPointForStart) {
                letters.get(ctr).x -= speed;
                letters.get(ctr).y += 1;

                if (ctr != 0 && letters.get(ctr).y == yPointForStart) {
                    if (letters.get(ctr).x - letters.get(ctr - 1).x <= 0) {
                        while (letters.get(ctr).x - letters.get(ctr - 1).x != 8) {
                            letters.get(ctr).x += speed;
                        }
                    } else if (letters.get(ctr).x - letters.get(ctr - 1).x >= 0) {
                        while (letters.get(ctr).x - letters.get(ctr - 1).x != 8) {
                            letters.get(ctr).x -= speed;
                        }
                    }
                }
            } else {
                ctr++;
            }
        }
    }

    public void paint(Graphics g) {

        for (int i = 0; i < letters.size(); i++) {
            g.drawString(Character.toString(letters.get(i).letter), letters.get(i).x, letters.get(i).y);
        }

    }

    public class Letter {
        char letter;
        int x;
        int y;
        int checker;

        public Letter(char letter, int x, int y, int checker) {
            this.letter = letter;
            this.x = x;
            this.y = y;
            this.checker = checker;
        }
    }
}
