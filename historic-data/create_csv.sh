#!/bin/sh

if [ "$#" -ne 1 ] ; then
	echo "Usage: $0 info_*.csv\n"
	exit 0
fi

touch $1
echo -n ',Station,Date,Direction,Sens' >> $1