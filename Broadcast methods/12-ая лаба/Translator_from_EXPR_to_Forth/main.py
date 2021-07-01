# Пример программы (какой-то массив строк с инструкциями на языке EXPR)
program_example = \
    ['begin',
     'y:=3;',
     'x:=y+5;',
     'y1:=7-x;',
     'z:=3*y1;',
     'вывод(x+z);',
     'end']

program_on_Forth_beginning_part = \
    ['#( program_on_Forth_language \ Название программы',
     'NoActive \ Эта инструкция означает, что задание запускается вручную',
     '\ Далее создаём столько слов, сколько у нас переменных']

program_on_Forth_part_with_vars = []

program_on_Forth_output_part = \
    ['Action:',
     '    \ Далее выводим на экран всё то, что нужно вывести']

program_on_Forth_ending_part = [')#']

# Функция, которая переводит выражение языка EXPR в выражение языка FORTH
def From_EXPR_Command_To_Forth_Command(str):
    if ';' in str:
        str = str[:-1]  # Убираем символ ';' из конца строки, он нам уже не нужен
    expr_operation = ' '
    if '+' in str:
        expr_operation = '+'
    elif '-' in str:
        expr_operation = '-'
    elif '*' in str:
        expr_operation = '*'
    elif '/' in str:
        expr_operation = '/'
    vars_and_nums = str.split(expr_operation)
    if len(vars_and_nums) == 1:
        return vars_and_nums[0]
    result_command = vars_and_nums[1] + ' ' + vars_and_nums[0] + ' ' + expr_operation
    return result_command

# Функция, которая переводит вывод языка EXPR в вывод языка FORTH
def From_EXPR_output_To_Forth_output(str):
    output_expr = ((str.split('('))[1])[:-2]
    output_expr_on_Forth = From_EXPR_Command_To_Forth_Command(output_expr)
    output_command = ('    MSG: "{0} = %{1}%"'.format(output_expr, output_expr_on_Forth))
    return output_command

# Количество открытых на данный момент конструкций begin
statements_opened = 0

for line in program_example:
    if line == 'begin':
        statements_opened += 1
        continue
    if line == 'end':
        statements_opened -= 1
        continue
    if statements_opened > 0:
        if 'вывод' in line:
            program_on_Forth_output_part.append(From_EXPR_output_To_Forth_output(line))
        else:
            Var_and_Expr = line.split(':=')
            Forth_var_command = (': {0} {1} ;'.format(Var_and_Expr[0], From_EXPR_Command_To_Forth_Command(Var_and_Expr[1])))
            program_on_Forth_part_with_vars.append(Forth_var_command)

Result = []
for line in program_on_Forth_beginning_part:
    Result.append(line)
for line in program_on_Forth_part_with_vars:
    Result.append(line)
for line in program_on_Forth_output_part:
    Result.append(line)
for line in program_on_Forth_ending_part:
    Result.append(line)

print("Исходная программа на языке EXPR:\n")
for line in program_example:
    print(line)
print("\nЭта же программа на языке стековой машины (на языке Forth):\n")
for line in Result:
    print(line)

input()
