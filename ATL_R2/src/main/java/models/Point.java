package models;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Point {

    private final int x;
    private final int y;

    private static final Integer[] xChange = {0, 0, -1, 1};

    private static final Integer[] yChange = {1, -1, 0, 0};

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Point getNext(SnakeDirection dir) {
        return new Point(this.getX() + xChange[dir.getDir()], this.getY() + yChange[dir.getDir()]);
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Point point = (Point) o;
        return x == point.x && y == point.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }
}
