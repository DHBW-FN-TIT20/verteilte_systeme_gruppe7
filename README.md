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
-p publisher.cpp
-b broker.cpp
-s subscriber.cpp
-r request_parser.cpp
```

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

