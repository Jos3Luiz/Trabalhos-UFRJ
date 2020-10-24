#!/bin/sh

set -x

rm data.txt
./catalogo help

echo ""
echo "PiratasDoCaribe Pixar 3.1" | ./catalogo inserir

echo ""
echo "Avatar Pixar 1.1" | ./catalogo inserir

echo ""
echo "Carros2 Pixar 2.1" | ./catalogo inserir

echo ""
echo "Carros3 Pixar 3.1" | ./catalogo inserir

echo ""
echo "Carros2\nNetflix" | ./catalogo edicaoProdutora

echo ""
echo "Carros3\n4.1" | ./catalogo edicaoNota

echo ""
./catalogo exibir

echo ""
./catalogo buscaPorNota

echo ""
echo "Carros2" | ./catalogo buscaPorNome

echo ""
./catalogo exibir

echo ""
cat data.txt
