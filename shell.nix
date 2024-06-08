let pkgs = import <nixpkgs> {};
in pkgs.mkShell {
  buildInputs = with pkgs; [
  	qt6Packages.qtbase
  	meson
  	ninja
  	nlohmann_json
  	pkg-config
  ];
}
