package assignment9;

import java.awt.Color;
import java.util.LinkedList;

import edu.princeton.cs.introcs.StdDraw;

public class Wall {

	public static final double WALL_SIZE = 0.04;
	private double x, y;
	private Color color;
	private LinkedList<Wall> walls;
	
	public Wall() {
		double randomX = Math.random();
		double randomY = Math.random();
		this.x = randomX;
		this.y = randomY;
		this.color = toHexString(0, 0, 0);
		this.walls = new LinkedList<Wall>();
	}
	
	public double getX() {
		return this.x;
	}
	
	public double getY() {
		return this.y;
	}
	
	public double getWallSize() {
		return WALL_SIZE;
	}
	
	public LinkedList<Wall> getWalls() {
		return this.walls;
	}

	private Color toHexString(int i, int j, int k) {
		Color black = new Color(i, j, k);
		return black;
	}
	
	public void draw() {
		StdDraw.setPenColor(this.color);
		for (int i=0; i<this.walls.size()-1; i++)
		{
			StdDraw.filledCircle(this.walls.get(i).getX(), this.walls.get(i).getY(), WALL_SIZE);
		}
	}
	
	public void addWall() {
		this.walls.add(new Wall());
	}
}

