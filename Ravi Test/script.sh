datapoints=5
shopt -s nullglob
numfiles=(./Dataset/*)
numfiles=${#numfiles[@]}
echo $numfiles
range=datapoints+numfiles
g++ -o test test.cpp
for ((i=1;i<=range;i++)); do
    ./test $i
done
