ESINMath es un sistema de computación simbólica desarrollado como parte del curso de Estructures de Sistemes d'Informació (ESIN) en la UPC. Este proyecto simula algunas de las funcionalidades básicas de software matemático avanzado como Mathematica, Maple o MuPAD, permitiendo la evaluación y manipulación de expresiones matemáticas de manera interactiva.

Descripción

Este proyecto tiene como objetivo desarrollar un sistema que permita la manipulación de expresiones simbólicas utilizando el lenguaje de programación C++. El programa acepta entradas interactivas en las que el usuario puede realizar operaciones básicas como asignaciones de variables, simplificaciones algebraicas y evaluaciones numéricas.

El sistema está diseñado para operar principalmente en el entorno Linux del STIC, y se evaluará en dicha plataforma. Asegúrate de que tu código funcione correctamente en este entorno, especialmente en el compilador g++ 9.4.0.
Características

ESINMath permite las siguientes funcionalidades:

    Evaluación de expresiones: Maneja operaciones matemáticas básicas con números enteros, racionales y reales.
    Asignación de variables: Permite asignar expresiones a variables, que pueden ser reutilizadas y modificadas durante la sesión.
    Desasignación de variables: Las variables pueden ser desasignadas en cualquier momento.
    Cálculo numérico: Evaluación de expresiones con resultados en punto flotante mediante la función evalf.
    Funciones algebraicas: Incluye funciones como raíces cuadradas (sqrt), logaritmos (log), y exponenciales (exp).
    Simplificación de expresiones: Simplifica automáticamente expresiones, aplicando reglas algebraicas.
    Interacción por comandos: El sistema espera comandos del usuario para realizar cálculos en tiempo real.

Estructura del Proyecto

El proyecto sigue un diseño modular, con varias clases y módulos dedicados a funciones específicas:

    Token: Representa los elementos básicos de una expresión, como números, operadores, funciones, y variables.
    Rational: Gestiona números racionales simplificados.
    Expression: Se encarga de la creación y manipulación de expresiones algebraicas.
    Variables: Administra las variables y sus asignaciones durante la sesión.
    Math Session: Controla la lógica de cada sesión interactiva.
    Math IO: Responsable de la entrada y salida del sistema.

Cada módulo está implementado en un archivo separado y tiene asignada una tarea específica en la arquitectura del programa.
