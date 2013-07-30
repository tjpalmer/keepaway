# Gnuplot graph generation script
# Gregory Kuhlmann, 2002

# Color output
set terminal postscript eps color solid "Helvetica" 24

# Black & White output
#set terminal postscript eps monochrome dashed "Helvetica" 24

# Output file
set output "./graph.eps"

# Title
set title ""

# Appearance
set style data lines
set nokey
set border 3
set xtics nomirror
set ytics nomirror
set multiplot

# Axes
set xrange [-0.5:36]
set xlabel "Training Time (hours)"

set yrange [5.5:13.5]
set ylabel "Episode Duration (seconds)"

# Plot Data
plot "./1.out"
