#include "minishell.h"

/*unset détruit la ou les variables dont le nom a
été passé en argument $var.
à l'intérieur du fonction le comportement varie
suivant le type de variable qu'on veut détruire.
Si variable globale détruite depuis une fonction,
seule la variable locale sera détruite.
la variable globale gardera la valeur acquise avant
l'appel à unset
*/