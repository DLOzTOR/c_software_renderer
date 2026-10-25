rm -fr ./out/*
cmake -S . -B ./out -G Ninja
cmake --build ./out