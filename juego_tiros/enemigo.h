#pragma once
#include <SFML/Graphics.hpp>

#include <stdlib.h>
using namespace sf;
using namespace std;


class Enemigo {
	public:

		Enemigo(Vector2f posicion);  //constructor
		Sprite get_sprite();         //funcion que nos retorna el sprite del enemigo
		float get_seconds();         //funcion que nos retorna

	private:

		Texture txt_monster;
		Sprite spr_monster;

		Clock * reloj1;  //puntero de tipo clock que funciona como un reloj
		Time * tiempo1;  //puntero de tipo Time que recorre el tiempo transcurrido
};
