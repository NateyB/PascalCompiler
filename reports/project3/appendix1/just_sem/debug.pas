program fib(input, output);
  var a: integer; var p: integer;
  var numsArray : array [6..12] of integer;
  var q: real;

  procedure fib1(aLongInt : integer; b : real;
                c : integer; d: integer);
    begin
        if a <= 1 then fib := c
        else call fib (a - 1, c, b + c)
    end;

  procedure fib2(a : integer);
    var b : real; var c : real; var sum : integer;
    var b : real;
    procedure rawr3(b : real);
      var q : real;
      begin
        q := b + sum;
        call fib2(q)
      end;

    begin
      q := not 3;
      q := (3 < 4) and (3.6 < p);
      a := a - 1;
      call fib1(3.2, 1);
      sum := 1;
      c := b;
      while not (a > 0) do
        call rawr3(b * 4);
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
      if not (1 < 74) or 3 then p:=(1 > 2) and(3 < n)
        else p:=not 2;
      numsArray[3] := 15.56;
      q := q[4];
      q[4] := 12
    end;

  begin
    call init;
    call fib2;
    call rawr3(34, 56)
  end.
