# 📊 APE 2 — Simulador de defensa de torres con colas y pilas

Bienvenidos al repositorio oficial de la **Actividad Práctica Experimental 2 (APE 2)** para la asignatura de **Estructuras de Datos**

---

## 📌 ¿De qué trata el proyecto?

Este proyecto implementa un simulador simplificado de un juego de defensa de torres, aplicando **colas** y **pilas** como estructuras lineales especializadas.

El sistema integra dos mecanismos principales:

1. **Colas (Queue):** Gestionan el movimiento de los enemigos a lo largo de una **ruta predefinida** mediante una **cola circular** que actualiza el estado (PV) de cada enemigo tras cada quantum de tiempo, y gestionan el orden de las oleadas.
2. **Pilas (Stack):** Implementan el historial de colocación y mejora de torres, permitiendo **deshacer** y **rehacer** acciones del jugador mediante dos pilas complementarias.

Por requisito obligatorio del caso de estudio, la clase que modela al enemigo se llama `Cozy`. El proyecto se implementa **en Java y en C++** (mismo diseño, portado entre lenguajes), y **toda la interfaz es por consola** (sin ventanas ni gráficos).

---

## 🎯 Objetivos

* **General:**
  * Desarrollar habilidades en el trabajo con listas secuenciales.

* **Específicos:**
  * Implementar una cola circular que gestione el movimiento y la actualización de PV de los enemigos a lo largo de la ruta predefinida.
  * Implementar un sistema de pilas para el historial de colocación/mejora de torres con funciones de deshacer y rehacer.
  * Comparar la implementación de pilas y colas utilizando las clases e interfaces que provee Java (`Stack`, `Deque`, `ArrayDeque`, `Queue`, `LinkedList`).
  * Diseñar y documentar formalmente el TDA correspondiente (estado, operaciones, invariantes).
  * Elaborar el informe técnico con el diagrama de clases UML y las pruebas de escritorio del sistema.

---

## 🧠 ¿Cómo diseñamos los TDAs y Estructuras?

Seguimos la metodología formal de análisis de TDA vista en clase: **estado del sistema → operaciones del TDA → invariantes → desarrollo de clases**.

### 1. TDA Cola de enemigos (movimiento y oleadas)

**Estado del sistema:**
- `Cozy`: `pv`, `pvMax`, `indiceRuta`, `velocidad`, `recompensa`.
- `colaCircular`: enemigos activos actualmente en la ruta.
- `colaOleadas`: oleadas pendientes de introducir, en orden.
- `Mapa.ruta`: ruta predefinida (fija) que siguen todos los enemigos.

**Operaciones del TDA:**

| Operación | Descripción |
| :--- | :--- |
| `encolar(Cozy)` | Ingresa un enemigo a la cola circular de la ruta |
| `actualizarQuantum()` | Aplica el daño de las torres en rango y avanza cada `Cozy` un paso en la ruta predefinida |
| `retirarSiMuere(Cozy)` | Excluye de la cola al enemigo cuyo `pv` llega a 0 |
| `siguienteOleada()` | Extrae la siguiente oleada de `colaOleadas` |

**Invariantes:**
1. Un `Cozy` permanece en la cola circular únicamente mientras `pv > 0`.
2. El orden de las oleadas respeta estrictamente FIFO.
3. La ruta es fija durante toda la partida; la posición de un `Cozy` en ella nunca retrocede.

### 2. TDA Historial de comandos (pilas de deshacer/rehacer)

**Estado del sistema:**
- `pilaDeshacer`: comandos de colocación/mejora ya ejecutados.
- `pilaRehacer`: comandos deshechos, disponibles para reaplicar.

**Operaciones del TDA:**

| Operación | Descripción |
| :--- | :--- |
| `registrar(ComandoTorre)` | Apila un comando recién ejecutado en `pilaDeshacer` |
| `deshacer()` | Extrae de `pilaDeshacer`, revierte el efecto y apila el comando en `pilaRehacer` |
| `rehacer()` | Extrae de `pilaRehacer`, reaplica el efecto y vuelve a apilar en `pilaDeshacer` |

**Invariantes:**
1. Un mismo comando no puede existir simultáneamente en ambas pilas.
2. `rehacer()` solo es válido si `pilaRehacer` no está vacía.
3. Todo `registrar()` nuevo vacía `pilaRehacer` (se pierde el "futuro" deshecho, igual que en cualquier editor de texto).
4. Una torre nunca puede colocarse sobre una casilla ya ocupada por otra torre.

---

## 👥 Equipo de Trabajo

Reparto por lenguaje: el par **Java** (Chalco y Tacuri) y el par **C++** (Tisalema y Silva) construyen el mismo programa completo — no se separa por estructura de datos (cola/pila), sino por archivo, dentro de un solo proyecto por lenguaje.

| Integrante | Rol | ¿Qué hace en el proyecto? |
| :--- | :--- | :--- |
| **Cunalata Mendoza Damian Alexander** | Líder Técnico & Integración | Gestión del repositorio en GitHub, ensambla `GestorJuego`/`Main` en Java, arma el menú de consola completo, comparación de implementaciones Java (`Stack` vs `ArrayDeque`, `LinkedList` vs `ArrayDeque`) |
| **Chalco Tasna Kenneth Mateo** | Programador Java | `Coordenada`, `Cozy`, `CatalogoEnemigos`, `Oleada`, `GestorOleadas`, `ColaEnemigos` (cola circular) |
| **Tacuri Santillan Mónica Sara** | Programadora Java | `Torre`, `TorreArquero`, `TorreCanon`, `CatalogoTorres`, `ComandoTorre` (+ subtipos), `HistorialComandos`, `Mapa` |
| **Tisalema Guashco Darwin Joel** | Programador C++ | Porta a C++ los mismos archivos que Chalco: `Coordenada`, `Cozy`, `CatalogoEnemigos`, `Oleada`, `GestorOleadas`, `ColaEnemigos` (`std::queue`) |
| **Silva Camuendo Luis Alexander** | Programador C++ | Porta a C++ los mismos archivos que Tacuri: `Torre`, subtipos, `CatalogoTorres`, `ComandoTorre` (+ subtipos), `HistorialComandos` (`std::stack`), `Mapa` |
| **Camacho Monta Josue Jampier** | Documentación (único responsable) | Informe completo: diagrama de clases UML, especificación formal del TDA, pruebas de escritorio, comparación teórica pilas vs colas |

---

## 📂 Organización de Carpetas

Estructura física del repositorio:

```text
ESTRUCTURA-DE-DATOS---APE-2/
├── Scr_Java/
│   ├── modelo/
│   │   ├── Coordenada.java
│   │   ├── Cozy.java
│   │   ├── CatalogoEnemigos.java
│   │   ├── Oleada.java
│   │   ├── Torre.java
│   │   ├── TorreArquero.java
│   │   ├── TorreCanon.java
│   │   └── CatalogoTorres.java
│   ├── estructuras/
│   │   ├── ColaEnemigos.java
│   │   ├── GestorOleadas.java
│   │   ├── Mapa.java
│   │   ├── ComandoTorre.java
│   │   ├── ComandoColocarTorre.java
│   │   ├── ComandoMejorarTorre.java
│   │   └── HistorialComandos.java
│   ├── gestor/
│   │   └── GestorJuego.java
│   └── Main.java
│
├── cpp/
│   ├── modelo/
│   │   ├── Coordenada.h
│   │   ├── Coordenada.cpp
│   │   ├── Cozy.h
│   │   ├── Cozy.cpp
│   │   ├── CatalogoEnemigos.h
│   │   ├── CatalogoEnemigos.cpp
│   │   ├── Oleada.h
│   │   ├── Oleada.cpp
│   │   ├── Torre.h
│   │   ├── Torre.cpp
│   │   ├── TorreArquero.h
│   │   ├── TorreArquero.cpp
│   │   ├── TorreCanon.h
│   │   ├── TorreCanon.cpp
│   │   ├── CatalogoTorres.h
│   │   └── CatalogoTorres.cpp
│   ├── estructuras/
│   │   ├── ColaEnemigos.h
│   │   ├── ColaEnemigos.cpp
│   │   ├── GestorOleadas.h
│   │   ├── GestorOleadas.cpp
│   │   ├── Mapa.h
│   │   ├── Mapa.cpp
│   │   ├── ComandoTorre.h
│   │   ├── ComandoColocarTorre.h
│   │   ├── ComandoColocarTorre.cpp
│   │   ├── ComandoMejorarTorre.h
│   │   ├── ComandoMejorarTorre.cpp
│   │   ├── HistorialComandos.h
│   │   └── HistorialComandos.cpp
│   ├── gestor/
│   │   ├── GestorJuego.h
│   │   └── GestorJuego.cpp
│   └── main.cpp
│
├── docs/
│   ├── Capturas_Pruebas/
│   ├── Diagramas_UML/
│   └── Informe_APE2_Estructura_de_Datos.pdf
│
├── .gitignore
└── README.md
```
