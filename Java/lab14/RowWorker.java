public class RowWorker implements Runnable
{
    public Matrix leftMatrix;
    public Matrix rightMatrix;
    public Matrix m3;
    public int rowIndex;
    public int cols1;
    public int cols2;
    public int rows;

    public RowWorker(Matrix m1, Matrix m2, Matrix m3, int rowIndex, int rows1, int cols1, int cols2)
    {
        this.m3 = m3;
        this.leftMatrix = m1;
        this.rightMatrix = m2;
        this.rowIndex = rowIndex;
        this.cols1 = cols1;
        this.cols2 = cols2;
        this.rows = rows1;
    }

    public void run()
    {
        while (this.rowIndex < this.rows)
        {
            for(int j = 0; j < cols1; j++)
            {
                for(int k = 0; k < cols2; k++)
                {
                    m3.matrix[rowIndex][j] += leftMatrix.matrix[rowIndex][k] * rightMatrix.matrix[k][j];
                }
            }
            rowIndex += 8;
        }
    }
}