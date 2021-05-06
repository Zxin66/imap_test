# FPGA_map_tool

FPGA Logic Synthesis test.

---

### Folder Descriptions

* [doc/](doc/) folder: Stores some documents.
* [res/](res/) folder: Stored some results that from test.
* [src/](src/) folder: Stored our source codes.
* [test/](test/) folder: Stored out test codes.
* [data/](data/) folder: Stored some data that may be used.
* [config/](config/) folder: Stored some configure files.

---
### Benchmarks
you can also find the benchmarks introduce in [doc/benchmarks_intro.pdf](doc/benchmarks%20intro.pdf)
* [EPFL benchmarks](https://github.com/fpga-tool-org/benchmarks)
    - Suppport Formats
      - Verilog
      - VHDL
      - BLIF
      - AIGER
    - Contents
      - 10 arithmetic benchmarks
      - 10 random/control benchmarks
      - 3 MtM (more than ten million) gates benchmarks
* [Yosys benchmarks](https://github.com/fpga-tool-org/yosys-bench)
    - Suppport Formats
      - Verilog
      - VHDL
    - Contents
      - small benchmarks
      - large benchmarks
* [IWLS 2005](http://iwls.org/iwls2005/benchmarks.html)
    - Suppport Formats
      - Verilog
      - OpenAccess
    - Contents
      - 26 from OpenCores
      - 4 from Gaisler Research
      - 3 from Faraday Technology Corporation
      - 21 from ITC 99
      - 30 from ISCAS 85 and 89

---
### Environment

* OS: ubuntu 18.04 WSL(Windows Subsystem for Linux)
* Ram: 16GB
* cpu cores: 12
* g++ version: 7.5.0
* c++ std: 2017

---
### Build-Yosys

1. Setup our whole project
```
    git clone https://github.com/fpga-tool-org/fpga-map-tool.git
    cd fpga-map-tool
```

2. Install Logic Synthesis tool - [Yosys](src/yosys)
```
    sudo apt-get install build-essential clang bison flex \
	libreadline-dev gawk tcl-dev libffi-dev git \
    libboost1.71-dev libboost-system1.71-dev \
	graphviz xdot pkg-config python3 libboost-system-dev \
	libboost-python-dev libboost-filesystem-dev zlib1g-dev

    /* jump to the yosys fpga-map-tool/src folder*/
    cd src/yosys

    make config-clang

    mkdir build
    cd build
    make -f ../Makefile

    sudo make install -f ../Makefile
```

3. Download benchmarks for test, and we test [Yosys-bench](https://github.com/fpga-tool-org/yosys-bench) for now stage!
```
    /* jump to the  fpga-map-tool/data folder*/
    cd ../../../data
    git clone https://github.com/fpga-tool-org/yosys-bench.git
```
4. Now we can test the verilog file using yosys!
```
for asic example: 
    cd yosys-bench/verilog/benchmarks_small/
    /* there are many small RTL  filefolders, and choose one*/
    cd decoder
    /* you have to run the generate.py script to generate many decoder-verilog files， and choose one*/
    python3 generate.py
    /* now we can test the verilog with Yosys*/
    yosys
    read_verilog decode_3_0.v
    hierarchy -check
    proc; opt; fsm; opt; memory; opt
    techmap; opt
    dfflibmap -liberty ../../../celllibs/simple/simple.lib
    abc -liberty ../../../celllibs/simple/simple.lib
    clean
    /* write synthesized design*/
    write_verilog synth.v
```
---
### Build-iFPGA
```
1. cd src/iFPGA
2. mkdir build && cd build
3. cmake ..
4. make
5. sudo make install  # install ifpga to /usr/local/bin
6. ./test_mockturtle
7. ./test_demo
8. ifpga -i [input_path] -o [output_path]
```

--- 
### Example FLow
based on the ifpga and yosys is all installed success!

```
yosys
yosys> read_aiger [xxx.aig]
yosys> hierarchy -check
yosys> proc;opt
yosys> fsm;opt
yosys> memory;opt
yosys> ifpga -o ifpga_output.v -l ifpga_output.lut
```


---
### Regression

*We use python+tcl scripts for our daily regression!*

* PCL-test
```
  /* install tkinter for using python-tcl*/
  sudo apt-get install python3-tk
  
  /* then run!*/
  cd fpga-map-tool/test/pcl_test/ 
  python3 test_yosys_flow.py --style asic
  /* it will generate the log file and result files*/
  ls log/
  ls result/

  /* later ported to the server for daily build automatically*/
```

* Anlu-test
```
  /* Completed by Anlu!*/
```

---
### Code-review

*We temporarily use github to review our code!*

---
### Daily Build
*We use Jenkins for auto daily build and regression*

- Our Server: ubuntu 20.04.2 LTS
- RAM: 64GB
- cpu cores: 64

```
  
  /* isntall java for jenkins dependency*/
  sudo apt install openjdk-11-jdk
  /* check*/
  java -version

  /* install Weekly releaseed jenkins */
  wget -q -O - https://pkg.jenkins.io/debian/jenkins.io.key | sudo apt-key add -
  sudo sh -c 'echo deb https://pkg.jenkins.io/debian binary/ > /etc/apt/sources.list.d/jenkins.list'
  sudo apt-get update
  sudo apt-get install jenkins
  
  /* check*/
  systemctl start jenkins

  /* start jenkins*/
  open your browser, and input http://localhost:8080 to install plugins and config it!
```

