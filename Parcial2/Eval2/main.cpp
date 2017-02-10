#include "VideoJuego.h"
#include "Almacen.h"
#include "GameFactory.h"

int main()
{
    GameFactory* gf = new GameFactory();
    VideoJuego* v1 = gf->createGame("Estrategia", VideoJuego::LUCHA, "myGame", 1);
    Estrategia v2 = *(Estrategia*)v1;
    VideoJuego* v3 = gf->createGame("Estrategia", VideoJuego::LUCHA, "thirdGame", 123);

    Almacen<VideoJuego> a;
    a.add(v1);
    a.add(&v2);
    a.add(v3);

    cout << a.findByName("thirdGame")[0]->getName();

    delete gf;
    delete v1;
    delete v3;
    gf = NULL;
    v1 = NULL;
    v3 = NULL;
}
