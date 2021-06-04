/*******************************************************************/
/* AUTOR: FRANCISCO JOSÉ LÓPEZ CARRILLO; FECHA_ENTREGA: 24/05/2020 */
/******************************************************************/
#include <C_Image.hpp>
#include <iostream>;
#include <cmath>;
#include <string>
#define _USE_MATH_DEFINES
using namespace std;
int Test(int argc, char **argv);

void rotacion(C_Image imagen1, double angulo, string str) {
	C_Image::IndexT row, col;
	C_Image::IndexT nAncho, nAlto;
	//Tratamos el angulo para que no de problemas. Aquí transformamos un angulo negativo en su equivalente positivo.
	if (angulo < 0.0) {
		angulo += 360;
	}
	if (angulo > 360) {
		angulo = fmod(angulo, 360);
		if (angulo < 0.0) {
			angulo += 360;
		}
	}
	//Pasamos todos los angulos en grados a radianes con sus correspondientes fórmulas para la posterior aplicacion.
	double convert = (angulo * 2 * 3.14159265 / 360);
	//para angulos de 0 a 90
	double convert090 = (angulo * 2 * M_PI / 360);
	//para cuando usamos angulos de 91 a 180 grados solo para uno de sus angulos, el de arriba.
	double angulo91180 = angulo - 90;
	double convert91180 = (angulo91180 * 2 * M_PI / 360);
	//para angulos de 181 a 270 grados
	double angulo181270 = angulo - 180;
	double convert181270 = (angulo181270 * 2 * M_PI / 360);
	//para angulo de 271 a 360
	double angulo360 = 360 - angulo;
	double convert360 = (angulo360 * 2 * M_PI / 360);

	//Esta formula la usamos para calcular el tamanyo que va a tener la nueva imagen tras haber introducido el angulo de rotacion
	double anguloR = fmod(angulo, 90);
	if (anguloR < 0.0) {
		anguloR += 90;
	}
	if (angulo == 90 || angulo == 180 || angulo == 270 || angulo == 360) {
		anguloR = 90;
	}
	double convertNuevaImagen = (anguloR * (M_PI / 2) / 90);
	double sinNewImage = sin(convertNuevaImagen);
	double cosNewImage = cos(convertNuevaImagen);
	if (angulo >= 0 && angulo <= 90 || angulo > 180 && angulo <= 270) {
		nAlto = ((sinNewImage * imagen1.LastRow()) + (cosNewImage * imagen1.LastCol()));
		nAncho = ((cosNewImage * imagen1.LastRow()) + (sinNewImage * imagen1.LastCol()));
	}
	else {
		nAncho = ((sinNewImage * imagen1.LastRow()) + (cosNewImage * imagen1.LastCol()));
		nAlto = ((cosNewImage * imagen1.LastRow()) + (sinNewImage * imagen1.LastCol()));
	}
	C_Print("La imagen introducia tiene las siguientes caracteristicas: \n");
	C_PrintNum("alto: ", imagen1.LastCol());
	C_PrintNum("ancho: ", imagen1.LastRow());
	C_Print("La nueva imagen tendra las siguientes caracteristicas: \n");
	C_PrintNum("Nuevo alto: ", nAlto);
	C_PrintNum("Nuevo ancho: ", nAncho);
	//Creamos la nueva imagen con las nuevas especificaciones
	C_Image imagen2(imagen1.FirstRow(), nAncho, imagen1.FirstCol(), nAlto);
	imagen1.Grey();
	long i = 1;
	long j = 1;
	double colorado = 0;
	double roware = 0;
	double cost = cos(convert);
	double sint = sin(convert);
	double sin90 = sin(convert090);
	double sin91180 = sin(convert91180);
	double cos91180 = cos(convert91180);
	double sin181270 = sin(convert181270);
	double cos181270 = cos(convert181270);
	double sin360 = sin(convert360);
	double anchoImg1 = imagen1.LastRow();
	double altoImg1 = imagen1.LastCol();
	int newRow, newCol;
	for(int k = 0; k <=1; k++){
	for (col = 1; col <= altoImg1; col++) {

		for (row = 1; row <= anchoImg1; row++) {
			//Formula para angulos de 0 a 90 grados
			if (angulo >= 0.0 && angulo <= 90.0) {
				roware = (col * sint) + (row * cost);
				colorado = col * cost - row * sint + sin90 * anchoImg1;
			}
			//formula para angulos de 91 a 180 grados
			if (angulo > 90.0 && angulo <= 180.0) {
				roware = (col * sint) + (row * cost) + sin91180 * anchoImg1;
				colorado = col * cost - row * sint + (cos91180 * anchoImg1 + sin91180 * altoImg1);
			}
			//formula de 181 a 270 grados
			if (angulo > 180.0 && angulo <= 270.0) {
				roware = (col * sint) + (row * cost) + (cos181270 * anchoImg1 + sin181270 * altoImg1);
				colorado = col * cost - row * sint + cos181270 * altoImg1;
			}
			//formula de 271 a 360 grados
			if (angulo > 270.0 && angulo <= 360.0) {
				roware = (col * sint) + (row * cost) + sin360 * altoImg1;
				colorado = col * cost - row * sint;
			}
			newRow = roware;
			newCol = colorado;

			if (newRow == 0) newRow = 1;
			if (newCol == 0) newCol = 1;
			imagen2(newRow, newCol) = imagen1(row, col);

		}

	}
	if (fmod(angulo, 90) == 0) {
		break;
	}
	// Aplicamos el filtro de la mediana si la foto no es 0,90,180,270,360... grados para eliminar el ruido.
	if (!k == 1) {
		C_Print("Aplicando filtro de la Mediana para eliminar el ruido... (Espere unos segundos)\n")
		imagen2.MedianFilter(imagen2, 3);
	}
}

	C_Print("La imagen ha sido rotada con exito...\n");
	C_Print("Guardando...\n");
	//Aqui le pongo el nombre a la imagen para que se guarde con el angulo que ha sido rotada.
	str = str.substr(0, str.find("."));
	str += "_Rotada_" + to_string(angulo) + ".bmp";
	const char* nombreFinal = str.c_str();
	imagen2.WriteBMP(nombreFinal);
	C_Print("Finalizado.\n");
	//Tras finalizar con exito dice el nombre de la nueva imagen
	C_Print("El nombre de la imagen es:");
	C_Print(nombreFinal);
	C_Print("\n");
}
void espejoVertical(C_Image imagen1, string str) {
	C_Print("La imagen introducia tiene las siguientes caracteristicas: \n");
	C_PrintNum("alto: ", imagen1.LastCol());
	C_PrintNum("ancho: ", imagen1.LastRow());
	C_Image imagen2(imagen1.FirstRow(), imagen1.LastRow(), imagen1.FirstCol(), imagen1.LastCol());
	for (int i = 1; i < imagen1.LastCol(); i++) {
		for (int j = 1; j < imagen1.LastRow(); j++) {
			imagen2(imagen1.LastRow() - j + 1, i) = imagen1(j, i);
		}
	}
	C_Print("Guardando.\n");

	str = str.substr(0, str.find("."));
	str += "_EspejoVertical.bmp";
	const char* nombreFinal = str.c_str();
	imagen2.WriteBMP(nombreFinal);
	C_Print("Finalizado.\n");
	//Tras finalizar con exito dice el nombre de la nueva imagen
	C_Print("El nombre de la imagen es:");
	C_Print(nombreFinal);
	C_Print("\n");
}
void espejoHorizontal(C_Image imagen1, string str) {
	C_Print("La imagen introducia tiene las siguientes caracteristicas: \n");
	C_PrintNum("alto: ", imagen1.LastCol());
	C_PrintNum("ancho: ", imagen1.LastRow());
	C_Image imagen2(imagen1.FirstRow(), imagen1.LastRow(), imagen1.FirstCol(), imagen1.LastCol());
	for (int i = 1; i < imagen1.LastCol(); i++) {
		for (int j = 1; j < imagen1.LastRow(); j++) {
			imagen2(j, imagen1.LastCol() - i + 1) = imagen1(j, i);
		}
	}
	C_Print("Guardando.\n");
	str = str.substr(0, str.find("."));
	str += "_EspejoHorizontal.bmp";
	const char* nombreFinal = str.c_str();
	imagen2.WriteBMP(nombreFinal);
	C_Print("Finalizado.\n");
	//Tras finalizar con exito dice el nombre de la nueva imagen
	C_Print("El nombre de la imagen es:");
	C_Print(nombreFinal);
	C_Print("\n");
}




int main(int argc, char **argv)
{
	//Rotación de imágenes
	printf("\nRotacion de imagenes...\n");
	C_Image imagen1;
	
	double angulo;
	string str;
	C_Print("Introduzca nombre de la imagen (con .bmp). Deje en blanco para imagen predeterminada.");
	C_Print("Si el archivo no existe el programa terminara.");
	getline(cin, str);
	if (str.length() == 0) {
		str = "SirPerro.bmp";
	}
	//Aquí introducimos el nombre de la imagen situado en la carpeta RUN. 
	printf("\nLeyendo la imagen...\n");
	const char* nombreImagen = str.c_str();
	imagen1.ReadBMP(nombreImagen);
	C_IfError(imagen1.Fail(), "Could not read the image file", return 1);
	C_Print("\n");
	C_Print("Imagen usada: ");
	C_Print(nombreImagen);
	C_Print("\n");
	C_Print("Elija una opcion.\n");
	C_Print("1. Rotacion sobre eje.");
	C_Print("2. Rotacion espejo Vertical.");
	C_Print("3. Rotacion espejo Horizontal.");
	C_Print("Defecto: Terminar ejecucion.");
	int opcion;
	C_Print("Su opcion:");
	cin >> opcion;
	C_Print("Opcion elegida: ");
	switch (opcion)
	{
	case 1:
		C_Print("Rotacion de imagenes sobre su eje.");
		printf("\nSeleccione el angulo de rotacion (en grados): \n");
		cin >> angulo;
		rotacion(imagen1, angulo, str);
		break;
	case 2: 
		C_Print("Modo espejo Vertical.");
		espejoVertical(imagen1, str);
		break;
	case 3: 
		C_Print("Modo espejo Horizontal.");
		espejoHorizontal(imagen1, str);
		break;
	default: 
		C_Print("Terminar la ejecucion.");
		C_Print("Terminado.\n");
		break;
	}
	
		return 0;
	//return Test(argc, argv);
}