{ pkgs ? import <nixpkgs> {}, }:

pkgs.stdenv.mkDerivation {
  name = "onkyo-ri-send-command";
  buildInputs = with pkgs; [
    (callPackage ./liblgpio.nix { })
  ];
}
