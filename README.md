**! ! ! Reviving the repository on 2021-09-23 ! ! !**
> - Tested on `fishtank`, `flagtail` machine, using `/mnt/misc/sw/x86_64/Debian/10/root/gnu/6.10.08/bin/root` which can be loaded by `module load root/gnu/6.10.08`.
> - This repository is revived by replacing the [`master`](https://github.com/nscl-hira/E15190-Unified-Analysis-Framework) branch with an identical copy from K. Zhu's local copy/modification/version of the framework on `fishtank`.
> - This "K. Zhu's version" is frozen as the [`zhu`](https://github.com/nscl-hira/E15190-Unified-Analysis-Framework/tree/zhu) branch; the original version that was last updated in 2019 is frozen as the [`frozen_20190327`](https://github.com/nscl-hira/E15190-Unified-Analysis-Framework/tree/frozen_20190327) branch. Never modify these two branches from now on. Instead, clone a new branch and work on it if you really need to do so.
> - Not everything on "K. Zhu's version" is more up-to-date. In fact, [`zhu`](https://github.com/nscl-hira/E15190-Unified-Analysis-Framework/tree/zhu) branch is missing *a lot* of scripts, calibration files, etc. especially those that are related to HiRA detector. This is expected because I did *not* attempt to merge [`zhu`](https://github.com/nscl-hira/E15190-Unified-Analysis-Framework/tree/zhu) with the [previous `master`](https://github.com/nscl-hira/E15190-Unified-Analysis-Framework/tree/519af280a82b8085a98b961a253713c252cee242) in any sense, but to simply replace the master branch by whatever K. Zhu was using for neutron analysis.
> - We, of course, still have many of the "HiRA" versions sitting somewhere on `fishtank`, primarily created by S. Sweany, R. Wang and many others. These versions are not being handled or considered in any way yet.

# E15190-Unified-Analysis-Framework
A global unified analysis framework to analyze HiRAEVT raw data structures, produce calibrated data with new data structures and analyze calibrated data. The framework is designed for E15190 data structures.

Contributors: Daniele Dell'Aquila [1], Kuan Zhu, Fanurs C.E. Teh [2]

[1] dellaqui@nscl.msu.edu
[2] teh@frib.msu.edu

Table of contents
=================
<!--ts-->
* [Getting the code](#getting-the-code)
  * [Using git](#using-git)
  * [Downloading from Git Hub](#downloading-from-git-hub)
* [Setup and Configuration](#setup-and-configuration)
  * [Requirements](#requirements)
  * [Compile the Code](#compile-the-code)
  * [Configure the Framework](#configure-the-framework)
  * [Limitations](#limitations)
* [The E15190Reader Framework](#the-e15190reader-framework)
  * [Framework Description](#framework-description)
  * [Run the Code](#run-the-code)
  * [Run the Code on NSCL ember](#run-the-code-on-nscl-ember)
  * [Calibrated Output Data](#calibrated-output-data)
  * [Customized Methods](#customized-methods)
  * [How to add new features](#how-to-add-new-features)
  * [Extension to future experiments](#extension-to-future-experiments)
  * [Notes for Developers](#notes-for-developers)
  * [Example 1 Generating calibrated data](#example-1-generating-calibrated-data)
  * [Example 2 Loop on raw data](#example-2-loop-on-raw-data)
  * [Example 3 Loop on calibrated data](#example-3-loop-on-calibrated-data)
<!--te-->

## Getting the code
### Using git
The latest version of the code can be obtained by using the git command. This is possible after installing git on a linux machine (see https://git-scm.com/download/linux for further documentation on how to install git). Use the following command to download the framework:
````
$ git clone https://github.com/nscl-hira/E15190-Unified-Analysis-Framework.git
````
### Downloading from Git Hub
The code can be downloaded also frm the Git Hub web page at the link: https://github.com/dellaquilamaster/HiRAEVT, by
clicking on the "Clone or Download" button on the right side of the page and then "Download ZIP". It is possible to donwload also a previous release of the code. For a complete list of all the releases please visit: https://github.com/nscl-hira/E15190-Unified-Analysis-Framework.git.
## Setup and Configuration

### Requirements
The code is compiled using the g++ compiler.
In order to compile and run the code ROOT 6 is required (the program has been tested with version 6.04.02). Please note that, since the program uses advanced ROOT 6 features, it is not possible to run or compile it by using an installation of ROOT 5. Ensure ROOT 6 environment variables are correctly exported. Usually one can use the command "source /mnt/misc/sw/x86_64/Debian/8/root/gnu/x.xx.xx/bin/thisroot.sh" or type it in the ".bash" file.

### Compile the code
You may consider using ROOT's official docker image. This repository has been tested with ROOT 6.26.10 on Ubuntu 22.04. To use Docker image on a shared Linux server,
```
singularity build image.sif docker://rootproject/root:6.26.10-ubuntu22.04
```
This command will build a file named `image.sif` in current directory. To enter the container, simply do
```
singularity shell image.sif
```
Once you are inside the container, you may follow the instructions to compile using `make`, and to run calibration, e.g. `./exec_BuildCalibratedData 4100`. Using Docker image is not a must. Any other ROOT installation may get the job done too. However, Docker provides many benefits. Google to learn more about it.

To compile the code by using gcc compiler use the command:
````
$ make -jN
$ make install
````
where, in multi-cpu machines, N can be used to specify the number of core to use in the compilation and significantly speed up the procedure.
To proceed with a clean compilation run before the command:
````
$ make clean
````
or
````
$ make distclean
````
the latter will clear also shared libraries generated by the "install" option and stored in the directory "lib/".

### Configure the Framework
Most of the framework's features are configured by means of the following file:
````
config/HiRAEVT.conf
````
That contains file paths, experiment information and the paths to calibration files for each detector handled by the framework. Starting from 2022, this file is generated automatically from `config/HiRAEVT.conf.template` using `config/generate_from_template.py`. This reason for this change of usage is because in the old `config/HiRAEVT.conf` file, the paths were user-specific. So when it was being committed to GitHub by a user, all other users would have to modify the paths accordingly. Nowadays, user would instead run something like
```
cd config/
python3 generate_from_template.py \
-d /mnt/users/dr_example/E15190-Unified-Analysis-Framework/calibrations/ \
-o /mnt/users/dr_example/output_root_files/
```
Here, `-d` flag should be provided with the `calibrations/` directory, and `-o` should be provided with the destination directory for calibrated ROOT files. Once this script is run, `config/HiRAEVT.conf` will be generated from `config/HiRAEVT.conf.template`.

## The E15190Reader Framework

### Framework Description
The framework provides a series of tools to easily handle data of the E15190 experiment, with HiRAEVTMapper data structures, by including all the existing calibrations and detector analysis features. The framework can be used by implementing individual programs, which typically make use of methods of a main class called E15190Reader. The framework is fully versatile since it allows to include any possible combination of existing detectors in the analysis, and any possible combination of required calibrations. Calibrations are automatically retrieved from the corresponding files (usually located in the "calibration" sub-folder, as configured run-by-run in the "config/HiRAEVT.conf" file, and depending on the required combination of detectors). The framework includes 3 main features that are here summarized:  
a) Looping on previously existing raw data  
b) Building a new tree with calibrated data structures  
c) Looping on previously built calibrated data tree  
For a) and c) cases, the user should usually write his own main program following the examples, respectively, given by exec_LoopOnData.cpp and exec_LoopOnCalibratedData.cpp. The core of the main program is usually implemented as a method of the E15190Reader main class. One can use the example provided by the template methods E15190Reader::LoopOnData(const char \*, Long64_t) and E15190Reader::LoopOnCalibratedData(const char \*, Long64_t), located in E15190Reader.cpp, respectively for cases a) and c). It is convenient to store the implementation of additional methods by the user in the file E15190ReaderCustomized. This allows to more easier update the program to a future version, restoring all the customized methods already implemented by the user. The case b) is usually standard and a basic implementation is provided in the main program exec_BuildCalibratedData.cpp.

### Run the code
Assuming that the user has created a main program called exec_TheMainProgram.cpp, which receives a series of input via the linux shell called input_1, input_2, ..., input_N. After compilation (see the Section "Compile the Code"), the user can simply launch the program as a normal linux program:
````
$ ./exec_TheMainProgram.exe output_1 output_2 ... output_N
````
Note that the executable file is automatically produced by the compilation procedure only when the main program file is named as "exec_\*.cpp" and that its extension is ".exe".

### Run the code on NSCL ember
To run the code in sbatch mode, e.g. in NSCL ember, use the following command (again making the same assumption of the previous section):
````
$ run_LaunchInEmber exec_TheMainProgram.exe output_1 output_2 ... output_N
````

