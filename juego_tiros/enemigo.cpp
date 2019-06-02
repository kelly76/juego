#include"enemigo.h"

#include<stdlib.h>

using namespace std;

Enemigo::Enemigo(Vector2f posicion)
{
	int numero_enemigo;
	numero_enemigo =rand()% 3 + 1;  //se escoge aleatoriamente un numero entre el 1 y el 3

	string path;

	path= "monster" + to_string(numero_enemigo)+ ".JPEG";  //escogemos la imagen del enemigo utilizando el numero aleatorio
    txt_monster.loadFromFile(path);
	spr_monster.setTexture(txt_monster);

	spr_monster.setPosition(posicion);  //ubicamos el sprite del enemigo en la posicion que obtuvimos del constructor

	reloj1 = new Clock;
	tiempo1 = new Time;
	*tiempo1 =reloj1->getElapsedTime();

}

Sprite Enemigo::get_sprite(){  //retornamos el sprite del enemigo
	return spr_monster;
}

float Enemigo::get_seconds(){  //obtenemos el tiempo1 en segundos

	*tiempo1 = reloj1->getElapsedTime();

	return tiempo1->asSeconds();
}
