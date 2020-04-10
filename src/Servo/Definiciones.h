#ifndef DEFINICIONES_H
#define DEFINICIONES_H

namespace rapidez
{
	/// Tipo enumerado que representa la rapidez del cambio
	/// \param
	enum intervalo {LENTO = 500, MEDIO = 200, RAPIDO = 50, INSTANTANEO = 0};
}

namespace motor
{
	enum incremento {SUBIR = 1, BAJAR = 0};
}

namespace ardubot
{
	enum giro {SOBRE_EJE = 0, EN_MOVIMIENTO = 1};
}
#endif
