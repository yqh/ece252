#!/bin/bash 
############################################################################
# File Name  : run_lab3.sh
# Author     : Yiqing Huang 
# Usage      : Name your executable as "paster2" and put it in the
#              same directory where you put this shell script.
#              Make sure the script has x bit set for user. If not, type
#              chmod u+x ./run_lab3.sh
#              The script requires one input argument, which is the image number 
#              ./run_lab3.sh <N>
#              where N is the image number. For example
#              ./run_lab3.sh 1
#              You can put the script in background and subsequent logout does not
#              stop it by using the following command:
#              nohup ./run_lab3.sh 1 &
#             
# Course Name: ECE252 Systems Programming and Concurrency
# Description: Lab3 utility - extracting timing info.
#              The script assumes the following output format at stdout
#              from the producer process.
#              Please do not output anything else to stdout.
#              It will affect the timing results otherwise.
#  -------------------------------------------
#  paster2 execution time: S seconds
#  -------------------------------------------
#  The script reads the last line where the timing info is and
#  then extract the S and output to a file. 
#  The outputfile naming convention is: B*_P*_C*_X*_N*.dat.
#  The script then compute for tables.
#  tb1_N*_$$.txt: average system execution time
#  tb2_N*_$$.txt: standard deviation of system execution time
#  where N is the user input $$ is the pid of process that executing this shell script.
#############################################################################
PROG="./paster2"
B="5 10"
P="1 5 10"
C="1 5 10"
X="0 200 400"
NN=5

exec_producer () 
{

    if [ $# != 7 ]; then
        echo "Usage: $0 <exec_name> <B> <P> <C> <X> <N> <NN>" 
        echo "  exec_name: executible's name"
        echo "  B: buffer size"
        echo "  P: number of producers"
        echo "  C: number of consumers"
        echo "  X: number of milliseconds to sleep in consumer"
        echo "  N: Image number to get"
        echo "  NN: number of times to run the executible for a given <B, P, C, X, N> pair "
        exit 1
    else
        PROGRAM=$1
        BUFFER_SIZE=$2
        NUM_P=$3
        NUM_C=$4
        NUM2SLEEP=$5
        IMG=$6
        X_TIMES=$7
    fi

    O_FILE='B'${BUFFER_SIZE}'_P'${NUM_P}'_C'${NUM_C}'_X'${NUM2SLEEP}'_N'${IMG}'.dat'
    touch ${O_FILE}
    xx=1
    while [ ${xx} -le ${X_TIMES} ]
    do
        cmd="${PROGRAM} ${BUFFER_SIZE} ${NUM_P} ${NUM_C} ${NUM2SLEEP} ${IMG}"
        str=`$cmd | tail -1 | awk -F' ' '{print $4}'`
        echo $str  >> ${O_FILE}
        xx=`expr $xx + 1`
    done
}

gen_data ()
{
    for x in $X
    do
        for b in $B
        do
            for p in $P 
            do
                if [ $p -gt $(($b+1)) ]; then
                    break
                fi
                for c in $C 
                do
                    if [ $c -gt $(($b+1)) ]; then
                        break
                    fi
                    exec_producer $PROG $b $p $c $x $1 $NN
                done
            done
        done
    done
}

# directly writing each timing string to the tb files.
gen_stat_per_pair ()
{
    if [ $# != 1 ]; then
        echo "Usage: $0 <.dat file name>" 
        exit 1
    else
        FNAME_DATA=$1
    fi
    LIST="${FNAME_TB[1]} ${FNAME_TB[2]}"
    
    awk -v fname_tb_list="$LIST" '
    BEGIN{
        num_files = split(fname_tb_list, fname_tb, " ")
    }
    {
        sum[1]   += $1
        sumsq[1] += $1*$1  
    }
    END{
        for(i = 1; i <= num_files/2; i++) {
            printf("%.6lf\n", sum[i]/NR) >> fname_tb[2*i-1] 
            printf("%.6lf\n", sqrt(NR/(NR-1) * (sumsq[i]/NR - (sum[i]/NR)**2))) >> fname_tb[2*i]
        }
    } ' "${FNAME_DATA}"

}

#$1 is the image number
gen_table ()
{
# assign table names
    NUM_TBS=2
    FNAME_TB[1]="tb1_N$1_$$.txt"
    FNAME_TB[2]="tb2_N$1_$$.txt"

# generate the table header
    i=1
    while [ ${i} -le ${NUM_TBS} ]
    do
        printf 'B,P,C,X,N,Time\n' >> ${FNAME_TB[${i}]} 
        i=`expr $i + 1`
    done

    for x in $X
    do
        for b in $B
        do
            for p in $P 
            do
                if [ $p -gt $(($b+1)) ]; then
                    break
                fi
                for c in $C
                do
                    if [ $c -gt $(($b+1)) ]; then
                        break
                    fi
                    i=1
                    while [ ${i} -le ${NUM_TBS} ]
                    do
                        printf '%d,%d,%d,%d,%d,' "$b" "$p" "$c" "$x" "$1" >> ${FNAME_TB[${i}]}
                        i=`expr $i + 1`
                    done
                    FNAME_DATA="B${b}_P${p}_C${c}_X${x}_N$1.dat"
                    echo $FNAME_DATA
                    gen_stat_per_pair $FNAME_DATA
                done
            done
        done
    done
}

if [ $# -ne 1 ]; then
    echo "Usage: ./run_lab3.sh <N>"
    echo "  N: image number, valide values are 1, 2 or 3"
    exit 1
fi

gen_data "$1"
gen_table "$1"
