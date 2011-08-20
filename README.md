========================================
About cpponep
========================================
cpponep is C++ binding for Exosite One-Platform API. The API is exposed over 
HTTP in a JSON RPC style interface.  It is designed to run on *nix operating 
systems (such as Linux).

Tested on Ubuntu 11.04 with g++ 4.5.2

License is BSD, Copyright 2011, Exosite LLC (see LICENSE file)


========================================
Dependencies
========================================
cpponep depends on the following libraries, which need to be installed before
cpponep can be compiled:

--) cURLpp (version 0.7.3 or newer): http://curlpp.org/<br>
--) jsoncpp (version 0.6.0-rc2 or newer): http://sourceforge.net/projects/jsoncpp/<br>


========================================
Quick Start
========================================

1) Build jsoncpp<br>
$ cd [DIR_OF_JSONCPP]<br>
$ scons platform=linux-gcc check<br>

NOTE: 'scons' and 'python' are required to build jsoncpp.

2) Copy header files and generated json library to 'onepv1' folder<br>
$ cp -r include/json [DIR_OF_CPPONEP]/onepv1/include<br>
$ cp libs/linux-gcc-x.x.x/libjson_linux-gcc-x.x.x_libmt.a [DIR_OF_CPPONEP]/onepv1/lib/libjson.a<br>

3) Build cURLpp<br>
$ cd [DIR_OF_CURLPP]<br>
$ ./configure<br>
$ make<br>
$ sudo make install<br>

NOTE: 'libboost' and 'libcurl' are required to build cURLpp. Add /usr/local/lib
to /etc/ld.so.conf and run ldconfig if necessary.

4) Build cpponep<br>
$ cd [DIR_OF_CPPONEP]/onepv1<br>
$ make<br>

5) Run example<br>
$ ./example<br>


========================================
User Application
========================================
To add cpponep library to your own application:

1) Copy all items in 'include' to the include directory of application.<br>
2) Copy *.a in 'lib' to the library directory of application.<br>


========================================
Release Info
========================================
----------------------------------------
Release 0.1
----------------------------------------
--) initial version<br>


