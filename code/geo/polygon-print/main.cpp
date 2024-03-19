/* 
 * Opis: Należy przekierować stdout do pliku i otworzyć go np. w przeglądarce.
 * \texttt{m} zwiększa obrazek, \texttt{d} zmniejsza rozmiar napisów/wierzchołków.
 */
#include "../point/main.cpp"

void polygon_print(vector<P> v, int r = 10) {
    int m = 350 / r, d = 50;
    auto ori = v;
    for (auto &p : v)
        p = P((p.x() + r * 1.1) * m, (p.y() + r * 1.1) * m);
    r = int(r * m * 2.5);
    printf("<svg height='%d' width='%d'><rect width='100%%' height='100%%' fill='white' />", r, r);
    int n = ssize(v);
    REP (i, n) {
        printf("<line x1='%Lf' y1='%Lf' x2='%Lf' y2='%Lf' style='stroke:black' />", v[i].x(), v[i].y(), v[(i + 1) % n].x(), v[(i + 1) % n].y());
        printf("<circle cx='%Lf' cy='%Lf' r='%f' fill='red' />", v[i].x(), v[i].y(), r / d / 10.0);
        printf("<text x='%Lf' y='%Lf' font-size='%d' fill='violet'>%d (%.1Lf, %.1Lf)</text>", v[i].x() + 5, v[i].y() - 5, r / d, i + 1, ori[i].x(), ori[i].y());
    }
    printf("</svg>\n");
}
