using System;
using System.IO;
using System.Diagnostics;

namespace practica1
{
    public struct Animal
    {
        public string Clase;// Obligatorio 
        public string? Orden;// Opcional el ? es para que estas variables puedan ser anuladas 
        public string Genero;// Obligatorio 
        public string? Especie;// Opcional    
        public string? Peso;// Opcional    
        public string? Cerebro;// Opcional  
    }

    class Program
    {
        static string? BuscarArchivo()//funcion para encontrar el path que tiene que seguir el ordenador para encontrar los archivos
        {
            string docs = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            string[] rutasPosibles = {
                "animales.csv",
                "animales.csv.csv",
                "Zooteca.csv",
                @"..\..\..\animales.csv",
                @"..\..\..\Zooteca.csv",
            };

            foreach (string r in rutasPosibles)
            {
                if (File.Exists(r)) return r;//para que devuelva la ruta que sirva en cada caso dependiendo del sistema que lo ejecute
            }

            return null;
        }

        static void Main(string[] args)
        {
            string? rutaFichero = BuscarArchivo();//llamada a la funcion hecha por nuestros problemas para encontrar el camino de los archivos en el ordenador 

            if (rutaFichero == null)
            {
                Console.WriteLine("Error: No se puede abrir el fichero 'animales.csv'.");//para que si no encuentra el archivo en los archivos del ordenador puedas identificarlo con mayor facilidad para ponerle remedio
                return;
            }

            int cargados = 0;//variables que guardan los archivos cargados
            int descartados = 0;//variables que guardan los archivos descartados

            Stopwatch sw = Stopwatch.StartNew();//para medir el tiempo de compilacion desde que se encuentra el archivo en el ordenador

            try
            {
                string[] lineas = File.ReadAllLines(rutaFichero);//para que pueda entrar al archivo a leerlo

                if (lineas.Length <= 1)
                {
                    Console.WriteLine("El fichero no contiene animales.");//por si el fichero estuviese vacio
                    return;
                }

                Animal[] Fichas = new Animal[lineas.Length - 1];//para pedirle la totalidad de las lineas del archivo

                for (int i = 1; i < lineas.Length; i++)
                {
                    string linea = lineas[i];//para que lea todas las lineas del archivo

                    if (string.IsNullOrEmpty(linea)) continue;//para que continue si una linea esta vacia por si acaso aunque segun hemos visto no es necesario

                    string[] datos = linea.Split(';');//separador por ; 

                    string? clase = (datos.Length > 0 && datos[0].Length > 0) ? datos[0] : null;//guardar los datos de la clase 
                    string? genero = (datos.Length > 2 && datos[2].Length > 0) ? datos[2] : null;//guardar los datos del genero

                    if (clase == null || genero == null)
                    {
                        descartados++;
                    }
                    else
                    {
                        Fichas[cargados].Clase = clase;
                        Fichas[cargados].Orden = (datos.Length > 1 && datos[1].Length > 0) ? datos[1] : null;
                        Fichas[cargados].Genero = genero;
                        Fichas[cargados].Especie = (datos.Length > 3 && datos[3].Length > 0) ? datos[3] : null;
                        Fichas[cargados].Peso = (datos.Length > 4 && datos[4].Length > 0) ? datos[4] : null;
                        Fichas[cargados].Cerebro = (datos.Length > 5 && datos[5].Length > 0) ? datos[5] : null;
                        cargados++;
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error durante la lectura del fichero: {ex.Message}");
                return;
            }

            sw.Stop();

            long microsegundos = (sw.ElapsedTicks * 1_000_000L) / Stopwatch.Frequency;

            Console.WriteLine("==========================================");
            Console.WriteLine("   RESULTADOS DE LA CARGA (MÓDULO C#)     ");
            Console.WriteLine("==========================================");
            Console.WriteLine($"Fichero leído                : animales.csv");
            Console.WriteLine($"Microsegundos de ejecución   : {microsegundos} us");
            Console.WriteLine($"Número de animales cargados  : {cargados}");
            Console.WriteLine($"Número de animales descartados: {descartados}");
            Console.WriteLine("==========================================");
        }
    }
}