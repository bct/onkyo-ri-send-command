{ stdenv
, fetchFromGitHub
}:

stdenv.mkDerivation rec {
  pname = "liblgpio";
  version = "0.2.2";

  src = fetchFromGitHub {
    owner = "joan2937";
    repo = "lg";
    rev = "v${version}";
    sha256 = "088nmmnlj6472a3g4mpzr9ag34wj8y0jhgazabw9if0cw5blnsgp";
  };

  buildPhase = ''
    make lib
  '';

  installPhase = ''
    mkdir -p $out/include
    mkdir -p $out/lib
    mkdir -p $out/man3

    install -m 0644 lgpio.h $out/include

    install -m 0755 liblgpio.so.1 $out/lib
    ln -s liblgpio.so.1 $out/lib/liblgpio.so

    install -m 0644 lgpio.3 $out/man3
  '';

  meta = {
    description = "lgpio is a library for Linux Single Board Computers (SBC) which allows control of the General Purpose Input Outputs (GPIO)";
    homepage = "http://abyz.me.uk/lg/lgpio.html";
  };
}
