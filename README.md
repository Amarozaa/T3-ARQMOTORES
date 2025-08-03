# Prototipo de Roguelike

**Plataforma:** Unreal Engine 5  
**Lenguaje principal:** Blueprints / C++  
**Autores:** Amaro Zurita y Martín Avendaño 

## Descripcion General

Prototipo de roguelike en tercera persona hecho para la tarea 3 del ramo Arquitectura de motores de videojuegos CC5512 de la Universidad de Chile, inspirado en *Risk of Rain 2*. El jugador controla a un mago el cual debe de derrotar a enemigos que aparecen en oleadas para obtener mejoras, y eventualmente derrotar a un jefe final que aparece despues de cierto tiempo.

## Mecanicas principales implementadas

- **Proyectiles:** El jugador puede lanzar un hechizo el cual impacta a los enemigos.
- **Tipos de enemigos:** Existen 2 tipos de enemigos, aereos y terrestres, cada uno con diferentes mecanicas de ataque.
- **Oleadas de enemigos:** Los enemigos aparecen en oleadas cada cierto tiempo.
- **Mejoras:** El jugador puede recoger mejoras que le mejoran estadisticas al jugador(velocidad de ataque, velocidad de movimiento o daño) interactuando con cofres que aparecen en el mapa o al derrotar enemigos con cierta probabilidad.
- **Jefe final:** Aparece un jefe final al cabo de cierto tiempo, el cual debe ser derrotado para completar el nivel.

## Controles

- **Moverse:** WASD
- **Atacar:** Click izquierdo 
- **Mover camara:** Mover el raton
- **Interactuar:** E


## Aspectos tecnicos

- Se posee una clase base proyectil en C++ (BaseDeProjectile.cpp) la cual define la logica general de un proyectill,  de la cual despues hereda el Blueprint BP_MainAttack. Esto facilitaria el crear nuevos proyectiles a futuro simplemente creando Blueprints hijos de la clase base.
- Tambien se pose una clase en c++ (SpawnZone.cpp) la define un volumen de spawn mediante un UBoxComponent, desde el cual se generan posiciones aleatorias para instanciar actores (Blueprints) en tiempo de juego. Utiliza raycasts verticales para asegurar que los actores se coloquen sobre superficies válidas del entorno, evitando intersecciones. La clase permite ajustar fácilmente el tipo y cantidad de actores a spawnear desde el editor.

## Estructura del proyecto
```
T3_ARQ/
├── Content/
│   ├── Attacks/
│   │   ├── BP_FireProjectile (Blueprint Class)
│   │   └── BP_MainAttack (Blueprint Class)
│   │
│   ├── Characters/
│   │   ├── Boss_Enemy/
│   │   ├── FloorEnemy/
│   │   ├── FlyingEnemy/
│   │   ├── Mannequins/
│   │   └── Wizard/
│   │
│   ├── Input/
│   │   ├── Actions/
│   │   ├── Touch/
│   │   ├── IMC_Default (Input Mapping Context)
│   │   └── IMC_MouseLook (Input Mapping Context)
│   │
│   ├── LevelPrototyping/
│   │   ├── Decoration/
│   │   ├── Interactable/
│   │   ├── Items/
│   │   ├── Materials/
│   │   ├── Meshes/
│   │   ├── SpawnZones/
│   │   └── Textures/
│   │
│   ├── Maps/
│   │   ├── GameModes/
│   │   ├── Materials/
│   │   ├── MainMenu.umap
│   │   ├── Map1.umap
│   │   └── MapNight.umap
│   │
│   ├── MixedVFX/  ← Contiene varios efectos Niagara.
│   │
│   ├── ThirdPerson/
│   │   ├── Blueprints/
│   │   │   ├── BP_ThirdPersonCharacter
│   │   │   ├── BP_ThirdPersonGameMode
│   │   │   └── BP_ThirdPersonPlayerController
│   │   └── Lvl_ThirdPerson.umap
│   │
│   ├── UI/
│   │   ├── Assets/
│   │   └── [Varios Widget Blueprints]
│   │
│   ├── VFX/  ← Contiene varios efectos visuales diversos.
│   │
│   └── Widgets/
│       └── WBP_MainMenu (Widget Blueprint)
│
├── Config/
│   └── DefaultInput.ini
│
├── Source/
│   └── T3_ArQ/
│       ├── T3_ArQ.Build.cs
│       │
│       ├── Public/
│       │   ├── BaseDeProjectile.h
│       │   ├── LootChest.h
│       │   └── SpawnZone.h
│       │
│       └── Private/
│           ├── BaseDeProjectile.cpp
│           ├── LootChest.cpp
│           └── SpawnZone.cpp
│
├── T3_ARQ.uproject
└── README.md
```
Creditos:

Asset mago by MadTrollStudio: https://sketchfab.com/3d-models/low-poly-mage-rigged-free-10771a1d02a145df95824b483515eeb6

Asset esqueleto by vinrax: https://sketchfab.com/3d-models/skeleton-character-psx-ece576bbed4b4364911c7596d828a558

Mixed VFX by G.G.: https://www.fab.com/listings/6518971c-c8ca-47d7-8611-1ff068b78dd5

