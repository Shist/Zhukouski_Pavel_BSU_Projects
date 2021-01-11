
public class AppletThread extends Thread {
	AppletGraph pa = null;

	public AppletThread(AppletGraph pa) {
		super();
		this.pa = pa;
	}

	public void run() {
		int r=pa.c.radius;
		while (true) {
			try {
				Thread.sleep(3);
				pa.c.rotateBy(0.01);
				pa.c.repaint();				
				pa.c.setLocation(pa.c.point.x-r,pa.c.point.y-r);
			} catch (InterruptedException e) {
				break;
			}
		}
	}

	

}
