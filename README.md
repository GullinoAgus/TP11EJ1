# TP11EJ1


Bienvenido al emulador Micro3000

Para no tener problemas, se pide mantener el orden en la carpeta resources, y que esta se encuentre en el directorio raiz del programa.
Es muy simple de utilizar, todas los botones tienen un texto que indica lo que realizan, en el caso de los pequeños botones que dicen b0 b1, etc son para realizar un toggle al bit x (b0 es bit 0 y asi) del puerto seleccionado por los botones grandes que dicen PUERTO A y PUERTO B. 
La estructura del micro en la imagen esta descrita por el siguiente arte ascii

               +-----------+
        -------|           |------- 0             b0
        -------|           |------- 0
        -------|           |------- 0
        -------|           |------- 0   Puerto B
        -------|           |------- 0
        -------|           |------- 0
        -------|           |------- 0
        -------|           |------- 0   _________ b7
        -------|           |------- 0             b0
        -------|           |------- 0
        -------|           |------- 0
        -------|           |------- 0   Puerto A
        -------|           |------- 0
        -------|           |------- 0
        -------|           |------- 0
        -------|           |------- 0             b7
               +-----------+
               
               
Para el caso del parpadeo, este responde a cualquier comando. El parpadeo se puede ver como una bandera que se levanta cuando se presiona el boton, y para bajarla hay que volverla a presiona, el estado de la bandera se ve en el boton. El parpadeo esta seteado para 1 segundo, pero con una constante de compilacion en el main.c se puede modificar.
Todos los pixel arts fueron dibujados por nuestro compañero gonzalo *Aplausos* muy bonitos.

Si de casualidad encontras algun bug, lo cual espero que no pase, pido piedad, quisimos hacer alta interfaz y salio muy bien, pero en una semana no llegamos a probar absolutamente todos los casos limites. Con suerto somos buenos programadores y el codigo no tiene problemas. Saludos y Kudos
