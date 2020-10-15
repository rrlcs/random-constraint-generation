datapoints=100
shopt -s nullglob
numfiles=(./Dataset/*)
numfiles=${#numfiles[@]}
# echo $numfiles
range=datapoints+numfiles
g++ -o main main.cpp
for ((i=$numfiles+1;i<=$range;i++)); do
    ./main $i
done