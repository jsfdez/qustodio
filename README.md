# Qustodio test by Jesus Fernandez

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
To run the client simply: `server address log_file ...`