# -- ********************************************************************* 
# -- Archivo : updatedatavalue.sh
# -- Proyecto : Campus-party FI-WARE
# -- Fecha : junio 2014 
# -- Copyright 2014 Eduardo R., Josue S., Armando V., Victor G., Ricardo B.
# -- --------------------------------------------------------------------- 
# -- This program is free software: you can redistribute it and/or modify 
# -- it under the terms of the GNU General Public License as published by 
# -- the Free Software Foundation, either version 3 of the License, or 
# -- (at your option) any later version. 

# -- This program is distributed in the hope that it will be useful, 
# -- but WITHOUT ANY WARRANTY; without even the implied warranty of 
# -- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
# -- GNU General Public License for more details. 

# -- You should have received a copy of the GNU General Public License 
# -- along with this program.  If not, see <http://www.gnu.org/licenses/>. 
# -- *********************************************************************

#!/bin/bash

# Getting sensor data
data=$1
#echo sensor data: $data

# Getting the line of the first appearance of value string
first=`grep -n "value" /root/test/sensor.json | head -n 1 | cut -d':' -f 1`
firstt=`echo $first\c`
#echo first line value: $firstt

# String to use in grep
str="\"value\" : $data"
#echo sed string: $str

# Copying template sensor data
cp /root/test/sensor.json /root/project/sensor.json

# Changing the first value argument
sed -i "$firstt\\$str" /root/project/sensor.json

# Udating the sensor data and getting the right code 200
string=`curl 130.206.82.44:1026/NGSI10/updateContext -s -S --header 'Content-Type: application/json' --header 'Accept: application/json' -d @/root/project/sensor.json | grep -w 'code' | cut -d'"' -f 4`
echo $string