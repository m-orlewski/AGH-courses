import chart1
import chart2

chart1.plot('Metoda jawna Eulera', 'Błąd globalny met. jawnej eulera',
          ['wyniki/euler1.dat', 'wyniki/euler2.dat', 'wyniki/euler3.dat'], 'wykresy/wykres_euler')

chart1.plot('Metoda jawna RK2', 'Błąd globalny met. jawnej RK2',
          ['wyniki/rk2_1.dat', 'wyniki/rk2_2.dat', 'wyniki/rk2_3.dat'], 'wykresy/wykres_rk2')

chart1.plot('Metoda jawna RK4', 'Błąd globalny met. jawnej RK4',
          ['wyniki/rk4_1.dat', 'wyniki/rk4_2.dat', 'wyniki/rk4_3.dat'], 'wykresy/wykres_rk4')

chart2.plot_rlc(['wyniki/RLC1.dat', 'wyniki/RLC2.dat', 'wyniki/RLC3.dat', 'wyniki/RLC4.dat'], 'wykresy/wykres_rlc')

