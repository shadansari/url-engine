
## SYSTEM REQUIREMENTS
- Tested on Ubuntu 18.04
- Install libsml2-dev, if not already installed.

## BUILD
'make all' builds the 'url-engine' executable.
```
cd url-engine
make clean
make all
```
## RUN
```
url-engine <posix|self> configuration.xml urls.txt
```
- Only 'posix' matching algorithm is supported.
- If no matching algorithm (posix, self) is speficied, then 'url-engine' defaults to 'posix'.

## TEST
A simple unit test is available:
```
make test
```
