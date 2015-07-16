# Client
The client is a command-line application that will accept one or more log 
les
as arguments.
It will establish one connection to the server and send all the questionable
activities found. Then it will terminate.

# Server
The server will process each connection in a separate thread. An extra thread
will be printing to the screen all the activities received during the last 5 seconds.

# Router logs format
The client must be able to parse logs in the following format (see attached log

le):
```
device: 01-42--ae-3b-25
url: https://google.com/search?q=cars
timestamp: 1397564362
device: 45-60-bd-51-1e-fe
url: https://porntube.com/
timestamp: 1397558823
device: 33-24-d6-85-0a-b2
url: http://en.wikipedia.org/wiki/Special:Random
timestamp: 1397572541
```
The log 
le contains a set of internet browsing events composed of three
lines each. First line is the device MAC-address. The second line is the visited
website. The third line is the time in seconds since the UNIX epoch when the
event took place.

## Requirements:
- boost
- qmake binary (in the Qt distribution)

## Building:
```
qmake
make
```

_Using BOOST_PATH environment variable may be necessary to find boost libraries before calling qmake._

## Creating projects for Visual Studio:
```
qmake -tp vc -recursive
```

## Third party libraries used: ##
* **Boost**: 
  * **Boost::asio**: Cross-platorform network library.
  * **Boost::test**: Cross-platform testing framework.
* **Rapidjson**: Message parsing/formating. I used json format for extensibility.

## Tested in: ##
* Visual Studio 2013 32bits @ Windows 8.1 64bits
* gcc 4.9.0 64bits @ Archlinux 64bits
* gcc 4.6.0 32bits @ SailfishOS

## Running: ##
To run the server only execute the server binary.
To run the client: `client server_address log_file ...`