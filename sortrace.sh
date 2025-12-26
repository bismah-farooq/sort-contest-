echo Generating 100000 random numbers
sleep 1
./generate 100000 -100000 100000
sleep 1
echo Starting system sort
sleep 1
{ time sort -n numbers.dat > systemsort.out; } 2>&1>> sortrace.log
sleep 1
echo Starting mysort
sleep 1
{ time ./mysort numbers.dat sort.out; } 2>&1>> sortrace.log
sleep 1
wc mysort.out
sort -c -n mysort.out 2>> sortrace.log


tail -f sortrace.log
