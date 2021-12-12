set term jpeg size 800,800
set size square
set out "wykresy/mapV5a.jpg"
set view map
set xlabel "y"
set ylabel "x"
splot "wyniki/mapV5a.dat" u 1:2:3 w pm3d

set out "wykresy/mapV5b.jpg"
splot "wyniki/mapV5b.dat" u 1:2:3 w pm3d

set out "wykresy/mapV5c.jpg"
splot "wyniki/mapV5c.dat" u 1:2:3 w pm3d

set out "wykresy/mapV6a.jpg"
splot "wyniki/mapV6a.dat" u 1:2:3 w pm3d

set out "wykresy/mapV6b.jpg"
splot "wyniki/mapV6b.dat" u 1:2:3 w pm3d

set out "wykresy/mapV6c.jpg"
splot "wyniki/mapV6c.dat" u 1:2:3 w pm3d