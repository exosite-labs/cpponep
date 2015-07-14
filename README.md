========================================
About cpponep
========================================
cpponep is C++ binding for Exosite One-Platform API. The API is exposed over 
HTTP in a JSON RPC style interface.  It is designed to run on *nix operating 
systems (such as Linux).

Tested on Ubuntu 14.04 with g++ 4.8.4

License is BSD, Copyright 2015, Exosite LLC (see LICENSE file)


========================================
Dependencies
========================================
cpponep depends on the following libraries, which need to be installed before
cpponep can be compiled:

--) cURLpp (version 0.7.3 or newer): http://curlpp.org/<br>
--) jsoncpp (version 1.6.4 or newer): https://github.com/open-source-parsers/jsoncpp/<br>


========================================
Quick Start
========================================

1) Build jsoncpp<br>
`$ cd [DIR_OF_JSONCPP]`<br>
`$ scons platform=linux-gcc check`<br>
`$ python amalgamate.py`<br>

NOTE: 'scons' and 'python' are required to build jsoncpp.

2) Copy source file and two header files to 'onepv1/src' and 'onepv1/include/json' respectively<br>
`$ cp dist/jsoncpp.cpp [DIR_OF_CPPONEP]/onepv1/src`<br>
`$ cp dist/json/json.h [DIR_OF_CPPONEP]/onepv1/include/json`<br>
`$ cp dist/json/json-forwards.h [DIR_OF_CPPONEP]/onepv1/include/json`<br>

3) Build cURLpp<br>
`$ cd [DIR_OF_CURLPP]`<br>
`$ ./configure`<br>
`$ make`<br>
`$ sudo make install`<br>

NOTE: 'libboost' and 'libcurl' are required to build cURLpp. Add /usr/local/lib
to /etc/ld.so.conf and run ldconfig if necessary.

4) Build cpponep<br>
`$ cd [DIR_OF_CPPONEP]/onepv1`<br>
`$ make`<br>

5) Run example<br>
`$ ./example`<br>


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
Release 0.2
----------------------------------------
--) add writegroup, usage, and recordbatch<br>
--) remove comment<br>
--) add writegroup example<br>

----------------------------------------
Release 0.1
----------------------------------------
--) initial version<br>


