package assignment9;

import java.awt.event.KeyEvent;

import edu.princeton.cs.introcs.StdDraw;

public class Game {
	private Food apple;
	private Snake gilbert;
	private Wall wall;
	
	public Game() {
		StdDraw.enableDoubleBuffering();
		this.apple = new Food();
		this.gilbert = new Snake();
		this.wall = new Wall();
	}
	
	public void play() {
		while (this.gilbert.isInbounds() == true) {
			int dir = getKeypress();
			this.gilbert.changeDirection(dir);
			this.gilbert.move();
			if (this.gilbert.eatFood(apple) == true)
			{
				this.gilbert.addSegment();
				this.gilbert.eatMove();
				this.apple = new Food();
				this.wall.addWall();
			}
			if (this.gilbert.touchWall(wall) == true)
			{
				return;
			}
			updateDrawing();
		}
	}
	
	private int getKeypress() {
		if(StdDraw.isKeyPressed(KeyEvent.VK_W)) {
			return 1;
		} else if (StdDraw.isKeyPressed(KeyEvent.VK_S)) {
			return 2;
		} else if (StdDraw.isKeyPressed(KeyEvent.VK_A)) {
			return 3;
		} else if (StdDraw.isKeyPressed(KeyEvent.VK_D)) {
			return 4;
		} else {
			return -1;
		}
	}
	
	/**
	 * Clears the screen, draws the snake and food, pauses, and shows the content
	 */
	private void updateDrawing() {
		StdDraw.clear();
		apple.draw();
		gilbert.draw();
		wall.draw();
		StdDraw.pause(50);
		StdDraw.show();
	}
	
	public static void main(String[] args) {
		Game g = new Game();
		g.play();
	}
}
