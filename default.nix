{ pkgs ? import <nixpkgs> {}, }:
{
  myProject = pkgs.stdenv.mkDerivation {
    name = "onkyo-lgpio";
    buildInputs = with pkgs; [
      (callPackage ./lgpio.nix { })
    ];
  };
}
