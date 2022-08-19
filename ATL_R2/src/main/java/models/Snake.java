package models;

import java.util.LinkedList;
import java.util.List;

public class Snake implements movable {
    private final List<Point> body;
    private int moveCounter;

    public Snake() {
        this.body = new LinkedList<>();
        this.moveCounter = 0;
    }

    public Snake(Point startPos, int startLen) {
        this.body = new LinkedList<>();
        this.moveCounter = 0;
        this.body.add(startPos);

        Point prev = startPos;
        for (int i = startLen - 1; i >= 0; i--) {
            Point newPoint = new Point(prev.getX() - 1, prev.getY());
            this.body.add(newPoint);
            prev = newPoint;
        }
    }

    @Override
    public boolean move(SnakeDirection dir) {
        this.moveCounter += 1;
        if (moveCounter == 5)
            moveCounter = 0;

        Point snakeTail = this.body.get(this.body.size() - 1);
        if (this.moveCounter > 0)
            this.body.remove(snakeTail);

        Point snakeHead = this.body.get(0);
        Point nextPoint = snakeHead.getNext(dir);

        if (valid(nextPoint)) {
            this.body.add(0, nextPoint);
            return true;
        }

        this.moveCounter -= 1;
        return false;
    }

    private boolean valid(Point point) {
        if (point.getX() >= 0 && point.getX() < 10 && point.getY() >= 0 && point.getY() < 10) {
            for (Point snakePoint: body) {
                if (snakePoint.equals(point))
                   return false;
            }
            return true;
        }
        return false;
    }

    public void print() {
        for (Point point: this.body) {
            System.out.print("(" + point.getX() + ", " + point.getY() + "), ");
        }
        System.out.println();
    }
}
