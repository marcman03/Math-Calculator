###!-------------------------------------------------------
###! CLASSE MATH_SESSIO
###!-------------------------------------------------------
###!
###!--------------
###1 Constructora
###!--------------
###!
#init S math_sessio
#S destroy
###!
###!
###!
###!--------------
###2 execute: assign
###!--------------
###!
#init S math_sessio
#init T token ASSIGNACIO
#init L list<token>
#il T
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token ASSIGNACIO
#init T2 token "x"
#init L list<token>
#il T1
#il T2
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#T2 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token ASSIGNACIO
#init T2 token "x"
#init L list<token>
#il T2
#il T1
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#T2 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T token BYEBYE
#init T1 token ASSIGNACIO
#init T2 token "y"
#init L list<token>
#il T
#il T1
#il T2
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T destroy
#T1 destroy
#T2 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T token BYEBYE
#init T1 token ASSIGNACIO
#init T2 token "y"
#init L list<token>
#il T2
#il T1
#il T
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T destroy
#T1 destroy
#T2 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T token 3
#init T1 token ASSIGNACIO
#init T2 token "y"
#init L list<token>
#il T2
#il T1
#il T
#S execp L
3
##3
#T destroy
#T1 destroy
#T2 destroy
#L destroy
#S destroy
###!
###!
#init S math_sessio
#init T1 token ASSIGNACIO
#init T2 token "x"
#init T3 token SUMA
#init T4 token "y"
#init L list<token>
#il T2
#il T1
#il T2
#il T3
#il T4
#S execp L
Error::math_sessio:52:Assignacio amb circularitat infinita.
##Error::math_sessio:52:Assignacio amb circularitat infinita.
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token ASSIGNACIO
#init T2 token "x"
#init T3 token SUMA
#init T4 token OBRIR_PAR
#init T5 token "y"
#init T6 token TANCAR_PAR
#init T7 token "z"
#init T8 token MULTIPLICACIO
#init L list<token>
#il T2
#il T1
#il T4
#il T5
#il T3
#il T7
#il T6
#il T8
#il T4
#il T5
#il T3
#il T7
#il T6
#il T8
#il T4
#il T5
#il T3
#il T7
#il T6
#il T8
#il T4
#il T5
#il T3
#il T2
#il T6
#S execp L
Error::math_sessio:52:Assignacio amb circularitat infinita.
##Error::math_sessio:52:Assignacio amb circularitat infinita.
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token ASSIGNACIO
#init T2 token "x"
#init T4 token "y"
#init L list<token>
#il T2
#il T1
#il T4
#S execp L
y
##y
#T1 destroy
#T2 destroy
#T4 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token ASSIGNACIO
#init T2 token "x"
#init T4 token "y"
#init L list<token>
#il T2
#il T1
#il T4
#S execp L
y
##y
#T1 destroy
#T2 destroy
#T4 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token ASSIGNACIO
#init T2 token "x"
#init T3 token DIVISIO
#init T4 token OBRIR_PAR
#init T5 token "y"
#init T6 token TANCAR_PAR
#init T7 token "z"
#init T8 token MULTIPLICACIO
#init L list<token>
#il T2
#il T1
#il T4
#il T5
#il T3
#il T7
#il T6
#il T8
#il T4
#il T5
#il T3
#il T7
#il T6
#il T8
#il T4
#il T5
#il T3
#il T7
#il T6
#il T8
#il T4
#il T5
#il T3
#il T7
#il T6
#S execp L
( y / z ) ^ 2 * y / z * y / z
##( y / z ) ^ 2 * ( y / z ) * ( y / z )
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token ASSIGNACIO
#init T2 token "x"
#init T3 token EXPONENCIACIO
#init T4 token "y"
#init T5 token OBRIR_PAR
#init T6 token TANCAR_PAR
#init T7 token "z"
#init T8 token DIVISIO
#init L list<token>
#il T2
#il T1
#il T4
#il T3
#il T5
#il T4
#il T8
#il T7
#il T3
#il T4
#il T6
#init T9 token 5
#init L1 list<token>
#il T4
#il T1
#il T9
#S execp L1
5
##5
#S execp L
5 ^ ( 5 / z ^ 5 )
##5 ^ ( 5 / z ^ 5 )
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#L destroy
#L1 destroy
#S destroy
###!
###!
###!
###!--------------
###3 execute: avaluacio
###!--------------
###!
#init S math_sessio
#init T1 token "x"
#init L list<token>
#il T1
#S execp L
x
##x
#T1 destroy
#L destroy
#S  destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token "x"
#init T4 token TANCAR_PAR
#init T5 token "2"
#init T6 token ASSIGNACIO
#init L list<token>
#il T1
#il T2
#il T3
#il T6
#il T5
#il T4
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token DESASSIGNACIO
#init T4 token TANCAR_PAR
#init T5 token "2"
#init T6 token "x"
#init L list<token>
#il T1
#il T2
#il T3
#il T6
#il T4
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T6 token "x"
#init L list<token>
#il T1
#il T6
#S execp L
Error::expressio:31:Error sintactic.
##Error::expressio:31:Error sintactic.
#T1 destroy
#T6 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token "x"
#init T4 token TANCAR_PAR
#init T5 token "2"
#init T6 token ASSIGNACIO
#init L1 list<token>
#il T1
#il T2
#il T3
#il T4
#init L2 list<token>
#il T3
#il T6
#il T5
#S execp L2
2
##2
#S execp L1
2.000000
##2.000000
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#L1 destroy
#L2 destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token "x"
#init T4 token TANCAR_PAR
#init T5 token 2
#init T6 token ASSIGNACIO
#init T7 token DIVISIO
#init T8 token 2.0
#init L1 list<token>
#il T1
#il T2
#il T3
#il T4
#init L2 list<token>
#il T3
#il T6
#il T5
#il T7
#il T8
#S execp L2
2 / 2.000000
##2 / 2.000000
#S execp L1
1.000000
##1.000000
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#L1 destroy
#L2 destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token VAR_PERCENTATGE
#init T4 token TANCAR_PAR
#init L1 list<token>
#il T1
#il T2
#il T3
#il T4
#S execp L1
%
##%
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#L1 destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token "x"
#init T4 token TANCAR_PAR
#init T5 token 2
#init T6 token ASSIGNACIO
#init T7 token DIVISIO
#init T8 token 2.0
#init T9 token VAR_PERCENTATGE
#init L1 list<token>
#il T1
#il T2
#il T9
#il T4
#init L2 list<token>
#il T3
#il T6
#il T5
#il T7
#il T8
#S execp L2
2 / 2.000000
##2 / 2.000000
#S execp L1
1.000000
##1.000000
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#L1 destroy
#L2 destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token VAR_PERCENTATGE
#init T4 token SUMA
#init T5 token "1"
#init T6 token TANCAR_PAR
#init L1 list<token>
#il T1
#il T2
#il T3
#il T4
#il T5
#il T6
#S execp L1
% + 1.000000
##% + 1.000000
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#L1 destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token "x"
#init T4 token TANCAR_PAR
#init T5 token 2
#init T7 token DIVISIO
#init T8 token 2.0
#init T9 token "y"
#init T10 token MULTIPLICACIO
#init L list<token>
#il T1
#il T2
#il T9
#il T10
#il T3
#il T7
#il T2
#il T5
#il T10
#il T8
#il T4
#il T4
#S execp L
y * x / 4.000000
##y * x / 4.000000
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#T10 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token "x"
#init T4 token TANCAR_PAR
#init T5 token 2
#init T7 token DIVISIO
#init T8 token 2.0
#init T9 token "y"
#init T10 token MULTIPLICACIO
#init T11 token ASSIGNACIO
#init L list<token>
#il T1
#il T2
#il T9
#il T10
#il T3
#il T7
#il T2
#il T5
#il T10
#il T8
#il T4
#il T4
#S execp L
y * x / 4.000000
##y * x / 4.000000
#init L1 list<token>
#il T3
#il T11
#il T5
#S execp L1
2
##2
#S execp L
y * 2.000000 / 4.000000
##y * 2.000000 / 4.000000
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#T10 destroy
#T11 destroy
#L destroy
#L1 destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token "x"
#init T4 token TANCAR_PAR
#init T5 token 2
#init T7 token DIVISIO
#init T8 token 2.0
#init T9 token "y"
#init T10 token MULTIPLICACIO
#init T11 token ASSIGNACIO
#init L list<token>
#il T1
#il T2
#il T9
#il T10
#il T3
#il T7
#il T2
#il T5
#il T10
#il T8
#il T4
#il T4
#S execp L
y * x / 4.000000
##y * x / 4.000000
#init L1 list<token>
#il T9
#il T11
#il T8
#S execp L1
2.000000
##2.000000
#S execp L
2.000000 * x / 4.000000
##2.000000 * x / 4.000000
#init L2 list<token>
#il T3
#il T11
#il T5
#S execp L2
2
##2
#S execp L
1.000000
##1.000000
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#T10 destroy
#T11 destroy
#L destroy
#L1 destroy
#L2 destroy
#S destroy
###!
###!
###!
###!--------------
###4 execute: unassign
###!--------------
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init L list<token>
#il T1
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init T2 token DESASSIGNACIO
#init L list<token>
#il T1
#il T2
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#T2 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init T2 token 2
#init L list<token>
#il T1
#il T2
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#T2 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init T2 token "v"
#init L list<token>
#il T2
#il T1
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#T2 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init T2 token "v"
#init T3 token DESASSIGNACIO
#init L list<token>
#il T1
#il T2
#il T3
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#T2 destroy
#T3 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init T2 token "v"
#init T3 token EXPONENCIACIO
#init T4 token "v"
#init L list<token>
#il T1
#il T2
#il T3
#il T4
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init T2 token "v"
#init T3 token ASSIGNACIO
#init T4 token 2
#init L list<token>
#il T1
#il T2
#il T3
#il T4
#S execp L
Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
##Error::math_sessio:51:La sintaxi de la comanda es incorrecta.
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init T2 token "v"
#init L list<token>
#il T1
#il T2
#S execp L
v
##v
#T1 destroy
#T2 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init T2 token "v"
#init T3 token ASSIGNACIO
#init T4 token "5"
#init L list<token>
#il T2
#S execp L
v
##v
#init L1 list<token>
#il T2
#il T3
#il T4
#S execp L1
5
##5
#S execp L
5
##5
#init L2 list<token>
#il T1
#il T2
#S execp L2
v
##v
#S execp L
v
##v
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#L destroy
#L1 destroy
#L2 destroy
#S destroy
###!
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init T2 token "v"
#init T3 token ASSIGNACIO
#init T4 token "x"
#init T5 token DIVISIO
#init T6 token "y"
#init T7 token RESTA
#init T8 token "z"
#init T9 token OBRIR_PAR
#init T10 token TANCAR_PAR
#init T11 token CANVI_DE_SIGNE
#init L list<token>
#il T2
#il T3
#il T4
#il T5
#il T6
#S execp L
x / y
##x / y
#init L1 list<token>
#il T4
#il T3
#il T6
#il T7
#il T9
#il T11
#il T8
#il T10
#S execp L1
y + z
##y + z
#init L5 list<token>
#il T4
#S execp L5
y + z
##y + z
#init L2 list<token>
#il T2
#S execp L2
( y + z ) / y
##( y + z ) / y
#init L3 list<token>
#il T8
#il T3
#il T11
#il T6
#S execp L3
- y
##- y
#S execp L2
0
##0
#S execp L5
0
##0
#init L4 list<token>
#il T1
#il T4
#S execp L4
x
##x
#S execp L2
x / y
##x / y
#S execp L5
x
##x
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#T10 destroy
#L destroy
#L1 destroy
#L2 destroy
#L3 destroy
#L4 destroy
#L5 destroy
#S destroy
###!
###!
###!
###!--------------
###5 end of sesion
###!--------------
###!
#init S math_sessio
#S eof
false
##false
#init T token BYEBYE
#init L list<token>
#il T
#S execp L

##
#S eof
true
##true
#T destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token "a"
#init T2 token ASSIGNACIO
#init T3 token OBRIR_PAR
#init T4 token "a"
#init T5 token SUMA
#init T6 token "b"
#init T7 token TANCAR_PAR
#init T8 token DIVISIO
#init T9 token 2
#init L1 list<token>
#il T1
#il T2
#il T3
#il T6
#il T5
#il T6
#il T7
#il T8
#il T9
#S execp L1
2 * b / 2
##2 * b / 2
#init T10 token BYEBYE
#init L2 list<token>
#il T10
#S execp L2

##
#S eof
true
##true
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#T10 destroy
#L1 destroy
#L2 destroy
#S destroy
###!
###!
###!
###!------
###6 dump
###!------
###!
#init S math_sessio
#S dumpp
% = 
##% = 
#S destroy
###!
#init S math_sessio
#init T1 token "v"
#init T2 token ASSIGNACIO
#init T3 token "5"
#init L list<token>
#il T1
#il T2
#il T3
#S execp L
5
##5
#S dumpp
% = 5 v = 5
##% = 5 v = 5
#T1 destroy
#T2 destroy
#T3 destroy
#L destroy
#S destroy
###!
#init S math_sessio
#init T1 token "v"
#init T2 token ASSIGNACIO
#init T3 token "5"
#init T4 token "x"
#init T5 token "y"
#init T6 token "z"
#init T7 token "t"
#init T8 token "u"
#init L list<token>
#il T1
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T4
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T5
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T6
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T7
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T8
#il T2
#il T3
#S execp L
5
##5
#L destroy
#S dumpp
% = 5 t = 5 u = 5 v = 5 x = 5 y = 5 z = 5
##% = 5 t = 5 u = 5 v = 5 x = 5 y = 5 z = 5
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#S destroy
###!
#init S math_sessio
#init T1 token "v"
#init T2 token ASSIGNACIO
#init T3 token "5"
#init T4 token "x"
#init T5 token "y"
#init T6 token "z"
#init T7 token "t"
#init T8 token "u"
#init L list<token>
#il T1
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T8
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T7
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T6
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T5
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T4
#il T2
#il T3
#S execp L
5
##5
#L destroy
#S dumpp
% = 5 t = 5 u = 5 v = 5 x = 5 y = 5 z = 5
##% = 5 t = 5 u = 5 v = 5 x = 5 y = 5 z = 5
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#S destroy
###!
#init S math_sessio
#init T1 token "v"
#init T2 token ASSIGNACIO
#init T3 token "5"
#init T4 token "x"
#init T5 token "y"
#init T6 token "z"
#init T7 token "t"
#init T8 token "u"
#init L list<token>
#il T6
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T4
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T7
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T1
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T8
#il T2
#il T3
#S execp L
5
##5
#L destroy
#init L list<token>
#il T5
#il T2
#il T3
#S execp L
5
##5
#L destroy
#S dumpp
% = 5 t = 5 u = 5 v = 5 x = 5 y = 5 z = 5
##% = 5 t = 5 u = 5 v = 5 x = 5 y = 5 z = 5
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#S destroy
###!
#init S math_sessio
#init T1 token "v"
#init T2 token ASSIGNACIO
#init T3 token "5"
#init T4 token "x"
#init T5 token "y"
#init T6 token "z"
#init T7 token "t"
#init T8 token "u"
#init T9 token SUMA
#init L list<token>
#il T1
#il T2
#il T3
#il T9
#il T4
#il T9
#il T5
#il T9
#il T6
#il T9
#il T7
#il T9
#il T8
#S execp L
5 + x + y + z + t + u
##5 + x + y + z + t + u
#S dumpp
% = 5+x+y+z+t+u v = 5+x+y+z+t+u
##% = 5+x+y+z+t+u v = 5+x+y+z+t+u
#init L1 list<token>
#il T6
#il T2
#il T4
#il T9
#il T5
#S execp L1
x + y
##x + y
#S dumpp
% = x+y v = 5+x+y+z+t+u z = x+y
##% = x+y v = 5+x+y+z+t+u z = x+y
#init T10 token DESASSIGNACIO
#init L2 list<token>
#il T10
#il T1
#S execp L2
v
##v
#S dumpp
% = x+y z = x+y
##% = x+y z = x+y
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#T10 destroy
#L destroy
#L1 destroy
#L2 destroy
#S destroy
###!
###!
###!
###!----------------
###7 apply all subst
###!----------------
###!
#init S math_sessio
#init E expressio
#S aasp E
NULLTOK
##NULLTOK
#E destroy
#S destroy
###!
#init S math_sessio
#init T1 token "x"
#init T2 token ASSIGNACIO
#init T3 token 5
#init L list<token>
#il T1
#il T2
#il T3
#S execp L
5
##5
#init T4 token "y"
#init L2 list<token>
#il T4
#init E expressio L2
#S aasp E 
y
##y
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#L destroy
#L2 destroy
#E destroy
#S destroy
###!
#init S math_sessio
#init T1 token "x"
#init T2 token ASSIGNACIO
#init T3 token 5
#init L list<token>
#il T1
#il T2
#il T3
#S execp L
5
##5
#init T4 token "x" 
#init L2 list<token>
#il T4
#init E expressio L2
#S aasp E 
5
##5
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#L destroy
#L2 destroy
#E destroy
#S destroy
###!
#init S math_sessio
#init T1 token "x"
#init T2 token ASSIGNACIO
#init T3 token 5
#init L list<token>
#il T1
#il T2
#il T3
#S execp L
5
##5
#init T4 token "x"
#init T5 token MULTIPLICACIO
#init T6 token "x"
#init L2 list<token>
#il T4
#il T5
#il T6
#init E expressio L2
#S aasp E 
5 * 5
##5 * 5
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#L destroy
#L2 destroy
#E destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token "x"
#init T4 token TANCAR_PAR
#init T5 token 2
#init T7 token DIVISIO
#init T8 token 2.0
#init T9 token "y"
#init T10 token MULTIPLICACIO
#init T11 token ASSIGNACIO
#init L1 list<token>
#il T3
#il T11
#il T5
#S execp L1
2
##2
#init L list<token>
#il T1
#il T2
#il T9
#il T10
#il T3
#il T7
#il T2
#il T5
#il T10
#il T8
#il T4
#il T4
#init E expressio L
#S aasp E
evalf ( y * 2 / ( 2 * 2.000000 ) )
##evalf ( y * 2 / ( 2 * 2.000000 ) )
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#T10 destroy
#T11 destroy
#L destroy
#L1 destroy
#E destroy
#S destroy
###!
#init S math_sessio
#init T1 token EVALF
#init T2 token OBRIR_PAR
#init T3 token "x"
#init T4 token TANCAR_PAR
#init T5 token 2
#init T7 token DIVISIO
#init T8 token 2.0
#init T9 token "y"
#init T10 token MULTIPLICACIO
#init T11 token ASSIGNACIO
#init L1 list<token>
#il T9
#il T11
#il T8
#S execp L1
2.000000
##2.000000
#init L2 list<token>
#il T3
#il T11
#il T5
#S execp L2
2
##2
#init L list<token>
#il T1
#il T2
#il T9
#il T10
#il T3
#il T7
#il T2
#il T5
#il T10
#il T8
#il T4
#il T4
#init E expressio L
#S aasp E
evalf ( 2.000000 * 2 / ( 2 * 2.000000 ) )
##evalf ( 2.000000 * 2 / ( 2 * 2.000000 ) )
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#T10 destroy
#T11 destroy
#L destroy
#L1 destroy
#L2 destroy
#E destroy
#S destroy
###!
#init S math_sessio
#init T1 token DESASSIGNACIO
#init T2 token "v"
#init T3 token ASSIGNACIO
#init T4 token "x"
#init T5 token DIVISIO
#init T6 token "y"
#init T7 token RESTA
#init T8 token "z"
#init T9 token OBRIR_PAR
#init T10 token TANCAR_PAR
#init T11 token CANVI_DE_SIGNE
#init L list<token>
#il T4
#il T5
#il T6
#init E expressio L
#S aasp E
x / y
##x / y
#init L1 list<token>
#il T4
#il T3
#il T6
#il T7
#il T9
#il T11
#il T8
#il T10
#S execp L1
y + z
##y + z
#S aasp E
( y + z ) / y
##( y + z ) / y
#init L3 list<token>
#il T8
#il T3
#il T6
#S execp L3
y
##y
#S aasp E
( y + y ) / y
##( y + y ) / y
#init L4 list<token>
#il T1
#il T4
#S execp L4
x
##x
#S aasp E
( y + y ) / y
##( y + y ) / y
#T1 destroy
#T2 destroy
#T3 destroy
#T4 destroy
#T5 destroy
#T6 destroy
#T7 destroy
#T8 destroy
#T9 destroy
#T10 destroy
#T11 destroy
#L destroy
#L1 destroy
#L3 destroy
#L4 destroy
#E destroy
#S destroy
