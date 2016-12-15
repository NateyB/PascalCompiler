program fib(input, output);
  var a: integer; var p: integer;
  var numsArray : array [6..12] of integer;
  var q: real;

  procedure fib1(aLongInt89 : integer; b : real; c : real);
    begin
        if a <= 1 then b := c
        else call fib1 (a - 1, c, b + c)
    end;

  procedure fib2(a : integer);
    var b : real; var c : real; var sum : integer;
    procedure rawr3(b : integer);
      var q : integer;
      begin
        q := b + 14;
        call fib2(b*22 + 47)
      end;

    begin
      a := a - 1;
      b := 0.5;
      sum := 1;
      c := b;
      while (a > 0) do
        begin
          a := a - 1;
          b := 3.5/4.4;
          sum := 15 + 19*37;
          c := b
        end;
      numsArray[9] := sum
    end;

  procedure init;
    begin
      p := 12;
      if (1 > 2) or (3 < 4) then p := 12
      else p := 14;
      numsArray[6] := 15 div 56;
      p := 2*p + numsArray[4] mod 16;
      q := 12.37
    end;

    begin
      call init;
      call fib2(15)
    end.
