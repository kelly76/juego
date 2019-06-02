#include"juego.h"

#include <iostream>
#include <string>

using namespace std;

Juego::Juego(Vector2f resolucion, string titulo){  //Constructor de la clase Juego
	game_over=false;
	fps =60;
	vidas=3;  //numero de vidas
	ventana1=new RenderWindow(VideoMode(resolucion.x,resolucion.y),titulo);  //abrimos una ventana para el juego
	ventana1->setFramerateLimit(fps);

	ventana1->setMouseCursorVisible(false);  //Hacer que no se vea el cursor del mouse

	for(int i=0;i<4;i++){
		slots_monsters[i]=false;  //indicamos que en los 4 espacios de la pantalla no hay enemigos
	}

	evento1=new Event;

	cargar_graficos();    //hacemos uso de esta funcion para cargar las imagenes

	reloj1=new Clock;     //en la variable reloj1 creamos un clock que nos servira como reloj
	tiempo1=new Time;     //en esta variable el Time nos retornara el tiempo transcurrido
	tiempo2=0;

	game_loop();          //llamamos a esta funcion cada vez que creemos una instancia de la clase Juego
}

void Juego::game_loop(){  //la funcion game_loop nos sirve para mantener el juego activo

	while(!game_over){    //mientras que la variable game_over no sea verdadera(true)

		*tiempo1=reloj1->getElapsedTime();   //obtenemos el tiempo transcurrido del reloj1

		if(tiempo1->asSeconds()>5+ tiempo2)  //si el tiempo1 en segundos es mayor al tiempo2 mas 5
		{
			tiempo2=tiempo1->asSeconds();    //a tiempo2 le asignamos el tiempo1 en segundos
			int resultado;
			resultado =rand()%100+1;         //este entero aleatorio nos sirve para crear o no enemigos

			if(resultado<30){
				//no creamos enemigos
			}
			else
			{
				bool espacio_disponible= false;  //booleano que utilizaremos para indicar si esta...
				                                 //...disponible el espacio de la pantalla en el que nos ubicamos
				for(int i=0;i<4;i++)
				{
					if(!slots_monsters[i])       //recorremos los espacios de la pantalla y si encuentra uno disponible...
					{
					       espacio_disponible = true;  //...cambiara espacio_disponible a true y...
						   break;                      //...dejaremos de rrecorrer los espacios
					}
				}
				if(espacio_disponible)
				{
					while (1)
					{
						int resultado = rand() % 3 + 0;  //variable diferente a la anterior, la usamos...
						                                 //...para recorrer aleatoriamente los espacios de la pantalla

						if (!slots_monsters[resultado])  //nos ubicamos en algun espacio disponible
						{
							monsters[resultado]= new Enemigo({(float)(200.0*resultado),300.0});  //creamos un enemigo y le indicamos su posicion
							break;
						}

					}
				}
			}
		}

		ventana1->clear();      //para limpiar la pantalla en cada vuelta

		procesar_eventos();     // llamamos a esta funcion para que se ejecute mientras el juego este activo

		ventana1->draw(spr_fondo); //muestra el fondo

		ventana1->draw(spr_mira);  //muestra la imagen de la mira

		ventana1->display();       //nos muestra la ventana

		if(vidas <1)               //si nuestro numero de vidas es menor a 1 el juego terminara
		{
			game_over=true;
		}
	}
}

void Juego::cargar_graficos(){  //cargamos  todas las imagenes del juego

	txt_fondo.loadFromFile("cementerio.JPEG");
	spr_fondo.setTexture(txt_fondo);
	//ajustamos el tamaño de la imagen de fondo a el tamaño de la ventana
    spr_fondo.setScale((float)ventana1->getSize().x/txt_fondo.getSize().x,(float)ventana1->getSize().y/txt_fondo.getSize().y);

	txt_mira.loadFromFile("mira.jpg");
	spr_mira.setTexture(txt_mira);


}

void Juego::procesar_eventos(){  //esta funcion actualiza el juego ante cualquier cambio o evento

	while(ventana1->pollEvent(*evento1))
	{
		switch(evento1->type)
		{
			case Event::MouseMoved:
				//a nuestra mira le pasa la posicion del mouse
				spr_mira.setPosition((Vector2f)Mouse::getPosition(*ventana1));
				break;
			case Event::Closed:
			    //para poder cerrar las ventanas
                exit(1);
                break;
			case Event::MouseButtonPressed:
                //si presionamos el boton del mouse
				FloatRect recta (spr_mira.getPosition(), (Vector2f)spr_mira.getTexture()->getSize()); //definimos la posicion de la mira y su tamaño en recta
				for(int i=0; i<4;i++)  //recorremos el arreglo de enemmigos
				{
					if(monsters[i])
					{
						if (monsters[i]->get_sprite().getGlobalBounds().intersects(recta));  //si el sprite del enemigo se intersecta con la recta es decir con la mira...
						{
							monsters[i]=NULL;                                                //...entonces ese enemigo pasa a ser NULL
						}
					}
				}
				break;
		}
	}
}



