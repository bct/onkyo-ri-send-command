{ stdenv
, fetchFromGitHub
}:

# C libraries & daemon for pigpio
stdenv.mkDerivation rec {
  pname = "lgpio";
  version = "0.2.2";

  src = fetchFromGitHub {
    owner = "joan2937";
    repo = "lg";
    rev = "v${version}";
    sha256 = "088nmmnlj6472a3g4mpzr9ag34wj8y0jhgazabw9if0cw5blnsgp";
  };

  buildPhase = ''
    make lib rgpiod rgs
  '';

  installPhase = ''
    mkdir -p $out/bin
    mkdir -p $out/include
    mkdir -p $out/lib
    mkdir -p $out/man1
    mkdir -p $out/man3

    install -m 0644 lgpio.h $out/include
    install -m 0644 rgpio.h $out/include

    install -m 0755 liblgpio.so.1 $out/lib
    install -m 0755 librgpio.so.1 $out/lib
    ln -s liblgpio.so.1 $out/lib/liblgpio.so
    ln -s librgpio.so.1 $out/lib/librgpio.so

    install -m 0755 rgpiod $out/bin
    install -m 0755 rgs $out/bin

    install -m 0644 rgpiod $out/man1
    install -m 0644 rgs $out/man1

    install -m 0644 lgpio.3 $out/man3
    install -m 0644 rgpio.3 $out/man3
  '';

  meta = {
    description = "lgpio is a library for Linux Single Board Computers (SBC) which allows control of the General Purpose Input Outputs (GPIO)";
    homepage = "http://abyz.me.uk/lg/lgpio.html";
  };
}
