#!/bin/sh -x

# clean shared memory regions and semaphores owned by the current user

USERID=`whoami`

# clean all shared memory regions owned by USERID
for id in `ipcs -m | grep $USERID | awk -F' ' '{print $2}' `
do
    ipcrm -m $id
done

# clean all semaphores owned by USERID
for id in `ipcs -s | grep $USERID | awk -F' ' '{print $2}' `
do
    ipcrm -s $id
done
