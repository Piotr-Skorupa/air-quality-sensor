# Air Quality Sensor
Home air quality sensor connected with Signomix platform.

Program is running as aqs-service on Raspberry Pi Zero and sends data to https://signomix.com/.

Get Signomix C++ header-only library from https://github.com/gskorupa/SignomixCPP.
Spdlog logging library: https://github.com/gabime/spdlog.
PMS air quality sensors library: https://github.com/fu-hsi/PMS.

### List of needed hardware:
1. Raspberry Pi Zero
2. Air quality sensor PMS7003
3. Adapter IDC 10pin 1,27mm - JST 1,25mm for PMS7003

### Building
First of all you need to install this packages on the new Raspberry
```bash
sudo apt install g++
sudo apt install cmake
sudo apt install libcurl4-gnutls-dev
sudo apt install libb64-dev
sudo apt-get install libboost-all-dev
```
Next you can create build directory and build the project
```bash
mkdir build
cd build
cmake ../
make
```
Now you can run air quality sensor service
```bash
./aqs-service
```
Service is logging directly to `/var/log/syslog`. To exit process, just kill it.
