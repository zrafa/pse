#!/bin/bash

FILENAME=$1
FILESIZE=$(stat -c%s "$FILENAME")
MINFILESIZE=36864
COUNT=$((MINFILESIZE-FILESIZE))
if [ "COUNT" > 0 ]; then
	echo "Size of $FILENAME = $FILESIZE bytes Min file size = $MINFILESIZE Count = $COUNT."
	dd bs=1 count=$COUNT if=/dev/zero of=$FILENAME oflag=append conv=notrunc
fi

