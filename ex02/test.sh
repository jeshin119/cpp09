# /bin/bash
rm -f out
touch out
chmod +r out

# test 1
# subject test
input="8 9 * 9 - 9 - 9 - 4 - 1 +"

echo "=====================================================================" >> out
echo "test 1 : subject test" >> out

echo "=====================================================================" >> out

echo "$input" >> out
echo "---------------------------------------------------------------------" >> out
./RPN "$input" >> out 2>&1

echo >>out