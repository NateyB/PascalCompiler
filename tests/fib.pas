program fib(input, output);
var n, p: integer;
var q: real;
var useless_array : array [1..12] of integer;

function fib(a : integer; b, c : real) : real;
begin
    if a <= 1 then fib := c
    else fib := fib(a - 1, c, b + c)
end;

function fib2(a : integer) : integer;
var b, c, sum : integer;
begin
  a := a - 1;
  b := 0;
  sum := 1;
  c := b;
  while (not a < -1) do
    begin
      a := a - 1;
      b := sum;
      sum := c + sum;
      c := b
    end;
  fib2 := sum;
end;

procedure init();
begin
  n := 12;
  p := 12;
  useless_array[3] := 15;
  q := 12
end;

begin
    init;
    writeln(+fib(n, 0, 1)*q/p + 4);
    writeln(fib2(n));
    writeln(useless_array[3])
end.
