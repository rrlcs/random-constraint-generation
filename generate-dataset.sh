datapoints=100
shopt -s nullglob
numfiles=(./Dataset-TSE/*) #Count files in this folder
numfiles=${#numfiles[@]}
# echo $numfiles
range=datapoints+numfiles
g++ -o main main.cpp
start=`date +%s%N`
for ((i=$numfiles+1;i<=$range;i++)); do
    ./main $i $datapoints   #Creates ith file in total number of datapoints.
done
end=`date +%s%N`
echo Execution time was `expr $end - $start` nanoseconds.