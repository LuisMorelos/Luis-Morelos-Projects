package assignment9;

import java.awt.Color;

import edu.princeton.cs.introcs.StdDraw;

public class BodySegment {

	private double x, y, size;
	private Color color;
	
	public BodySegment(double x, double y, double size) {
		this.x = x;
		this.y = y;
		this.size = size;
		this.color = toHexString(147, 225, 71);
	}
	
	private Color toHexString(int i, int j, int k) {
		Color green = new Color(i, j, k);
		return green;
	}
	
	public double getX() {
		return this.x;
	}
	
	public double setX(double d) {
		this.x = d;
		return d;
	}
	
	public double getY() {
		return this.y;
	}
	
	public double setY(double d) {
		this.y = d;
		return d;
	}

	/**
	 * Draws the segment
	 */
	public void draw() {
		StdDraw.setPenColor(this.color);
		StdDraw.filledCircle(this.x, this.y, this.size);
	}
	
}
