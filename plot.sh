rm -f moves.dat compares.dat
echo "n,Insertion Sort,Batcher Sort,Heap Sort,Quick Sort" > moves.dat
echo "n,Insertion Sort,Batcher Sort,Heap Sort,Quick Sort" > compares.dat
for n in 10 20 50 100 500 1000 10000
do
    ins=`./sorting -i -n $n -p 0 | awk -F',' '{print $3}' | awk '{print $1}'`
    batcher=`./sorting -b -n $n -p 0 | awk -F',' '{print $3}' | awk '{print $1}'`
    heap=`./sorting -h -n $n -p 0 | awk -F',' '{print $3}' | awk '{print $1}'`
    quick=`./sorting -q -n $n -p 0 | awk -F',' '{print $3}' | awk '{print $1}'`
    echo $n,$ins,$batcher,$heap,$quick >> moves.dat

    ins=`./sorting -i -n $n -p 0 | awk -F',' '{print $4}' | awk '{print $1}'`
    batcher=`./sorting -b -n $n -p 0 | awk -F',' '{print $4}' | awk '{print $1}'`
    heap=`./sorting -h -n $n -p 0 | awk -F',' '{print $4}' | awk '{print $1}'`
    quick=`./sorting -q -n $n -p 0 | awk -F',' '{print $4}' | awk '{print $1}'`
    echo $n,$ins,$batcher,$heap,$quick >> compares.dat
done
exit

rm -f moves.plot
echo "set terminal jpeg" > moves.plot
echo 'set output "moves.jpeg"' >> moves.plot
echo 'set xlabel "Elements"' >> moves.plot
echo 'set ylabel "Moves"' >> moves.plot
echo 'set title "Moves Performed"' >> moves.plot
#echo 'plot "moves.dat" with lines notitle' >> moves.plot
echo "plot 'moves.dat' using 1:2 w lines title 'Insertion Sort', \
     '' using 1:3 w lines title 'Batcher Sort', \
     '' using 1:4 w lines title 'Heap Sort', \
     '' using 1:5 w lines title 'Quick Sort'" >> moves.plot

gnuplot moves.plot

rm -f compares.plot
echo "set terminal jpeg" > compares.plot
echo 'set output "compares.jpeg"' >> compares.plot
echo 'set xlabel "Elements"' >> compares.plot
echo 'set ylabel "Comparisons"' >> compares.plot
echo 'set title "Comparisons Done"' >> compares.plot
#echo 'plot "compares.dat" with lines notitle' >> compares.plot
echo "plot 'compares.dat' using 1:2 w lines title 'Insertion Sort', \
     '' using 1:3 w lines title 'Batcher Sort', \
     '' using 1:4 w lines title 'Heap Sort', \
     '' using 1:5 w lines title 'Quick Sort'" >> compares.plot

gnuplot compares.plot
