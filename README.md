

## BNF kod
```
<code> ::= <syntax> | <syntax> "\n" <code>
<syntax> ::= <whitespace> <syntax> | <loop> | <assignment> | <output>
<loop> ::= "while" <whitespace> <condition> <whitespace> "{\n" <code> "\n" <optwhitespace> "}" <whitespace>
<if> ::= "if" <whitespace> <condition> <whitespace> "{\n" <code> "\n" <optwhitespace> "}" <whitespace>
<assignment> ::= "int" <whitespace> <variable> <whitespace> "=" <whitespace> <expression> ";"
<output> ::= "print" <whitespace> <variable> ";" 
<condition> ::= <expression> <whitespace> <comparetor> <whitespace> <expression>

<whitespace> ::= " " <whitespace> | " "
<optwhitespace> ::= " " <optwhitespace> | ""

<expression> ::= <value> | <expression> <operator> <expression>

<value> ::= <number> | <variable>

<variable> ::= <letter> | <variable> <letter> | <variable> <digit>
<number> ::= <digit> | <digit> <number>
<comparetor> ::= "<" | ">" | "!=" | "==" | "<=" | ">="
<operator> ::= "+" | "-" | "*" | "/"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<letter> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z" 
```