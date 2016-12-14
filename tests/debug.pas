program fib(input, output);
var n: integer; var p: integer;
var numsArray : array [6..12] of integer;
var q: real;

  procedure fib(a : integer; b : real; c : real);
    begin
        if a <= 1 then fib := c
        else call fib (a - 1, c, b + c)
    end;

  procedure fib2(a : integer);
  var b : integer; var c : real; var sum : integer;
    procedure rawr3(b : real);
      var q : integer;
      begin
        q := b + 2.0;
        call fib2(q)
      end;
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
      fib2 := sum
    end;

  procedure init;
  begin
    n := 12;
    if (1 and 2) or 3 then p := 12
    else p := 14;
    numsArray[3] := 15.56;
    q := q[4];
    q[4] := 12
  end;

  begin
    call init;
    call fib2;
    call rawr3(34)
  end.
