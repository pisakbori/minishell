0. practice microshell. find subject.
1. take 1 absolute path as arg, run it
2. take 2args, put pipe between them. like this: ./microshell ls "|" grep microshell

ls -l | grep '.c' | awk '{ print $9 }' | sort -r

3. modify split. to handle double quotes.
   when something enclosed in quotes, consider it as one unit and don't split. discard the quotes

cat | cat | | ls
bash: syntax error near unexpected token `|'

||
bash: syntax error near unexpected token `||'
