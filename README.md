# Testat - Verteilte Systeme - Gruppe 7

Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler

## Publisher-Subscriber-System

## :computer: Contributing

### :gear: compile via script
Navigate to /scripts directory:

```
cd scripts/
```

Grant execute permission to the file:

```shell
chmod +x compile.sh
```
Compile all:

```shell
./compile.sh
```
Add parameters to compile individual files:
```
-b broker_main.cpp
-c client_main.cpp
```

Run the broker by changing into the /build directory:

```
cd ../build
```

Start the broker using:

```
./broker_main_exe --server-address insert_address --server-port insert_port
```

Then you can start a client using:

```
./client_main_exe --server-address insert_broker_address --server-port insert_broker_port --action insert_action
```

For `--action` there are the following options:

```
SUBSCRIBE_TOPIC --topicName insert_topic_name
PUBLISH_TOPIC --topicName insert_topic_name --message "insert your message here"
LIST_TOPIC
GET_TOPIC_STATUS --topicName insert_topic_name
```

The client will terminate automatically after receiving the response from the broker, except if you used `SUBSCRIBE_TOPIC` in which case the connection remains open to receive topics. You can use the key combination `Ctrl+C` to properly close the client and the broker.

### :test_tube: unit tests

Navigate to /scripts directory:

```
cd scripts/
```

Grant execute permission to the files:
```shell
chmod +x compile_tests.sh run_tests.sh
```

Compile all unit tests:
```shell
./compile_tests.sh
```

Run all unit tests:
```
./run_tests.sh
```

