#!/bin/bash
mkdir -p outputs

RUN_CONF=${RUN_CONF:-LDCT6-stru-meshB}

LAUNCHER=${LAUNCHER:-jsrun -n1}
NRUN=${1:-1}
date

for MP in 1 2 4 8 16
do
	export OMP_NUM_THREADS=$MP
	printf "Threads=$MP "
        for i in `seq $NRUN`
      	do
  		FILE=outputs/RUN-$RUN_CONF-$(date -u +%A-%H.%M.%S).$USER.MP$MP
		date > $FILE

		$LAUNCHER ./incexplicitSerial $RUN_CONF >> $FILE
		TIME=$(sed -n 's/.*Total time taken = \(.*\) seconds/\1/p' $FILE)
		[[ -z "$MIN_TIME" ]] || SPEEDUP="($(bc <<< "scale=2; $MIN_TIME/$TIME" &2> /dev/null)) "
		printf "$TIME$SPEEDUP "
	done
	echo
	[[ $MP -eq 1 ]] && MIN_TIME=$TIME
done


#python3 test-$RUN_CONF-Re1000.py
