# RayDataEstudiants
Practica sobre l'algorisme Ray Tracing implementada per:
Francisco Barrio, Miguel March, Joan Travé i Marcos Plaza.

GiVD - P1
----------  
####Abstract
Durant aquesta pràctica hem desenvolupat els conceptes de Ray Tracing estudiats a l'assignatura, dividits en tres fases.

######Fase 1
En aquesta fase hem situat els diferents objectes (dels tipus que s'especifiquen més avall) a l'escena, tot establint
els límits d'aquesta. A més hem implementat la càrrega d'una escena a partir de dades proporcionades en un fitxer de text pla,
reescalant la mida dels objectes aixi com situant-los en la posició llegida.

######Fase 2
Un cop tenim els objectes ben plantejats, passem a donar un efecte d'iluminació empleant Blinn-Phong i mesurant la projecció 
de les ombres i reflexions respecte els objectes cap a l'escena (a l'hora de veure quin valor RGB donavem a cada píxel). A més hem afegit nous materials 
els quals es comporten de diferent manera envers la llum.

######Fase 3
En aquesta última fase, hem aplicat la técnica del mapejat UV per a poder posar una "textura o imatge" a sobre d'un pla afitat. Al mateix temps que calculavem 
la iluminació a l'escena (en cas d'haver interseccio amb algun objecte agafem i si es tracta de MaterialTextura agafarem els téxels corresponents).

######Preguntes

Fase 1:

Q: Com calcularàs el centre del teu objecte en l'escena virtual?\
A: El centre serà traslladant en tantes unitats com el punt minim dels seus limits

Q: Com calcularàs la seva escala?\
A: L'escalarem multiplicantlo per la relació entre el punt minim i maxim dels limits i la dimensió de l'escena.

Fase 2:

Q: En el cas que hi hagi un objecte entre la llum i el punt on s'està calculant la il·luminació, quina component de la fórmula de Blinn-Phong s'haurà de tenir en compte?\
A: Només s'haurà de tenir en compte la il·luminació ambient en aquest cas.

Q: Implementa Blinn-Phong per fases, raonant a cada resultat per què et donen les visualitzacions corresponents, tenint en compte que les esferes tenen com a Kd el color definit abans i una Ka = (0.2,0.2, 0.2), una Ks = (1.0, 1.0, 1.0) i una shineness de 10.0. Com hauries de modificar la teva paleta per a poder tenir Materials i no colors difusos? Comenta com has solucionat aquest problema a la pràctica.\
A: Hem triat una opció intermitja, hem fet que els rajos primaris (i els secundaris de menys de 5 rebots) prenen el color del background, i la resta prenen la intensitat ambient global.

Q: En afegir materials transparents, pots calcular les ombres segons el color del material transparent que traspassa la llum? Què has de modificar en la teva pràctica?\
A: El que hem d'afegir seria, al calcul del raig d'ombra, fer que retorni que no intersecta només si el material de l'objecte amb el que intersecta el raig és transparent.

####Features

- Figures
    - [x] Triangle 
        - Marcos
    - [x] Cilynder
        - Miguel
    - [x] Boundary Object
        - Marcos
- Blinn-Phong
    - [x] Light
        - Fran
    - [x] Basic Blinn-Phong
        - Fran
    - [x] Reflection
        - Fran i Miguel 
    - [x] Transparency
        - Fran i Miguel 
- Material
    - [x] Metal
        - Fran i Miguel
    - [x] Transparent
        - Fran i Miguel
    - [x] Texture
        - Marcos 
- Data 
    - [x] situacion en el mapa
        - Joan 
    - [x] textura en el plano
        - Joan i Marcos 
    - [x] nuevas escenas
        - Joan 

####Extensions
*(NOTA: Las extensiones de la práctica que hayáis implementado y que no estén listadas en el apartado anterior)*

- [x] Hem fet servir el métode conegut com Multisample anti-aliasing per tal de millorar la qualitat de la imatge, agafant valors
de píxels molt propers al valor del píxel que s'esta calculant en cada iteració i sumant-los per acabar
fent la mitjana entre el número de mostres. Tot i que és un métode de supersampling, amb tot el que aixó comporta (és més car computacionalment), hem trobat que 
ha suavitzat molt els contorns de cada figura i ha millorat molt la qualitat de la imatge.

[AFEGIR EXTENSIONS AQUI]

####Screenshots
*(NOTA: Capturas de pantalla de las pruebas que hayáis realizado)*

####Additional Information
*(NOTA: Horas de dedicación y problemas principales que hayáis tenido durante la realización de las prácticas)*

- [x] De la part de llegir dades no s'ha assolit tots els objectius (no s'ha arribat a llegir materials
a través del fitxer de dades), degut a falta de temps.