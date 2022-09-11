## Brainfuck-rt
Lightweight and fast brainfuck interpreter (runner) and translator (to C)

## Compile
```sh
# Clone the repo
git clone https://github.com/rilysh/brainfuck-rt.git
# Now run make
make
# For test
make test

# Be ensure you've installed `git` and `make` in your system
```

## Info
Interpreter: At first it read all the brainfuck instructions and temporarily saves all of them in an array, calculating instructions length and regarding this calculation, it starts to read each instruction by indexing the array. Areas like in a loop use a temporary array to calculate `[` and another array to match the previous array position with the index of the first array.

Translator: Same as interpreter, read all instructions and the length but instead of just matching, it uses 4 temporary integer variables for increment and decrement and writes all of them including the C main point snippet.
