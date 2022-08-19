package models;

public enum SnakeDirection {
    UP(0),
    DOWN(1),
    LEFT(2),
    RIGHT(3);

    private int dir;
    private SnakeDirection(int dir) {
        this.dir = dir;
    }

    public int getDir() {
        return this.dir;
    }
};
