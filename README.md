# Testat - Verteilte Systeme - Gruppe 7

Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler

## Publisher-Subscriber-System

## :computer: Contributing

### :gear: compile via script
navigate to /scripts directory:

```
cd scripts/
```

grant execute permission to the file:

```shell
chmod +x compile.sh
```
compile all:

```shell
./compile.sh
```
add parameters to compile individual files:
```
-b broker_main.cpp
-c client_main.cpp
```

run the broker by changing into the /build directory:

```
cd ../build
```

start the broker using:

```
./broker_main_exe --server-address insert_address --server-port insert_port
```

then you can start a client using:

```
./client_main_exe --server-address insert_broker_address --server-port insert_broker_port --action insert_action
```

for `--action` there are the following options:

```
SUBSCRIBE_TOPIC
UNSUBSCRIBE_TOPIC
PUBLISH_TOPIC
LIST_TOPIC
GET_TOPIC_STATUS
```

please note that you can only use `PUBLISH_TOPIC` if you also provide a message using:

```
--message "your message"
```

the client will terminate automatically after receiving the response from the broker, except if you used `SUBSCRIBE_TOPIC` in which case the connection remains open to receive topics. You can use the key combination Ctrl+C to properly close the client and the broker.

### :test_tube: unit tests

navigate to /scripts directory:

```
cd scripts/
```

grant execute permission to the files:
```shell
chmod +x compile_tests.sh run_tests.sh
```

compile all unit tests:
```shell
./compile_tests.sh
```

run all unit tests:
```
./run_tests.sh
```

