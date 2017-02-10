#pragma once

#include<string>
#include"ClonTemplate.h"
#include"mcheck.h"

using namespace std;

class VideoJuego
{
public:
    enum tipo{LUCHA=1, ARCADE=2, PLATAFORMA=3, GRAFICA=4, IDIOMAS=5, MUSICA=6};
    VideoJuego() = default;
    VideoJuego(string nombre, int num_serie, VideoJuego::tipo tipo_juego)
    : nombre(new string(nombre)), num_serie(new int(num_serie)), tipo_juego(new tipo(tipo_juego))
    {
    }
    VideoJuego(const VideoJuego &obj)
    {
        nombre = new string;
        num_serie = new int;
        tipo_juego = new tipo;
        *nombre = *obj.nombre;
        *num_serie = *obj.num_serie;
        *tipo_juego = *obj.tipo_juego;

    }
    virtual ~VideoJuego()
    {
      delete nombre;
      delete num_serie;
      delete tipo_juego;
      nombre = NULL;
      num_serie = NULL;
      tipo_juego = NULL;
    }
    string getName()
    {
        return *nombre;
    }
protected:
    string* nombre;
    int* num_serie;
    tipo* tipo_juego;
};

class Estrategia : public ClonTemplate<VideoJuego, Estrategia>
{
public:
    Estrategia(string nombre, int num_serie, VideoJuego::tipo tipo_juego, int number_of_players)
    {
        this->nombre = new string(nombre);
        this->num_serie = new int(num_serie);
        this->tipo_juego = new VideoJuego::tipo(tipo_juego);
        this->number_of_players = new int(number_of_players);
    }
    ~Estrategia()
    {
      delete number_of_players;
      number_of_players = NULL;
    }
protected:
    int* number_of_players;
};

class Aventura : public ClonTemplate<VideoJuego, Aventura>
{
public:
    Aventura(string nombre, int num_serie, VideoJuego::tipo tipo_juego, string rate_category)
    {
        this->nombre = new string(nombre);
        this->num_serie = new int(num_serie);
        this->tipo_juego = new VideoJuego::tipo(tipo_juego);
        this->rate_category = new string(rate_category);
    }
    ~Aventura()
    {
      delete rate_category;
      rate_category = NULL;
    }
protected:
    string* rate_category;
};

class Aprendizaje : public ClonTemplate<VideoJuego, Aprendizaje>
{
public:
    Aprendizaje(string nombre, int num_serie, VideoJuego::tipo tipo_juego, int num_niveles)
    {
        this->nombre = new string(nombre);
        this->num_serie = new int(num_serie);
        this->tipo_juego = new VideoJuego::tipo(tipo_juego);
        this->num_niveles = new int(num_niveles);
    }
    ~Aprendizaje()
    {
      delete num_niveles;
      num_niveles = NULL;
    }
protected:
    int* num_niveles;
};
