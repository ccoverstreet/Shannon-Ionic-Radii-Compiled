{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "https://channels.nixos.org/nixpkgs-unstable/nixexprs.tar.zst";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
  flake-utils.lib.eachDefaultSystem (system:
    let 
      pkgs = nixpkgs.legacyPackages.${system};
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
