NUM_NODES = 10
WORLD_SIZE = 1000


buildall: fsharp cpp racket csharp java haskell ocaml lisp rust go gccgo d nim oraclejava crystal

fsharp: fs.fs
	fsharpc fs.fs

cpp: cpp.cpp
	g++ cpp.cpp -std=c++14 -march=native -Wall -Wextra -Wshadow -O9 -march=native -o cpp

racket: rkt.rkt
	raco exe rkt.rkt

csharp: cs.cs
	mcs -unsafe cs.cs; mono -O=all --aot ./cs.exe

oraclejava: ojv.java
	/usr/bin/oraclejavac ojv.java

java: jv.java
	javac jv.java

haskell: hs.hs
	ghc hs.hs -O3

haskellprof: hs.hs
	ghc hs.hs -O3 -prof -fprof-auto -caf-all -fforce-recomp -rtsopts

ocaml: ml.ml
	ocamlfind ocamlopt -linkpkg -package unix -noassert -unsafe -fno-PIC -nodynlink -inline 100 -o ml ml.ml

lisp: lisp.lisp
	sbcl --core /usr/local/lib/sbcl/sbcl.core --load lisp.lisp --non-interactive

rust: rs.rs
	rustc rs.rs --opt-level=3

rust_unsafe: rs_unsafe.rs
	rustc rs_unsafe.rs --opt-level=3	

go: go.go
	go build go.go

gccgo: gccgo.go
	gccgo -O3 -o gccgo gccgo.go

d: d.d
	ldc2 d.d -ofd -O3 -release -inline -boundscheck=off

crystal: crystal.cr
	crystal build crystal.cr --release

nim: nim.nim
	nim c --cc:clang --passC:-march=native -d:release nim.nim

graphbuilder: mkgraph.go
	go build mkgraph.go

graph: graphbuilder
	./mkgraph -places=$(NUM_NODES) -worldsize=$(WORLD_SIZE) > agraph
