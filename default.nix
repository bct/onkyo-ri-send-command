{ pkgs ? import <nixpkgs> {}, }:

pkgs.stdenv.mkDerivation {
  name = "onkyo-ri-send-command";
  src = ./.;

  buildInputs = with pkgs; [
    (callPackage ./liblgpio.nix { })
  ];

  installPhase = ''
    mkdir -p $out/bin

    install -m 0755 onkyo-ri-send-command $out/bin
  '';
}
