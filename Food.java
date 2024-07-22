package assignment9;

import java.awt.Color;

import edu.princeton.cs.introcs.StdDraw;

public class Food {

	public static final double FOOD_SIZE = 0.02;
	private double x, y;
	private Color color;
	
	/**
	 * Creates a new Food at a random location
	 */
	public Food() {
		double randomX = Math.random();
		double randomY = Math.random();
		this.x = randomX;
		this.y = randomY;
		this.color = toHexString(255, 0, 0);
	}
	
	public double getX() {
		return this.x;
	}
	
	public double getY() {
		return this.y;
	}
	
	private Color toHexString(int i, int j, int k) {
		Color red = new Color(i, j, k);
		return red;
	}

	/**
	 * Draws the Food
	 */
	public void draw() {
		StdDraw.setPenColor(this.color);
		StdDraw.filledCircle(this.x, this.y, FOOD_SIZE);
	}
}
