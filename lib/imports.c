#include <emscripten.h>
#include <stdio.h>

int main() {

    printf("WASM Ready\n");

    emscripten_run_script("console.log('Hello from C')");
    return 1;
}
