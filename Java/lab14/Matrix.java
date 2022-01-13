import java.util.Random;
import java.util.List;
import java.util.ArrayList;

public class Matrix
{
    private int rows;
    private int cols;
    public int[][] matrix = null;

    public Matrix(int rows, int cols, boolean empty)
    {
        this.rows = rows;
        this.cols = cols;

        matrix = new int[this.rows][this.cols];
        Random r = new Random();
        for (int i=0; i < rows; i++)
        {
            for (int j=0; j < cols; j++)
            {
                if (empty)
                    matrix[i][j] = 0;
                else
                    matrix[i][j] = r.nextInt(10);
            }
        }
    }

    public void print()
    {
        for (int i=0; i < rows; i++)
        {
            for (int j=0; j < cols; j++)
            {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static Matrix multiply(Matrix m1, Matrix m2)
    {
        Matrix m3 = new Matrix(m1.rows, m2.cols, true);

        long start = System.currentTimeMillis();

        for(int i = 0; i < m1.rows; i++)
        {
            for(int j = 0; j < m2.cols; j++)
            {
                for(int k = 0; k < m1.cols; k++)
                {
                    m3.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
                }
            }
        }

        long stop = System.currentTimeMillis();
        long time = stop - start;
        System.out.println("Czas wykonania bez uzycia watkow(ms.): " + time);

        return m3;
    }

    public static Matrix multiThreadPly(Matrix m1, Matrix m2)
    {
        Matrix m3 = new Matrix(m1.rows, m2.cols, true);
        List<Thread> threads = new ArrayList<Thread>();

        long start = System.currentTimeMillis();

        for (int i=0; i < 8; i++)
        {
            Thread thread = new Thread(new RowWorker(m1, m2, m3, i, m1.rows, m1.cols, m2.cols));
            thread.start();
            threads.add(thread);
        }

        while (threads.size() != 0)
        {
            for (int i=0; i < threads.size(); i++)
            {
                if (threads.get(i).isAlive() == false)
                {
                    threads.remove(i);
                }
            }
        }

        long stop = System.currentTimeMillis();
        long time = stop - start;
        System.out.println("Czas wykonania z uzyciem watkow(ms.): " + time);

        return m3;
    }

    public int getRows()
    {
        return rows;
    }

    public int getCols()
    {
        return cols;
    }
}