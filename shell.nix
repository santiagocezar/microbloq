let
	pkgs = import <nixpkgs> {};
	lager = import (builtins.fetchGit {
		url = "https://github.com/arximboldi/lager";
		rev = "503ea6accc0ce6af683a207a9a02de4a9bf0bedc";
	});
in pkgs.mkShell {
	nativeBuildInputs = with pkgs; [
		libclang.python
		pkg-config
		meson
		ninja
		cmake
		clang-tools
	];
	buildInputs = with pkgs; [
		lager
		qt6Packages.qtbase
		nlohmann_json
	];
}
