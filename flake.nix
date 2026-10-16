{
  description = "Shannon Ionic Radii CLI";

  inputs = {
    nixpkgs.url = "https://channels.nixos.org/nixpkgs-unstable/nixexprs.tar.zst";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
  flake-utils.lib.eachDefaultSystem (system:
    let 
      pkgs = nixpkgs.legacyPackages.${system};
      generatedProgram = pkgs.stdenv.mkDerivation {
        pname = "shannonradiicli";
        version = "0.1.0";
        src = self;
        nativeBuildInputs = [ pkgs.gnumake pkgs.python3 ];
        buildPhase = ''
          cd cppsrc
          make
          cd ..
          '';
        installPhase = ''
          mkdir -p $out/bin
          cp cppsrc/shannonradiicli $out/bin/
          '';
      };
    in
    {
      packages.default = generatedProgram;

      apps.default = {
        type = "app";
        program = "${self.packages.${system}.default}/bin/shannonradiicli";
      };

    });
}
