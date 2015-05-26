for (( i = 10; i < 12; i++ ))
do  
    for (( j = 1; j < 2; j++ ))
    do
    echo i = $i and j = $j
	./generator_omp	$i -e 2 -o out$i.txt | tee -a outputnormal.txt
    done		  
done
