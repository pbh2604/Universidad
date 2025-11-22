package es.upm.Vista;

import es.upm.App;

public class VSelectores {
    public static final String CYAN = "\u001B[36m";
    public static int recogerOpcion(int numeroParametros) {
        int opcion = -1;
        do {
            while (!App.scanner.hasNextInt()) {
                System.out.println("Por favor, introduce un número entero válido:");
                App.scanner.next();
            }
            opcion = App.scanner.nextInt();
            App.scanner.nextLine();
            if (opcion < 0 || opcion > numeroParametros)
                System.out.println("El número debe estar entre 1 y " + numeroParametros + " :");
        } while (opcion < 0 || opcion > numeroParametros);
        return opcion;
    }
}
