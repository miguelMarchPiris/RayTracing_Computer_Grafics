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

