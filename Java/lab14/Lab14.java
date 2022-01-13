// stworzyc program który utworzy dwie macierze z losowymi liczbami całkowitymi o wymiarach które wpisuje uzytkownik na poczatku wykonywania programu
// m1 => m x p
// m2 => n x p
// następnie wykonuje operacje mnożenia macierzy
// raz bez użycia wątków
// drugi raz przy użyciu wielu wątków
// uzytkownik otrzymuje output
// jesli wynikowa macierz ma wymiar wiekszy niz 10x10 nie printujemy ani wylosowanych ani wynikowej, podajemy tylko czasy
//SINGLE THREAD:
//Matrix 1 :
//
//830  930  360
//840  140  580
//200  270  370
//
//Matrix 2 :
//
//440  600  390
//630  590  390
//830  220  530
//
//Output Matrix :
//
//1249900  1125900  877200
//939200  714200  689600
//565200  360700  379400
//
//Time taken in milli seconds: 2
//==================
//MULTIPLE THREAD
//Matrix 1 :
//
//830  930  360
//840  140  580
//200  270  370
//
//Matrix 2 :
//
//440  600  390
//630  590  390
//830  220  530
//
//Output Matrix :
//
//1249900  1125900  877200
//939200  714200  689600
//565200  360700  379400
//
//Time taken in milli seconds: 1
//==================

// Mierzenie czasu: System.currentTimeMillis()
// Liczba dostępnych procesorów: Runtime.getRuntime().availableProcessors()

import java.util.Scanner;

public class Lab14
{
    public static void main(String args[])
    {
        Scanner scanner = new Scanner(System.in);
        int rows1, cols1, rows2, cols2;

        System.out.println("Podaj wymiary 1 macierzy: ");
        rows1 = scanner.nextInt();
        cols1 = scanner.nextInt();

        System.out.println("Podaj wymiary 2 macierzy: ");
        rows2 = scanner.nextInt();
        cols2 = scanner.nextInt();

        System.out.println("m1 => " + rows1 + " x " + cols1);
        System.out.println("m2 => " + rows2 + " x " + cols2);

        if (cols1 != rows2 || rows1 <= 0 || cols1 <= 0 || rows2 <= 0 || cols2 <= 0)
        {
            System.out.println("Wymiary powinny byc wieksze od zera oraz cols1 powinno byc rowne rows2");
            return;
        }

        Matrix m1 = new Matrix(rows1, cols1, false);
        Matrix m2 = new Matrix(rows2, cols2, false);

        Matrix m3 = Matrix.multiply(m1, m2);
        Matrix m4 = Matrix.multiThreadPly(m1, m2);


        if (m3.getRows() < 10 && m3.getCols() < 10)
            m3.print();
        if (m4.getRows() < 10 && m4.getCols() < 10)
            m4.print();
    }
}
