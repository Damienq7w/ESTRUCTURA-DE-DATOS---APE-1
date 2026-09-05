# 📊 APE 1 — Gestión de colección de datos utilizando vectores.

Bienvenidos al repositorio oficial de la **Actividad Práctica Experimental 1 (APE 1)** para la asignatura de **Estructuras de Datos**

---

## 📌 ¿De qué trata el proyecto?

Este proyecto implementa y evalúa el almacenamiento, manipulación y cálculo estadístico (media/promedio) de valores estructurados en memoria estática contigua, aplicando los principios fundamentales de la **Programación Orientada a Objetos (POO)** y los **Tipos de Datos Abstractos (TDA)** en **Java** y **C++**.

El sistema integra dos módulos principales:

1. **Gestor de Estudiantes:** Realiza la insertación de datos de estudiantes, almacenando calificaciones en vectores y calculando el promedio individual y la media general del curso con algoritmos de desplazamiento mecánico para evitar huecos en memoria.
2. **Gestor de Vehículos:** Modelado de una flota vehicular mediante jerarquía de clases (`Vehiculo`, `Automovil`, `Motocicleta`), clases abstractas, herencia, interfaces (`IVehiculoGestor`) y polimorfismo en tiempo de ejecución.

---

## 🎯 Objetivos

* **General:**
  * Determinar el cálculo de la media de valores estructurados utilizando programación orientada a objetos y vectores.

* **Específicos:**
  * Determinar el cálculo de la media de valores estructurados utilizando programación orientada a objetos y vectores.
  * Crear una aplicación para registrar y gestionar los datos de los estudiantes mediante programación orientada a objetos.
  * Almacenar y gestionar las calificaciones de los estudiantes utilizando vectores.
  * Calcular el promedio de las calificaciones de un estudiante y del curso mediante la aplicación.

---

## 🧠 ¿Cómo diseñamos los TDAs y Estructuras?

Seguimos la metodología formal vista en clase:

### 1. Módulo Gestor de Estudiantes
* **Entidad y Atributos:**
  * `id` (`int`): Identificador único inmutable.
  * `nombre` (`String` / `std::string`): Nombre del estudiante.
  * `edad` (`int`): Edad válida ($edad > 0$).
  * `promedio` (`double`): Calificación estructurada calculada ($0.0 \le promedio \le 10.0$).
* **Estructura Interna:**
  * `arreglo`: Vector estático de tamaño fijo para almacenar registros en memoria contigua.
  * `cantidad` (`int`): Cursor dinámico que delimita el rango útil de datos $[0, cantidad - 1]$.
* **Cálculo de la Media:**
  * Cálculo del promedio individual y promedio global del curso iterando sobre las posiciones activas.

### 2. Módulo Gestor de Vehículos
* **Jerarquía de Clases y Abstracción:**
  * `IVehiculoGestor`: Interfaz pura que define el contrato de operaciones (el "Qué").
  * `Vehiculo`: Clase abstracta que define atributos comunes y métodos virtuales puros (`mostrarInformacion()`).
  * `Automovil` y `Motocicleta`: Clases derivadas que especializan los atributos y comportamientos.
* **Polimorfismo:** Manipulación de objetos mediante punteros/referencias a la clase base sin acoplar la implementación interna.

---

## 👥 Equipo de Trabajo

| Integrante | Rol | ¿Qué hace en el proyecto? |
| :--- | :--- | :--- |
| **Cunalata Mendoza Damian Alexander** | Líder Técnico & Dev Java | Gestión del repositorio en GitHub, control de ramas/PRs, integración global y desarrollo del módulo `Gestor_Vehiculos` en Java. |
| **Chalco Tasna Kenneth Mateo** | Programador Java (Estudiantes) | Desarrollo completo del módulo `Gestor_Estudiantes` en Java (`Estudiante.java`, `GestorEstudiantes.java`, `Main.java`) con validación de entradas y cálculo de promedios. |
| **Tisalema Guashco Darwin Joel** | Programador C++ (Estudiantes) | Desarrollo completo del módulo `Gestor_Estudiantes` en C++ (`Estudiante.cpp`, `GestorEstudiantes.cpp`, `Main.cpp`) con vectores nativos y menús interactivos. |
| **Silva Camuendo Luis Alexander** | Programador C++ (Vehículos) | Portabilidad e implementación del módulo `Gestor_Vehiculos` en C++ (`Vehiculo`, `Automovil`, `Motocicleta`, `GestorVehiculos`, `MainVehiculos.cpp`) con herencia y métodos virtuales. |
| **Tacuri Santillan Mónica Sara** | Documentación Teórica & UML | Redacción del marco metodológico, relación requisitos-código y elaboración de los diagramas de clases UML para ambos módulos. |
| **Camacho Monta Josue Jampier** | Documentación Técnica & QA | Especificación formal del TDA, invariantes matemáticos, pseudocódigo, pruebas de escritorio y capturas de pruebas de estrés. |

---

## 📂 Organización de Carpetas

Estructura física del repositorio:

```text
ESTRUCTURA-DE-DATOS---APE-1/
├── Scr_Java/
│   ├── Gestor_Estudiantes/
│   │   ├── Estudiante.java
│   │   ├── GestorEstudiantes.java
│   │   └── Main.java
│   └── Gestor_Vehiculos/
│       ├── Automovil.java
│       ├── GestorVehiculos.java
│       ├── IVehiculoGestor.java
│       ├── MainVehiculos.java
│       ├── Motocicleta.java
│       └── Vehiculo.java
│
├── cpp/
│   ├── Gestor_Estudiantes/
│   │   ├── Estudiante.cpp
│   │   ├── GestorEstudiantes.cpp
│   │   └── Main.cpp
│   └── Gestor_Vehiculos/
│       ├── Automovil.cpp
│       ├── Automovil.h
│       ├── GestorVehiculos.cpp
│       ├── GestorVehiculos.h
│       ├── IVehiculoGestor.h
│       ├── MainVehiculos.cpp
│       ├── Motocicleta.cpp
│       ├── Motocicleta.h
│       ├── Vehiculo.cpp
│       └── Vehiculo.h
│
├── docs/
│   ├── Capturas_Pruebas/
│   │   ├── Gestor_Estudiantes/
│   │   └── Gestor_Vehiculos/
│   ├── Diagramas_UML/
│   │   ├── Gestor_Estudiantes/
│   │   └── Gestor_Vehiculos/
│   └── Informe_APE1_Estructura_de_Datos.pdf
│
├── .gitignore
└── README.md
