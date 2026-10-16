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
      generatedHeader = pkgs.stdenv.mkDerivation {
        pname = "radiiheader";
        version = "0.1.0";
        src = self;
        nativeBuildInputs = [ pkgs.gnumake pkgs.python3 ];
        buildPhase = ''
          make
          '';
        installPhase = ''
          mkdir -p $out
          cp shannonradiicli $out/
          '';
      };
      generatedScript = pkgs.stdenv.mkDerivation {
        pname = "tester";
        version = "0.1.0";
        src = self;
        nativeBuildInputs = [ pkgs.gnumake pkgs.python3 ];
        buildPhase = ''
          cd src
          make
          cd ..
          '';
        installPhase = ''
          mkdir -p $out
          cp src/shannonradiicli.py $out/
          '';
      };
    in
    {

      packages.default = pkgs.writeShellApplication {
        name = "shannonradiicli";
        runtimeInputs = [pkgs.uv];
        text = ''
          exec uv run "${generatedScript}/shannonradiicli.py" "$@"
          '';
      };

      apps.default = {
        type = "app";
        program = "${self.packages.${system}.default}/bin/shannonradiicli";
      };

    });
}
