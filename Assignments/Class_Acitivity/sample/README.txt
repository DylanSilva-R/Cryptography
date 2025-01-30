sample.tar.gz

A file containing the input and results of a vignere encryption, where:
The encryption passed through plaintext into the cyphertext characters
 not found in the 56 character alphabet of lower/upper case letters otherwise
they are encrypted.

run0  -- a bash script
vigenere.cpp -- source code used to encrypt


FILE SET 0:
The key used was "wereandroid"
the alphabet used is the letters lowercase + " " ( a space) + uppercase
	see alpha_space.txt

input0.txt
cypher0.txt
recover0.txt
recover0_ignore.txt     -- contains recovered plaintext from input cypher if ignoring non alphabet characters
alpha_space.txt

FILESET 1:
The key used was "cypher" (quotes not included)
the alphabet used is more limited, all lowercase letters, alphalc26.txt

input1.txt
cypher1.txt
recover1.txt     -- contains recovered plaintext from input cypher.txt, passes non-alphabet characters through
alphalc26.txt
