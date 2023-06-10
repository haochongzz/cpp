class BasePacket;
  int A = 1;
  int B = 1;

  function void print ();
    $display ("dummy display");
  endfunction
endclass



class DerivedPacket extends BasePacket;
endclass
