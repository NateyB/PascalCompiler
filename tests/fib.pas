program fib(input, output);
var n: integer;
var q: real;

function fib(a, b, c : integer) : integer;
begin
    if a = 0 then fib := c
    else fib := fib(a - 1, c, b + c)
end;

function fib2(a : integer) : integer;
var b, c, sum : integer;
begin
  a := a - 1;
  b := 0;
  sum := 1;
  c := b;
  while (a > 0) do
    begin
      a := a - 1;
      b := sum;
      sum := c + sum;
      c := b
    end;
  fib2 := sum;
end;

function init() : integer;
begin
  n := 12;
  q := 12
end;

begin
    init();
    writeln(fib2(n)*q)
end.
