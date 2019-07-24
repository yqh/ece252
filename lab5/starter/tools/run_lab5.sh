#!/bin/bash  -x
############################################################################
# File Name  : run_lab5.sh
# Author     : Yiqing Huang 
# Usage      : Name your executable as "paster2" and put it in the
#              same directory where you put this shell script.
#              Make sure the script has x bit set for user. If not, type
#              chmod u+x ./run_lab5.sh
#              The script requires no input argument and output nothing to
#              the standard output if runs successfully.
#              nohup ./run_lab5.sh &
#              will put the script in the background and logging out from the
#              the machine will not affect it.
#             
# Course Name: ECE252 Systems Programming and Concurrency
# Description: Lab5 utility - extracting timing info.
#              The script assumes the following output format at stdout.
#              Please do not output anything else to stdout.
#              It will affect the timing results otherwise.
#  -------------------------------------------
#  findpng3 execution time: S seconds
#  -------------------------------------------
#  The script reads the last line where the timing info is and
#  then extract the S and output to a file. 
#  The outputfile naming convention is: T[0-9]+_M[0-9]+.dat.
#  The script then compute for tables.
#  tb1_$$.txt: average system execution time
#  tb2_$$.txt: standard deviation of system execution time
#  where $$ is the pid of process that executing this shell script.
#############################################################################
PROG="./findpng3"
T="1 10 20"
M="1 10 20 30 40 50 100"
NN=5

exec_producer () 
{

    if [ $# != 4 ]; then
        echo "Usage: $0 <exec_name> -t  T -m M <seed_url>" 
        echo "  exec_name: executible's name"
        echo "  T: number of threads"
        echo "  M: number of valid png links"
        echo "  NN: number of times to run the executible for a given <T, M> pair "
        exit 1
    else
        PROGRAM=$1
        NUM_T=$2
        NUM_M=$3
        X_TIMES=$4
        SEED_URL="http://ece252-1.uwaterloo.ca/lab5"
    fi

    O_FILE='T'${NUM_T}'_M'${NUM_M}'.dat'
    touch ${O_FILE}
    xx=1
    while [ ${xx} -le ${X_TIMES} ]
    do
        cmd="${PROGRAM} -t ${NUM_T} -m ${NUM_M} ${SEED_URL}"
        str=`$cmd | tail -1 | awk -F' ' '{print $4}'`
        echo $str  >> ${O_FILE}
        xx=`expr $xx + 1`
    done
}

gen_data ()
{
    for t in $T
    do
        for m in $M
        do
            exec_producer $PROG $t $m $NN
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
    FNAME_TB[1]="tb1_$$.txt"
    FNAME_TB[2]="tb2_$$.txt"

# generate the table header
    i=1
    while [ ${i} -le ${NUM_TBS} ]
    do
        printf 'T,M,Time\n' >> ${FNAME_TB[${i}]} 
        i=`expr $i + 1`
    done

    for t in $T 
    do
        for m in $M
        do
            i=1
            while [ ${i} -le ${NUM_TBS} ]
            do
                printf '%d,%d,' "$t" "$m" >> ${FNAME_TB[${i}]}
                i=`expr $i + 1`
            done
            FNAME_DATA="T${t}_M${m}.dat"
            echo $FNAME_DATA
            gen_stat_per_pair $FNAME_DATA
        done
    done
}

gen_data 
gen_table
