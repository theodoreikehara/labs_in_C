#!/bin/bash

make clean && make collatz   # Rebuild the sincos executable.
rm -f /tmp/length.dat        # Deletes the existing .dat files
rm -f /tmp/maxdots.dat
rm -f /tmp/length_histo.dat

# this protion is from Eugene's section
for i in {2..10000}; do                         # runs through 2-10000
    ./collatz -n $i | wc -l >> /tmp/length.dat  # appends to the file the length
    ./collatz -n $i | sort -rn | head -n 1 >> /tmp/maxdots.dat       # sorts then gets the max
done

sort -n /tmp/length.dat > /tmp/temp.dat
uniq -c /tmp/temp.dat > /tmp/length_histo.dat


# this gnuplot section is from the provided bash file

# This is the heredoc that is sent to gnuplot.
gnuplot <<END
    set terminal pdf
    set output "collatz_sequ_leng.pdf"
    set title "Collatz Sequence Lengths"
    set xlabel "n"
    set ylabel "length"
    set yrange [0:300]
    set xrange [0:10000]
    set zeroaxis
    plot "/tmp/length.dat" with dots title ""
END

# This is the heredoc that is sent to gnuplot.
gnuplot <<END
    set terminal pdf
    set output "collatz_max_dot.pdf"
    set title "Maximum Collatz Sequence Value"
    set xlabel "n"
    set ylabel "value"
    set yrange [0:100000]
    set xrange [0:10000]
    set zeroaxis
    plot "/tmp/maxdots.dat" with dots title ""
END

# This is the heredoc that is sent to gnuplot.
gnuplot <<END
    set terminal pdf
    set output "collatz_length_histo.pdf"
    set title "Collatz Sequence Length Histogram"
    set xlabel "length"
    set ylabel "frequency"
    set yrange [0:200]
    set xrange [0:225]
    set zeroaxis

    set style histogram
    set boxwidth 0 absolute
    plot "/tmp/length_histo.dat" using 2:1 with boxes title ""
END


