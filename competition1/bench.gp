set terminal pdfcairo font 'Liberation Sans,10' size 14cm,9cm
set style line 20 lc rgb '#808080' lt 1
set border 3 back ls 20
set tics nomirror out scale 0.75
set style line 21 lc rgb'#808080' lt 0 lw 1
set arrow from graph 1,0 to graph 1.05,0 size screen 0.025,10,60 filled ls 20
set arrow from graph 0,1 to graph 0,1.05 size screen 0.025,10,60 filled ls 20
set style fill transparent solid 0.3
set style line 1 lc rgb '#ff4400' lt 1 lw 2
set style line 2 lc rgb '#ffa500' lt 1 lw 2
set style line 3 lc rgb '#0000ff' lt 1 lw 2
set style line 4 lc rgb '#006300' lt 1 lw 2
unset mxtics
set xlabel  offset screen 0.464286, character 1.5 norotate
unset logscale x
set yrange [0:246.39]
unset mytics
set ylabel 'time [ns]' offset character 6, screen 0.477778 norotate
unset logscale y
set title 'category:charset type:fl test:sum'
set key outside title 'benchmark' Left
unset grid
set tmargin 4
set format x '%.0f'
set xtics scale 0
set format x ''
set grid ytics ls 21
num_of_datasets = 4.0
outer_data_margin = 0.2
inter_box_gap = 0.2 / num_of_datasets
bars_space = 1 - outer_data_margin
usable_data_space = 1 - (outer_data_margin + (num_of_datasets - 1) * inter_box_gap)
bwidth = usable_data_space / num_of_datasets
offset = (bars_space - bwidth) / 4
step = bwidth + inter_box_gap
set boxwidth bwidth
plot \
 '-' using ($1 - offset + 0 * step):4 with boxes notitle ls 1,\
 '-' using ($1 - offset + 0 * step):2 with boxes notitle ls 1,\
 '-' using ($1 - offset + 0 * step):3 with boxes title 'insert' ls 1, \
  \
 '-' using ($1 - offset + 1 * step):4 with boxes notitle ls 2,\
 '-' using ($1 - offset + 1 * step):2 with boxes notitle ls 2,\
 '-' using ($1 - offset + 1 * step):3 with boxes title 'intersect' ls 2, \
  \
 '-' using ($1 - offset + 2 * step):4 with boxes notitle ls 3,\
 '-' using ($1 - offset + 2 * step):2 with boxes notitle ls 3,\
 '-' using ($1 - offset + 2 * step):3 with boxes title 'union_' ls 3, \
  \
 '-' using ($1 - offset + 3 * step):4 with boxes notitle ls 4,\
 '-' using ($1 - offset + 3 * step):2 with boxes notitle ls 4,\
 '-' using ($1 - offset + 3 * step):3 with boxes title 'sum' ls 4
 1 232.233749666667 218.516666666667 246.39
end
 1 232.233749666667 218.516666666667 246.39
end
 1 232.233749666667 218.516666666667 246.39
end
 1 210.920048666667 197.53 224.713333333334
end
 1 210.920048666667 197.53 224.713333333334
end
 1 210.920048666667 197.53 224.713333333334
end
 1 212.618250666666 199.253333333333 226.29
end
 1 212.618250666666 199.253333333333 226.29
end
 1 212.618250666666 199.253333333333 226.29
end
 1 220.429255 207.203333333334 234.066666666667
end
 1 220.429255 207.203333333334 234.066666666667
end
 1 220.429255 207.203333333334 234.066666666667
end
