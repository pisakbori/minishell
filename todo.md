<!-- 0. practice microshell. find subject.
1. take 1 absolute path as arg, run it
2. take 2args, put pipe between them. like this: ./microshell ls "|" grep microshell

ls -l | grep '.c' | awk '{ print $9 }' | sort -r

3. modify split. to handle double quotes.
   when something enclosed in quotes, consider it as one unit and don't split. discard the quotes

cat | cat | | ls
bash: syntax error near unexpected token `|'

||
bash: syntax error near unexpected token `||'

lsof -c sleep | grep pipe
 -->

touch tmp_x_file1
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
export PATH=$HOME
echo $PATH
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
unset PATH
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
echo 42
/bin/rm -f tmp_x_file1

cd -

unset PATH
echo $PATH
/bin/ls
echo 1
cd -
echo 42

mkdir tmp_path_test1 tmp_path_test2
printf '#include <unistd.h>\nint main(){write(1, \"1\\n\", 2);}' > tmp_path_test1/test1.c
gcc tmp_path_test1/test1.c -o tmp_path_test1/a.out
printf '#include <unistd.h>\nint main(){write(1, \"2\\n\", 2);}' > tmp_path_test2/test2.c
gcc tmp_path_test2/test2.c -o tmp_path_test2/a.out
export PATH=tmp_path_test1:tmp_path_test2
a.out
export PATH=tmp_path_test2:tmp_path_test1
a.out
/bin/rm -rf tmp_path_test1 tmp_path_test2

cd "cmds/"
/bin/ls

cd cmds/
/bin/ls

cd ./cmds/
/bin/ls

ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la >> out | cat << stop3
fe
wf
fwe
f
stop
dw
stop1
dwasd
stop2
cat Makefile | ls > out
cat out
/bin/rm -f out
