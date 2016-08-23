program fib(input, output);
var n: integer;

function fib(a, b, c, d : integer) : integer;
begin
    if a = 0 then fib := c
    else fib := fib(a - 1, c, b + c, d + b + c)
end;

begin
    read(n);
    writeln(fib(n - 1, 0, 1, 0))
end.
