import models.Point;
import models.Snake;
import models.SnakeDirection;

public class Driver {
    public static void main(String[] args) {
        Snake snake = new Snake(new Point(8, 8), 3);
        snake.print();
        if (snake.move(SnakeDirection.RIGHT))
            snake.print();
        else
            System.out.println("Game Over!");

        if (snake.move(SnakeDirection.RIGHT))
            snake.print();
        else
            System.out.println("Game Over!");
    }
}
