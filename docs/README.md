# dtpcontrols


## Quickstart recipe for firmware developers & testers

Here is a recipe for installing dtpcontrols and uhallibs onto dunedaq-v2.9.0.

```
source /cvmfs/dunedaq.opensciencegrid.org/setup_dunedaq.sh
setup_dbt dunedaq-v2.9.0
dbt-create.sh workDir
cd workDir/sourcecode
git clone https://github.com/DUNE-DAQ/dtpcontrols.git -b python_fixes
git clone https://github.com/DUNE-DAQ/uhallibs.git
dbt-workarea-env
dbt-build.p
```

For more info on setup and build, see : 
https://dune-daq-sw.readthedocs.io/en/latest/packages/daq-buildtools/

