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

lsof -c sleep | grep pipe

Test 78: ❌ cat <missing | echo oi
mini output = (minishell: oi)
bash output = (oi)

Test 79: ❌ cat <missing | cat <"./test_files/infile"
mini output = (minishell: hi hello world 42)
bash output = (hi hello world 42)

Test 80: ❌ echo <123 <456 hi | echo 42
mini output = (minishell: 42)
bash output = (42)

Test 131: ❌ cat <minishell.h|ls
mini output = (`MsfU %=~dU "V 8ϾTV L
V README.md a31V bash.supp bash_outfiles bonus bonus_bonus builtins echo extras local.supp loop.out manual_tests mini_outfiles os_specific outfiles pipes redirects syntax test_files tester wildcards)
bash output = (��T�U `MsfU 2��U ����U���uU %=~dU K���U a���U ��j�U #(��U #�+'�U #�B�V &=e;�U (��ۥU 1�� "V 6�ҧ�U 8ϾTV 8��O�U 922�CV B?�B5V C�ky-V C��U K^�0�U L
MV V N`��XU O���U README.md R��b�U S+[�U [��oU \�Yx�U a31V bX�U bash.supp bash_outfiles bonus bonus_bonus builtins c�D��U echo extras local.supp loop.out manual_tests mini_outfiles os_specific outfiles pipes redirects syntax t_���U test_files tester wildcards �4��U ���w�U �}�U �0���U ����LV �#�jU �(@8nU ��0*^U ��dYV �9��U ���GV �j���U ��x��U �Q�b�U �w��.V �V �
                                       ���U �a�BV �>@w�U ��̞#V �z� V ה��U ���>�U �9�bU ݜh�hU ��u�U �sh�U �kK�mU �
                                u8.V ���`gU �\*�JV �:���U �-U�U ��sF3V)
