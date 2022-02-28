# dtpcontrols


## Quickstart recipe for firmware developers & testers

The recipe below can be used for installing dtpcontrols and uhallibs onto dunedaq-v2.9.0, to obtain a working area.

```
source /cvmfs/dunedaq.opensciencegrid.org/setup_dunedaq.sh
setup_dbt dunedaq-v2.9.0
dbt-create.sh workDir
cd workDir/sourcecode
git clone https://github.com/DUNE-DAQ/dtpcontrols.git [ -b <tag> ]
git clone https://github.com/DUNE-DAQ/uhallibs.git
dbt-workarea-env
dbt-build.py
```

For more info on setup and build, see : 
https://dune-daq-sw.readthedocs.io/en/latest/packages/daq-buildtools/

