package es.upm;

import es.upm.Controladora.*;
import es.upm.Modelo.Usuario;
import es.upm.Vista.IVistas.IVistaInicio;
import es.upm.Vista.VInicio;
import es.upm.Vista.VSelectores;
import servidor.ExternalRRSS;
import java.util.Scanner;

public class App {

    public static Scanner scanner = new Scanner(System.in);
    IVistaInicio vistaInicio;
    CCuidador cCuidador;
    CResponsable cResponsable;
    CCuidados cCuidados;
    Poblador poblador;

    public App() {
        vistaInicio = new VInicio();
        cCuidador = new CCuidador();
        cResponsable = new CResponsable(cCuidador);
        cCuidados = new CCuidados();
        cCuidador.setcResponsable(cResponsable);
        poblador = new Poblador(cCuidador, cResponsable, cCuidados);
        poblador.poblarDatos();
    }

    public void iniciar() {
        Usuario usuarioLogueado = null;
        while (true) {
            vistaInicio.mostrarInicio();
            int opcion = VSelectores.recogerOpcion(3);
            switch (opcion) {
                case 0:
                    return;
                case 1:
                    String identificador = ExternalRRSS.LoginRRSS();
                    if (cResponsable.login(identificador) != null)
                        usuarioLogueado = cResponsable.login(identificador);

                    else if (cCuidador.login(identificador) != null)
                        usuarioLogueado = cCuidador.login(identificador);
                    else {
                        VInicio.setMessageerror("Usuario no registrado");
                        usuarioLogueado = null;
                    }
                    if (usuarioLogueado != null) {
                        do{
                            vistaInicio.mostrarOpciones();
                            opcion = VSelectores.recogerOpcion(5);
                            ejecutarOpcion(opcion, usuarioLogueado);
                        }while (opcion != 0);
                    }
                    break;
                case 2:
                    cResponsable.crearUsuario();
                    break;
                case 3:
                    cCuidador.crearUsuario();
                    break;
                default:
                    System.out.println("Por favor, introduce un número entre 1 y 3.");
                    break;
            }
        }
    }

    private void ejecutarOpcion(int opcion, Usuario logueado) {
        switch (opcion) {
            case 0:
                break;
            case 1:
                cResponsable.listarMascotas(logueado);
                break;
            case 2:
                cCuidador.listarCuidados(logueado);
                break;
            case 3:
                cCuidados.publicarCuidado(logueado);
                break;
            case 4:
                cResponsable.agregarMascota(logueado);
                break;
            case 5:
                cCuidados.buscarCuidados(logueado);
        }
    }

    public static void main(String[] args) {
        App app = new App();
        app.iniciar();
    }
}
