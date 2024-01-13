#!/bin/sh

# Server details
server="localhost"
port="3000"

# Data to send
data="*2\r\n\$4\r\nECHO\r\n\$3\r\nhey\r\n"

# Number of connections to create
num_connections=1

# Create connections and send data
for i in $(seq 1 $num_connections)
do
    (echo "$data") | nc $server $port
done