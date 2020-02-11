# Real-time data analysis of Paris Metro

## Overview

This is a project done in Ecole Polytechnique, proposed in the course INF442:
Algorithms of data analysis in C++. We collect measurements taken from the 
real-time API exposed by RATP (Paris metro). For RERA et RERB, we periodically 
poll a web service that reports estimated times of passage in order to analyze, 
data mine and compare these historical data with the theoretical ones.

This project was done in collaboration with my classmate, Sylvanus Mahe. It 
consists of two parts: data collection and information extraction.

All the data we used are zipped inside **data.zip** including theoretical and 
historical data (real-time).

## Data collection

### Theoretical data

The theoretical data are available on the website of RATP. We used **panda**
inside jupyter notebook in order to visualize these data.

### Historical data (real-time)

To be able to collect measurements from the RATP server, we had to ask for 
authorization from the **opendata** service. Finally we were able to send
**SOAP** requests by the use of **Postman** to obtain responses. The three
major services are *getLines*, *getStations* and *getMissionsNext*.
We made use of *getMissionsNext* in order to collect data for any given train
station.

We wrote scripts in order to:
- launch **Postman** in command line via **newman** 
(https://www.npmjs.com/package/newman). We were able to construct a collection 
of requests for each train station and obtain a response grouped together 
represented in *json*.
- parse *json* response files to collect the specific response represented in 
*xml* (real-time information for each train station).
- construct *csv* files from *xml* files (extract useful information)
- automate the three above procedures

We then used **panda** to visulaize the *csv* files we constructed. Due to the 
lack of time, we only obtained real-time data for a period of 2-3 days, for 
both RERA and RERB. The data was not complete, but still enough to do some 
analysis.

## Information extraction

Please refer to **data-illustration.ipynb** to visualize our work of data 
mining. Especially, we were able to visualize the passage frequency of trains
at different hours. We tried to apply logitic regression on these data in C++
with the help of the library **eigen**. Given the train station and the time, 
the algorithm was expected to be able to predict if a train is going to be late 
or not (or more/less than 10 minutes). However the success rate was rather
low (10 percents).

## Further details

Please refer to **report.pdf** for further details (in French).