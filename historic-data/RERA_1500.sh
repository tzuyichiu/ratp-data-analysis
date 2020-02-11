#!/bin/sh

for i in `seq 1 500`; do
	newman run RERA_request.json -n 5 --delay-request 1000 --reporters cli,json --reporter-json-export RERA_1500_$i.json
	./json_to_csv.sh RER_1500_$i.json info_RERA_1500.csv
done
