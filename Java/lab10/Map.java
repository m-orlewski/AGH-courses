import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;


public class Map
{
    private char[][] map = null;
    private int size = 0;
    private double water_probability = 1.0;
    private int[] skarb_pos = new int[2];
    private int[] gracz_pos = new int[2];
    char prev = '*';

    public void setSize(int size) throws TooSmallGameSizeException
    {
        if (size > 3)
            this.size = size;
        else
            throw new TooSmallGameSizeException();
    }

    public void setWaterProbability(double prob) throws TooSmallWaterProbabilityException
    {
        if (prob > 0.0 && prob < 1.0)
            this.water_probability = prob;
        else
            throw new TooSmallWaterProbabilityException();
    }

    public void fillMap()
    {
        map = new char[size][size];
        for (int i=0; i < size; i++)
        {
            for (int j=0; j < size; j++)
            {
                double rd = Math.random();

                if (rd <= water_probability)
                    map[i][j] = 'W';
                else
                    map[i][j] = '*';

            }
        }
            map[0][0] = 'G';
            map[size-1][size-1] = 'S';

            skarb_pos[0] = size-1;
            skarb_pos[1] = size-1;
            gracz_pos[0] = 0;
            gracz_pos[1] = 0;
    }

    public void print()
    {
        System.out.print("\n\n");
        for (int i=0; i < size; i++)
        {
            for (int j=0; j < size; j++)
            {
                System.out.print(map[i][j] + " ");
            }
            System.out.println();
        }
    }

    public void gameLoop()
    {
        Scanner scanner = new Scanner(System.in);
        while (true)
        {
            char choice = scanner.next().charAt(0);

            int dx = 0;
            int dy = 0;
            try
            {
                if (choice == 'l')
                    dx = -1;
                else if (choice == 'p')
                    dx = 1;
                else if (choice == 'g')
                    dy = -1;
                else if (choice == 'd')
                   dy = 1;
                else
                    throw new CommandNotRecognisedException();
            }
            catch (CommandNotRecognisedException e)
            {
                System.err.println("Exception: Nieznana komenda");
                break;
            }

            try
            {
                move(dx, dy);
            }
            catch (WetSocksException e)
            {
                System.err.println("Wszedles w wode, koniec gry!");
                break;
            }
            catch (OutOfMapException e)
            {  
                System.err.println("Wyszedles poza mape, koniec gry");
                break;
            }
            catch (GameWonException e)
            {
                System.err.println("Wygrales, koniec gry");
                break;
            }
            catch (GameOverException e)
            {
                break;
            }

            print();
        }
    }

    public void move(int dx, int dy) throws GameOverException
    {
        if (gracz_pos[0] + dy < 0 || gracz_pos[0] + dy >= size || gracz_pos[1] + dx < 0 || gracz_pos[1] + dx >= size)
            throw new OutOfMapException();

        map[gracz_pos[0]][gracz_pos[1]] = prev;
        gracz_pos[0] += dy;
        gracz_pos[1] += dx;
        prev = map[gracz_pos[0]][gracz_pos[1]];
        map[gracz_pos[0]][gracz_pos[1]] = 'G';
        
        if (gracz_pos[0] == skarb_pos[0] && gracz_pos[1] == skarb_pos[1])
            throw new GameWonException();

        if (prev == 'W')
            throw new WetSocksException();
    }
}