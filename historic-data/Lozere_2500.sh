#!/bin/sh

for i in `seq 1 5`; do
	newman run Lozere_request.json -n 500 --delay-request 30000 --silent --reporters cli,json --reporter-json-export Lozere_2500_$i.json
	./json_to_csv.sh Lozere_2500_$i.json info_Lozere_2500.csv
done