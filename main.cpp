#include "FrontCompression.h"

int main(){
    FrontCompression frontCompression;
    frontCompression.compress("phonelist.txt");
    frontCompression.decompress("phonelist[compressed].txt");
    return 0;
}
