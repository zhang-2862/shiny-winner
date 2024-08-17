
namespace MySpace
{
int add(int x, int y) {
    return x + y;
}

double add(double x, int y) {
    return x + y;
}

double add(int x, double y) {
    return x + y;
}

int add(int x, int y, int z) {
    return x + y + z;
}

int add(double x, double y = 100.0) {
    return x + y;
}
} // end of namespace MySpace

    

