package assignment9;

import java.util.LinkedList;

import edu.princeton.cs.introcs.StdDraw;

public class Snake {

	private static final double SEGMENT_SIZE = 0.02;
	private static final double MOVEMENT_SIZE = SEGMENT_SIZE * 1.01;
	private static final double START_X = 0.5;
	private static final double START_Y = 0.5;
	private LinkedList<BodySegment> segments;
	private double deltaX;
	private double deltaY;
	
	public Snake() {
		deltaX = 0;
		deltaY = 0;
		this.segments = new LinkedList<BodySegment>();
		this.segments.add(new BodySegment(START_X, START_Y, SEGMENT_SIZE));
	}
	
	public void addSegment() {
		this.segments.add(new BodySegment(this.segments.getLast().getX(), this.segments.getLast().getY(), SEGMENT_SIZE));
	}
	
	public void eatMove() {
		for (int i=this.segments.size()-1; i>0; i--)
		{
			this.segments.get(i).setX(this.segments.get(i-1).getX());
			this.segments.get(i).setY(this.segments.get(i-1).getY());
		}
		this.segments.getFirst().setX(this.segments.getFirst().getX() + deltaX);
		this.segments.getFirst().setY(this.segments.getFirst().getY() + deltaY);
	}
	
	public void changeDirection(int direction) {
		if(direction == 1) { 
			deltaY = MOVEMENT_SIZE;
			deltaX = 0;
		} else if (direction == 2) {
			deltaY = -MOVEMENT_SIZE;
			deltaX = 0;
		} else if (direction == 3) {
			deltaY = 0;
			deltaX = -MOVEMENT_SIZE;
		} else if (direction == 4) {
			deltaY = 0;
			deltaX = MOVEMENT_SIZE;
		}
	}
	
	/**
	 * Moves the snake by updating the position of each of the segments
	 * based on the current direction of travel
	 */
	public void move() {
		for (int i=this.segments.size()-1; i>0; i--)
		{
			this.segments.get(i).setX(this.segments.get(i-1).getX());
			this.segments.get(i).setY(this.segments.get(i-1).getY());
		}
		this.segments.getFirst().setX(this.segments.getFirst().getX() + deltaX);
		this.segments.getFirst().setY(this.segments.getFirst().getY() + deltaY);
	}
	
	/**
	 * Draws the snake by drawing each segment
	 */
	public void draw() {
		int count = 0;
		for (int i=0; i<this.segments.size(); i++)
		{
			this.segments.get(i).draw();
			count++;
		}
		String numSegments = "Points: " + count;
		StdDraw.setPenColor(0, 0, 0);
		StdDraw.text(0.07, 0.95, numSegments);
	}
	
	/**
	 * The snake attempts to eat the given food, growing if it does so successfully
	 * @param f the food to be eaten
	 * @return true if the snake successfully ate the food
	 */
	public boolean eatFood(Food f) {
		double xDistance = Math.pow(this.segments.getFirst().getX() - f.getX(), 2);
		double yDistance = Math.pow(this.segments.getFirst().getY() - f.getY(), 2);
		double distance = Math.sqrt(xDistance + yDistance);
		if (distance < (SEGMENT_SIZE * 2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	public boolean touchWall(Wall w) {
		for (int i=0; i<w.getWalls().size()-1; i++)
		{
			double xDistance = Math.pow(this.segments.getFirst().getX() - w.getWalls().get(i).getX(), 2);
			double yDistance = Math.pow(this.segments.getFirst().getY() - w.getWalls().get(i).getY(), 2);
			double distance = Math.sqrt(xDistance + yDistance);
			if (distance < (SEGMENT_SIZE + w.getWallSize()-0.01))
			{
				return true;
			}
		}
		return false;
	}
	
	/**
	 * Returns true if the head of the snake is in bounds
	 * @return whether or not the head is in the bounds of the window
	 */
	public boolean isInbounds() {
		if (this.segments.getFirst().getX() < 0 || this.segments.getFirst().getX() > 1 || this.segments.getFirst().getY() < 0 || this.segments.getFirst().getY() > 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
