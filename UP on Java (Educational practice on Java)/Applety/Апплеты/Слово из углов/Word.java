import java.applet.Applet;
import java.awt.Font;
import java.awt.Graphics;




public class Word extends Applet implements Runnable{
	String myString = "Мой апплет";
	String haveToDraw = "";
	Character currentLetter = null;
	int currentIndex = 0;
	int direction = 0;
	int coordinateX;
	int currentCoordinateX = 0, currentCoordinateY = 0;
	Thread appletThread = null;
	
	public void init() {
		
		if (appletThread == null) {
			appletThread = new Thread(this);
			currentLetter = myString.charAt(0);
			currentIndex++;
			appletThread.start();
		}
		setSize(600,600);
	}
	
	public void paint(Graphics gr) {
		gr.setFont(new Font("TimesRoman",Font.BOLD,36));
		int beginX = (getWidth() - gr.getFontMetrics().stringWidth(myString))/2;
		gr.drawString(haveToDraw,  beginX , getHeight()/2);
		if (haveToDraw == "")
			coordinateX = beginX;
		else
			coordinateX = gr.getFontMetrics().stringWidth(haveToDraw) + beginX;
		gr.drawString(currentLetter + "", currentCoordinateX, currentCoordinateY);
	}
	
	public void nextLetter() {
		haveToDraw += currentLetter;
		if (currentIndex == myString.length())
			currentLetter = null;
		else {
			while (currentIndex != myString.length() && myString.charAt(currentIndex) == ' ') {
				haveToDraw += ' ';
				currentIndex++;
			}
			currentLetter = myString.charAt(currentIndex);
			currentIndex++;
		}
	}
	
	public void drawNext() {
		int stepX = 5;
		int stepY = 5;
		if (direction == 0) {
			if (currentCoordinateX + stepX > coordinateX ) {
				if (currentCoordinateY + stepY > getHeight()/2) {
					direction++;
					currentCoordinateX = getWidth();
					currentCoordinateY = 0;
					nextLetter();
				}
				else {
					currentCoordinateX = coordinateX;
					currentCoordinateY += stepY;
				}	
			}
			else if (currentCoordinateY + stepY > getHeight()/2) {
				currentCoordinateX += stepX;
			}
			else {
				currentCoordinateX += stepX;
				currentCoordinateY += stepY;
			}
		}
		else if (direction == 1) {
			if (currentCoordinateX - stepX < coordinateX ) {
				if(currentCoordinateY + stepY > getHeight()/2) {
					direction++;
					currentCoordinateX = 0;
					currentCoordinateY = getHeight();
					nextLetter();
				}
				else 
					currentCoordinateY += stepY;
			}
			else if(currentCoordinateY + stepY > getHeight()/2){
				currentCoordinateX -= stepX;
			}
			else {
				currentCoordinateX -= stepX;
				currentCoordinateY += stepY;
			}
		}
		else if (direction == 2) {
			if (currentCoordinateX + stepX > coordinateX ) {
				if(currentCoordinateY - stepY < getHeight()/2) {
					direction++;
					currentCoordinateX = getWidth();
					currentCoordinateY = getHeight();
					nextLetter();
				}
				else 
					currentCoordinateY -= stepY;
			}
			else if (currentCoordinateY - stepY < getHeight()/2) {
				currentCoordinateX += stepX;
			}
			else {
				currentCoordinateX += stepX;
				currentCoordinateY -= stepY;
			}
		}
		else {
			if (currentCoordinateX - stepX < coordinateX ) {
				if(currentCoordinateY - stepY < getHeight()/2) {
					direction = 0;
					currentCoordinateX = 0;
					currentCoordinateY = 0;
					nextLetter();
				}
				else 
					currentCoordinateY -= stepY;
			}
			else if (currentCoordinateY - stepY < getHeight()/2) {
				currentCoordinateX -= stepX;
			}
			else {
				currentCoordinateX -= stepX;
				currentCoordinateY -= stepY;
			}
		}
		repaint();
	}
	
	public void run() {
		while (true) {
			try {
				if (currentLetter == null)
					break;
				else {
					drawNext();
				}
				appletThread.sleep(100);
			}
			catch(Exception ex) {
				break;
			}
		}
	}
	
	public void destroy() {
		if (appletThread != null) {
			appletThread.interrupt();
			appletThread = null;
		}
		
	}
}
