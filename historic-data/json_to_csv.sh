#!/bin/sh

if [ "$#" -ne 2 ] ; then
	echo "Usage: $0 json_name csv_name\n"
	exit 0
fi

if ! [ -f $1 ] ; then
	echo "$1 doesn't exist."
	exit 1
fi

if ! [ -f $2 ] ; then
	echo "$2 doesn't exist."
	exit 1
fi

mkdir xml
parse_json/parse_json $1

for file in xml/*;
do
	parse_xml/current_train_per_station ${file} $2
done

rm -r xml