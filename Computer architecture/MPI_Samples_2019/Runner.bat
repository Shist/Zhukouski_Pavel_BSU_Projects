set AppPath="%1"
set ProcessCount=8
start cmd /k "mpiexec -n %ProcessCount% %AppPath%"