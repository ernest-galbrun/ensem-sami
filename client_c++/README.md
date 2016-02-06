# Cortex C++ Client
The purpose of the project is to develop a C++ library for requesting the position of the objects to the server of the motion vision Cortex. This library is built with [Boost.Asio](http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio.html) and [Boost.Thread](http://www.boost.org/doc/libs/1_60_0/doc/html/thread.html) so it should work both on linux or windows machine.

**This project is in development mode so everything is not yet ready and doesn't yet work.**

## 5 min quickstart
This section will be written once the first version of the project will be done.

## How does it work?
Well, well, well, so far in the project this is how we plan to develop.
![Class diagram](https://github.com/ernest-galbrun/ensem-sami/blob/client_c%2B%2B/client_c%2B%2B/design/class_diagram.png)

The CortexClient file represents the main class, it provides all the callable methods. For started, it creates an SocketBoost's instance which will initiate a connection to the server. Then the SocketBoost's instance will perform a UDP request to the remote server every second in order to keep the data updated. On server's response, the datas are sent to the SocketParser which will translate the bytes encoded data into an understandable format inside of the Data class. Finally, the Data class has 2 two methods in order to ensure a secure access and update with semaphore.

## Dependencies
- Boost.Asio - v 1.60
- Boost.Thread - v 1.60

## License
This directory gathers all the work done by Schwartz Nicolas and Cedrini Thomas for their research project at Télécom Nancy.
